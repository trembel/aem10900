// clang-format off
/**
 * @file aem10900_reg.h
 * @brief AEM10900
 * @note do not edit directly: generated using reginald from ../aem10900.yaml.
 *
 * Generator: c.funcpack
 *
 * Listing file author: Silvano Cortesi
 *
 * Listing file notice:
 *   Licensed under LGPL-3.0
 *   File Version: 0.9.2
 */
#ifndef REGINALD_AEM10900_REG_H
#define REGINALD_AEM10900_REG_H

#include <stdint.h>
#include <stdbool.h>

// =============================================================================
// ==== APM Register ===========================================================
// =============================================================================
// Average Power Monitoring Control Register.
// Fields:
//  - [0] EN (bool): Enable APM. When set to True, APM is enabled.
//  - [1] MODE (enum MODE): APM operating mode. Pulse Counter Mode or Power Meter Mode.
//  - [3:2] WINDOW (enum WINDOW): Select the APM computation window (noted TA in Section 9.4). The energy transferred is integrated over this configurable time window. (W_xx_yy) with xx being computation window and yy being refresh rate.

#define AEM10900_APM_ADDRESS  (0x9U) //!< APM register address
#define AEM10900_APM_RESET_LE {0x0U} //!< APM register reset value
#define AEM10900_APM_RESET_BE {0x0U} //!< APM register reset value

// Register-specific enums and sub-layouts:

/** @brief APM operating mode. Pulse Counter Mode or Power Meter Mode. */
enum aem10900_mode {
  /** @brief Power meter mode - the number of pulses during a period is multiplied by a value to obtain the energy that has been transferred taking into account the efficiency of the AEM10900. */
  AEM10900_MODE_POWER_METER = 0x1U,
  /** @brief Pulse counter mode - the AEM10900 counts the number of current pulses drawn by the boost converter. */
  AEM10900_MODE_PULSE_COUNTER = 0x0U,
};

/** @brief Select the APM computation window (noted TA in Section 9.4). The energy transferred is integrated over this configurable time window. (W_xx_yy) with xx being computation window and yy being refresh rate. */
enum aem10900_window {
  AEM10900_WINDOW_W_128MS_256MS = 0x0U,
  AEM10900_WINDOW_W_32MS_64MS = 0x2U,
  AEM10900_WINDOW_W_64MS_128MS = 0x1U,
};

// Register Layout Struct:

/**
 * @brief Average Power Monitoring Control Register.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_apm {
  /** @brief Enable APM. When set to True, APM is enabled. */
  bool en;
  /** @brief APM operating mode. Pulse Counter Mode or Power Meter Mode. */
  enum aem10900_mode mode;
  /** @brief Select the APM computation window (noted TA in Section 9.4). The energy transferred is integrated over this configurable time window. (W_xx_yy) with xx being computation window and yy being refresh rate. */
  enum aem10900_window window;
};

// Enum validation functions:

/**
 * @brief Check if a numeric value is a valid @ref enum aem10900_mode.
 * @returns bool (true/false)
 */
#define AEM10900_IS_VALID_MODE(_VAL_) (                                                            \
  ((_VAL_) <= 0x1U) ? true :                                                                       \
  false )

/**
 * @brief Check if a numeric value is a valid @ref enum aem10900_window.
 * @returns bool (true/false)
 */
#define AEM10900_IS_VALID_WINDOW(_VAL_) (                                                          \
  ((_VAL_) <= 0x2U) ? true :                                                                       \
  false )

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_apm struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_apm_pack_le(const struct aem10900_apm *r, uint8_t val[1]) {
  // EN @ apm[0]:
  val[0] &= (uint8_t)~0x1U;
  val[0] |= (uint8_t)(((uint8_t)r->en) & 0x1U);
  // MODE @ apm[1]:
  val[0] &= (uint8_t)~0x2U;
  val[0] |= (uint8_t)(((uint8_t)(r->mode << 1)) & 0x2U);
  // WINDOW @ apm[3:2]:
  val[0] &= (uint8_t)~0xCU;
  val[0] |= (uint8_t)(((uint8_t)(r->window << 2)) & 0xCU);
}

/**
 * @brief Convert @ref struct aem10900_apm struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_apm_pack_be(const struct aem10900_apm *r, uint8_t val[1]) {
  // EN @ apm[0]:
  val[0] &= (uint8_t)~0x1U;
  val[0] |= (uint8_t)(((uint8_t)r->en) & 0x1U);
  // MODE @ apm[1]:
  val[0] &= (uint8_t)~0x2U;
  val[0] |= (uint8_t)(((uint8_t)(r->mode << 1)) & 0x2U);
  // WINDOW @ apm[3:2]:
  val[0] &= (uint8_t)~0xCU;
  val[0] |= (uint8_t)(((uint8_t)(r->window << 2)) & 0xCU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_apm aem10900_apm_unpack_le(const uint8_t val[1]) {
  struct aem10900_apm r = {0};
  // EN @ apm[0]:
  r.en = (bool)((val[0] & 0x1U));
  // MODE @ apm[1]:
  r.mode = (enum aem10900_mode)(((val[0] & 0x2U) >> 1));
  // WINDOW @ apm[3:2]:
  r.window = (enum aem10900_window)(((val[0] & 0xCU) >> 2));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_apm aem10900_apm_unpack_be(const uint8_t val[1]) {
  struct aem10900_apm r = {0};
  // EN @ apm[0]:
  r.en = (bool)((val[0] & 0x1U));
  // MODE @ apm[1]:
  r.mode = (enum aem10900_mode)(((val[0] & 0x2U) >> 1));
  // WINDOW @ apm[3:2]:
  r.window = (enum aem10900_window)(((val[0] & 0xCU) >> 2));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_apm(const struct aem10900_apm *r) {
  if (!(AEM10900_IS_VALID_MODE(r->mode))) return 2;
  if (!(AEM10900_IS_VALID_WINDOW(r->window))) return 3;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_apm_try_unpack_le(const uint8_t val[1], struct aem10900_apm *r) {
  *r = aem10900_apm_unpack_le(val);
  return aem10900_validate_apm(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_apm_try_unpack_be(const uint8_t val[1], struct aem10900_apm *r) {
  *r = aem10900_apm_unpack_be(val);
  return aem10900_validate_apm(r);
}

// =============================================================================
// ==== APM0 Register ==========================================================
// =============================================================================
// APM Data Register 0.
// Fields:
//  - [7:0] DATA (uint): Lower byte of APM data.

#define AEM10900_APM0_ADDRESS  (0xEU) //!< APM0 register address
#define AEM10900_APM0_RESET_LE {0x0U} //!< APM0 register reset value
#define AEM10900_APM0_RESET_BE {0x0U} //!< APM0 register reset value

// Register Layout Struct:

/**
 * @brief APM Data Register 0.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_apm0 {
  /** @brief Lower byte of APM data. */
  uint8_t data;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_apm0 struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_apm0_pack_le(const struct aem10900_apm0 *r, uint8_t val[1]) {
  // DATA @ apm0[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/**
 * @brief Convert @ref struct aem10900_apm0 struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_apm0_pack_be(const struct aem10900_apm0 *r, uint8_t val[1]) {
  // DATA @ apm0[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_apm0 aem10900_apm0_unpack_le(const uint8_t val[1]) {
  struct aem10900_apm0 r = {0};
  // DATA @ apm0[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_apm0 aem10900_apm0_unpack_be(const uint8_t val[1]) {
  struct aem10900_apm0 r = {0};
  // DATA @ apm0[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_apm0(const struct aem10900_apm0 *r) {
  if ((r->data & ~(uint8_t)0xFF) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_apm0_try_unpack_le(const uint8_t val[1], struct aem10900_apm0 *r) {
  *r = aem10900_apm0_unpack_le(val);
  return aem10900_validate_apm0(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_apm0_try_unpack_be(const uint8_t val[1], struct aem10900_apm0 *r) {
  *r = aem10900_apm0_unpack_be(val);
  return aem10900_validate_apm0(r);
}

// =============================================================================
// ==== APM1 Register ==========================================================
// =============================================================================
// APM Data Register 1.
// Fields:
//  - [7:0] DATA (uint): Middle byte of APM data.

#define AEM10900_APM1_ADDRESS  (0xFU) //!< APM1 register address
#define AEM10900_APM1_RESET_LE {0x0U} //!< APM1 register reset value
#define AEM10900_APM1_RESET_BE {0x0U} //!< APM1 register reset value

// Register Layout Struct:

/**
 * @brief APM Data Register 1.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_apm1 {
  /** @brief Middle byte of APM data. */
  uint8_t data;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_apm1 struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_apm1_pack_le(const struct aem10900_apm1 *r, uint8_t val[1]) {
  // DATA @ apm1[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/**
 * @brief Convert @ref struct aem10900_apm1 struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_apm1_pack_be(const struct aem10900_apm1 *r, uint8_t val[1]) {
  // DATA @ apm1[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_apm1 aem10900_apm1_unpack_le(const uint8_t val[1]) {
  struct aem10900_apm1 r = {0};
  // DATA @ apm1[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_apm1 aem10900_apm1_unpack_be(const uint8_t val[1]) {
  struct aem10900_apm1 r = {0};
  // DATA @ apm1[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_apm1(const struct aem10900_apm1 *r) {
  if ((r->data & ~(uint8_t)0xFF) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_apm1_try_unpack_le(const uint8_t val[1], struct aem10900_apm1 *r) {
  *r = aem10900_apm1_unpack_le(val);
  return aem10900_validate_apm1(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_apm1_try_unpack_be(const uint8_t val[1], struct aem10900_apm1 *r) {
  *r = aem10900_apm1_unpack_be(val);
  return aem10900_validate_apm1(r);
}

// =============================================================================
// ==== APM2 Register ==========================================================
// =============================================================================
// APM Data Register 2.
// Fields:
//  - [7:0] DATA (uint): Upper byte of APM data.

#define AEM10900_APM2_ADDRESS  (0x10U) //!< APM2 register address
#define AEM10900_APM2_RESET_LE {0x0U}  //!< APM2 register reset value
#define AEM10900_APM2_RESET_BE {0x0U}  //!< APM2 register reset value

// Register Layout Struct:

/**
 * @brief APM Data Register 2.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_apm2 {
  /** @brief Upper byte of APM data. */
  uint8_t data;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_apm2 struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_apm2_pack_le(const struct aem10900_apm2 *r, uint8_t val[1]) {
  // DATA @ apm2[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/**
 * @brief Convert @ref struct aem10900_apm2 struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_apm2_pack_be(const struct aem10900_apm2 *r, uint8_t val[1]) {
  // DATA @ apm2[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_apm2 aem10900_apm2_unpack_le(const uint8_t val[1]) {
  struct aem10900_apm2 r = {0};
  // DATA @ apm2[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_apm2 aem10900_apm2_unpack_be(const uint8_t val[1]) {
  struct aem10900_apm2 r = {0};
  // DATA @ apm2[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_apm2(const struct aem10900_apm2 *r) {
  if ((r->data & ~(uint8_t)0xFF) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_apm2_try_unpack_le(const uint8_t val[1], struct aem10900_apm2 *r) {
  *r = aem10900_apm2_unpack_le(val);
  return aem10900_validate_apm2(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_apm2_try_unpack_be(const uint8_t val[1], struct aem10900_apm2 *r) {
  *r = aem10900_apm2_unpack_be(val);
  return aem10900_validate_apm2(r);
}

// =============================================================================
// ==== CTRL Register ==========================================================
// =============================================================================
// Control register for I2C configuration.
// Fields:
//  - [0] UPDATE (enum UPDATE): This field is used to control the source of the AEM10900 configuration (GPIO or I2C).
//  - [1] RESERVED (fixed: 0x0): Write 0x00.
//  - [2] SYNCBUSY (enum SYNCBUSY): This field indicates whether the synchronization from the I2C registers to the system registers is ongoing or not.

#define AEM10900_CTRL_ADDRESS  (0xBU) //!< CTRL register address
#define AEM10900_CTRL_RESET_LE {0x0U} //!< CTRL register reset value
#define AEM10900_CTRL_RESET_BE {0x0U} //!< CTRL register reset value

// Register-specific enums and sub-layouts:

/** @brief This field indicates whether the synchronization from the I2C registers to the system registers is ongoing or not. */
enum aem10900_syncbusy {
  /** @brief CTRL register not synchronizing. */
  AEM10900_SYNCBUSY_NSYNC = 0x0U,
  /** @brief CTRL register synchronizing. */
  AEM10900_SYNCBUSY_SYNC = 0x1U,
};

/** @brief This field is used to control the source of the AEM10900 configuration (GPIO or I2C). */
enum aem10900_update {
  /** @brief Load configurations from the GPIOs */
  AEM10900_UPDATE_GPIO = 0x0U,
  /** @brief Load configurations from the I2C registers */
  AEM10900_UPDATE_I2C = 0x1U,
};

// Register Layout Struct:

/**
 * @brief Control register for I2C configuration.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_ctrl {
  /** @brief This field indicates whether the synchronization from the I2C registers to the system registers is ongoing or not. */
  enum aem10900_syncbusy syncbusy;
  /** @brief This field is used to control the source of the AEM10900 configuration (GPIO or I2C). */
  enum aem10900_update update;
};

// Enum validation functions:

/**
 * @brief Check if a numeric value is a valid @ref enum aem10900_syncbusy.
 * @returns bool (true/false)
 */
#define AEM10900_IS_VALID_SYNCBUSY(_VAL_) (                                                        \
  ((_VAL_) <= 0x1U) ? true :                                                                       \
  false )

/**
 * @brief Check if a numeric value is a valid @ref enum aem10900_update.
 * @returns bool (true/false)
 */
#define AEM10900_IS_VALID_UPDATE(_VAL_) (                                                          \
  ((_VAL_) <= 0x1U) ? true :                                                                       \
  false )

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_ctrl struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_ctrl_pack_le(const struct aem10900_ctrl *r, uint8_t val[1]) {
  // RESERVED @ ctrl[1]:
  val[0] &= (uint8_t)~0x2U;
  val[0] |= (uint8_t)0x0; // Fixed value.
  // SYNCBUSY @ ctrl[2]:
  val[0] &= (uint8_t)~0x4U;
  val[0] |= (uint8_t)(((uint8_t)(r->syncbusy << 2)) & 0x4U);
  // UPDATE @ ctrl[0]:
  val[0] &= (uint8_t)~0x1U;
  val[0] |= (uint8_t)(((uint8_t)r->update) & 0x1U);
}

/**
 * @brief Convert @ref struct aem10900_ctrl struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_ctrl_pack_be(const struct aem10900_ctrl *r, uint8_t val[1]) {
  // RESERVED @ ctrl[1]:
  val[0] &= (uint8_t)~0x2U;
  val[0] |= (uint8_t)0x0; // Fixed value.
  // SYNCBUSY @ ctrl[2]:
  val[0] &= (uint8_t)~0x4U;
  val[0] |= (uint8_t)(((uint8_t)(r->syncbusy << 2)) & 0x4U);
  // UPDATE @ ctrl[0]:
  val[0] &= (uint8_t)~0x1U;
  val[0] |= (uint8_t)(((uint8_t)r->update) & 0x1U);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_ctrl aem10900_ctrl_unpack_le(const uint8_t val[1]) {
  struct aem10900_ctrl r = {0};
  // SYNCBUSY @ ctrl[2]:
  r.syncbusy = (enum aem10900_syncbusy)(((val[0] & 0x4U) >> 2));
  // UPDATE @ ctrl[0]:
  r.update = (enum aem10900_update)((val[0] & 0x1U));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_ctrl aem10900_ctrl_unpack_be(const uint8_t val[1]) {
  struct aem10900_ctrl r = {0};
  // SYNCBUSY @ ctrl[2]:
  r.syncbusy = (enum aem10900_syncbusy)(((val[0] & 0x4U) >> 2));
  // UPDATE @ ctrl[0]:
  r.update = (enum aem10900_update)((val[0] & 0x1U));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_ctrl(const struct aem10900_ctrl *r) {
  if (!(AEM10900_IS_VALID_SYNCBUSY(r->syncbusy))) return 3;
  if (!(AEM10900_IS_VALID_UPDATE(r->update))) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_ctrl_try_unpack_le(const uint8_t val[1], struct aem10900_ctrl *r) {
  *r = aem10900_ctrl_unpack_le(val);
  return aem10900_validate_ctrl(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_ctrl_try_unpack_be(const uint8_t val[1], struct aem10900_ctrl *r) {
  *r = aem10900_ctrl_unpack_be(val);
  return aem10900_validate_ctrl(r);
}

// =============================================================================
// ==== IRQEN Register =========================================================
// =============================================================================
// IRQ Enable Register.
// Fields:
//  - [0] I2CRDY (bool): Enable IRQ for I2C ready status.
//  - [1] VOVDIS (bool): Enable IRQ for overdischarge detection.
//  - [2] VOVCH (bool): Enable IRQ for overcharge detection.
//  - [3] SRCTHRESH (bool): Enable IRQ for SRC LOW threshold crossing (set in sleep register).
//  - [4] TEMP (bool): Enable IRQ when temperature crosses temperature limits.
//  - [5] APMDONE (bool): Enable IRQ for completion of APM measurement.
//  - [6] APMERR (bool): Enable IRQ for signaling an error in the APM.

#define AEM10900_IRQEN_ADDRESS  (0xAU) //!< IRQEN register address
#define AEM10900_IRQEN_RESET_LE {0x1U} //!< IRQEN register reset value
#define AEM10900_IRQEN_RESET_BE {0x1U} //!< IRQEN register reset value

// Register Layout Struct:

/**
 * @brief IRQ Enable Register.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_irqen {
  /** @brief Enable IRQ for completion of APM measurement. */
  bool apmdone;
  /** @brief Enable IRQ for signaling an error in the APM. */
  bool apmerr;
  /** @brief Enable IRQ for I2C ready status. */
  bool i2crdy;
  /** @brief Enable IRQ for SRC LOW threshold crossing (set in sleep register). */
  bool srcthresh;
  /** @brief Enable IRQ when temperature crosses temperature limits. */
  bool temp;
  /** @brief Enable IRQ for overcharge detection. */
  bool vovch;
  /** @brief Enable IRQ for overdischarge detection. */
  bool vovdis;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_irqen struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_irqen_pack_le(const struct aem10900_irqen *r, uint8_t val[1]) {
  // APMDONE @ irqen[5]:
  val[0] &= (uint8_t)~0x20U;
  val[0] |= (uint8_t)(((uint8_t)(r->apmdone << 5)) & 0x20U);
  // APMERR @ irqen[6]:
  val[0] &= (uint8_t)~0x40U;
  val[0] |= (uint8_t)(((uint8_t)(r->apmerr << 6)) & 0x40U);
  // I2CRDY @ irqen[0]:
  val[0] &= (uint8_t)~0x1U;
  val[0] |= (uint8_t)(((uint8_t)r->i2crdy) & 0x1U);
  // SRCTHRESH @ irqen[3]:
  val[0] &= (uint8_t)~0x8U;
  val[0] |= (uint8_t)(((uint8_t)(r->srcthresh << 3)) & 0x8U);
  // TEMP @ irqen[4]:
  val[0] &= (uint8_t)~0x10U;
  val[0] |= (uint8_t)(((uint8_t)(r->temp << 4)) & 0x10U);
  // VOVCH @ irqen[2]:
  val[0] &= (uint8_t)~0x4U;
  val[0] |= (uint8_t)(((uint8_t)(r->vovch << 2)) & 0x4U);
  // VOVDIS @ irqen[1]:
  val[0] &= (uint8_t)~0x2U;
  val[0] |= (uint8_t)(((uint8_t)(r->vovdis << 1)) & 0x2U);
}

/**
 * @brief Convert @ref struct aem10900_irqen struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_irqen_pack_be(const struct aem10900_irqen *r, uint8_t val[1]) {
  // APMDONE @ irqen[5]:
  val[0] &= (uint8_t)~0x20U;
  val[0] |= (uint8_t)(((uint8_t)(r->apmdone << 5)) & 0x20U);
  // APMERR @ irqen[6]:
  val[0] &= (uint8_t)~0x40U;
  val[0] |= (uint8_t)(((uint8_t)(r->apmerr << 6)) & 0x40U);
  // I2CRDY @ irqen[0]:
  val[0] &= (uint8_t)~0x1U;
  val[0] |= (uint8_t)(((uint8_t)r->i2crdy) & 0x1U);
  // SRCTHRESH @ irqen[3]:
  val[0] &= (uint8_t)~0x8U;
  val[0] |= (uint8_t)(((uint8_t)(r->srcthresh << 3)) & 0x8U);
  // TEMP @ irqen[4]:
  val[0] &= (uint8_t)~0x10U;
  val[0] |= (uint8_t)(((uint8_t)(r->temp << 4)) & 0x10U);
  // VOVCH @ irqen[2]:
  val[0] &= (uint8_t)~0x4U;
  val[0] |= (uint8_t)(((uint8_t)(r->vovch << 2)) & 0x4U);
  // VOVDIS @ irqen[1]:
  val[0] &= (uint8_t)~0x2U;
  val[0] |= (uint8_t)(((uint8_t)(r->vovdis << 1)) & 0x2U);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_irqen aem10900_irqen_unpack_le(const uint8_t val[1]) {
  struct aem10900_irqen r = {0};
  // APMDONE @ irqen[5]:
  r.apmdone = (bool)(((val[0] & 0x20U) >> 5));
  // APMERR @ irqen[6]:
  r.apmerr = (bool)(((val[0] & 0x40U) >> 6));
  // I2CRDY @ irqen[0]:
  r.i2crdy = (bool)((val[0] & 0x1U));
  // SRCTHRESH @ irqen[3]:
  r.srcthresh = (bool)(((val[0] & 0x8U) >> 3));
  // TEMP @ irqen[4]:
  r.temp = (bool)(((val[0] & 0x10U) >> 4));
  // VOVCH @ irqen[2]:
  r.vovch = (bool)(((val[0] & 0x4U) >> 2));
  // VOVDIS @ irqen[1]:
  r.vovdis = (bool)(((val[0] & 0x2U) >> 1));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_irqen aem10900_irqen_unpack_be(const uint8_t val[1]) {
  struct aem10900_irqen r = {0};
  // APMDONE @ irqen[5]:
  r.apmdone = (bool)(((val[0] & 0x20U) >> 5));
  // APMERR @ irqen[6]:
  r.apmerr = (bool)(((val[0] & 0x40U) >> 6));
  // I2CRDY @ irqen[0]:
  r.i2crdy = (bool)((val[0] & 0x1U));
  // SRCTHRESH @ irqen[3]:
  r.srcthresh = (bool)(((val[0] & 0x8U) >> 3));
  // TEMP @ irqen[4]:
  r.temp = (bool)(((val[0] & 0x10U) >> 4));
  // VOVCH @ irqen[2]:
  r.vovch = (bool)(((val[0] & 0x4U) >> 2));
  // VOVDIS @ irqen[1]:
  r.vovdis = (bool)(((val[0] & 0x2U) >> 1));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_irqen(const struct aem10900_irqen *r) {
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_irqen_try_unpack_le(const uint8_t val[1], struct aem10900_irqen *r) {
  *r = aem10900_irqen_unpack_le(val);
  return aem10900_validate_irqen(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_irqen_try_unpack_be(const uint8_t val[1], struct aem10900_irqen *r) {
  *r = aem10900_irqen_unpack_be(val);
  return aem10900_validate_irqen(r);
}

// =============================================================================
// ==== IRQFLG Register ========================================================
// =============================================================================
// The IRQFLG register contains all interrupt flags, corresponding to those enabled in the IRQEN register. This register is reseted when read.
// Fields:
//  - [0] I2CRDY (bool): Flag indicating I2C ready status.
//  - [1] VOVDIS (bool): Flag indicating overdischarge detection.
//  - [2] VOVCH (bool): Flag indicating overcharge detection.
//  - [3] SRCTHRESH (bool): Flag indicating SRC LOW threshold crossing (set in sleep register).
//  - [4] TEMP (bool): Flag indicating temperature crossed temperature limits.
//  - [5] APMDONE (bool): Flag indicating completion of APM measurement.
//  - [6] APMERR (bool): Flag indicating error in the APM.

#define AEM10900_IRQFLG_ADDRESS  (0xCU) //!< IRQFLG register address
#define AEM10900_IRQFLG_RESET_LE {0x0U} //!< IRQFLG register reset value
#define AEM10900_IRQFLG_RESET_BE {0x0U} //!< IRQFLG register reset value

// Register Layout Struct:

/**
 * @brief The IRQFLG register contains all interrupt flags, corresponding to those enabled in the IRQEN register. This register is reseted when read.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_irqflg {
  /** @brief Flag indicating completion of APM measurement. */
  bool apmdone;
  /** @brief Flag indicating error in the APM. */
  bool apmerr;
  /** @brief Flag indicating I2C ready status. */
  bool i2crdy;
  /** @brief Flag indicating SRC LOW threshold crossing (set in sleep register). */
  bool srcthresh;
  /** @brief Flag indicating temperature crossed temperature limits. */
  bool temp;
  /** @brief Flag indicating overcharge detection. */
  bool vovch;
  /** @brief Flag indicating overdischarge detection. */
  bool vovdis;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_irqflg struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_irqflg_pack_le(const struct aem10900_irqflg *r, uint8_t val[1]) {
  // APMDONE @ irqflg[5]:
  val[0] &= (uint8_t)~0x20U;
  val[0] |= (uint8_t)(((uint8_t)(r->apmdone << 5)) & 0x20U);
  // APMERR @ irqflg[6]:
  val[0] &= (uint8_t)~0x40U;
  val[0] |= (uint8_t)(((uint8_t)(r->apmerr << 6)) & 0x40U);
  // I2CRDY @ irqflg[0]:
  val[0] &= (uint8_t)~0x1U;
  val[0] |= (uint8_t)(((uint8_t)r->i2crdy) & 0x1U);
  // SRCTHRESH @ irqflg[3]:
  val[0] &= (uint8_t)~0x8U;
  val[0] |= (uint8_t)(((uint8_t)(r->srcthresh << 3)) & 0x8U);
  // TEMP @ irqflg[4]:
  val[0] &= (uint8_t)~0x10U;
  val[0] |= (uint8_t)(((uint8_t)(r->temp << 4)) & 0x10U);
  // VOVCH @ irqflg[2]:
  val[0] &= (uint8_t)~0x4U;
  val[0] |= (uint8_t)(((uint8_t)(r->vovch << 2)) & 0x4U);
  // VOVDIS @ irqflg[1]:
  val[0] &= (uint8_t)~0x2U;
  val[0] |= (uint8_t)(((uint8_t)(r->vovdis << 1)) & 0x2U);
}

/**
 * @brief Convert @ref struct aem10900_irqflg struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_irqflg_pack_be(const struct aem10900_irqflg *r, uint8_t val[1]) {
  // APMDONE @ irqflg[5]:
  val[0] &= (uint8_t)~0x20U;
  val[0] |= (uint8_t)(((uint8_t)(r->apmdone << 5)) & 0x20U);
  // APMERR @ irqflg[6]:
  val[0] &= (uint8_t)~0x40U;
  val[0] |= (uint8_t)(((uint8_t)(r->apmerr << 6)) & 0x40U);
  // I2CRDY @ irqflg[0]:
  val[0] &= (uint8_t)~0x1U;
  val[0] |= (uint8_t)(((uint8_t)r->i2crdy) & 0x1U);
  // SRCTHRESH @ irqflg[3]:
  val[0] &= (uint8_t)~0x8U;
  val[0] |= (uint8_t)(((uint8_t)(r->srcthresh << 3)) & 0x8U);
  // TEMP @ irqflg[4]:
  val[0] &= (uint8_t)~0x10U;
  val[0] |= (uint8_t)(((uint8_t)(r->temp << 4)) & 0x10U);
  // VOVCH @ irqflg[2]:
  val[0] &= (uint8_t)~0x4U;
  val[0] |= (uint8_t)(((uint8_t)(r->vovch << 2)) & 0x4U);
  // VOVDIS @ irqflg[1]:
  val[0] &= (uint8_t)~0x2U;
  val[0] |= (uint8_t)(((uint8_t)(r->vovdis << 1)) & 0x2U);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_irqflg aem10900_irqflg_unpack_le(const uint8_t val[1]) {
  struct aem10900_irqflg r = {0};
  // APMDONE @ irqflg[5]:
  r.apmdone = (bool)(((val[0] & 0x20U) >> 5));
  // APMERR @ irqflg[6]:
  r.apmerr = (bool)(((val[0] & 0x40U) >> 6));
  // I2CRDY @ irqflg[0]:
  r.i2crdy = (bool)((val[0] & 0x1U));
  // SRCTHRESH @ irqflg[3]:
  r.srcthresh = (bool)(((val[0] & 0x8U) >> 3));
  // TEMP @ irqflg[4]:
  r.temp = (bool)(((val[0] & 0x10U) >> 4));
  // VOVCH @ irqflg[2]:
  r.vovch = (bool)(((val[0] & 0x4U) >> 2));
  // VOVDIS @ irqflg[1]:
  r.vovdis = (bool)(((val[0] & 0x2U) >> 1));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_irqflg aem10900_irqflg_unpack_be(const uint8_t val[1]) {
  struct aem10900_irqflg r = {0};
  // APMDONE @ irqflg[5]:
  r.apmdone = (bool)(((val[0] & 0x20U) >> 5));
  // APMERR @ irqflg[6]:
  r.apmerr = (bool)(((val[0] & 0x40U) >> 6));
  // I2CRDY @ irqflg[0]:
  r.i2crdy = (bool)((val[0] & 0x1U));
  // SRCTHRESH @ irqflg[3]:
  r.srcthresh = (bool)(((val[0] & 0x8U) >> 3));
  // TEMP @ irqflg[4]:
  r.temp = (bool)(((val[0] & 0x10U) >> 4));
  // VOVCH @ irqflg[2]:
  r.vovch = (bool)(((val[0] & 0x4U) >> 2));
  // VOVDIS @ irqflg[1]:
  r.vovdis = (bool)(((val[0] & 0x2U) >> 1));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_irqflg(const struct aem10900_irqflg *r) {
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_irqflg_try_unpack_le(const uint8_t val[1], struct aem10900_irqflg *r) {
  *r = aem10900_irqflg_unpack_le(val);
  return aem10900_validate_irqflg(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_irqflg_try_unpack_be(const uint8_t val[1], struct aem10900_irqflg *r) {
  *r = aem10900_irqflg_unpack_be(val);
  return aem10900_validate_irqflg(r);
}

// =============================================================================
// ==== MPPTCFG Register =======================================================
// =============================================================================
// MPPT timing and ratio configuration.
// Fields:
//  - [3:0] RATIO (enum RATIO): MPP ratio
//  - [6:4] TIMING (enum TIMING): MPP Timing (T_xx_yy) with xx being T_VOC and yy being T_MPPT.

#define AEM10900_MPPTCFG_ADDRESS  (0x1U)  //!< MPPTCFG register address
#define AEM10900_MPPTCFG_RESET_LE {0x77U} //!< MPPTCFG register reset value
#define AEM10900_MPPTCFG_RESET_BE {0x77U} //!< MPPTCFG register reset value

// Register-specific enums and sub-layouts:

/** @brief MPP ratio */
enum aem10900_ratio {
  AEM10900_RATIO_R_35 = 0x8U,
  AEM10900_RATIO_R_50 = 0x9U,
  AEM10900_RATIO_R_60 = 0x3U,
  AEM10900_RATIO_R_65 = 0x2U,
  AEM10900_RATIO_R_70 = 0x6U,
  AEM10900_RATIO_R_75 = 0x5U,
  AEM10900_RATIO_R_80 = 0x7U,
  AEM10900_RATIO_R_85 = 0x4U,
  AEM10900_RATIO_R_90 = 0x1U,
  AEM10900_RATIO_R_ZMPP = 0x0U,
};

/** @brief MPP Timing (T_xx_yy) with xx being T_VOC and yy being T_MPPT. */
enum aem10900_timing {
  AEM10900_TIMING_T_256MS_16384MS = 0x1U,
  AEM10900_TIMING_T_2MS_128MS = 0x5U,
  AEM10900_TIMING_T_2MS_256MS = 0x7U,
  AEM10900_TIMING_T_2MS_64MS = 0x0U,
  AEM10900_TIMING_T_4MS_256MS = 0x4U,
  AEM10900_TIMING_T_4MS_512MS = 0x6U,
  AEM10900_TIMING_T_64MS_4096MS = 0x2U,
  AEM10900_TIMING_T_8MS_1024MS = 0x3U,
};

// Register Layout Struct:

/**
 * @brief MPPT timing and ratio configuration.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_mpptcfg {
  /** @brief MPP ratio */
  enum aem10900_ratio ratio;
  /** @brief MPP Timing (T_xx_yy) with xx being T_VOC and yy being T_MPPT. */
  enum aem10900_timing timing;
};

// Enum validation functions:

/**
 * @brief Check if a numeric value is a valid @ref enum aem10900_ratio.
 * @returns bool (true/false)
 */
#define AEM10900_IS_VALID_RATIO(_VAL_) (                                                           \
  ((_VAL_) <= 0x9U) ? true :                                                                       \
  false )

/**
 * @brief Check if a numeric value is a valid @ref enum aem10900_timing.
 * @returns bool (true/false)
 */
#define AEM10900_IS_VALID_TIMING(_VAL_) (                                                          \
  ((_VAL_) <= 0x7U) ? true :                                                                       \
  false )

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_mpptcfg struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_mpptcfg_pack_le(const struct aem10900_mpptcfg *r, uint8_t val[1]) {
  // RATIO @ mpptcfg[3:0]:
  val[0] &= (uint8_t)~0xFU;
  val[0] |= (uint8_t)(((uint8_t)r->ratio) & 0xFU);
  // TIMING @ mpptcfg[6:4]:
  val[0] &= (uint8_t)~0x70U;
  val[0] |= (uint8_t)(((uint8_t)(r->timing << 4)) & 0x70U);
}

/**
 * @brief Convert @ref struct aem10900_mpptcfg struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_mpptcfg_pack_be(const struct aem10900_mpptcfg *r, uint8_t val[1]) {
  // RATIO @ mpptcfg[3:0]:
  val[0] &= (uint8_t)~0xFU;
  val[0] |= (uint8_t)(((uint8_t)r->ratio) & 0xFU);
  // TIMING @ mpptcfg[6:4]:
  val[0] &= (uint8_t)~0x70U;
  val[0] |= (uint8_t)(((uint8_t)(r->timing << 4)) & 0x70U);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_mpptcfg aem10900_mpptcfg_unpack_le(const uint8_t val[1]) {
  struct aem10900_mpptcfg r = {0};
  // RATIO @ mpptcfg[3:0]:
  r.ratio = (enum aem10900_ratio)((val[0] & 0xFU));
  // TIMING @ mpptcfg[6:4]:
  r.timing = (enum aem10900_timing)(((val[0] & 0x70U) >> 4));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_mpptcfg aem10900_mpptcfg_unpack_be(const uint8_t val[1]) {
  struct aem10900_mpptcfg r = {0};
  // RATIO @ mpptcfg[3:0]:
  r.ratio = (enum aem10900_ratio)((val[0] & 0xFU));
  // TIMING @ mpptcfg[6:4]:
  r.timing = (enum aem10900_timing)(((val[0] & 0x70U) >> 4));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_mpptcfg(const struct aem10900_mpptcfg *r) {
  if (!(AEM10900_IS_VALID_RATIO(r->ratio))) return 1;
  if (!(AEM10900_IS_VALID_TIMING(r->timing))) return 5;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_mpptcfg_try_unpack_le(const uint8_t val[1], struct aem10900_mpptcfg *r) {
  *r = aem10900_mpptcfg_unpack_le(val);
  return aem10900_validate_mpptcfg(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_mpptcfg_try_unpack_be(const uint8_t val[1], struct aem10900_mpptcfg *r) {
  *r = aem10900_mpptcfg_unpack_be(val);
  return aem10900_validate_mpptcfg(r);
}

// =============================================================================
// ==== PN0 Register ===========================================================
// =============================================================================
// Part Number Register 0.
// Fields:
//  - [7:0] DATA (uint): Part number identification byte 0.

#define AEM10900_PN0_ADDRESS  (0xE0U) //!< PN0 register address
#define AEM10900_PN0_RESET_LE {0x30U} //!< PN0 register reset value
#define AEM10900_PN0_RESET_BE {0x30U} //!< PN0 register reset value

// Register Layout Struct:

/**
 * @brief Part Number Register 0.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_pn0 {
  /** @brief Part number identification byte 0. */
  uint8_t data;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_pn0 struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_pn0_pack_le(const struct aem10900_pn0 *r, uint8_t val[1]) {
  // DATA @ pn0[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/**
 * @brief Convert @ref struct aem10900_pn0 struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_pn0_pack_be(const struct aem10900_pn0 *r, uint8_t val[1]) {
  // DATA @ pn0[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_pn0 aem10900_pn0_unpack_le(const uint8_t val[1]) {
  struct aem10900_pn0 r = {0};
  // DATA @ pn0[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_pn0 aem10900_pn0_unpack_be(const uint8_t val[1]) {
  struct aem10900_pn0 r = {0};
  // DATA @ pn0[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_pn0(const struct aem10900_pn0 *r) {
  if ((r->data & ~(uint8_t)0xFF) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_pn0_try_unpack_le(const uint8_t val[1], struct aem10900_pn0 *r) {
  *r = aem10900_pn0_unpack_le(val);
  return aem10900_validate_pn0(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_pn0_try_unpack_be(const uint8_t val[1], struct aem10900_pn0 *r) {
  *r = aem10900_pn0_unpack_be(val);
  return aem10900_validate_pn0(r);
}

// =============================================================================
// ==== PN1 Register ===========================================================
// =============================================================================
// Part Number Register 1.
// Fields:
//  - [7:0] DATA (uint): Part number identification byte 1.

#define AEM10900_PN1_ADDRESS  (0xE1U) //!< PN1 register address
#define AEM10900_PN1_RESET_LE {0x30U} //!< PN1 register reset value
#define AEM10900_PN1_RESET_BE {0x30U} //!< PN1 register reset value

// Register Layout Struct:

/**
 * @brief Part Number Register 1.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_pn1 {
  /** @brief Part number identification byte 1. */
  uint8_t data;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_pn1 struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_pn1_pack_le(const struct aem10900_pn1 *r, uint8_t val[1]) {
  // DATA @ pn1[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/**
 * @brief Convert @ref struct aem10900_pn1 struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_pn1_pack_be(const struct aem10900_pn1 *r, uint8_t val[1]) {
  // DATA @ pn1[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_pn1 aem10900_pn1_unpack_le(const uint8_t val[1]) {
  struct aem10900_pn1 r = {0};
  // DATA @ pn1[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_pn1 aem10900_pn1_unpack_be(const uint8_t val[1]) {
  struct aem10900_pn1 r = {0};
  // DATA @ pn1[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_pn1(const struct aem10900_pn1 *r) {
  if ((r->data & ~(uint8_t)0xFF) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_pn1_try_unpack_le(const uint8_t val[1], struct aem10900_pn1 *r) {
  *r = aem10900_pn1_unpack_le(val);
  return aem10900_validate_pn1(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_pn1_try_unpack_be(const uint8_t val[1], struct aem10900_pn1 *r) {
  *r = aem10900_pn1_unpack_be(val);
  return aem10900_validate_pn1(r);
}

// =============================================================================
// ==== PN2 Register ===========================================================
// =============================================================================
// Part Number Register 2.
// Fields:
//  - [7:0] DATA (uint): Part number identification byte 2.

#define AEM10900_PN2_ADDRESS  (0xE2U) //!< PN2 register address
#define AEM10900_PN2_RESET_LE {0x39U} //!< PN2 register reset value
#define AEM10900_PN2_RESET_BE {0x39U} //!< PN2 register reset value

// Register Layout Struct:

/**
 * @brief Part Number Register 2.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_pn2 {
  /** @brief Part number identification byte 2. */
  uint8_t data;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_pn2 struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_pn2_pack_le(const struct aem10900_pn2 *r, uint8_t val[1]) {
  // DATA @ pn2[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/**
 * @brief Convert @ref struct aem10900_pn2 struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_pn2_pack_be(const struct aem10900_pn2 *r, uint8_t val[1]) {
  // DATA @ pn2[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_pn2 aem10900_pn2_unpack_le(const uint8_t val[1]) {
  struct aem10900_pn2 r = {0};
  // DATA @ pn2[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_pn2 aem10900_pn2_unpack_be(const uint8_t val[1]) {
  struct aem10900_pn2 r = {0};
  // DATA @ pn2[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_pn2(const struct aem10900_pn2 *r) {
  if ((r->data & ~(uint8_t)0xFF) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_pn2_try_unpack_le(const uint8_t val[1], struct aem10900_pn2 *r) {
  *r = aem10900_pn2_unpack_le(val);
  return aem10900_validate_pn2(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_pn2_try_unpack_be(const uint8_t val[1], struct aem10900_pn2 *r) {
  *r = aem10900_pn2_unpack_be(val);
  return aem10900_validate_pn2(r);
}

// =============================================================================
// ==== PN3 Register ===========================================================
// =============================================================================
// Part Number Register 3.
// Fields:
//  - [7:0] DATA (uint): Part number identification byte 3.

#define AEM10900_PN3_ADDRESS  (0xE3U) //!< PN3 register address
#define AEM10900_PN3_RESET_LE {0x30U} //!< PN3 register reset value
#define AEM10900_PN3_RESET_BE {0x30U} //!< PN3 register reset value

// Register Layout Struct:

/**
 * @brief Part Number Register 3.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_pn3 {
  /** @brief Part number identification byte 3. */
  uint8_t data;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_pn3 struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_pn3_pack_le(const struct aem10900_pn3 *r, uint8_t val[1]) {
  // DATA @ pn3[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/**
 * @brief Convert @ref struct aem10900_pn3 struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_pn3_pack_be(const struct aem10900_pn3 *r, uint8_t val[1]) {
  // DATA @ pn3[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_pn3 aem10900_pn3_unpack_le(const uint8_t val[1]) {
  struct aem10900_pn3 r = {0};
  // DATA @ pn3[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_pn3 aem10900_pn3_unpack_be(const uint8_t val[1]) {
  struct aem10900_pn3 r = {0};
  // DATA @ pn3[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_pn3(const struct aem10900_pn3 *r) {
  if ((r->data & ~(uint8_t)0xFF) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_pn3_try_unpack_le(const uint8_t val[1], struct aem10900_pn3 *r) {
  *r = aem10900_pn3_unpack_le(val);
  return aem10900_validate_pn3(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_pn3_try_unpack_be(const uint8_t val[1], struct aem10900_pn3 *r) {
  *r = aem10900_pn3_unpack_be(val);
  return aem10900_validate_pn3(r);
}

// =============================================================================
// ==== PN4 Register ===========================================================
// =============================================================================
// Part Number Register 4.
// Fields:
//  - [7:0] DATA (uint): Part number identification byte 4.

#define AEM10900_PN4_ADDRESS  (0xE4U) //!< PN4 register address
#define AEM10900_PN4_RESET_LE {0x31U} //!< PN4 register reset value
#define AEM10900_PN4_RESET_BE {0x31U} //!< PN4 register reset value

// Register Layout Struct:

/**
 * @brief Part Number Register 4.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_pn4 {
  /** @brief Part number identification byte 4. */
  uint8_t data;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_pn4 struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_pn4_pack_le(const struct aem10900_pn4 *r, uint8_t val[1]) {
  // DATA @ pn4[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/**
 * @brief Convert @ref struct aem10900_pn4 struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_pn4_pack_be(const struct aem10900_pn4 *r, uint8_t val[1]) {
  // DATA @ pn4[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_pn4 aem10900_pn4_unpack_le(const uint8_t val[1]) {
  struct aem10900_pn4 r = {0};
  // DATA @ pn4[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_pn4 aem10900_pn4_unpack_be(const uint8_t val[1]) {
  struct aem10900_pn4 r = {0};
  // DATA @ pn4[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_pn4(const struct aem10900_pn4 *r) {
  if ((r->data & ~(uint8_t)0xFF) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_pn4_try_unpack_le(const uint8_t val[1], struct aem10900_pn4 *r) {
  *r = aem10900_pn4_unpack_le(val);
  return aem10900_validate_pn4(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_pn4_try_unpack_be(const uint8_t val[1], struct aem10900_pn4 *r) {
  *r = aem10900_pn4_unpack_be(val);
  return aem10900_validate_pn4(r);
}

// =============================================================================
// ==== PWR Register ===========================================================
// =============================================================================
// Register dedicated to the power settings of the AEM10900.
// Fields:
//  - [0] KEEPALEN (bool): Keep alive enable. True means VINT supplied by STO, False means VINT supplied by SRC.
//  - [1] HPEN (bool): High-power mode enable. True means automatic change between modes, False means disabled.
//  - [2] TMONEN (bool): Temperature monitoring enable. True enables monitoring of ambient temperature.
//  - [3] STOCHDIS (bool): Battery charging disable. True means battery charging is disabled.
//  - [7:4] RESERVED (fixed: 0x0): Write to 0x00.

#define AEM10900_PWR_ADDRESS  (0x6U) //!< PWR register address
#define AEM10900_PWR_RESET_LE {0x7U} //!< PWR register reset value
#define AEM10900_PWR_RESET_BE {0x7U} //!< PWR register reset value

// Register Layout Struct:

/**
 * @brief Register dedicated to the power settings of the AEM10900.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_pwr {
  /** @brief High-power mode enable. True means automatic change between modes, False means disabled. */
  bool hpen;
  /** @brief Keep alive enable. True means VINT supplied by STO, False means VINT supplied by SRC. */
  bool keepalen;
  /** @brief Battery charging disable. True means battery charging is disabled. */
  bool stochdis;
  /** @brief Temperature monitoring enable. True enables monitoring of ambient temperature. */
  bool tmonen;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_pwr struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_pwr_pack_le(const struct aem10900_pwr *r, uint8_t val[1]) {
  // HPEN @ pwr[1]:
  val[0] &= (uint8_t)~0x2U;
  val[0] |= (uint8_t)(((uint8_t)(r->hpen << 1)) & 0x2U);
  // KEEPALEN @ pwr[0]:
  val[0] &= (uint8_t)~0x1U;
  val[0] |= (uint8_t)(((uint8_t)r->keepalen) & 0x1U);
  // RESERVED @ pwr[7:4]:
  val[0] &= (uint8_t)~0xF0U;
  val[0] |= (uint8_t)0x0; // Fixed value.
  // STOCHDIS @ pwr[3]:
  val[0] &= (uint8_t)~0x8U;
  val[0] |= (uint8_t)(((uint8_t)(r->stochdis << 3)) & 0x8U);
  // TMONEN @ pwr[2]:
  val[0] &= (uint8_t)~0x4U;
  val[0] |= (uint8_t)(((uint8_t)(r->tmonen << 2)) & 0x4U);
}

/**
 * @brief Convert @ref struct aem10900_pwr struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_pwr_pack_be(const struct aem10900_pwr *r, uint8_t val[1]) {
  // HPEN @ pwr[1]:
  val[0] &= (uint8_t)~0x2U;
  val[0] |= (uint8_t)(((uint8_t)(r->hpen << 1)) & 0x2U);
  // KEEPALEN @ pwr[0]:
  val[0] &= (uint8_t)~0x1U;
  val[0] |= (uint8_t)(((uint8_t)r->keepalen) & 0x1U);
  // RESERVED @ pwr[7:4]:
  val[0] &= (uint8_t)~0xF0U;
  val[0] |= (uint8_t)0x0; // Fixed value.
  // STOCHDIS @ pwr[3]:
  val[0] &= (uint8_t)~0x8U;
  val[0] |= (uint8_t)(((uint8_t)(r->stochdis << 3)) & 0x8U);
  // TMONEN @ pwr[2]:
  val[0] &= (uint8_t)~0x4U;
  val[0] |= (uint8_t)(((uint8_t)(r->tmonen << 2)) & 0x4U);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_pwr aem10900_pwr_unpack_le(const uint8_t val[1]) {
  struct aem10900_pwr r = {0};
  // HPEN @ pwr[1]:
  r.hpen = (bool)(((val[0] & 0x2U) >> 1));
  // KEEPALEN @ pwr[0]:
  r.keepalen = (bool)((val[0] & 0x1U));
  // STOCHDIS @ pwr[3]:
  r.stochdis = (bool)(((val[0] & 0x8U) >> 3));
  // TMONEN @ pwr[2]:
  r.tmonen = (bool)(((val[0] & 0x4U) >> 2));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_pwr aem10900_pwr_unpack_be(const uint8_t val[1]) {
  struct aem10900_pwr r = {0};
  // HPEN @ pwr[1]:
  r.hpen = (bool)(((val[0] & 0x2U) >> 1));
  // KEEPALEN @ pwr[0]:
  r.keepalen = (bool)((val[0] & 0x1U));
  // STOCHDIS @ pwr[3]:
  r.stochdis = (bool)(((val[0] & 0x8U) >> 3));
  // TMONEN @ pwr[2]:
  r.tmonen = (bool)(((val[0] & 0x4U) >> 2));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_pwr(const struct aem10900_pwr *r) {
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_pwr_try_unpack_le(const uint8_t val[1], struct aem10900_pwr *r) {
  *r = aem10900_pwr_unpack_le(val);
  return aem10900_validate_pwr(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_pwr_try_unpack_be(const uint8_t val[1], struct aem10900_pwr *r) {
  *r = aem10900_pwr_unpack_be(val);
  return aem10900_validate_pwr(r);
}

// =============================================================================
// ==== SLEEP Register =========================================================
// =============================================================================
// The Sleep register enables the sleep mode and sets the conditions for entering the sleep state.
// Fields:
//  - [0] EN (bool): The field enables sleep state when set to True (depending then on source voltage).
//  - [3:1] SRCTHRESH (enum SRCTHRESH): This field sets the source voltage threshold below which the AEM10900 enters sleep state.

#define AEM10900_SLEEP_ADDRESS  (0x7U) //!< SLEEP register address
#define AEM10900_SLEEP_RESET_LE {0x1U} //!< SLEEP register reset value
#define AEM10900_SLEEP_RESET_BE {0x1U} //!< SLEEP register reset value

// Register-specific enums and sub-layouts:

/** @brief This field sets the source voltage threshold below which the AEM10900 enters sleep state. */
enum aem10900_srcthresh {
  /** @brief Sleep threshold at 0.202V. */
  AEM10900_SRCTHRESH_V_202MV = 0x1U,
  /** @brief Sleep threshold at 0.255V. */
  AEM10900_SRCTHRESH_V_255MV = 0x2U,
  /** @brief Sleep threshold at 0.300V. */
  AEM10900_SRCTHRESH_V_300MV = 0x3U,
  /** @brief Sleep threshold at 0.360V. */
  AEM10900_SRCTHRESH_V_360MV = 0x4U,
  /** @brief Sleep threshold at 0.405V. */
  AEM10900_SRCTHRESH_V_405MV = 0x5U,
  /** @brief Sleep threshold at 0.510V. */
  AEM10900_SRCTHRESH_V_510MV = 0x6U,
  /** @brief Sleep threshold at 0.600V. */
  AEM10900_SRCTHRESH_V_600MV = 0x7U,
  /** @brief Unknown what this option means. */
  AEM10900_SRCTHRESH_V_MV = 0x0U,
};

// Register Layout Struct:

/**
 * @brief The Sleep register enables the sleep mode and sets the conditions for entering the sleep state.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_sleep {
  /** @brief The field enables sleep state when set to True (depending then on source voltage). */
  bool en;
  /** @brief This field sets the source voltage threshold below which the AEM10900 enters sleep state. */
  enum aem10900_srcthresh srcthresh;
};

// Enum validation functions:

/**
 * @brief Check if a numeric value is a valid @ref enum aem10900_srcthresh.
 * @returns bool (true/false)
 */
#define AEM10900_IS_VALID_SRCTHRESH(_VAL_) (                                                       \
  ((_VAL_) <= 0x7U) ? true :                                                                       \
  false )

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_sleep struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_sleep_pack_le(const struct aem10900_sleep *r, uint8_t val[1]) {
  // EN @ sleep[0]:
  val[0] &= (uint8_t)~0x1U;
  val[0] |= (uint8_t)(((uint8_t)r->en) & 0x1U);
  // SRCTHRESH @ sleep[3:1]:
  val[0] &= (uint8_t)~0xEU;
  val[0] |= (uint8_t)(((uint8_t)(r->srcthresh << 1)) & 0xEU);
}

/**
 * @brief Convert @ref struct aem10900_sleep struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_sleep_pack_be(const struct aem10900_sleep *r, uint8_t val[1]) {
  // EN @ sleep[0]:
  val[0] &= (uint8_t)~0x1U;
  val[0] |= (uint8_t)(((uint8_t)r->en) & 0x1U);
  // SRCTHRESH @ sleep[3:1]:
  val[0] &= (uint8_t)~0xEU;
  val[0] |= (uint8_t)(((uint8_t)(r->srcthresh << 1)) & 0xEU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_sleep aem10900_sleep_unpack_le(const uint8_t val[1]) {
  struct aem10900_sleep r = {0};
  // EN @ sleep[0]:
  r.en = (bool)((val[0] & 0x1U));
  // SRCTHRESH @ sleep[3:1]:
  r.srcthresh = (enum aem10900_srcthresh)(((val[0] & 0xEU) >> 1));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_sleep aem10900_sleep_unpack_be(const uint8_t val[1]) {
  struct aem10900_sleep r = {0};
  // EN @ sleep[0]:
  r.en = (bool)((val[0] & 0x1U));
  // SRCTHRESH @ sleep[3:1]:
  r.srcthresh = (enum aem10900_srcthresh)(((val[0] & 0xEU) >> 1));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_sleep(const struct aem10900_sleep *r) {
  if (!(AEM10900_IS_VALID_SRCTHRESH(r->srcthresh))) return 2;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_sleep_try_unpack_le(const uint8_t val[1], struct aem10900_sleep *r) {
  *r = aem10900_sleep_unpack_le(val);
  return aem10900_validate_sleep(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_sleep_try_unpack_be(const uint8_t val[1], struct aem10900_sleep *r) {
  *r = aem10900_sleep_unpack_be(val);
  return aem10900_validate_sleep(r);
}

// =============================================================================
// ==== SRC Register ===========================================================
// =============================================================================
// Source Voltage Register.
// Fields:
//  - [7:0] DATA (uint): Voltage level of the energy source connected to SRC. Conversion according to table 32 in DS v1.5

#define AEM10900_SRC_ADDRESS  (0x13U) //!< SRC register address
#define AEM10900_SRC_RESET_LE {0x0U}  //!< SRC register reset value
#define AEM10900_SRC_RESET_BE {0x0U}  //!< SRC register reset value

// Register Layout Struct:

/**
 * @brief Source Voltage Register.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_src {
  /** @brief Voltage level of the energy source connected to SRC. Conversion according to table 32 in DS v1.5 */
  uint8_t data;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_src struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_src_pack_le(const struct aem10900_src *r, uint8_t val[1]) {
  // DATA @ src[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/**
 * @brief Convert @ref struct aem10900_src struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_src_pack_be(const struct aem10900_src *r, uint8_t val[1]) {
  // DATA @ src[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_src aem10900_src_unpack_le(const uint8_t val[1]) {
  struct aem10900_src r = {0};
  // DATA @ src[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_src aem10900_src_unpack_be(const uint8_t val[1]) {
  struct aem10900_src r = {0};
  // DATA @ src[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_src(const struct aem10900_src *r) {
  if ((r->data & ~(uint8_t)0xFF) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_src_try_unpack_le(const uint8_t val[1], struct aem10900_src *r) {
  *r = aem10900_src_unpack_le(val);
  return aem10900_validate_src(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_src_try_unpack_be(const uint8_t val[1], struct aem10900_src *r) {
  *r = aem10900_src_unpack_be(val);
  return aem10900_validate_src(r);
}

// =============================================================================
// ==== STATUS Register ========================================================
// =============================================================================
// Status register of AEM10900.
// Fields:
//  - [1] VOVDIS (bool): Status indicating whether the battery is higher or lower than the overdischarge level threshold. If the battery voltage goes below VOVDIS then the field is set to true, else it is set to false.
//  - [2] VOVCH (bool): Status indicating whether the battery voltage is higher or lower than the overcharge level threshold. If the battery voltage rises above VOVCH then the field is set to 1, else it is set to 0.
//  - [3] SRCTHRESH (bool): Status indicating whether the source voltage is higher or lower than the sleep level threshold. If the source voltage is higher than the sleep level then the field is set to 0, else the field is set to 1.
//  - [4] TEMP (bool): Bit is set to 1 if the ambient temperature is outside the range defined by the TEMPCOLD and TEMPHOT registers. It is set to 0 is the temperature is within this range.
//  - [5] RESERVED (fixed: 0x0): Write 0x00.
//  - [6] CHARGE (bool): Status indicating whether the AEM is currently charging the battery or not. If this bit is set to 0, the storage element is charging. If it is set to 1, the storage element is not charging.
//  - [7] BSTDIS (bool): Status indicating whether the storage charging is enabled or not via the GPIO or I2C. If this bit is set to 0, the storage element charging is enabled. If it is set to 1, the storage element charging is disabled.

#define AEM10900_STATUS_ADDRESS  (0xDU) //!< STATUS register address
#define AEM10900_STATUS_RESET_LE {0x0U} //!< STATUS register reset value
#define AEM10900_STATUS_RESET_BE {0x0U} //!< STATUS register reset value

// Register Layout Struct:

/**
 * @brief Status register of AEM10900.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_status {
  /** @brief Status indicating whether the storage charging is enabled or not via the GPIO or I2C. If this bit is set to 0, the storage element charging is enabled. If it is set to 1, the storage element charging is disabled. */
  bool bstdis;
  /** @brief Status indicating whether the AEM is currently charging the battery or not. If this bit is set to 0, the storage element is charging. If it is set to 1, the storage element is not charging. */
  bool charge;
  /** @brief Status indicating whether the source voltage is higher or lower than the sleep level threshold. If the source voltage is higher than the sleep level then the field is set to 0, else the field is set to 1. */
  bool srcthresh;
  /** @brief Bit is set to 1 if the ambient temperature is outside the range defined by the TEMPCOLD and TEMPHOT registers. It is set to 0 is the temperature is within this range. */
  bool temp;
  /** @brief Status indicating whether the battery voltage is higher or lower than the overcharge level threshold. If the battery voltage rises above VOVCH then the field is set to 1, else it is set to 0. */
  bool vovch;
  /** @brief Status indicating whether the battery is higher or lower than the overdischarge level threshold. If the battery voltage goes below VOVDIS then the field is set to true, else it is set to false. */
  bool vovdis;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_status struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_status_pack_le(const struct aem10900_status *r, uint8_t val[1]) {
  // BSTDIS @ status[7]:
  val[0] &= (uint8_t)~0x80U;
  val[0] |= (uint8_t)(((uint8_t)(r->bstdis << 7)) & 0x80U);
  // CHARGE @ status[6]:
  val[0] &= (uint8_t)~0x40U;
  val[0] |= (uint8_t)(((uint8_t)(r->charge << 6)) & 0x40U);
  // RESERVED @ status[5]:
  val[0] &= (uint8_t)~0x20U;
  val[0] |= (uint8_t)0x0; // Fixed value.
  // SRCTHRESH @ status[3]:
  val[0] &= (uint8_t)~0x8U;
  val[0] |= (uint8_t)(((uint8_t)(r->srcthresh << 3)) & 0x8U);
  // TEMP @ status[4]:
  val[0] &= (uint8_t)~0x10U;
  val[0] |= (uint8_t)(((uint8_t)(r->temp << 4)) & 0x10U);
  // VOVCH @ status[2]:
  val[0] &= (uint8_t)~0x4U;
  val[0] |= (uint8_t)(((uint8_t)(r->vovch << 2)) & 0x4U);
  // VOVDIS @ status[1]:
  val[0] &= (uint8_t)~0x2U;
  val[0] |= (uint8_t)(((uint8_t)(r->vovdis << 1)) & 0x2U);
}

/**
 * @brief Convert @ref struct aem10900_status struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_status_pack_be(const struct aem10900_status *r, uint8_t val[1]) {
  // BSTDIS @ status[7]:
  val[0] &= (uint8_t)~0x80U;
  val[0] |= (uint8_t)(((uint8_t)(r->bstdis << 7)) & 0x80U);
  // CHARGE @ status[6]:
  val[0] &= (uint8_t)~0x40U;
  val[0] |= (uint8_t)(((uint8_t)(r->charge << 6)) & 0x40U);
  // RESERVED @ status[5]:
  val[0] &= (uint8_t)~0x20U;
  val[0] |= (uint8_t)0x0; // Fixed value.
  // SRCTHRESH @ status[3]:
  val[0] &= (uint8_t)~0x8U;
  val[0] |= (uint8_t)(((uint8_t)(r->srcthresh << 3)) & 0x8U);
  // TEMP @ status[4]:
  val[0] &= (uint8_t)~0x10U;
  val[0] |= (uint8_t)(((uint8_t)(r->temp << 4)) & 0x10U);
  // VOVCH @ status[2]:
  val[0] &= (uint8_t)~0x4U;
  val[0] |= (uint8_t)(((uint8_t)(r->vovch << 2)) & 0x4U);
  // VOVDIS @ status[1]:
  val[0] &= (uint8_t)~0x2U;
  val[0] |= (uint8_t)(((uint8_t)(r->vovdis << 1)) & 0x2U);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_status aem10900_status_unpack_le(const uint8_t val[1]) {
  struct aem10900_status r = {0};
  // BSTDIS @ status[7]:
  r.bstdis = (bool)(((val[0] & 0x80U) >> 7));
  // CHARGE @ status[6]:
  r.charge = (bool)(((val[0] & 0x40U) >> 6));
  // SRCTHRESH @ status[3]:
  r.srcthresh = (bool)(((val[0] & 0x8U) >> 3));
  // TEMP @ status[4]:
  r.temp = (bool)(((val[0] & 0x10U) >> 4));
  // VOVCH @ status[2]:
  r.vovch = (bool)(((val[0] & 0x4U) >> 2));
  // VOVDIS @ status[1]:
  r.vovdis = (bool)(((val[0] & 0x2U) >> 1));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_status aem10900_status_unpack_be(const uint8_t val[1]) {
  struct aem10900_status r = {0};
  // BSTDIS @ status[7]:
  r.bstdis = (bool)(((val[0] & 0x80U) >> 7));
  // CHARGE @ status[6]:
  r.charge = (bool)(((val[0] & 0x40U) >> 6));
  // SRCTHRESH @ status[3]:
  r.srcthresh = (bool)(((val[0] & 0x8U) >> 3));
  // TEMP @ status[4]:
  r.temp = (bool)(((val[0] & 0x10U) >> 4));
  // VOVCH @ status[2]:
  r.vovch = (bool)(((val[0] & 0x4U) >> 2));
  // VOVDIS @ status[1]:
  r.vovdis = (bool)(((val[0] & 0x2U) >> 1));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_status(const struct aem10900_status *r) {
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_status_try_unpack_le(const uint8_t val[1], struct aem10900_status *r) {
  *r = aem10900_status_unpack_le(val);
  return aem10900_validate_status(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_status_try_unpack_be(const uint8_t val[1], struct aem10900_status *r) {
  *r = aem10900_status_unpack_be(val);
  return aem10900_validate_status(r);
}

// =============================================================================
// ==== STO Register ===========================================================
// =============================================================================
// Battery Voltage Register.
// Fields:
//  - [7:0] DATA (uint): Voltage level of the storage element (battery) connected to STO. VSTO = 4.8V * DATA / 256

#define AEM10900_STO_ADDRESS  (0x12U) //!< STO register address
#define AEM10900_STO_RESET_LE {0x0U}  //!< STO register reset value
#define AEM10900_STO_RESET_BE {0x0U}  //!< STO register reset value

// Register Layout Struct:

/**
 * @brief Battery Voltage Register.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_sto {
  /** @brief Voltage level of the storage element (battery) connected to STO. VSTO = 4.8V * DATA / 256 */
  uint8_t data;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_sto struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_sto_pack_le(const struct aem10900_sto *r, uint8_t val[1]) {
  // DATA @ sto[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/**
 * @brief Convert @ref struct aem10900_sto struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_sto_pack_be(const struct aem10900_sto *r, uint8_t val[1]) {
  // DATA @ sto[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_sto aem10900_sto_unpack_le(const uint8_t val[1]) {
  struct aem10900_sto r = {0};
  // DATA @ sto[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_sto aem10900_sto_unpack_be(const uint8_t val[1]) {
  struct aem10900_sto r = {0};
  // DATA @ sto[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_sto(const struct aem10900_sto *r) {
  if ((r->data & ~(uint8_t)0xFF) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_sto_try_unpack_le(const uint8_t val[1], struct aem10900_sto *r) {
  *r = aem10900_sto_unpack_le(val);
  return aem10900_validate_sto(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_sto_try_unpack_be(const uint8_t val[1], struct aem10900_sto *r) {
  *r = aem10900_sto_unpack_be(val);
  return aem10900_validate_sto(r);
}

// =============================================================================
// ==== STOMON Register ========================================================
// =============================================================================
// Configures the acquisition rate of the ADC that measures STO voltage.
// Fields:
//  - [2:0] RATE (enum RATE): Acquisition Rate.

#define AEM10900_STOMON_ADDRESS  (0x8U) //!< STOMON register address
#define AEM10900_STOMON_RESET_LE {0x0U} //!< STOMON register reset value
#define AEM10900_STOMON_RESET_BE {0x0U} //!< STOMON register reset value

// Register-specific enums and sub-layouts:

/** @brief Acquisition Rate. */
enum aem10900_rate {
  /** @brief Every 1.024s. Consumption is 0.4nA. */
  AEM10900_RATE_R_1024MS = 0x0U,
  /** @brief Every 128ms. Consumption is 3.2nA. */
  AEM10900_RATE_R_128MS = 0x3U,
  /** @brief Every 256ms. Consumption is 1.6nA. */
  AEM10900_RATE_R_256MS = 0x2U,
  /** @brief Every 512ms. Consumption is 0.8nA. */
  AEM10900_RATE_R_512MS = 0x1U,
  /** @brief Every 64ms. Consumption is 6.4nA. */
  AEM10900_RATE_R_64MS = 0x4U,
};

// Register Layout Struct:

/**
 * @brief Configures the acquisition rate of the ADC that measures STO voltage.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_stomon {
  /** @brief Acquisition Rate. */
  enum aem10900_rate rate;
};

// Enum validation functions:

/**
 * @brief Check if a numeric value is a valid @ref enum aem10900_rate.
 * @returns bool (true/false)
 */
#define AEM10900_IS_VALID_RATE(_VAL_) (                                                            \
  ((_VAL_) <= 0x4U) ? true :                                                                       \
  false )

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_stomon struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_stomon_pack_le(const struct aem10900_stomon *r, uint8_t val[1]) {
  // RATE @ stomon[2:0]:
  val[0] &= (uint8_t)~0x7U;
  val[0] |= (uint8_t)(((uint8_t)r->rate) & 0x7U);
}

/**
 * @brief Convert @ref struct aem10900_stomon struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_stomon_pack_be(const struct aem10900_stomon *r, uint8_t val[1]) {
  // RATE @ stomon[2:0]:
  val[0] &= (uint8_t)~0x7U;
  val[0] |= (uint8_t)(((uint8_t)r->rate) & 0x7U);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_stomon aem10900_stomon_unpack_le(const uint8_t val[1]) {
  struct aem10900_stomon r = {0};
  // RATE @ stomon[2:0]:
  r.rate = (enum aem10900_rate)((val[0] & 0x7U));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_stomon aem10900_stomon_unpack_be(const uint8_t val[1]) {
  struct aem10900_stomon r = {0};
  // RATE @ stomon[2:0]:
  r.rate = (enum aem10900_rate)((val[0] & 0x7U));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_stomon(const struct aem10900_stomon *r) {
  if (!(AEM10900_IS_VALID_RATE(r->rate))) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_stomon_try_unpack_le(const uint8_t val[1], struct aem10900_stomon *r) {
  *r = aem10900_stomon_unpack_le(val);
  return aem10900_validate_stomon(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_stomon_try_unpack_be(const uint8_t val[1], struct aem10900_stomon *r) {
  *r = aem10900_stomon_unpack_be(val);
  return aem10900_validate_stomon(r);
}

// =============================================================================
// ==== TEMP Register ==========================================================
// =============================================================================
// Temperature Data Register.
// Fields:
//  - [7:0] DATA (uint): Temperature data measured by the thermal monitoring circuit. (8bit, 1V REF)

#define AEM10900_TEMP_ADDRESS  (0x11U) //!< TEMP register address
#define AEM10900_TEMP_RESET_LE {0x0U}  //!< TEMP register reset value
#define AEM10900_TEMP_RESET_BE {0x0U}  //!< TEMP register reset value

// Register Layout Struct:

/**
 * @brief Temperature Data Register.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_temp {
  /** @brief Temperature data measured by the thermal monitoring circuit. (8bit, 1V REF) */
  uint8_t data;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_temp struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_temp_pack_le(const struct aem10900_temp *r, uint8_t val[1]) {
  // DATA @ temp[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/**
 * @brief Convert @ref struct aem10900_temp struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_temp_pack_be(const struct aem10900_temp *r, uint8_t val[1]) {
  // DATA @ temp[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->data) & 0xFFU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_temp aem10900_temp_unpack_le(const uint8_t val[1]) {
  struct aem10900_temp r = {0};
  // DATA @ temp[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_temp aem10900_temp_unpack_be(const uint8_t val[1]) {
  struct aem10900_temp r = {0};
  // DATA @ temp[7:0]:
  r.data = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_temp(const struct aem10900_temp *r) {
  if ((r->data & ~(uint8_t)0xFF) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_temp_try_unpack_le(const uint8_t val[1], struct aem10900_temp *r) {
  *r = aem10900_temp_unpack_le(val);
  return aem10900_validate_temp(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_temp_try_unpack_be(const uint8_t val[1], struct aem10900_temp *r) {
  *r = aem10900_temp_unpack_be(val);
  return aem10900_validate_temp(r);
}

// =============================================================================
// ==== TEMPCOLD Register ======================================================
// =============================================================================
// Low temperature threshold for charging. Defaults to 0 degC.
// Fields:
//  - [7:0] THRESH (uint): Cold temperature level, set as THRESH = 256*R_TH(T) / (R_TH(T) + R_DIV).

#define AEM10900_TEMPCOLD_ADDRESS  (0x4U)  //!< TEMPCOLD register address
#define AEM10900_TEMPCOLD_RESET_LE {0x8FU} //!< TEMPCOLD register reset value
#define AEM10900_TEMPCOLD_RESET_BE {0x8FU} //!< TEMPCOLD register reset value

// Register Layout Struct:

/**
 * @brief Low temperature threshold for charging. Defaults to 0 degC.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_tempcold {
  /** @brief Cold temperature level, set as THRESH = 256*R_TH(T) / (R_TH(T) + R_DIV). */
  uint8_t thresh;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_tempcold struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_tempcold_pack_le(const struct aem10900_tempcold *r, uint8_t val[1]) {
  // THRESH @ tempcold[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->thresh) & 0xFFU);
}

/**
 * @brief Convert @ref struct aem10900_tempcold struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_tempcold_pack_be(const struct aem10900_tempcold *r, uint8_t val[1]) {
  // THRESH @ tempcold[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->thresh) & 0xFFU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_tempcold aem10900_tempcold_unpack_le(const uint8_t val[1]) {
  struct aem10900_tempcold r = {0};
  // THRESH @ tempcold[7:0]:
  r.thresh = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_tempcold aem10900_tempcold_unpack_be(const uint8_t val[1]) {
  struct aem10900_tempcold r = {0};
  // THRESH @ tempcold[7:0]:
  r.thresh = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_tempcold(const struct aem10900_tempcold *r) {
  if ((r->thresh & ~(uint8_t)0xFF) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_tempcold_try_unpack_le(const uint8_t val[1], struct aem10900_tempcold *r) {
  *r = aem10900_tempcold_unpack_le(val);
  return aem10900_validate_tempcold(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_tempcold_try_unpack_be(const uint8_t val[1], struct aem10900_tempcold *r) {
  *r = aem10900_tempcold_unpack_be(val);
  return aem10900_validate_tempcold(r);
}

// =============================================================================
// ==== TEMPHOT Register =======================================================
// =============================================================================
// High temperature threshold for charging. Defaults to 45 degC.
// Fields:
//  - [7:0] THRESH (uint): Hot temperature level, set as THRESH = 256*R_TH(T) / (R_TH(T) + R_DIV).

#define AEM10900_TEMPHOT_ADDRESS  (0x5U)  //!< TEMPHOT register address
#define AEM10900_TEMPHOT_RESET_LE {0x2FU} //!< TEMPHOT register reset value
#define AEM10900_TEMPHOT_RESET_BE {0x2FU} //!< TEMPHOT register reset value

// Register Layout Struct:

/**
 * @brief High temperature threshold for charging. Defaults to 45 degC.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_temphot {
  /** @brief Hot temperature level, set as THRESH = 256*R_TH(T) / (R_TH(T) + R_DIV). */
  uint8_t thresh;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_temphot struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_temphot_pack_le(const struct aem10900_temphot *r, uint8_t val[1]) {
  // THRESH @ temphot[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->thresh) & 0xFFU);
}

/**
 * @brief Convert @ref struct aem10900_temphot struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_temphot_pack_be(const struct aem10900_temphot *r, uint8_t val[1]) {
  // THRESH @ temphot[7:0]:
  val[0] &= (uint8_t)~0xFFU;
  val[0] |= (uint8_t)(((uint8_t)r->thresh) & 0xFFU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_temphot aem10900_temphot_unpack_le(const uint8_t val[1]) {
  struct aem10900_temphot r = {0};
  // THRESH @ temphot[7:0]:
  r.thresh = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_temphot aem10900_temphot_unpack_be(const uint8_t val[1]) {
  struct aem10900_temphot r = {0};
  // THRESH @ temphot[7:0]:
  r.thresh = (uint8_t)((val[0] & 0xFFU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_temphot(const struct aem10900_temphot *r) {
  if ((r->thresh & ~(uint8_t)0xFF) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_temphot_try_unpack_le(const uint8_t val[1], struct aem10900_temphot *r) {
  *r = aem10900_temphot_unpack_le(val);
  return aem10900_validate_temphot(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_temphot_try_unpack_be(const uint8_t val[1], struct aem10900_temphot *r) {
  *r = aem10900_temphot_unpack_be(val);
  return aem10900_validate_temphot(r);
}

// =============================================================================
// ==== VERSION Register =======================================================
// =============================================================================
// Version Register.
// Fields:
//  - [3:0] MINOR (fixed: 0x0): Minor revision number.
//  - [7:4] MAJOR (fixed: 0x0): Major revision number.

#define AEM10900_VERSION_ADDRESS  (0x0U) //!< VERSION register address
#define AEM10900_VERSION_RESET_LE {0x0U} //!< VERSION register reset value
#define AEM10900_VERSION_RESET_BE {0x0U} //!< VERSION register reset value

// Register Layout Struct:

/**
 * @brief Version Register.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_version {
  int dummy; // Register contains no variable fields.
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_version struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_version_pack_le(const struct aem10900_version *r, uint8_t val[1]) {
  // MAJOR @ version[7:4]:
  val[0] &= (uint8_t)~0xF0U;
  val[0] |= (uint8_t)0x0; // Fixed value.
  // MINOR @ version[3:0]:
  val[0] &= (uint8_t)~0xFU;
  val[0] |= (uint8_t)0x0; // Fixed value.
  (void)r;
}

/**
 * @brief Convert @ref struct aem10900_version struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_version_pack_be(const struct aem10900_version *r, uint8_t val[1]) {
  // MAJOR @ version[7:4]:
  val[0] &= (uint8_t)~0xF0U;
  val[0] |= (uint8_t)0x0; // Fixed value.
  // MINOR @ version[3:0]:
  val[0] &= (uint8_t)~0xFU;
  val[0] |= (uint8_t)0x0; // Fixed value.
  (void)r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_version aem10900_version_unpack_le(const uint8_t val[1]) {
  struct aem10900_version r = {0};
  (void)val;
  (void)r;
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_version aem10900_version_unpack_be(const uint8_t val[1]) {
  struct aem10900_version r = {0};
  (void)val;
  (void)r;
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_version(const struct aem10900_version *r) {
  (void)r;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_version_try_unpack_le(const uint8_t val[1], struct aem10900_version *r) {
  *r = aem10900_version_unpack_le(val);
  return aem10900_validate_version(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_version_try_unpack_be(const uint8_t val[1], struct aem10900_version *r) {
  *r = aem10900_version_unpack_be(val);
  return aem10900_validate_version(r);
}

// =============================================================================
// ==== VOVCH Register =========================================================
// =============================================================================
// Overcharge level of the storage element.
// Fields:
//  - [5:0] THRESH (uint): Overcharge level of the battery, set as THRESH = (V_ovch - 1.2375) / 0.05625.

#define AEM10900_VOVCH_ADDRESS  (0x3U)  //!< VOVCH register address
#define AEM10900_VOVCH_RESET_LE {0x33U} //!< VOVCH register reset value
#define AEM10900_VOVCH_RESET_BE {0x33U} //!< VOVCH register reset value

// Register Layout Struct:

/**
 * @brief Overcharge level of the storage element.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_vovch {
  /** @brief Overcharge level of the battery, set as THRESH = (V_ovch - 1.2375) / 0.05625. */
  uint8_t thresh;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_vovch struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_vovch_pack_le(const struct aem10900_vovch *r, uint8_t val[1]) {
  // THRESH @ vovch[5:0]:
  val[0] &= (uint8_t)~0x3FU;
  val[0] |= (uint8_t)(((uint8_t)r->thresh) & 0x3FU);
}

/**
 * @brief Convert @ref struct aem10900_vovch struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_vovch_pack_be(const struct aem10900_vovch *r, uint8_t val[1]) {
  // THRESH @ vovch[5:0]:
  val[0] &= (uint8_t)~0x3FU;
  val[0] |= (uint8_t)(((uint8_t)r->thresh) & 0x3FU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_vovch aem10900_vovch_unpack_le(const uint8_t val[1]) {
  struct aem10900_vovch r = {0};
  // THRESH @ vovch[5:0]:
  r.thresh = (uint8_t)((val[0] & 0x3FU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_vovch aem10900_vovch_unpack_be(const uint8_t val[1]) {
  struct aem10900_vovch r = {0};
  // THRESH @ vovch[5:0]:
  r.thresh = (uint8_t)((val[0] & 0x3FU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_vovch(const struct aem10900_vovch *r) {
  if ((r->thresh & ~(uint8_t)0x3F) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_vovch_try_unpack_le(const uint8_t val[1], struct aem10900_vovch *r) {
  *r = aem10900_vovch_unpack_le(val);
  return aem10900_validate_vovch(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_vovch_try_unpack_be(const uint8_t val[1], struct aem10900_vovch *r) {
  *r = aem10900_vovch_unpack_be(val);
  return aem10900_validate_vovch(r);
}

// =============================================================================
// ==== VOVDIS Register ========================================================
// =============================================================================
// Overdischarge level of the storage element.
// Fields:
//  - [5:0] THRESH (uint): Discharge level of the battery, set as THRESH = (V_ovdis - 0.50625) / 0.05625.

#define AEM10900_VOVDIS_ADDRESS  (0x2U)  //!< VOVDIS register address
#define AEM10900_VOVDIS_RESET_LE {0x2DU} //!< VOVDIS register reset value
#define AEM10900_VOVDIS_RESET_BE {0x2DU} //!< VOVDIS register reset value

// Register Layout Struct:

/**
 * @brief Overdischarge level of the storage element.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
struct aem10900_vovdis {
  /** @brief Discharge level of the battery, set as THRESH = (V_ovdis - 0.50625) / 0.05625. */
  uint8_t thresh;
};

// Layout struct conversion functions:

/**
 * @brief Convert @ref struct aem10900_vovdis struct to packed little-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_vovdis_pack_le(const struct aem10900_vovdis *r, uint8_t val[1]) {
  // THRESH @ vovdis[5:0]:
  val[0] &= (uint8_t)~0x3FU;
  val[0] |= (uint8_t)(((uint8_t)r->thresh) & 0x3FU);
}

/**
 * @brief Convert @ref struct aem10900_vovdis struct to packed big-endian value.
 * @note use pack/unpack functions for conversion to/from packed binary value
 */
static inline void aem10900_vovdis_pack_be(const struct aem10900_vovdis *r, uint8_t val[1]) {
  // THRESH @ vovdis[5:0]:
  val[0] &= (uint8_t)~0x3FU;
  val[0] |= (uint8_t)(((uint8_t)r->thresh) & 0x3FU);
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_vovdis aem10900_vovdis_unpack_le(const uint8_t val[1]) {
  struct aem10900_vovdis r = {0};
  // THRESH @ vovdis[5:0]:
  r.thresh = (uint8_t)((val[0] & 0x3FU));
  return r;
}

/** @brief Convert packed {endian} binary value to struct. */
static inline struct aem10900_vovdis aem10900_vovdis_unpack_be(const uint8_t val[1]) {
  struct aem10900_vovdis r = {0};
  // THRESH @ vovdis[5:0]:
  r.thresh = (uint8_t)((val[0] & 0x3FU));
  return r;
}

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
static inline int aem10900_validate_vovdis(const struct aem10900_vovdis *r) {
  if ((r->thresh & ~(uint8_t)0x3F) != 0) return 1;
  return 0;
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_vovdis_try_unpack_le(const uint8_t val[1], struct aem10900_vovdis *r) {
  *r = aem10900_vovdis_unpack_le(val);
  return aem10900_validate_vovdis(r);
}

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
static inline int aem10900_vovdis_try_unpack_be(const uint8_t val[1], struct aem10900_vovdis *r) {
  *r = aem10900_vovdis_unpack_be(val);
  return aem10900_validate_vovdis(r);
}

// =============================================================================
// ==== Generic Macros =========================================================
// =============================================================================

/**
 * @brief Convert struct to packed little-endian binary value.
 * All non-field/always write bits are left untouched.
 */
#define AEM10900_PACK_LE(_struct_ptr_, _val_) _Generic((_struct_ptr_),                             \
    struct aem10900_apm* : aem10900_apm_pack_le,                                                   \
    struct aem10900_apm0* : aem10900_apm0_pack_le,                                                 \
    struct aem10900_apm1* : aem10900_apm1_pack_le,                                                 \
    struct aem10900_apm2* : aem10900_apm2_pack_le,                                                 \
    struct aem10900_ctrl* : aem10900_ctrl_pack_le,                                                 \
    struct aem10900_irqen* : aem10900_irqen_pack_le,                                               \
    struct aem10900_irqflg* : aem10900_irqflg_pack_le,                                             \
    struct aem10900_mpptcfg* : aem10900_mpptcfg_pack_le,                                           \
    struct aem10900_pn0* : aem10900_pn0_pack_le,                                                   \
    struct aem10900_pn1* : aem10900_pn1_pack_le,                                                   \
    struct aem10900_pn2* : aem10900_pn2_pack_le,                                                   \
    struct aem10900_pn3* : aem10900_pn3_pack_le,                                                   \
    struct aem10900_pn4* : aem10900_pn4_pack_le,                                                   \
    struct aem10900_pwr* : aem10900_pwr_pack_le,                                                   \
    struct aem10900_sleep* : aem10900_sleep_pack_le,                                               \
    struct aem10900_src* : aem10900_src_pack_le,                                                   \
    struct aem10900_status* : aem10900_status_pack_le,                                             \
    struct aem10900_sto* : aem10900_sto_pack_le,                                                   \
    struct aem10900_stomon* : aem10900_stomon_pack_le,                                             \
    struct aem10900_temp* : aem10900_temp_pack_le,                                                 \
    struct aem10900_tempcold* : aem10900_tempcold_pack_le,                                         \
    struct aem10900_temphot* : aem10900_temphot_pack_le,                                           \
    struct aem10900_version* : aem10900_version_pack_le,                                           \
    struct aem10900_vovch* : aem10900_vovch_pack_le,                                               \
    struct aem10900_vovdis* : aem10900_vovdis_pack_le                                              \
  )(_struct_ptr_, _val_)

/**
 * @brief Convert struct to packed big-endian binary value.
 * All non-field/always write bits are left untouched.
 */
#define AEM10900_PACK_BE(_struct_ptr_, _val_) _Generic((_struct_ptr_),                             \
    struct aem10900_apm* : aem10900_apm_pack_be,                                                   \
    struct aem10900_apm0* : aem10900_apm0_pack_be,                                                 \
    struct aem10900_apm1* : aem10900_apm1_pack_be,                                                 \
    struct aem10900_apm2* : aem10900_apm2_pack_be,                                                 \
    struct aem10900_ctrl* : aem10900_ctrl_pack_be,                                                 \
    struct aem10900_irqen* : aem10900_irqen_pack_be,                                               \
    struct aem10900_irqflg* : aem10900_irqflg_pack_be,                                             \
    struct aem10900_mpptcfg* : aem10900_mpptcfg_pack_be,                                           \
    struct aem10900_pn0* : aem10900_pn0_pack_be,                                                   \
    struct aem10900_pn1* : aem10900_pn1_pack_be,                                                   \
    struct aem10900_pn2* : aem10900_pn2_pack_be,                                                   \
    struct aem10900_pn3* : aem10900_pn3_pack_be,                                                   \
    struct aem10900_pn4* : aem10900_pn4_pack_be,                                                   \
    struct aem10900_pwr* : aem10900_pwr_pack_be,                                                   \
    struct aem10900_sleep* : aem10900_sleep_pack_be,                                               \
    struct aem10900_src* : aem10900_src_pack_be,                                                   \
    struct aem10900_status* : aem10900_status_pack_be,                                             \
    struct aem10900_sto* : aem10900_sto_pack_be,                                                   \
    struct aem10900_stomon* : aem10900_stomon_pack_be,                                             \
    struct aem10900_temp* : aem10900_temp_pack_be,                                                 \
    struct aem10900_tempcold* : aem10900_tempcold_pack_be,                                         \
    struct aem10900_temphot* : aem10900_temphot_pack_be,                                           \
    struct aem10900_version* : aem10900_version_pack_be,                                           \
    struct aem10900_vovch* : aem10900_vovch_pack_be,                                               \
    struct aem10900_vovdis* : aem10900_vovdis_pack_be                                              \
  )(_struct_ptr_, _val_)

/**
 * @brief Validate struct
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 * Confirms that all enums are valid, and all values fit into respective fields
 */
#define AEM10900_VALIDATE(_struct_ptr_) _Generic((_struct_ptr_),                                   \
    struct aem10900_apm* : aem10900_apm_validate,                                                  \
    struct aem10900_apm0* : aem10900_apm0_validate,                                                \
    struct aem10900_apm1* : aem10900_apm1_validate,                                                \
    struct aem10900_apm2* : aem10900_apm2_validate,                                                \
    struct aem10900_ctrl* : aem10900_ctrl_validate,                                                \
    struct aem10900_irqen* : aem10900_irqen_validate,                                              \
    struct aem10900_irqflg* : aem10900_irqflg_validate,                                            \
    struct aem10900_mpptcfg* : aem10900_mpptcfg_validate,                                          \
    struct aem10900_pn0* : aem10900_pn0_validate,                                                  \
    struct aem10900_pn1* : aem10900_pn1_validate,                                                  \
    struct aem10900_pn2* : aem10900_pn2_validate,                                                  \
    struct aem10900_pn3* : aem10900_pn3_validate,                                                  \
    struct aem10900_pn4* : aem10900_pn4_validate,                                                  \
    struct aem10900_pwr* : aem10900_pwr_validate,                                                  \
    struct aem10900_sleep* : aem10900_sleep_validate,                                              \
    struct aem10900_src* : aem10900_src_validate,                                                  \
    struct aem10900_status* : aem10900_status_validate,                                            \
    struct aem10900_sto* : aem10900_sto_validate,                                                  \
    struct aem10900_stomon* : aem10900_stomon_validate,                                            \
    struct aem10900_temp* : aem10900_temp_validate,                                                \
    struct aem10900_tempcold* : aem10900_tempcold_validate,                                        \
    struct aem10900_temphot* : aem10900_temphot_validate,                                          \
    struct aem10900_version* : aem10900_version_validate,                                          \
    struct aem10900_vovch* : aem10900_vovch_validate,                                              \
    struct aem10900_vovdis* : aem10900_vovdis_validate                                             \
  )(_struct_ptr_)

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
#define AEM10900_TRY_UNPACK_LE(_val_, _struct_ptr_) _Generic((_struct_ptr_),                       \
    struct aem10900_apm* : aem10900_apm_try_unpack_le,                                             \
    struct aem10900_apm0* : aem10900_apm0_try_unpack_le,                                           \
    struct aem10900_apm1* : aem10900_apm1_try_unpack_le,                                           \
    struct aem10900_apm2* : aem10900_apm2_try_unpack_le,                                           \
    struct aem10900_ctrl* : aem10900_ctrl_try_unpack_le,                                           \
    struct aem10900_irqen* : aem10900_irqen_try_unpack_le,                                         \
    struct aem10900_irqflg* : aem10900_irqflg_try_unpack_le,                                       \
    struct aem10900_mpptcfg* : aem10900_mpptcfg_try_unpack_le,                                     \
    struct aem10900_pn0* : aem10900_pn0_try_unpack_le,                                             \
    struct aem10900_pn1* : aem10900_pn1_try_unpack_le,                                             \
    struct aem10900_pn2* : aem10900_pn2_try_unpack_le,                                             \
    struct aem10900_pn3* : aem10900_pn3_try_unpack_le,                                             \
    struct aem10900_pn4* : aem10900_pn4_try_unpack_le,                                             \
    struct aem10900_pwr* : aem10900_pwr_try_unpack_le,                                             \
    struct aem10900_sleep* : aem10900_sleep_try_unpack_le,                                         \
    struct aem10900_src* : aem10900_src_try_unpack_le,                                             \
    struct aem10900_status* : aem10900_status_try_unpack_le,                                       \
    struct aem10900_sto* : aem10900_sto_try_unpack_le,                                             \
    struct aem10900_stomon* : aem10900_stomon_try_unpack_le,                                       \
    struct aem10900_temp* : aem10900_temp_try_unpack_le,                                           \
    struct aem10900_tempcold* : aem10900_tempcold_try_unpack_le,                                   \
    struct aem10900_temphot* : aem10900_temphot_try_unpack_le,                                     \
    struct aem10900_version* : aem10900_version_try_unpack_le,                                     \
    struct aem10900_vovch* : aem10900_vovch_try_unpack_le,                                         \
    struct aem10900_vovdis* : aem10900_vovdis_try_unpack_le                                        \
  )(_val_, _struct_ptr_)

/**
 * @brief Attempt to convert packed {endian} binary value to struct.
 * @returns 0 if valid.
 * @returns the position of the first invalid field if invalid.
 */
#define AEM10900_TRY_UNPACK_BE(_val_, _struct_ptr_) _Generic((_struct_ptr_),                       \
    struct aem10900_apm* : aem10900_apm_try_unpack_be,                                             \
    struct aem10900_apm0* : aem10900_apm0_try_unpack_be,                                           \
    struct aem10900_apm1* : aem10900_apm1_try_unpack_be,                                           \
    struct aem10900_apm2* : aem10900_apm2_try_unpack_be,                                           \
    struct aem10900_ctrl* : aem10900_ctrl_try_unpack_be,                                           \
    struct aem10900_irqen* : aem10900_irqen_try_unpack_be,                                         \
    struct aem10900_irqflg* : aem10900_irqflg_try_unpack_be,                                       \
    struct aem10900_mpptcfg* : aem10900_mpptcfg_try_unpack_be,                                     \
    struct aem10900_pn0* : aem10900_pn0_try_unpack_be,                                             \
    struct aem10900_pn1* : aem10900_pn1_try_unpack_be,                                             \
    struct aem10900_pn2* : aem10900_pn2_try_unpack_be,                                             \
    struct aem10900_pn3* : aem10900_pn3_try_unpack_be,                                             \
    struct aem10900_pn4* : aem10900_pn4_try_unpack_be,                                             \
    struct aem10900_pwr* : aem10900_pwr_try_unpack_be,                                             \
    struct aem10900_sleep* : aem10900_sleep_try_unpack_be,                                         \
    struct aem10900_src* : aem10900_src_try_unpack_be,                                             \
    struct aem10900_status* : aem10900_status_try_unpack_be,                                       \
    struct aem10900_sto* : aem10900_sto_try_unpack_be,                                             \
    struct aem10900_stomon* : aem10900_stomon_try_unpack_be,                                       \
    struct aem10900_temp* : aem10900_temp_try_unpack_be,                                           \
    struct aem10900_tempcold* : aem10900_tempcold_try_unpack_be,                                   \
    struct aem10900_temphot* : aem10900_temphot_try_unpack_be,                                     \
    struct aem10900_version* : aem10900_version_try_unpack_be,                                     \
    struct aem10900_vovch* : aem10900_vovch_try_unpack_be,                                         \
    struct aem10900_vovdis* : aem10900_vovdis_try_unpack_be                                        \
  )(_val_, _struct_ptr_)

#endif /* REGINALD_AEM10900_REG_H */
// clang-format on
