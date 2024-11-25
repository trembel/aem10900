/**
 * @file aem10900.h
 * @brief AEM10900 Driver
 *
 * Listing file author: Silvano Cortesi
 *
 * Listing file notice:
 *   Licensed under LGPL-3.0
 *   File Version: 0.9.2
 */

#ifndef AEM10900_H
#define AEM10900_H

#include "aem10900_reg.h"
#include <stddef.h>
#include <stdint.h>

/**
 * @brief Driver error codes
 */
typedef enum {
  E_AEM10900_SUCCESS = 0,            //!< Success
  E_AEM10900_NULLPTR_ERR = (1 << 0), //!< Nullpointer error
  E_AEM10900_COM_ERR = (1 << 1),     //!< Communication error
  E_AEM10900_CONFIG_ERR = (1 << 2),  //!< Configuration error
  E_AEM10900_NO_DATA_ERR = (1 << 3), //!< No Data available error
  E_AEM10900_ERR = (1 << 4),         //!< Other error
} aem10900_err_t;

// ======== Configuration =====================================================

/**
 * @brief Register Configuration struct.
 * Represents the registers of a single device. Holds the device configuration.
 */
struct aem10900_reg_config {
  struct aem10900_version version;
  struct aem10900_mpptcfg mpptcfg;
  struct aem10900_vovdis vovdis;
  struct aem10900_vovch vovch;
  struct aem10900_tempcold tempcold;
  struct aem10900_temphot temphot;
  struct aem10900_pwr pwr;
  struct aem10900_sleep sleep;
  struct aem10900_stomon stomon;
  struct aem10900_apm apm;
  struct aem10900_irqen irqen;
  struct aem10900_ctrl ctrl;
  struct aem10900_irqflg irqflg;
  struct aem10900_status status;
  struct aem10900_apm0 apm0;
  struct aem10900_apm1 apm1;
  struct aem10900_apm2 apm2;
  struct aem10900_temp temp;
  struct aem10900_sto sto;
  struct aem10900_src src;
  struct aem10900_pn0 pn0;
  struct aem10900_pn1 pn1;
  struct aem10900_pn2 pn2;
  struct aem10900_pn3 pn3;
  struct aem10900_pn4 pn4;
};

// ======== Handle Definition ==================================================

/**
 * @brief Device Handle struct.
 * Represents a single physical device. Holds the hardware-specific interface
 * functions, and device configuration.
 */
struct aem10900_h {
  // === Interface function pointers. Required. ===
  /**
   * @brief Pointer to the device-specific spi-read function
   * @warning Required!
   *
   * @param dev_adr The devices i2c slave address
   * @param start_reg_adr The register address of the first register to read.
   * @param buf Pointer to a buffer pointer holding the results
   * @param length Length of the buffer
   * @return @ref E_AEM10900_SUCCESS if read was successful, otherwise @ref
   * E_AEM10900_COM_ERR.
   */
  aem10900_err_t (*i2c_read_regs)(uint8_t dev_adr, uint8_t start_reg_adr,
                                  uint8_t *buf, size_t length);

  /**
   * @brief Pointer to the device-specific spi-write function
   * @warning Required!
   *
   * @param dev_adr The devices i2c slave address
   * @param start_reg_adr The register address of the first register to write.
   * @param buf Pointer to a buffer pointer holding the data to write
   * @param length Length of the buffer
   * @return @ref E_AEM10900_SUCCESS if write was successful, otherwise @ref
   * E_AEM10900_COM_ERR.
   */
  aem10900_err_t (*i2c_write_regs)(uint8_t dev_adr, uint8_t start_reg_adr,
                                   uint8_t *buf, size_t length);

  // === Interface function pointers. Optional. ===

  /**
   * @brief Pointer to logging function.
   * Called by the driver to log status and error messages, with an optional
   * integer variable to log. Note that the string does not contain any
   * formatting specifiers, and should be logged as follows (if has_int_arg is
   * true):
   *
   * printf("%s: %s %i", is_err ? "ERR" : "LOG", msg, arg);
   *
   * @param msg the log message
   * @param is_err indicates if this is an error message
   * @param has_int_arg indicates if this message is accompanied by an integer
   * variable to log.
   * @param arg the integer variable to log if has_int_arg is true.
   */
  void (*log)(char *msg, bool is_err, bool has_int_arg, uint32_t arg);

  // === Device Configuration. Required. ===
  struct aem10900_reg_config conf; //!< Configuration. Required.
  uint8_t dev_adr;                 //!< Device I2C Slave Address. Required.
};

// ======== Function Prototypes ================================================
/**
 * @brief Initialize the device configuration with all reset values.
 *
 * @note This function should be called before any other driver functions are
 * called.
 *
 * @param conf Pointer to the device-register config struct.
 * @return @ref E_AEM10900_SUCCESS if successful, otherwise an error code from
 * @ref aem10900_err_t.
 */
aem10900_err_t
aem10900_init_struct_with_reset_val(struct aem10900_reg_config *conf);

/**
 * @brief Initialize the device.
 * Validates the driver handle, Tests the connection to the device,
 * and applies the complete device configuration within the handle to the
 * device.
 *
 * @note This function should be called after the struct is initialize but
 * before any other driver functions are called.
 *
 * @param h Pointer to the device-specific handle struct.
 * @return @ref E_AEM10900_SUCCESS if successful, otherwise an error code
 * from
 * @ref aem10900_err_t.
 */
aem10900_err_t aem10900_init(struct aem10900_h *h);

/**
 * @brief Get and Clear IRQ Status.
 * This function gets the IRQ flag and clears the interrupt status.
 * Function replaces content of conf.irqflag with result
 *
 * @param h Pointer to the device-specific handle struct.
 * @return @ref E_AEM10900_SUCCESS if successful, otherwise an error code
 * from
 * @ref aem10900_err_t.
 */
aem10900_err_t aem10900_read_irqflag(struct aem10900_h *h);

/**
 * @brief Get the battery voltage.
 * This function gets the battery voltage.
 * Function replaces content of conf.sto with result
 *
 * @param h Pointer to the device-specific handle struct.
 * @param result Pointer to a result float, containing the battery voltage
 * @return @ref E_AEM10900_SUCCESS if successful, otherwise an error code
 * from
 * @ref aem10900_err_t.
 */
aem10900_err_t aem10900_read_battery_voltage(struct aem10900_h *h,
                                             float *result);

/**
 * @brief Get apm data.
 * This function gets the apm data, depending on the mode, result will either
 * be the integrated power or pulse cound
 * Function replaces content of conf.apmX with result
 *
 * @param h Pointer to the device-specific handle struct.
 * @param mode Conversion mode for the data registers
 * @param result Pointer to a result float, containing the result
 * @return @ref E_AEM10900_SUCCESS if successful, otherwise an error code
 * from
 * @ref aem10900_err_t.
 */
aem10900_err_t aem10900_read_apm_data(struct aem10900_h *h,
                                      enum aem10900_mode mode, float *result);

/**
 * @brief Get the source voltage.
 * This function gets the source voltage.
 * Function replaces content of conf.src with result
 *
 * @param h Pointer to the device-specific handle struct.
 * @param result Pointer to a result float, containing the source voltage
 * @return @ref E_AEM10900_SUCCESS if successful, otherwise an error code
 * from
 * @ref aem10900_err_t.
 */
aem10900_err_t aem10900_read_source_voltage(struct aem10900_h *h,
                                            float *result);

/**
 * @brief Function to write to a specific register of a device
 *
 * @note Calls internally the i2c_write functions
 *
 * @param reg_adr Register address to write to.
 * @param val 8-bit number holding value.
 * @return @ref E_AEM10900_SUCCESS if write was successful, otherwise @ref
 * E_AEM10900_COM_ERR.
 */
aem10900_err_t aem10900_write_reg(const struct aem10900_h *h, uint8_t reg_adr,
                                  uint8_t val);

/**
 * @brief Function to write to multiple registers of a device
 *
 * @note Calls internally the i2c_write functions
 *
 * @param start_reg_adr Start register address to write to.
 * @param buf Pointer to a buffer pointer holding the data to write
 * @param length Length of the buffer
 * @return @ref E_AEM10900_SUCCESS if write was successful, otherwise @ref
 * E_AEM10900_COM_ERR.
 */
aem10900_err_t aem10900_write_regs(const struct aem10900_h *h,
                                   uint8_t start_reg_adr, uint8_t *buf,
                                   size_t length);

/**
 * @brief Function to read from a specific register of a device
 *
 * @note Calls internally the i2c_read functions
 *
 * @param reg_adr Register address to read to.
 * @param res Pointer to an 8-bit number holding result.
 * @return @ref E_AEM10900_SUCCESS if read was successful, otherwise @ref
 * E_AEM10900_COM_ERR.
 */
aem10900_err_t aem10900_read_reg(const struct aem10900_h *h, uint8_t reg_adr,
                                 uint8_t *res);

/**
 * @brief Function to read to from multiple registers of a device
 *
 * @note Calls internally the i2c_read functions
 *
 * @param start_reg_adr Start register address to read to.
 * @param buf Pointer to a buffer pointer holding the data to read
 * @param length Length of the buffer
 * @return @ref E_AEM10900_SUCCESS if read was successful, otherwise @ref
 * E_AEM10900_COM_ERR.
 */
aem10900_err_t aem10900_read_regs(const struct aem10900_h *h,
                                  uint8_t start_reg_adr, uint8_t *buf,
                                  size_t length);

/**
 * @brief Initialize the given register configuration with the reset values
 * (from little endian).
 *
 * @param conf pointer to a register configuration
 * @return @ref E_AEM10900_SUCCESS if successful, otherwise an error code from
 * @ref aem10900_err_t.
 */
static inline void aem10900_reset_val_le(struct aem10900_reg_config *conf) {
  conf->version =
      aem10900_version_unpack_le((uint8_t[1])AEM10900_VERSION_RESET_LE);
  conf->mpptcfg =
      aem10900_mpptcfg_unpack_le((uint8_t[1])AEM10900_MPPTCFG_RESET_LE);
  conf->vovdis =
      aem10900_vovdis_unpack_le((uint8_t[1])AEM10900_VOVDIS_RESET_LE);
  conf->vovch = aem10900_vovch_unpack_le((uint8_t[1])AEM10900_VOVCH_RESET_LE);
  conf->tempcold =
      aem10900_tempcold_unpack_le((uint8_t[1])AEM10900_TEMPCOLD_RESET_LE);
  conf->temphot =
      aem10900_temphot_unpack_le((uint8_t[1])AEM10900_TEMPHOT_RESET_LE);
  conf->pwr = aem10900_pwr_unpack_le((uint8_t[1])AEM10900_PWR_RESET_LE);
  conf->sleep = aem10900_sleep_unpack_le((uint8_t[1])AEM10900_SLEEP_RESET_LE);
  conf->stomon =
      aem10900_stomon_unpack_le((uint8_t[1])AEM10900_STOMON_RESET_LE);
  conf->apm = aem10900_apm_unpack_le((uint8_t[1])AEM10900_APM_RESET_LE);
  conf->irqen = aem10900_irqen_unpack_le((uint8_t[1])AEM10900_IRQEN_RESET_LE);
  conf->ctrl = aem10900_ctrl_unpack_le((uint8_t[1])AEM10900_CTRL_RESET_LE);
  conf->irqflg =
      aem10900_irqflg_unpack_le((uint8_t[1])AEM10900_IRQFLG_RESET_LE);
  conf->status =
      aem10900_status_unpack_le((uint8_t[1])AEM10900_STATUS_RESET_LE);
  conf->apm0 = aem10900_apm0_unpack_le((uint8_t[1])AEM10900_APM0_RESET_LE);
  conf->apm1 = aem10900_apm1_unpack_le((uint8_t[1])AEM10900_APM1_RESET_LE);
  conf->apm2 = aem10900_apm2_unpack_le((uint8_t[1])AEM10900_APM2_RESET_LE);
  conf->temp = aem10900_temp_unpack_le((uint8_t[1])AEM10900_TEMP_RESET_LE);
  conf->sto = aem10900_sto_unpack_le((uint8_t[1])AEM10900_STO_RESET_LE);
  conf->src = aem10900_src_unpack_le((uint8_t[1])AEM10900_SRC_RESET_LE);
  conf->pn0 = aem10900_pn0_unpack_le((uint8_t[1])AEM10900_PN0_RESET_LE);
  conf->pn1 = aem10900_pn1_unpack_le((uint8_t[1])AEM10900_PN1_RESET_LE);
  conf->pn2 = aem10900_pn2_unpack_le((uint8_t[1])AEM10900_PN2_RESET_LE);
  conf->pn3 = aem10900_pn3_unpack_le((uint8_t[1])AEM10900_PN3_RESET_LE);
  conf->pn4 = aem10900_pn4_unpack_le((uint8_t[1])AEM10900_PN4_RESET_LE);
}

/**
 * @brief Function to pack a given register configuration into a byte array as
 * little endian.
 *
 * @param conf pointer to a register configuration
 * @param byte_arr pointer to a array, which will be filled with the register
 * values (to be transmitted to the device)
 */
static inline void aem10900_pack_le(const struct aem10900_reg_config *conf,
                                    uint8_t byte_arr[25]) {
  aem10900_version_pack_le(&conf->version, &byte_arr[0]);
  aem10900_mpptcfg_pack_le(&conf->mpptcfg, &byte_arr[1]);
  aem10900_vovdis_pack_le(&conf->vovdis, &byte_arr[2]);
  aem10900_vovch_pack_le(&conf->vovch, &byte_arr[3]);
  aem10900_tempcold_pack_le(&conf->tempcold, &byte_arr[4]);
  aem10900_temphot_pack_le(&conf->temphot, &byte_arr[5]);
  aem10900_pwr_pack_le(&conf->pwr, &byte_arr[6]);
  aem10900_sleep_pack_le(&conf->sleep, &byte_arr[7]);
  aem10900_stomon_pack_le(&conf->stomon, &byte_arr[8]);
  aem10900_apm_pack_le(&conf->apm, &byte_arr[9]);
  aem10900_irqen_pack_le(&conf->irqen, &byte_arr[10]);
  aem10900_ctrl_pack_le(&conf->ctrl, &byte_arr[11]);
  aem10900_irqflg_pack_le(&conf->irqflg, &byte_arr[12]);
  aem10900_status_pack_le(&conf->status, &byte_arr[13]);
  aem10900_apm0_pack_le(&conf->apm0, &byte_arr[14]);
  aem10900_apm1_pack_le(&conf->apm1, &byte_arr[15]);
  aem10900_apm2_pack_le(&conf->apm2, &byte_arr[16]);
  aem10900_temp_pack_le(&conf->temp, &byte_arr[17]);
  aem10900_sto_pack_le(&conf->sto, &byte_arr[18]);
  aem10900_src_pack_le(&conf->src, &byte_arr[19]);
  aem10900_pn0_pack_le(&conf->pn0, &byte_arr[20]);
  aem10900_pn1_pack_le(&conf->pn1, &byte_arr[21]);
  aem10900_pn2_pack_le(&conf->pn2, &byte_arr[22]);
  aem10900_pn3_pack_le(&conf->pn3, &byte_arr[23]);
  aem10900_pn4_pack_le(&conf->pn4, &byte_arr[24]);
}

/**
 * @brief Function to pack a given register configuration into a byte array as
 * big endian.
 *
 * @param conf pointer to a register configuration
 * @param byte_arr pointer to a array, which will be filled with the register
 * values (to be transmitted to the device)
 */
static inline void aem10900_pack_be(const struct aem10900_reg_config *conf,
                                    uint8_t byte_arr[25]) {
  aem10900_version_pack_be(&conf->version, &byte_arr[24]);
  aem10900_mpptcfg_pack_be(&conf->mpptcfg, &byte_arr[23]);
  aem10900_vovdis_pack_be(&conf->vovdis, &byte_arr[22]);
  aem10900_vovch_pack_be(&conf->vovch, &byte_arr[21]);
  aem10900_tempcold_pack_be(&conf->tempcold, &byte_arr[20]);
  aem10900_temphot_pack_be(&conf->temphot, &byte_arr[19]);
  aem10900_pwr_pack_be(&conf->pwr, &byte_arr[18]);
  aem10900_sleep_pack_be(&conf->sleep, &byte_arr[17]);
  aem10900_stomon_pack_be(&conf->stomon, &byte_arr[16]);
  aem10900_apm_pack_be(&conf->apm, &byte_arr[15]);
  aem10900_irqen_pack_be(&conf->irqen, &byte_arr[14]);
  aem10900_ctrl_pack_be(&conf->ctrl, &byte_arr[13]);
  aem10900_irqflg_pack_be(&conf->irqflg, &byte_arr[12]);
  aem10900_status_pack_be(&conf->status, &byte_arr[11]);
  aem10900_apm0_pack_be(&conf->apm0, &byte_arr[10]);
  aem10900_apm1_pack_be(&conf->apm1, &byte_arr[9]);
  aem10900_apm2_pack_be(&conf->apm2, &byte_arr[8]);
  aem10900_temp_pack_be(&conf->temp, &byte_arr[7]);
  aem10900_sto_pack_be(&conf->sto, &byte_arr[6]);
  aem10900_src_pack_be(&conf->src, &byte_arr[5]);
  aem10900_pn0_pack_be(&conf->pn0, &byte_arr[4]);
  aem10900_pn1_pack_be(&conf->pn1, &byte_arr[3]);
  aem10900_pn2_pack_be(&conf->pn2, &byte_arr[2]);
  aem10900_pn3_pack_be(&conf->pn3, &byte_arr[1]);
  aem10900_pn4_pack_be(&conf->pn4, &byte_arr[0]);
}

#endif // AEM10900_H
