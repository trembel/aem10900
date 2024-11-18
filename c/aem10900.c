/**
 * @file aem10900.c
 * @brief AEM10900 Driver
 *
 * Listing file author: Silvano Cortesi
 *
 * Listing file notice:
 *   Licensed under TBD
 */

#include "aem10900.h"
#include "aem10900_reg.h"
#include <stdint.h>
#include <string.h>

// ======== Macro Quick Access
// =================================================================

#define DRVR_LOG(msg)                                                          \
  if (h != 0 && h->log != 0) {                                                 \
    h->log(msg, false, false, 0);                                              \
  }

#define DRVR_LOG_VAR(msg, val)                                                 \
  if (h != 0 && h->log != 0) {                                                 \
    h->log(msg, false, true, val);                                             \
  }

#define DRVR_ERR(msg)                                                          \
  if (h != 0 && h->log != 0) {                                                 \
    h->log(msg, true, false, 0);                                               \
  }

#define DRVR_ERR_VAR(msg, val)                                                 \
  if (h != 0 && h->log != 0) {                                                 \
    h->log(msg, true, true, val);                                              \
  }

// ======== Private Prototypes (not shared)
// =================================================================
static aem10900_err_t validate_handle(const struct aem10900_h *h);
static aem10900_err_t check_connection(const struct aem10900_h *h);

aem10900_err_t write_cfg_regs(const struct aem10900_h *h);
aem10900_err_t verify_cfg_regs(const struct aem10900_h *h);

float source_voltage_lookup(uint8_t input);

// ======== Public Functions
// =================================================================
aem10900_err_t
aem10900_init_struct_with_reset_val(struct aem10900_reg_config *conf) {
  // Check that pointer is none zero
  aem10900_err_t err = E_AEM10900_SUCCESS;
  if (conf == 0) {
    return E_AEM10900_NULLPTR_ERR;
  }
  // Fill default configuration into struct
  aem10900_reset_val_le(conf);

  return err;
}

aem10900_err_t aem10900_init(struct aem10900_h *h) {
  aem10900_err_t err = E_AEM10900_SUCCESS;

  // Check if handles are valid
  err |= validate_handle(h);
  if (err)
    return err;

  // Check if connection is valid by reading out VERSION
  err |= check_connection(h);
  if (err)
    return err;

  // Set configuration to device
  err |= write_cfg_regs(h);
  if (err) {
    DRVR_ERR("Failed to write all config registers");
  }

  // Wait until syncbusy is low
  {
    uint8_t ctrl_data = 0;
    struct aem10900_ctrl ctrl = {.syncbusy = true};

    while (ctrl.syncbusy == true) {
      err |= aem10900_read_reg(h, AEM10900_CTRL_ADDRESS, &ctrl_data);
      if (err) {
        DRVR_ERR("Failed to read ctrl register, while waiting for syncbusy");
      }
      struct aem10900_ctrl ctrl_temp = aem10900_ctrl_unpack_le(&ctrl_data);
      memcpy(&ctrl, &ctrl_temp, sizeof(struct aem10900_ctrl));
    }
  }

  // Verify configuration of device
  err |= verify_cfg_regs(h);
  if (err) {
    DRVR_ERR("Failed to verify all config registers");
  }

  return err;
}

aem10900_err_t aem10900_get_irqflag(struct aem10900_h *h) {
  aem10900_err_t err = E_AEM10900_SUCCESS;
  uint8_t data = 0;

  err = aem10900_read_reg(h, AEM10900_IRQFLG_ADDRESS, &data);

  struct aem10900_irqflg flag = aem10900_irqflg_unpack_le(&data);
  memcpy(&h->conf.irqflg, &flag, sizeof(struct aem10900_irqflg));

  return err;
}

aem10900_err_t aem10900_get_apm_data(struct aem10900_h *h,
                                     enum aem10900_mode mode, float *result) {
  aem10900_err_t err = E_AEM10900_SUCCESS;
  uint8_t data[3] = {0};

  // Read data
  err = aem10900_read_regs(h, AEM10900_APM0_ADDRESS, data, sizeof(data));

  // Copy data to struct
  struct aem10900_apm0 apm0 = aem10900_apm0_unpack_le(&data[0]);
  struct aem10900_apm1 apm1 = aem10900_apm1_unpack_le(&data[1]);
  struct aem10900_apm2 apm2 = aem10900_apm2_unpack_le(&data[2]);

  // Move into h
  h->conf.apm0.data = apm0.data;
  h->conf.apm1.data = apm1.data;
  h->conf.apm2.data = apm2.data;

  // Get result depending on mode
  if (mode == AEM10900_MODE_POWER_METER) {
    uint8_t shift = (apm2.data >> 4) & 0x0F;
    uint32_t data = ((apm2.data & 0x0F) << 16) | (apm1.data << 8) | apm0.data;
    // TODO: How to handle different V_SRC...
    // Assume for now V_SRC > 0.7V
    *result = (float)(data << shift) * 0.10166;
  } else if (mode == AEM10900_MODE_PULSE_COUNTER) {
    uint32_t data = ((apm2.data & 0x0F) << 16) | (apm1.data << 8) | apm0.data;
    *result = (float)data;
  }

  return err;
}

aem10900_err_t aem10900_get_battery_voltage(struct aem10900_h *h,
                                            float *result) {
  aem10900_err_t err = E_AEM10900_SUCCESS;
  uint8_t data = 0;

  // Read data
  err = aem10900_read_reg(h, AEM10900_STO_ADDRESS, &data);

  // Copy data to struct
  struct aem10900_sto sto = aem10900_sto_unpack_le(&data);

  // Move into h
  h->conf.sto.data = sto.data;

  // Convert result to voltage
  *result = 4.8 * (float)sto.data / 256.0;

  return err;
}

aem10900_err_t aem10900_get_source_voltage(struct aem10900_h *h,
                                           float *result) {
  aem10900_err_t err = E_AEM10900_SUCCESS;
  uint8_t data = 0;

  // Read data
  err = aem10900_read_reg(h, AEM10900_SRC_ADDRESS, &data);

  // Copy data to struct
  struct aem10900_src src = aem10900_src_unpack_le(&data);

  // Move into h
  h->conf.src.data = src.data;

  // Lookup value
  *result = source_voltage_lookup(src.data);
  if (*result == -1.0f) {
    DRVR_ERR_VAR("source voltage is invalid", src.data);
    err |= E_AEM10900_NO_DATA_ERR;
  }

  return err;
}

aem10900_err_t aem10900_write_reg(const struct aem10900_h *h, uint8_t reg_adr,
                                  uint8_t val) {
  return aem10900_write_regs(h, reg_adr, &val, 1);
}

aem10900_err_t aem10900_write_regs(const struct aem10900_h *h,
                                   uint8_t start_reg_adr, uint8_t *buf,
                                   size_t length) {
  return h->i2c_write_regs(h->dev_adr, start_reg_adr, buf, length);
}

aem10900_err_t aem10900_read_reg(const struct aem10900_h *h, uint8_t reg_adr,
                                 uint8_t *res) {
  return aem10900_read_regs(h, reg_adr, res, 1);
}

aem10900_err_t aem10900_read_regs(const struct aem10900_h *h,
                                  uint8_t start_reg_adr, uint8_t *buf,
                                  size_t length) {
  return h->i2c_read_regs(h->dev_adr, start_reg_adr, buf, length);
}

// ======== Private Functions
// =================================================================

// Check that the handles are not null pointers
aem10900_err_t validate_handle(const struct aem10900_h *h) {
  aem10900_err_t err = E_AEM10900_SUCCESS;

  if (h == 0) {
    return E_AEM10900_NULLPTR_ERR;
  }

  if (h->i2c_read_regs == 0) {
    DRVR_ERR("i2c_read_regs is nullptr!");
    err |= E_AEM10900_NULLPTR_ERR;
  }

  if (h->i2c_write_regs == 0) {
    DRVR_ERR("i2c_write_regs is nullptr!");
    err |= E_AEM10900_NULLPTR_ERR;
  }

  return err;
}

// Readout VERSION to check connection is good
aem10900_err_t check_connection(const struct aem10900_h *h) {

  aem10900_err_t err = E_AEM10900_SUCCESS;

  // Part number value:
  uint8_t part_number[5] = {0};
  aem10900_pn0_pack_le(&h->conf.pn0, &part_number[0]);
  aem10900_pn1_pack_le(&h->conf.pn1, &part_number[1]);
  aem10900_pn2_pack_le(&h->conf.pn2, &part_number[2]);
  aem10900_pn3_pack_le(&h->conf.pn3, &part_number[3]);
  aem10900_pn4_pack_le(&h->conf.pn4, &part_number[4]);

  // Check part number value:
  uint8_t result[sizeof(part_number)] = {0};
  aem10900_read_regs(h, AEM10900_PN0_ADDRESS, result, sizeof(result));

  for (size_t i = 0; i < sizeof(part_number); i++) {
    if (part_number[i] != result[i]) {
      DRVR_ERR("Got wrong part number(s)!");
      return err;
      // return E_AEM10900_COM_ERR;
    }
  }

  return err;
}

// Write all cfg registers to the device
aem10900_err_t write_cfg_regs(const struct aem10900_h *h) {
  aem10900_err_t err = E_AEM10900_SUCCESS;

  uint8_t byte_arr[11] = {0};

  // From MPPTCFG (0x01) to CTRL (0x0B), all others are RO
  aem10900_mpptcfg_pack_le(&h->conf.mpptcfg, &byte_arr[0]);
  aem10900_vovdis_pack_le(&h->conf.vovdis, &byte_arr[1]);
  aem10900_vovch_pack_le(&h->conf.vovch, &byte_arr[2]);
  aem10900_tempcold_pack_le(&h->conf.tempcold, &byte_arr[3]);
  aem10900_temphot_pack_le(&h->conf.temphot, &byte_arr[4]);
  aem10900_pwr_pack_le(&h->conf.pwr, &byte_arr[5]);
  aem10900_sleep_pack_le(&h->conf.sleep, &byte_arr[6]);
  aem10900_stomon_pack_le(&h->conf.stomon, &byte_arr[7]);
  aem10900_apm_pack_le(&h->conf.apm, &byte_arr[8]);
  aem10900_irqen_pack_le(&h->conf.irqen, &byte_arr[9]);
  aem10900_ctrl_pack_le(&h->conf.ctrl, &byte_arr[10]);

  err = aem10900_write_regs(h, AEM10900_MPPTCFG_ADDRESS, byte_arr,
                            sizeof(byte_arr));

  return err;
}

// Read all cfg registers and verify them
aem10900_err_t verify_cfg_regs(const struct aem10900_h *h) {
  aem10900_err_t err = E_AEM10900_SUCCESS;

  uint8_t byte_arr[11] = {0};

  // From MPPTCFG (0x01) to CTRL (0x0B), check whether values are correct
  err = aem10900_read_regs(h, AEM10900_MPPTCFG_ADDRESS, byte_arr,
                           sizeof(byte_arr));

  struct aem10900_mpptcfg mpptcfg = aem10900_mpptcfg_unpack_le(&byte_arr[0]);
  if (memcmp(&mpptcfg, &h->conf.mpptcfg, sizeof(struct aem10900_mpptcfg)) !=
      0) {
    DRVR_ERR("Register MPPTCFG is not as desired!");
    return err | E_AEM10900_CONFIG_ERR;
  }
  struct aem10900_vovdis vovdis = aem10900_vovdis_unpack_le(&byte_arr[1]);
  if (memcmp(&vovdis, &h->conf.vovdis, sizeof(struct aem10900_vovdis)) != 0) {
    DRVR_ERR("Register VOVDIS is not as desired!");
    return err | E_AEM10900_CONFIG_ERR;
  }
  struct aem10900_vovch vovch = aem10900_vovch_unpack_le(&byte_arr[2]);
  if (memcmp(&vovch, &h->conf.vovch, sizeof(struct aem10900_vovch)) != 0) {
    DRVR_ERR("Register VOVCH is not as desired!");
    return err | E_AEM10900_CONFIG_ERR;
  }
  struct aem10900_tempcold tempcold = aem10900_tempcold_unpack_le(&byte_arr[3]);
  if (memcmp(&tempcold, &h->conf.tempcold, sizeof(struct aem10900_tempcold)) !=
      0) {
    DRVR_ERR("Register TEMPCOLD is not as desired!");
    return err | E_AEM10900_CONFIG_ERR;
  }
  struct aem10900_temphot temphot = aem10900_temphot_unpack_le(&byte_arr[4]);
  if (memcmp(&temphot, &h->conf.temphot, sizeof(struct aem10900_temphot)) !=
      0) {
    DRVR_ERR("Register TEMPHOT is not as desired!");
    return err | E_AEM10900_CONFIG_ERR;
  }
  struct aem10900_pwr pwr = aem10900_pwr_unpack_le(&byte_arr[5]);
  if (memcmp(&pwr, &h->conf.pwr, sizeof(struct aem10900_pwr)) != 0) {
    DRVR_ERR("Register PWR is not as desired!");
    return err | E_AEM10900_CONFIG_ERR;
  }
  struct aem10900_sleep sleep = aem10900_sleep_unpack_le(&byte_arr[6]);
  if (memcmp(&sleep, &h->conf.sleep, sizeof(struct aem10900_sleep)) != 0) {
    DRVR_ERR("Register SLEEP is not as desired!");
    return err | E_AEM10900_CONFIG_ERR;
  }
  struct aem10900_stomon stomon = aem10900_stomon_unpack_le(&byte_arr[7]);
  if (memcmp(&stomon, &h->conf.stomon, sizeof(struct aem10900_stomon)) != 0) {
    DRVR_ERR("Register STOMON is not as desired!");
    return err | E_AEM10900_CONFIG_ERR;
  }
  struct aem10900_apm apm = aem10900_apm_unpack_le(&byte_arr[8]);
  if (memcmp(&apm, &h->conf.apm, sizeof(struct aem10900_apm)) != 0) {
    DRVR_ERR("Register APM is not as desired!");
    return err | E_AEM10900_CONFIG_ERR;
  }
  struct aem10900_irqen irqen = aem10900_irqen_unpack_le(&byte_arr[9]);
  if (memcmp(&irqen, &h->conf.irqen, sizeof(struct aem10900_irqen)) != 0) {
    DRVR_ERR("Register IRQEN is not as desired!");
    return err | E_AEM10900_CONFIG_ERR;
  }
  struct aem10900_ctrl ctrl = aem10900_ctrl_unpack_le(&byte_arr[10]);
  if (memcmp(&ctrl, &h->conf.ctrl, sizeof(struct aem10900_ctrl)) != 0) {
    DRVR_ERR("Register CTRL is not as desired!");
    return err | E_AEM10900_CONFIG_ERR;
  }

  return err;
}

// Define the offset for the first key
#define SRC_VOLTAGE_MIN_KEY 0x06
#define SRC_VOLTAGE_MAX_KEY 0x3A

// Create the lookup table with an offset, in millivolts
const uint16_t source_voltage_lookup_table[SRC_VOLTAGE_MAX_KEY -
                                           SRC_VOLTAGE_MIN_KEY + 1] = {
    [0x06 - SRC_VOLTAGE_MIN_KEY] = 113,  [0x07 - SRC_VOLTAGE_MIN_KEY] = 128,
    [0x08 - SRC_VOLTAGE_MIN_KEY] = 142,  [0x09 - SRC_VOLTAGE_MIN_KEY] = 158,
    [0x0A - SRC_VOLTAGE_MIN_KEY] = 172,  [0x0B - SRC_VOLTAGE_MIN_KEY] = 188,
    [0x0C - SRC_VOLTAGE_MIN_KEY] = 203,  [0x0D - SRC_VOLTAGE_MIN_KEY] = 217,
    [0x0E - SRC_VOLTAGE_MIN_KEY] = 233,  [0x0F - SRC_VOLTAGE_MIN_KEY] = 247,
    [0x10 - SRC_VOLTAGE_MIN_KEY] = 263,  [0x11 - SRC_VOLTAGE_MIN_KEY] = 278,
    [0x12 - SRC_VOLTAGE_MIN_KEY] = 292,  [0x13 - SRC_VOLTAGE_MIN_KEY] = 315,
    [0x14 - SRC_VOLTAGE_MIN_KEY] = 345,  [0x15 - SRC_VOLTAGE_MIN_KEY] = 375,
    [0x16 - SRC_VOLTAGE_MIN_KEY] = 405,  [0x17 - SRC_VOLTAGE_MIN_KEY] = 435,
    [0x18 - SRC_VOLTAGE_MIN_KEY] = 465,  [0x19 - SRC_VOLTAGE_MIN_KEY] = 495,
    [0x1A - SRC_VOLTAGE_MIN_KEY] = 525,  [0x1B - SRC_VOLTAGE_MIN_KEY] = 555,
    [0x1C - SRC_VOLTAGE_MIN_KEY] = 585,  [0x1D - SRC_VOLTAGE_MIN_KEY] = 615,
    [0x1E - SRC_VOLTAGE_MIN_KEY] = 645,  [0x1F - SRC_VOLTAGE_MIN_KEY] = 675,
    [0x20 - SRC_VOLTAGE_MIN_KEY] = 705,  [0x21 - SRC_VOLTAGE_MIN_KEY] = 735,
    [0x22 - SRC_VOLTAGE_MIN_KEY] = 765,  [0x23 - SRC_VOLTAGE_MIN_KEY] = 795,
    [0x24 - SRC_VOLTAGE_MIN_KEY] = 825,  [0x25 - SRC_VOLTAGE_MIN_KEY] = 855,
    [0x26 - SRC_VOLTAGE_MIN_KEY] = 885,  [0x27 - SRC_VOLTAGE_MIN_KEY] = 915,
    [0x28 - SRC_VOLTAGE_MIN_KEY] = 945,  [0x29 - SRC_VOLTAGE_MIN_KEY] = 975,
    [0x2A - SRC_VOLTAGE_MIN_KEY] = 1005, [0x2B - SRC_VOLTAGE_MIN_KEY] = 1035,
    [0x2C - SRC_VOLTAGE_MIN_KEY] = 1065, [0x2D - SRC_VOLTAGE_MIN_KEY] = 1095,
    [0x2E - SRC_VOLTAGE_MIN_KEY] = 1125, [0x2F - SRC_VOLTAGE_MIN_KEY] = 1155,
    [0x30 - SRC_VOLTAGE_MIN_KEY] = 1185, [0x31 - SRC_VOLTAGE_MIN_KEY] = 1215,
    [0x32 - SRC_VOLTAGE_MIN_KEY] = 1245, [0x33 - SRC_VOLTAGE_MIN_KEY] = 1275,
    [0x34 - SRC_VOLTAGE_MIN_KEY] = 1305, [0x35 - SRC_VOLTAGE_MIN_KEY] = 1335,
    [0x36 - SRC_VOLTAGE_MIN_KEY] = 1365, [0x37 - SRC_VOLTAGE_MIN_KEY] = 1395,
    [0x38 - SRC_VOLTAGE_MIN_KEY] = 1425, [0x39 - SRC_VOLTAGE_MIN_KEY] = 1455,
    [0x3A - SRC_VOLTAGE_MIN_KEY] = 1485,
};

// Function to look up a source voltage value
float source_voltage_lookup(uint8_t input) {
  if (input >= SRC_VOLTAGE_MIN_KEY && input <= SRC_VOLTAGE_MAX_KEY) {
    return (float)source_voltage_lookup_table[input - SRC_VOLTAGE_MIN_KEY] /
           1000;
  }
  // Return a special value to indicate that the key was not found
  return -1.0f;
}
