#![allow(clippy::unnecessary_cast)]
#![allow(clippy::module_name_repetitions)]
#![allow(unused_imports)]
//! # `AEM10900` Registers.
//!
//! ## Infos
//!
//! Generated using reginald from `../../aem10900.yaml`.
//! 
//! Listing file author: Silvano Cortesi
//!
//! Listing file notice:
//!   Licensed under LGPL-3.0
//!   File Version: 0.9.2
//!
//! ## Register Overview
//! | Address | Name         | Brief                                                                                                                                       |
//! | ------- | ------------ | ------------------------------------------------------------------------------------------------------------------------------------------- |
//! | 0x00    | [`Version`]  | Version Register.                                                                                                                           |
//! | 0x01    | [`Mpptcfg`]  | MPPT timing and ratio configuration.                                                                                                        |
//! | 0x02    | [`Vovdis`]   | Overdischarge level of the storage element.                                                                                                 |
//! | 0x03    | [`Vovch`]    | Overcharge level of the storage element.                                                                                                    |
//! | 0x04    | [`Tempcold`] | Low temperature threshold for charging. Defaults to 0 degC.                                                                                 |
//! | 0x05    | [`Temphot`]  | High temperature threshold for charging. Defaults to 45 degC.                                                                               |
//! | 0x06    | [`Pwr`]      | Register dedicated to the power settings of the AEM10900.                                                                                   |
//! | 0x07    | [`Sleep`]    | The Sleep register enables the sleep mode and sets the conditions for entering the sleep state.                                             |
//! | 0x08    | [`Stomon`]   | Configures the acquisition rate of the ADC that measures STO voltage.                                                                       |
//! | 0x09    | [`Apm`]      | Average Power Monitoring Control Register.                                                                                                  |
//! | 0x0A    | [`Irqen`]    | IRQ Enable Register.                                                                                                                        |
//! | 0x0B    | [`Ctrl`]     | Control register for I2C configuration.                                                                                                     |
//! | 0x0C    | [`Irqflg`]   | The IRQFLG register contains all interrupt flags, corresponding to those enabled in the IRQEN register. This register is reseted when read. |
//! | 0x0D    | [`Status`]   | Status register of AEM10900.                                                                                                                |
//! | 0x0E    | [`Apm0`]     | APM Data Register 0.                                                                                                                        |
//! | 0x0F    | [`Apm1`]     | APM Data Register 1.                                                                                                                        |
//! | 0x10    | [`Apm2`]     | APM Data Register 2.                                                                                                                        |
//! | 0x11    | [`Temp`]     | Temperature Data Register.                                                                                                                  |
//! | 0x12    | [`Sto`]      | Battery Voltage Register.                                                                                                                   |
//! | 0x13    | [`Src`]      | Source Voltage Register.                                                                                                                    |
//! | 0xE0    | [`Pn0`]      | Part Number Register 0.                                                                                                                     |
//! | 0xE1    | [`Pn1`]      | Part Number Register 1.                                                                                                                     |
//! | 0xE2    | [`Pn2`]      | Part Number Register 2.                                                                                                                     |
//! | 0xE3    | [`Pn3`]      | Part Number Register 3.                                                                                                                     |
//! | 0xE4    | [`Pn4`]      | Part Number Register 4.                                                                                                                     |

// ==== Traits =================================================================

use core::convert::Infallible;
use core::fmt::{Debug, Display};

// Struct to bytes converstion:
pub trait ToBytes<const N: usize>: Sized {
    fn to_le_bytes(&self) -> [u8; N];

    #[inline(always)]
    fn to_be_bytes(&self) -> [u8; N] {
        let mut val = self.to_le_bytes();
        val.reverse();
        val
    }
}

// Bytes to struct conversion (fallible):
pub trait TryFromBytes<const N: usize>: Sized {
    type Error;

    fn try_from_le_bytes(val: &[u8; N]) -> Result<Self, Self::Error>;

    #[inline(always)]
    fn try_from_be_bytes(val: &[u8; N]) -> Result<Self, Self::Error> {
        let mut val = *val;
        val.reverse();
        Self::try_from_le_bytes(&val)
    }
}

// Bytes to struct conversion (infallible):
pub trait FromBytes<const N: usize>: Sized {
    fn from_le_bytes(val: &[u8; N]) -> Self;

    #[inline(always)]
    fn from_be_bytes(val: &[u8; N]) -> Self {
        let mut val = *val;
        val.reverse();
        Self::from_le_bytes(&val)
    }
}

// Implement fallible conversion for infallible conversion:
impl<const N: usize, T> TryFromBytes<N> for T
where
    T: FromBytes<N>,
{
    type Error = Infallible;

    #[inline(always)]
    fn try_from_le_bytes(val: &[u8; N]) -> Result<Self, Self::Error> {
        Ok(Self::from_le_bytes(val))
    }

    #[inline(always)]
    fn try_from_be_bytes(val: &[u8; N]) -> Result<Self, Self::Error> {
        Ok(Self::from_be_bytes(val))
    }
}

// Bytes to struct conversion (infallible, but possibly lossy):
pub trait FromMaskedBytes<const N: usize>: Sized {
    fn from_masked_le_bytes(val: &[u8; N]) -> Self;

    #[inline(always)]
    fn from_masked_be_bytes(val: &[u8; N]) -> Self {
        let mut val = *val;
        val.reverse();
        Self::from_masked_le_bytes(&val)
    }
}

// Implement possibly conversion for infallible conversion:
impl<const N: usize, T> FromMaskedBytes<N> for T
where
    T: FromBytes<N>,
{
    fn from_masked_le_bytes(val: &[u8; N]) -> Self {
        Self::from_le_bytes(val)
    }

    #[inline(always)]
    fn from_masked_be_bytes(val: &[u8; N]) -> Self {
        Self::from_be_bytes(val)
    }
}

// Errors:
#[derive(Debug, PartialEq, Clone)]
pub struct FromBytesError {
    pub pos: usize,
}

impl Display for FromBytesError {
    fn fmt(&self, f: &mut core::fmt::Formatter<'_>) -> core::fmt::Result {
        write!(f, "Failed to unpack field at bit {}", self.pos)
    }
}

// Register properties:
pub enum ResetVal<const N: usize> {
    BigEndian([u8; N]),
    LittleEndian([u8; N]),
}

pub trait Register<const N: usize, A> {
    const ADDRESS: A;
    const RESET_VAL: Option<ResetVal<N>>;

    fn reset_val_le() -> Option<[u8; N]> {
        match Self::RESET_VAL {
            None => None,
            Some(ResetVal::LittleEndian(val_le)) => Some(val_le),
            Some(ResetVal::BigEndian(val)) => {
                let mut val = val;
                val.reverse();
                Some(val)
            }
        }
    }

    fn reset_val_be() -> Option<[u8; N]> {
        match Self::RESET_VAL {
            None => None,
            Some(ResetVal::LittleEndian(val)) => {
                let mut val = val;
                val.reverse();
                Some(val)
            }
            Some(ResetVal::BigEndian(val_be)) => Some(val_be),
        }
    }
}

// ==== `VERSION` Register =====================================================

/// `VERSION` Register
///
/// Address: 0x0
///
/// Reset Value: 0x0
///
/// Version Register.
///
/// Fixed bits:
/// - `[7:0]` = 0b0
#[derive(Debug, PartialEq)]
pub struct Version {
}

/// Register Properties
impl Register<1, u8> for Version {
    const ADDRESS: u8 = 0x0;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x0]));
}

/// Reset Value
impl Default for Version {
    fn default() -> Self {
        Self {
        }
    }
}

// ==== `MPPTCFG` Register =====================================================

/// `MPPTCFG` Register
///
/// Address: 0x1
///
/// Reset Value: 0x77
///
/// MPPT timing and ratio configuration.
#[derive(Debug, PartialEq)]
pub struct Mpptcfg {
    /// MPP ratio
    ///
    /// Bits: `[3:0]`
    pub ratio: Ratio,
    /// MPP Timing (T_xx_yy) with xx being T_VOC and yy being T_MPPT.
    ///
    /// Bits: `[6:4]`
    pub timing: Timing,
}

// Register-specific sub-layouts:
/// MPP ratio
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Ratio {
    R35, // 0x8
    R50, // 0x9
    R60, // 0x3
    R65, // 0x2
    R70, // 0x6
    R75, // 0x5
    R80, // 0x7
    R85, // 0x4
    R90, // 0x1
    RZmpp, // 0x0
}

/// MPP Timing (T_xx_yy) with xx being T_VOC and yy being T_MPPT.
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Timing {
    T256ms16384ms, // 0x1
    T2ms128ms, // 0x5
    T2ms256ms, // 0x7
    T2ms64ms, // 0x0
    T4ms256ms, // 0x4
    T4ms512ms, // 0x6
    T64ms4096ms, // 0x2
    T8ms1024ms, // 0x3
}

/// Register Properties
impl Register<1, u8> for Mpptcfg {
    const ADDRESS: u8 = 0x1;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x77]));
}

/// Reset Value
impl Default for Mpptcfg {
    fn default() -> Self {
        Self {
            ratio: Ratio::R80,
            timing: Timing::T2ms256ms,
        }
    }
}

// ==== `VOVDIS` Register ======================================================

/// `VOVDIS` Register
///
/// Address: 0x2
///
/// Reset Value: 0x2D
///
/// Overdischarge level of the storage element.
#[derive(Debug, PartialEq)]
pub struct Vovdis {
    /// Discharge level of the battery, set as THRESH = (V_ovdis - 0.50625) / 0.05625.
    ///
    /// Bits: `[5:0]`
    pub thresh: u8,
}

/// Register Properties
impl Register<1, u8> for Vovdis {
    const ADDRESS: u8 = 0x2;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x2D]));
}

/// Reset Value
impl Default for Vovdis {
    fn default() -> Self {
        Self {
            thresh: 0x2D,
        }
    }
}

// ==== `VOVCH` Register =======================================================

/// `VOVCH` Register
///
/// Address: 0x3
///
/// Reset Value: 0x33
///
/// Overcharge level of the storage element.
#[derive(Debug, PartialEq)]
pub struct Vovch {
    /// Overcharge level of the battery, set as THRESH = (V_ovch - 1.2375) / 0.05625.
    ///
    /// Bits: `[5:0]`
    pub thresh: u8,
}

/// Register Properties
impl Register<1, u8> for Vovch {
    const ADDRESS: u8 = 0x3;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x33]));
}

/// Reset Value
impl Default for Vovch {
    fn default() -> Self {
        Self {
            thresh: 0x33,
        }
    }
}

// ==== `TEMPCOLD` Register ====================================================

/// `TEMPCOLD` Register
///
/// Address: 0x4
///
/// Reset Value: 0x8F
///
/// Low temperature threshold for charging. Defaults to 0 degC.
#[derive(Debug, PartialEq)]
pub struct Tempcold {
    /// Cold temperature level, set as THRESH = 256*R_TH(T) / (R_TH(T) + R_DIV).
    ///
    /// Bits: `[7:0]`
    pub thresh: u8,
}

/// Register Properties
impl Register<1, u8> for Tempcold {
    const ADDRESS: u8 = 0x4;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x8F]));
}

/// Reset Value
impl Default for Tempcold {
    fn default() -> Self {
        Self {
            thresh: 0x8F,
        }
    }
}

// ==== `TEMPHOT` Register =====================================================

/// `TEMPHOT` Register
///
/// Address: 0x5
///
/// Reset Value: 0x2F
///
/// High temperature threshold for charging. Defaults to 45 degC.
#[derive(Debug, PartialEq)]
pub struct Temphot {
    /// Hot temperature level, set as THRESH = 256*R_TH(T) / (R_TH(T) + R_DIV).
    ///
    /// Bits: `[7:0]`
    pub thresh: u8,
}

/// Register Properties
impl Register<1, u8> for Temphot {
    const ADDRESS: u8 = 0x5;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x2F]));
}

/// Reset Value
impl Default for Temphot {
    fn default() -> Self {
        Self {
            thresh: 0x2F,
        }
    }
}

// ==== `PWR` Register =========================================================

/// `PWR` Register
///
/// Address: 0x6
///
/// Reset Value: 0x7
///
/// Register dedicated to the power settings of the AEM10900.
///
/// Fixed bits:
/// - `[7:4]` = 0b0
#[derive(Debug, PartialEq)]
pub struct Pwr {
    /// High-power mode enable. True means automatic change between modes, False means disabled.
    ///
    /// Bits: `[1]`
    pub hpen: bool,
    /// Keep alive enable. True means VINT supplied by STO, False means VINT supplied by SRC.
    ///
    /// Bits: `[0]`
    pub keepalen: bool,
    /// Battery charging disable. True means battery charging is disabled.
    ///
    /// Bits: `[3]`
    pub stochdis: bool,
    /// Temperature monitoring enable. True enables monitoring of ambient temperature.
    ///
    /// Bits: `[2]`
    pub tmonen: bool,
}

/// Register Properties
impl Register<1, u8> for Pwr {
    const ADDRESS: u8 = 0x6;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x7]));
}

/// Reset Value
impl Default for Pwr {
    fn default() -> Self {
        Self {
            hpen: true,
            keepalen: true,
            stochdis: false,
            tmonen: true,
        }
    }
}

// ==== `SLEEP` Register =======================================================

/// `SLEEP` Register
///
/// Address: 0x7
///
/// Reset Value: 0x1
///
/// The Sleep register enables the sleep mode and sets the conditions for entering the sleep state.
#[derive(Debug, PartialEq)]
pub struct Sleep {
    /// The field enables sleep state when set to True (depending then on source voltage).
    ///
    /// Bits: `[0]`
    pub en: bool,
    /// This field sets the source voltage threshold below which the AEM10900 enters sleep state.
    ///
    /// Bits: `[3:1]`
    pub srcthresh: Srcthresh,
}

// Register-specific sub-layouts:
/// This field sets the source voltage threshold below which the AEM10900 enters sleep state.
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Srcthresh {
    /// Sleep threshold at 0.202V.
    V202mv, // 0x1
    /// Sleep threshold at 0.255V.
    V255mv, // 0x2
    /// Sleep threshold at 0.300V.
    V300mv, // 0x3
    /// Sleep threshold at 0.360V.
    V360mv, // 0x4
    /// Sleep threshold at 0.405V.
    V405mv, // 0x5
    /// Sleep threshold at 0.510V.
    V510mv, // 0x6
    /// Sleep threshold at 0.600V.
    V600mv, // 0x7
    /// Unknown what this option means.
    VMv, // 0x0
}

/// Register Properties
impl Register<1, u8> for Sleep {
    const ADDRESS: u8 = 0x7;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x1]));
}

/// Reset Value
impl Default for Sleep {
    fn default() -> Self {
        Self {
            en: true,
            srcthresh: Srcthresh::VMv,
        }
    }
}

// ==== `STOMON` Register ======================================================

/// `STOMON` Register
///
/// Address: 0x8
///
/// Reset Value: 0x0
///
/// Configures the acquisition rate of the ADC that measures STO voltage.
#[derive(Debug, PartialEq)]
pub struct Stomon {
    /// Acquisition Rate.
    ///
    /// Bits: `[2:0]`
    pub rate: Rate,
}

// Register-specific sub-layouts:
/// Acquisition Rate.
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Rate {
    /// Every 1.024s. Consumption is 0.4nA.
    R1024ms, // 0x0
    /// Every 128ms. Consumption is 3.2nA.
    R128ms, // 0x3
    /// Every 256ms. Consumption is 1.6nA.
    R256ms, // 0x2
    /// Every 512ms. Consumption is 0.8nA.
    R512ms, // 0x1
    /// Every 64ms. Consumption is 6.4nA.
    R64ms, // 0x4
}

/// Register Properties
impl Register<1, u8> for Stomon {
    const ADDRESS: u8 = 0x8;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x0]));
}

/// Reset Value
impl Default for Stomon {
    fn default() -> Self {
        Self {
            rate: Rate::R1024ms,
        }
    }
}

// ==== `APM` Register =========================================================

/// `APM` Register
///
/// Address: 0x9
///
/// Reset Value: 0x0
///
/// Average Power Monitoring Control Register.
#[derive(Debug, PartialEq)]
pub struct Apm {
    /// Enable APM. When set to True, APM is enabled.
    ///
    /// Bits: `[0]`
    pub en: bool,
    /// APM operating mode. Pulse Counter Mode or Power Meter Mode.
    ///
    /// Bits: `[1]`
    pub mode: Mode,
    /// Select the APM computation window (noted TA in Section 9.4). The energy transferred is integrated over this configurable time window. (W_xx_yy) with xx being computation window and yy being refresh rate.
    ///
    /// Bits: `[3:2]`
    pub window: Window,
}

// Register-specific sub-layouts:
/// APM operating mode. Pulse Counter Mode or Power Meter Mode.
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Mode {
    /// Power meter mode - the number of pulses during a period is multiplied by a value to obtain the energy that has been transferred taking into account the efficiency of the AEM10900.
    PowerMeter, // 0x1
    /// Pulse counter mode - the AEM10900 counts the number of current pulses drawn by the boost converter.
    PulseCounter, // 0x0
}

/// Select the APM computation window (noted TA in Section 9.4). The energy transferred is integrated over this configurable time window. (W_xx_yy) with xx being computation window and yy being refresh rate.
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Window {
    W128ms256ms, // 0x0
    W32ms64ms, // 0x2
    W64ms128ms, // 0x1
}

/// Register Properties
impl Register<1, u8> for Apm {
    const ADDRESS: u8 = 0x9;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x0]));
}

/// Reset Value
impl Default for Apm {
    fn default() -> Self {
        Self {
            en: false,
            mode: Mode::PulseCounter,
            window: Window::W128ms256ms,
        }
    }
}

// ==== `IRQEN` Register =======================================================

/// `IRQEN` Register
///
/// Address: 0xA
///
/// Reset Value: 0x1
///
/// IRQ Enable Register.
#[derive(Debug, PartialEq)]
pub struct Irqen {
    /// Enable IRQ for completion of APM measurement.
    ///
    /// Bits: `[5]`
    pub apmdone: bool,
    /// Enable IRQ for signaling an error in the APM.
    ///
    /// Bits: `[6]`
    pub apmerr: bool,
    /// Enable IRQ for I2C ready status.
    ///
    /// Bits: `[0]`
    pub i2crdy: bool,
    /// Enable IRQ for SRC LOW threshold crossing (set in sleep register).
    ///
    /// Bits: `[3]`
    pub srcthresh: bool,
    /// Enable IRQ when temperature crosses temperature limits.
    ///
    /// Bits: `[4]`
    pub temp: bool,
    /// Enable IRQ for overcharge detection.
    ///
    /// Bits: `[2]`
    pub vovch: bool,
    /// Enable IRQ for overdischarge detection.
    ///
    /// Bits: `[1]`
    pub vovdis: bool,
}

/// Register Properties
impl Register<1, u8> for Irqen {
    const ADDRESS: u8 = 0xA;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x1]));
}

/// Reset Value
impl Default for Irqen {
    fn default() -> Self {
        Self {
            apmdone: false,
            apmerr: false,
            i2crdy: true,
            srcthresh: false,
            temp: false,
            vovch: false,
            vovdis: false,
        }
    }
}

// ==== `CTRL` Register ========================================================

/// `CTRL` Register
///
/// Address: 0xB
///
/// Reset Value: 0x0
///
/// Control register for I2C configuration.
///
/// Fixed bits:
/// - `[1]` = 0b0
#[derive(Debug, PartialEq)]
pub struct Ctrl {
    /// This field indicates whether the synchronization from the I2C registers to the system registers is ongoing or not.
    ///
    /// Bits: `[2]`
    pub syncbusy: Syncbusy,
    /// This field is used to control the source of the AEM10900 configuration (GPIO or I2C).
    ///
    /// Bits: `[0]`
    pub update: Update,
}

// Register-specific sub-layouts:
/// This field indicates whether the synchronization from the I2C registers to the system registers is ongoing or not.
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Syncbusy {
    /// CTRL register not synchronizing.
    Nsync, // 0x0
    /// CTRL register synchronizing.
    Sync, // 0x1
}

/// This field is used to control the source of the AEM10900 configuration (GPIO or I2C).
#[derive(Clone, Copy, Debug, PartialEq)]
pub enum Update {
    /// Load configurations from the GPIOs
    Gpio, // 0x0
    /// Load configurations from the I2C registers
    I2c, // 0x1
}

/// Register Properties
impl Register<1, u8> for Ctrl {
    const ADDRESS: u8 = 0xB;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x0]));
}

/// Reset Value
impl Default for Ctrl {
    fn default() -> Self {
        Self {
            syncbusy: Syncbusy::Nsync,
            update: Update::Gpio,
        }
    }
}

// ==== `IRQFLG` Register ======================================================

/// `IRQFLG` Register
///
/// Address: 0xC
///
/// Reset Value: 0x0
///
/// The IRQFLG register contains all interrupt flags, corresponding to those enabled in the IRQEN register. This register is reseted when read.
#[derive(Debug, PartialEq)]
pub struct Irqflg {
    /// Flag indicating completion of APM measurement.
    ///
    /// Bits: `[5]`
    pub apmdone: bool,
    /// Flag indicating error in the APM.
    ///
    /// Bits: `[6]`
    pub apmerr: bool,
    /// Flag indicating I2C ready status.
    ///
    /// Bits: `[0]`
    pub i2crdy: bool,
    /// Flag indicating SRC LOW threshold crossing (set in sleep register).
    ///
    /// Bits: `[3]`
    pub srcthresh: bool,
    /// Flag indicating temperature crossed temperature limits.
    ///
    /// Bits: `[4]`
    pub temp: bool,
    /// Flag indicating overcharge detection.
    ///
    /// Bits: `[2]`
    pub vovch: bool,
    /// Flag indicating overdischarge detection.
    ///
    /// Bits: `[1]`
    pub vovdis: bool,
}

/// Register Properties
impl Register<1, u8> for Irqflg {
    const ADDRESS: u8 = 0xC;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x0]));
}

/// Reset Value
impl Default for Irqflg {
    fn default() -> Self {
        Self {
            apmdone: false,
            apmerr: false,
            i2crdy: false,
            srcthresh: false,
            temp: false,
            vovch: false,
            vovdis: false,
        }
    }
}

// ==== `STATUS` Register ======================================================

/// `STATUS` Register
///
/// Address: 0xD
///
/// Reset Value: 0x0
///
/// Status register of AEM10900.
///
/// Fixed bits:
/// - `[5]` = 0b0
#[derive(Debug, PartialEq)]
pub struct Status {
    /// Status indicating whether the storage charging is enabled or not via the GPIO or I2C. If this bit is set to 0, the storage element charging is enabled. If it is set to 1, the storage element charging is disabled.
    ///
    /// Bits: `[7]`
    pub bstdis: bool,
    /// Status indicating whether the AEM is currently charging the battery or not. If this bit is set to 0, the storage element is charging. If it is set to 1, the storage element is not charging.
    ///
    /// Bits: `[6]`
    pub charge: bool,
    /// Status indicating whether the source voltage is higher or lower than the sleep level threshold. If the source voltage is higher than the sleep level then the field is set to 0, else the field is set to 1.
    ///
    /// Bits: `[3]`
    pub srcthresh: bool,
    /// Bit is set to 1 if the ambient temperature is outside the range defined by the TEMPCOLD and TEMPHOT registers. It is set to 0 is the temperature is within this range.
    ///
    /// Bits: `[4]`
    pub temp: bool,
    /// Status indicating whether the battery voltage is higher or lower than the overcharge level threshold. If the battery voltage rises above VOVCH then the field is set to 1, else it is set to 0.
    ///
    /// Bits: `[2]`
    pub vovch: bool,
    /// Status indicating whether the battery is higher or lower than the overdischarge level threshold. If the battery voltage goes below VOVDIS then the field is set to true, else it is set to false.
    ///
    /// Bits: `[1]`
    pub vovdis: bool,
}

/// Register Properties
impl Register<1, u8> for Status {
    const ADDRESS: u8 = 0xD;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x0]));
}

/// Reset Value
impl Default for Status {
    fn default() -> Self {
        Self {
            bstdis: false,
            charge: false,
            srcthresh: false,
            temp: false,
            vovch: false,
            vovdis: false,
        }
    }
}

// ==== `APM0` Register ========================================================

/// `APM0` Register
///
/// Address: 0xE
///
/// Reset Value: 0x0
///
/// APM Data Register 0.
#[derive(Debug, PartialEq)]
pub struct Apm0 {
    /// Lower byte of APM data.
    ///
    /// Bits: `[7:0]`
    pub data: u8,
}

/// Register Properties
impl Register<1, u8> for Apm0 {
    const ADDRESS: u8 = 0xE;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x0]));
}

/// Reset Value
impl Default for Apm0 {
    fn default() -> Self {
        Self {
            data: 0x0,
        }
    }
}

// ==== `APM1` Register ========================================================

/// `APM1` Register
///
/// Address: 0xF
///
/// Reset Value: 0x0
///
/// APM Data Register 1.
#[derive(Debug, PartialEq)]
pub struct Apm1 {
    /// Middle byte of APM data.
    ///
    /// Bits: `[7:0]`
    pub data: u8,
}

/// Register Properties
impl Register<1, u8> for Apm1 {
    const ADDRESS: u8 = 0xF;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x0]));
}

/// Reset Value
impl Default for Apm1 {
    fn default() -> Self {
        Self {
            data: 0x0,
        }
    }
}

// ==== `APM2` Register ========================================================

/// `APM2` Register
///
/// Address: 0x10
///
/// Reset Value: 0x0
///
/// APM Data Register 2.
#[derive(Debug, PartialEq)]
pub struct Apm2 {
    /// Upper byte of APM data.
    ///
    /// Bits: `[7:0]`
    pub data: u8,
}

/// Register Properties
impl Register<1, u8> for Apm2 {
    const ADDRESS: u8 = 0x10;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x0]));
}

/// Reset Value
impl Default for Apm2 {
    fn default() -> Self {
        Self {
            data: 0x0,
        }
    }
}

// ==== `TEMP` Register ========================================================

/// `TEMP` Register
///
/// Address: 0x11
///
/// Reset Value: 0x0
///
/// Temperature Data Register.
#[derive(Debug, PartialEq)]
pub struct Temp {
    /// Temperature data measured by the thermal monitoring circuit. (8bit, 1V REF)
    ///
    /// Bits: `[7:0]`
    pub data: u8,
}

/// Register Properties
impl Register<1, u8> for Temp {
    const ADDRESS: u8 = 0x11;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x0]));
}

/// Reset Value
impl Default for Temp {
    fn default() -> Self {
        Self {
            data: 0x0,
        }
    }
}

// ==== `STO` Register =========================================================

/// `STO` Register
///
/// Address: 0x12
///
/// Reset Value: 0x0
///
/// Battery Voltage Register.
#[derive(Debug, PartialEq)]
pub struct Sto {
    /// Voltage level of the storage element (battery) connected to STO. VSTO = 4.8V * DATA / 256
    ///
    /// Bits: `[7:0]`
    pub data: u8,
}

/// Register Properties
impl Register<1, u8> for Sto {
    const ADDRESS: u8 = 0x12;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x0]));
}

/// Reset Value
impl Default for Sto {
    fn default() -> Self {
        Self {
            data: 0x0,
        }
    }
}

// ==== `SRC` Register =========================================================

/// `SRC` Register
///
/// Address: 0x13
///
/// Reset Value: 0x0
///
/// Source Voltage Register.
#[derive(Debug, PartialEq)]
pub struct Src {
    /// Voltage level of the energy source connected to SRC. Conversion according to table 32 in DS v1.5
    ///
    /// Bits: `[7:0]`
    pub data: u8,
}

/// Register Properties
impl Register<1, u8> for Src {
    const ADDRESS: u8 = 0x13;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x0]));
}

/// Reset Value
impl Default for Src {
    fn default() -> Self {
        Self {
            data: 0x0,
        }
    }
}

// ==== `PN0` Register =========================================================

/// `PN0` Register
///
/// Address: 0xE0
///
/// Reset Value: 0x30
///
/// Part Number Register 0.
#[derive(Debug, PartialEq)]
pub struct Pn0 {
    /// Part number identification byte 0.
    ///
    /// Bits: `[7:0]`
    pub data: u8,
}

/// Register Properties
impl Register<1, u8> for Pn0 {
    const ADDRESS: u8 = 0xE0;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x30]));
}

/// Reset Value
impl Default for Pn0 {
    fn default() -> Self {
        Self {
            data: 0x30,
        }
    }
}

// ==== `PN1` Register =========================================================

/// `PN1` Register
///
/// Address: 0xE1
///
/// Reset Value: 0x30
///
/// Part Number Register 1.
#[derive(Debug, PartialEq)]
pub struct Pn1 {
    /// Part number identification byte 1.
    ///
    /// Bits: `[7:0]`
    pub data: u8,
}

/// Register Properties
impl Register<1, u8> for Pn1 {
    const ADDRESS: u8 = 0xE1;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x30]));
}

/// Reset Value
impl Default for Pn1 {
    fn default() -> Self {
        Self {
            data: 0x30,
        }
    }
}

// ==== `PN2` Register =========================================================

/// `PN2` Register
///
/// Address: 0xE2
///
/// Reset Value: 0x39
///
/// Part Number Register 2.
#[derive(Debug, PartialEq)]
pub struct Pn2 {
    /// Part number identification byte 2.
    ///
    /// Bits: `[7:0]`
    pub data: u8,
}

/// Register Properties
impl Register<1, u8> for Pn2 {
    const ADDRESS: u8 = 0xE2;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x39]));
}

/// Reset Value
impl Default for Pn2 {
    fn default() -> Self {
        Self {
            data: 0x39,
        }
    }
}

// ==== `PN3` Register =========================================================

/// `PN3` Register
///
/// Address: 0xE3
///
/// Reset Value: 0x30
///
/// Part Number Register 3.
#[derive(Debug, PartialEq)]
pub struct Pn3 {
    /// Part number identification byte 3.
    ///
    /// Bits: `[7:0]`
    pub data: u8,
}

/// Register Properties
impl Register<1, u8> for Pn3 {
    const ADDRESS: u8 = 0xE3;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x30]));
}

/// Reset Value
impl Default for Pn3 {
    fn default() -> Self {
        Self {
            data: 0x30,
        }
    }
}

// ==== `PN4` Register =========================================================

/// `PN4` Register
///
/// Address: 0xE4
///
/// Reset Value: 0x31
///
/// Part Number Register 4.
#[derive(Debug, PartialEq)]
pub struct Pn4 {
    /// Part number identification byte 4.
    ///
    /// Bits: `[7:0]`
    pub data: u8,
}

/// Register Properties
impl Register<1, u8> for Pn4 {
    const ADDRESS: u8 = 0xE4;
    const RESET_VAL: Option<ResetVal<1>> = Some(ResetVal::LittleEndian([0x31]));
}

/// Reset Value
impl Default for Pn4 {
    fn default() -> Self {
        Self {
            data: 0x31,
        }
    }
}

// ==== `MODE` Enum Conversion Functions =======================================

impl FromMaskedBytes<1> for Mode {
    fn from_masked_le_bytes(val: &[u8; 1]) -> Self {
        match [val[0] & 0x1] {
            [0x1] => Self::PowerMeter,
            [0x0] => Self::PulseCounter,
            _ => unreachable!(),
        }
    }
}

impl TryFromBytes<1> for Mode {
    type Error = FromBytesError;

    fn try_from_le_bytes(val: &[u8; 1]) -> Result<Self, Self::Error> {
        let bytes_outside = [val[0] & 0xFE];
        if bytes_outside == [0; 1] {
            Ok(Self::from_masked_le_bytes(val))
        } else {
            Err(Self::Error {pos: 0})
        }
    }
}

impl ToBytes<1> for Mode {
    fn to_le_bytes(&self) -> [u8; 1] {
        match self {
            Self::PowerMeter => [0x1],
            Self::PulseCounter => [0x0],
        }
    }
}

// ==== `RATE` Enum Conversion Functions =======================================

impl TryFromBytes<1> for Rate {
    type Error = FromBytesError;

    fn try_from_le_bytes(val: &[u8; 1]) -> Result<Self, Self::Error> {
        match val {
           [0x0] => Ok(Self::R1024ms),
           [0x3] => Ok(Self::R128ms),
           [0x2] => Ok(Self::R256ms),
           [0x1] => Ok(Self::R512ms),
           [0x4] => Ok(Self::R64ms),
            _ => Err(Self::Error {pos: 0})
        }
    }
}

impl ToBytes<1> for Rate {
    fn to_le_bytes(&self) -> [u8; 1] {
        match self {
            Self::R1024ms => [0x0],
            Self::R128ms => [0x3],
            Self::R256ms => [0x2],
            Self::R512ms => [0x1],
            Self::R64ms => [0x4],
        }
    }
}

// ==== `RATIO` Enum Conversion Functions ======================================

impl TryFromBytes<1> for Ratio {
    type Error = FromBytesError;

    fn try_from_le_bytes(val: &[u8; 1]) -> Result<Self, Self::Error> {
        match val {
           [0x8] => Ok(Self::R35),
           [0x9] => Ok(Self::R50),
           [0x3] => Ok(Self::R60),
           [0x2] => Ok(Self::R65),
           [0x6] => Ok(Self::R70),
           [0x5] => Ok(Self::R75),
           [0x7] => Ok(Self::R80),
           [0x4] => Ok(Self::R85),
           [0x1] => Ok(Self::R90),
           [0x0] => Ok(Self::RZmpp),
            _ => Err(Self::Error {pos: 0})
        }
    }
}

impl ToBytes<1> for Ratio {
    fn to_le_bytes(&self) -> [u8; 1] {
        match self {
            Self::R35 => [0x8],
            Self::R50 => [0x9],
            Self::R60 => [0x3],
            Self::R65 => [0x2],
            Self::R70 => [0x6],
            Self::R75 => [0x5],
            Self::R80 => [0x7],
            Self::R85 => [0x4],
            Self::R90 => [0x1],
            Self::RZmpp => [0x0],
        }
    }
}

// ==== `SRCTHRESH` Enum Conversion Functions ==================================

impl FromMaskedBytes<1> for Srcthresh {
    fn from_masked_le_bytes(val: &[u8; 1]) -> Self {
        match [val[0] & 0x7] {
            [0x1] => Self::V202mv,
            [0x2] => Self::V255mv,
            [0x3] => Self::V300mv,
            [0x4] => Self::V360mv,
            [0x5] => Self::V405mv,
            [0x6] => Self::V510mv,
            [0x7] => Self::V600mv,
            [0x0] => Self::VMv,
            _ => unreachable!(),
        }
    }
}

impl TryFromBytes<1> for Srcthresh {
    type Error = FromBytesError;

    fn try_from_le_bytes(val: &[u8; 1]) -> Result<Self, Self::Error> {
        let bytes_outside = [val[0] & 0xF8];
        if bytes_outside == [0; 1] {
            Ok(Self::from_masked_le_bytes(val))
        } else {
            Err(Self::Error {pos: 0})
        }
    }
}

impl ToBytes<1> for Srcthresh {
    fn to_le_bytes(&self) -> [u8; 1] {
        match self {
            Self::V202mv => [0x1],
            Self::V255mv => [0x2],
            Self::V300mv => [0x3],
            Self::V360mv => [0x4],
            Self::V405mv => [0x5],
            Self::V510mv => [0x6],
            Self::V600mv => [0x7],
            Self::VMv => [0x0],
        }
    }
}

// ==== `SYNCBUSY` Enum Conversion Functions ===================================

impl FromMaskedBytes<1> for Syncbusy {
    fn from_masked_le_bytes(val: &[u8; 1]) -> Self {
        match [val[0] & 0x1] {
            [0x0] => Self::Nsync,
            [0x1] => Self::Sync,
            _ => unreachable!(),
        }
    }
}

impl TryFromBytes<1> for Syncbusy {
    type Error = FromBytesError;

    fn try_from_le_bytes(val: &[u8; 1]) -> Result<Self, Self::Error> {
        let bytes_outside = [val[0] & 0xFE];
        if bytes_outside == [0; 1] {
            Ok(Self::from_masked_le_bytes(val))
        } else {
            Err(Self::Error {pos: 0})
        }
    }
}

impl ToBytes<1> for Syncbusy {
    fn to_le_bytes(&self) -> [u8; 1] {
        match self {
            Self::Nsync => [0x0],
            Self::Sync => [0x1],
        }
    }
}

// ==== `TIMING` Enum Conversion Functions =====================================

impl FromMaskedBytes<1> for Timing {
    fn from_masked_le_bytes(val: &[u8; 1]) -> Self {
        match [val[0] & 0x7] {
            [0x1] => Self::T256ms16384ms,
            [0x5] => Self::T2ms128ms,
            [0x7] => Self::T2ms256ms,
            [0x0] => Self::T2ms64ms,
            [0x4] => Self::T4ms256ms,
            [0x6] => Self::T4ms512ms,
            [0x2] => Self::T64ms4096ms,
            [0x3] => Self::T8ms1024ms,
            _ => unreachable!(),
        }
    }
}

impl TryFromBytes<1> for Timing {
    type Error = FromBytesError;

    fn try_from_le_bytes(val: &[u8; 1]) -> Result<Self, Self::Error> {
        let bytes_outside = [val[0] & 0xF8];
        if bytes_outside == [0; 1] {
            Ok(Self::from_masked_le_bytes(val))
        } else {
            Err(Self::Error {pos: 0})
        }
    }
}

impl ToBytes<1> for Timing {
    fn to_le_bytes(&self) -> [u8; 1] {
        match self {
            Self::T256ms16384ms => [0x1],
            Self::T2ms128ms => [0x5],
            Self::T2ms256ms => [0x7],
            Self::T2ms64ms => [0x0],
            Self::T4ms256ms => [0x4],
            Self::T4ms512ms => [0x6],
            Self::T64ms4096ms => [0x2],
            Self::T8ms1024ms => [0x3],
        }
    }
}

// ==== `UPDATE` Enum Conversion Functions =====================================

impl FromMaskedBytes<1> for Update {
    fn from_masked_le_bytes(val: &[u8; 1]) -> Self {
        match [val[0] & 0x1] {
            [0x0] => Self::Gpio,
            [0x1] => Self::I2c,
            _ => unreachable!(),
        }
    }
}

impl TryFromBytes<1> for Update {
    type Error = FromBytesError;

    fn try_from_le_bytes(val: &[u8; 1]) -> Result<Self, Self::Error> {
        let bytes_outside = [val[0] & 0xFE];
        if bytes_outside == [0; 1] {
            Ok(Self::from_masked_le_bytes(val))
        } else {
            Err(Self::Error {pos: 0})
        }
    }
}

impl ToBytes<1> for Update {
    fn to_le_bytes(&self) -> [u8; 1] {
        match self {
            Self::Gpio => [0x0],
            Self::I2c => [0x1],
        }
    }
}

// ==== `WINDOW` Enum Conversion Functions =====================================

impl TryFromBytes<1> for Window {
    type Error = FromBytesError;

    fn try_from_le_bytes(val: &[u8; 1]) -> Result<Self, Self::Error> {
        match val {
           [0x0] => Ok(Self::W128ms256ms),
           [0x2] => Ok(Self::W32ms64ms),
           [0x1] => Ok(Self::W64ms128ms),
            _ => Err(Self::Error {pos: 0})
        }
    }
}

impl ToBytes<1> for Window {
    fn to_le_bytes(&self) -> [u8; 1] {
        match self {
            Self::W128ms256ms => [0x0],
            Self::W32ms64ms => [0x2],
            Self::W64ms128ms => [0x1],
        }
    }
}

// ==== `APM` Layout Conversion Functions ======================================

impl ToBytes<1> for Apm {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // EN @ Apm[0]:
        val[0] |= (u8::from(self.en) & 0x1) as u8;
        // MODE @ Apm[1]:
        let mode: [u8; 1] = self.mode.to_le_bytes();
        val[0] |= (mode[0] << 1) & 0x2;
        // WINDOW @ Apm[3:2]:
        let window: [u8; 1] = self.window.to_le_bytes();
        val[0] |= (window[0] << 2) & 0xC;
        val
    }
}

impl TryFromBytes<1> for Apm {
    type Error = FromBytesError;
    fn try_from_le_bytes(val: &[u8; 1]) -> Result<Self, Self::Error> {
        // MODE @ Apm[1]:
        let mut mode: [u8; 1] = [0; 1];
        mode[0] |= (val[0] & 0x2) >> 1;
        // WINDOW @ Apm[3:2]:
        let mut window: [u8; 1] = [0; 1];
        window[0] |= (val[0] & 0xC) >> 2;
        Ok(Self {
          // EN @ Apm[0]:
          en: val[0] & 0x1 != 0,
          // MODE @ Apm[1]:
          mode: Mode::from_masked_le_bytes(&mode),
          // WINDOW @ Apm[3:2]:
          window: Window::try_from_le_bytes(&window).map_err(|x| Self::Error {pos: x.pos + 2})?,
        })
    }
}

impl From<Apm> for u8 {
    fn from(value: Apm) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl TryFrom<u8> for Apm {
    type Error = FromBytesError;
    fn try_from(value: u8) -> Result<Self, Self::Error> {
        Self::try_from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `APM0` Layout Conversion Functions =====================================

impl ToBytes<1> for Apm0 {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // DATA @ Apm0[7:0]:
        val[0] |= self.data as u8;
        val
    }
}

impl FromBytes<1> for Apm0 {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // DATA @ Apm0[7:0]:
          data: val[0],
        }
    }
}

impl From<Apm0> for u8 {
    fn from(value: Apm0) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Apm0 {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `APM1` Layout Conversion Functions =====================================

impl ToBytes<1> for Apm1 {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // DATA @ Apm1[7:0]:
        val[0] |= self.data as u8;
        val
    }
}

impl FromBytes<1> for Apm1 {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // DATA @ Apm1[7:0]:
          data: val[0],
        }
    }
}

impl From<Apm1> for u8 {
    fn from(value: Apm1) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Apm1 {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `APM2` Layout Conversion Functions =====================================

impl ToBytes<1> for Apm2 {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // DATA @ Apm2[7:0]:
        val[0] |= self.data as u8;
        val
    }
}

impl FromBytes<1> for Apm2 {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // DATA @ Apm2[7:0]:
          data: val[0],
        }
    }
}

impl From<Apm2> for u8 {
    fn from(value: Apm2) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Apm2 {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `CTRL` Layout Conversion Functions =====================================

impl ToBytes<1> for Ctrl {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // RESERVED @ Ctrl[1]:
        val[0] |= 0x0; // Fixed value.
        // SYNCBUSY @ Ctrl[2]:
        let syncbusy: [u8; 1] = self.syncbusy.to_le_bytes();
        val[0] |= (syncbusy[0] << 2) & 0x4;
        // UPDATE @ Ctrl[0]:
        let update: [u8; 1] = self.update.to_le_bytes();
        val[0] |= update[0] & 0x1;
        val
    }
}

impl FromBytes<1> for Ctrl {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        // SYNCBUSY @ Ctrl[2]:
        let mut syncbusy: [u8; 1] = [0; 1];
        syncbusy[0] |= (val[0] & 0x4) >> 2;
        // UPDATE @ Ctrl[0]:
        let mut update: [u8; 1] = [0; 1];
        update[0] |= val[0] & 0x1;
        Self {
          // SYNCBUSY @ Ctrl[2]:
          syncbusy: Syncbusy::from_masked_le_bytes(&syncbusy),
          // UPDATE @ Ctrl[0]:
          update: Update::from_masked_le_bytes(&update),
        }
    }
}

impl From<Ctrl> for u8 {
    fn from(value: Ctrl) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Ctrl {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `IRQEN` Layout Conversion Functions ====================================

impl ToBytes<1> for Irqen {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // APMDONE @ Irqen[5]:
        val[0] |= ((u8::from(self.apmdone) << 5) & 0x20) as u8;
        // APMERR @ Irqen[6]:
        val[0] |= ((u8::from(self.apmerr) << 6) & 0x40) as u8;
        // I2CRDY @ Irqen[0]:
        val[0] |= (u8::from(self.i2crdy) & 0x1) as u8;
        // SRCTHRESH @ Irqen[3]:
        val[0] |= ((u8::from(self.srcthresh) << 3) & 0x8) as u8;
        // TEMP @ Irqen[4]:
        val[0] |= ((u8::from(self.temp) << 4) & 0x10) as u8;
        // VOVCH @ Irqen[2]:
        val[0] |= ((u8::from(self.vovch) << 2) & 0x4) as u8;
        // VOVDIS @ Irqen[1]:
        val[0] |= ((u8::from(self.vovdis) << 1) & 0x2) as u8;
        val
    }
}

impl FromBytes<1> for Irqen {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // APMDONE @ Irqen[5]:
          apmdone: (val[0] & 0x20) >> 5 != 0,
          // APMERR @ Irqen[6]:
          apmerr: (val[0] & 0x40) >> 6 != 0,
          // I2CRDY @ Irqen[0]:
          i2crdy: val[0] & 0x1 != 0,
          // SRCTHRESH @ Irqen[3]:
          srcthresh: (val[0] & 0x8) >> 3 != 0,
          // TEMP @ Irqen[4]:
          temp: (val[0] & 0x10) >> 4 != 0,
          // VOVCH @ Irqen[2]:
          vovch: (val[0] & 0x4) >> 2 != 0,
          // VOVDIS @ Irqen[1]:
          vovdis: (val[0] & 0x2) >> 1 != 0,
        }
    }
}

impl From<Irqen> for u8 {
    fn from(value: Irqen) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Irqen {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `IRQFLG` Layout Conversion Functions ===================================

impl ToBytes<1> for Irqflg {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // APMDONE @ Irqflg[5]:
        val[0] |= ((u8::from(self.apmdone) << 5) & 0x20) as u8;
        // APMERR @ Irqflg[6]:
        val[0] |= ((u8::from(self.apmerr) << 6) & 0x40) as u8;
        // I2CRDY @ Irqflg[0]:
        val[0] |= (u8::from(self.i2crdy) & 0x1) as u8;
        // SRCTHRESH @ Irqflg[3]:
        val[0] |= ((u8::from(self.srcthresh) << 3) & 0x8) as u8;
        // TEMP @ Irqflg[4]:
        val[0] |= ((u8::from(self.temp) << 4) & 0x10) as u8;
        // VOVCH @ Irqflg[2]:
        val[0] |= ((u8::from(self.vovch) << 2) & 0x4) as u8;
        // VOVDIS @ Irqflg[1]:
        val[0] |= ((u8::from(self.vovdis) << 1) & 0x2) as u8;
        val
    }
}

impl FromBytes<1> for Irqflg {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // APMDONE @ Irqflg[5]:
          apmdone: (val[0] & 0x20) >> 5 != 0,
          // APMERR @ Irqflg[6]:
          apmerr: (val[0] & 0x40) >> 6 != 0,
          // I2CRDY @ Irqflg[0]:
          i2crdy: val[0] & 0x1 != 0,
          // SRCTHRESH @ Irqflg[3]:
          srcthresh: (val[0] & 0x8) >> 3 != 0,
          // TEMP @ Irqflg[4]:
          temp: (val[0] & 0x10) >> 4 != 0,
          // VOVCH @ Irqflg[2]:
          vovch: (val[0] & 0x4) >> 2 != 0,
          // VOVDIS @ Irqflg[1]:
          vovdis: (val[0] & 0x2) >> 1 != 0,
        }
    }
}

impl From<Irqflg> for u8 {
    fn from(value: Irqflg) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Irqflg {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `MPPTCFG` Layout Conversion Functions ==================================

impl ToBytes<1> for Mpptcfg {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // RATIO @ Mpptcfg[3:0]:
        let ratio: [u8; 1] = self.ratio.to_le_bytes();
        val[0] |= ratio[0] & 0xF;
        // TIMING @ Mpptcfg[6:4]:
        let timing: [u8; 1] = self.timing.to_le_bytes();
        val[0] |= (timing[0] << 4) & 0x70;
        val
    }
}

impl TryFromBytes<1> for Mpptcfg {
    type Error = FromBytesError;
    fn try_from_le_bytes(val: &[u8; 1]) -> Result<Self, Self::Error> {
        // RATIO @ Mpptcfg[3:0]:
        let mut ratio: [u8; 1] = [0; 1];
        ratio[0] |= val[0] & 0xF;
        // TIMING @ Mpptcfg[6:4]:
        let mut timing: [u8; 1] = [0; 1];
        timing[0] |= (val[0] & 0x70) >> 4;
        Ok(Self {
          // RATIO @ Mpptcfg[3:0]:
          ratio: Ratio::try_from_le_bytes(&ratio)?,
          // TIMING @ Mpptcfg[6:4]:
          timing: Timing::from_masked_le_bytes(&timing),
        })
    }
}

impl From<Mpptcfg> for u8 {
    fn from(value: Mpptcfg) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl TryFrom<u8> for Mpptcfg {
    type Error = FromBytesError;
    fn try_from(value: u8) -> Result<Self, Self::Error> {
        Self::try_from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `PN0` Layout Conversion Functions ======================================

impl ToBytes<1> for Pn0 {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // DATA @ Pn0[7:0]:
        val[0] |= self.data as u8;
        val
    }
}

impl FromBytes<1> for Pn0 {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // DATA @ Pn0[7:0]:
          data: val[0],
        }
    }
}

impl From<Pn0> for u8 {
    fn from(value: Pn0) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Pn0 {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `PN1` Layout Conversion Functions ======================================

impl ToBytes<1> for Pn1 {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // DATA @ Pn1[7:0]:
        val[0] |= self.data as u8;
        val
    }
}

impl FromBytes<1> for Pn1 {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // DATA @ Pn1[7:0]:
          data: val[0],
        }
    }
}

impl From<Pn1> for u8 {
    fn from(value: Pn1) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Pn1 {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `PN2` Layout Conversion Functions ======================================

impl ToBytes<1> for Pn2 {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // DATA @ Pn2[7:0]:
        val[0] |= self.data as u8;
        val
    }
}

impl FromBytes<1> for Pn2 {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // DATA @ Pn2[7:0]:
          data: val[0],
        }
    }
}

impl From<Pn2> for u8 {
    fn from(value: Pn2) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Pn2 {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `PN3` Layout Conversion Functions ======================================

impl ToBytes<1> for Pn3 {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // DATA @ Pn3[7:0]:
        val[0] |= self.data as u8;
        val
    }
}

impl FromBytes<1> for Pn3 {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // DATA @ Pn3[7:0]:
          data: val[0],
        }
    }
}

impl From<Pn3> for u8 {
    fn from(value: Pn3) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Pn3 {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `PN4` Layout Conversion Functions ======================================

impl ToBytes<1> for Pn4 {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // DATA @ Pn4[7:0]:
        val[0] |= self.data as u8;
        val
    }
}

impl FromBytes<1> for Pn4 {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // DATA @ Pn4[7:0]:
          data: val[0],
        }
    }
}

impl From<Pn4> for u8 {
    fn from(value: Pn4) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Pn4 {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `PWR` Layout Conversion Functions ======================================

impl ToBytes<1> for Pwr {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // HPEN @ Pwr[1]:
        val[0] |= ((u8::from(self.hpen) << 1) & 0x2) as u8;
        // KEEPALEN @ Pwr[0]:
        val[0] |= (u8::from(self.keepalen) & 0x1) as u8;
        // RESERVED @ Pwr[7:4]:
        val[0] |= 0x0; // Fixed value.
        // STOCHDIS @ Pwr[3]:
        val[0] |= ((u8::from(self.stochdis) << 3) & 0x8) as u8;
        // TMONEN @ Pwr[2]:
        val[0] |= ((u8::from(self.tmonen) << 2) & 0x4) as u8;
        val
    }
}

impl FromBytes<1> for Pwr {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // HPEN @ Pwr[1]:
          hpen: (val[0] & 0x2) >> 1 != 0,
          // KEEPALEN @ Pwr[0]:
          keepalen: val[0] & 0x1 != 0,
          // STOCHDIS @ Pwr[3]:
          stochdis: (val[0] & 0x8) >> 3 != 0,
          // TMONEN @ Pwr[2]:
          tmonen: (val[0] & 0x4) >> 2 != 0,
        }
    }
}

impl From<Pwr> for u8 {
    fn from(value: Pwr) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Pwr {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `SLEEP` Layout Conversion Functions ====================================

impl ToBytes<1> for Sleep {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // EN @ Sleep[0]:
        val[0] |= (u8::from(self.en) & 0x1) as u8;
        // SRCTHRESH @ Sleep[3:1]:
        let srcthresh: [u8; 1] = self.srcthresh.to_le_bytes();
        val[0] |= (srcthresh[0] << 1) & 0xE;
        val
    }
}

impl FromBytes<1> for Sleep {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        // SRCTHRESH @ Sleep[3:1]:
        let mut srcthresh: [u8; 1] = [0; 1];
        srcthresh[0] |= (val[0] & 0xE) >> 1;
        Self {
          // EN @ Sleep[0]:
          en: val[0] & 0x1 != 0,
          // SRCTHRESH @ Sleep[3:1]:
          srcthresh: Srcthresh::from_masked_le_bytes(&srcthresh),
        }
    }
}

impl From<Sleep> for u8 {
    fn from(value: Sleep) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Sleep {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `SRC` Layout Conversion Functions ======================================

impl ToBytes<1> for Src {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // DATA @ Src[7:0]:
        val[0] |= self.data as u8;
        val
    }
}

impl FromBytes<1> for Src {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // DATA @ Src[7:0]:
          data: val[0],
        }
    }
}

impl From<Src> for u8 {
    fn from(value: Src) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Src {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `STATUS` Layout Conversion Functions ===================================

impl ToBytes<1> for Status {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // BSTDIS @ Status[7]:
        val[0] |= ((u8::from(self.bstdis) << 7) & 0x80) as u8;
        // CHARGE @ Status[6]:
        val[0] |= ((u8::from(self.charge) << 6) & 0x40) as u8;
        // RESERVED @ Status[5]:
        val[0] |= 0x0; // Fixed value.
        // SRCTHRESH @ Status[3]:
        val[0] |= ((u8::from(self.srcthresh) << 3) & 0x8) as u8;
        // TEMP @ Status[4]:
        val[0] |= ((u8::from(self.temp) << 4) & 0x10) as u8;
        // VOVCH @ Status[2]:
        val[0] |= ((u8::from(self.vovch) << 2) & 0x4) as u8;
        // VOVDIS @ Status[1]:
        val[0] |= ((u8::from(self.vovdis) << 1) & 0x2) as u8;
        val
    }
}

impl FromBytes<1> for Status {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // BSTDIS @ Status[7]:
          bstdis: (val[0] & 0x80) >> 7 != 0,
          // CHARGE @ Status[6]:
          charge: (val[0] & 0x40) >> 6 != 0,
          // SRCTHRESH @ Status[3]:
          srcthresh: (val[0] & 0x8) >> 3 != 0,
          // TEMP @ Status[4]:
          temp: (val[0] & 0x10) >> 4 != 0,
          // VOVCH @ Status[2]:
          vovch: (val[0] & 0x4) >> 2 != 0,
          // VOVDIS @ Status[1]:
          vovdis: (val[0] & 0x2) >> 1 != 0,
        }
    }
}

impl From<Status> for u8 {
    fn from(value: Status) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Status {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `STO` Layout Conversion Functions ======================================

impl ToBytes<1> for Sto {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // DATA @ Sto[7:0]:
        val[0] |= self.data as u8;
        val
    }
}

impl FromBytes<1> for Sto {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // DATA @ Sto[7:0]:
          data: val[0],
        }
    }
}

impl From<Sto> for u8 {
    fn from(value: Sto) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Sto {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `STOMON` Layout Conversion Functions ===================================

impl ToBytes<1> for Stomon {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // RATE @ Stomon[2:0]:
        let rate: [u8; 1] = self.rate.to_le_bytes();
        val[0] |= rate[0] & 0x7;
        val
    }
}

impl TryFromBytes<1> for Stomon {
    type Error = FromBytesError;
    fn try_from_le_bytes(val: &[u8; 1]) -> Result<Self, Self::Error> {
        // RATE @ Stomon[2:0]:
        let mut rate: [u8; 1] = [0; 1];
        rate[0] |= val[0] & 0x7;
        Ok(Self {
          // RATE @ Stomon[2:0]:
          rate: Rate::try_from_le_bytes(&rate)?,
        })
    }
}

impl From<Stomon> for u8 {
    fn from(value: Stomon) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl TryFrom<u8> for Stomon {
    type Error = FromBytesError;
    fn try_from(value: u8) -> Result<Self, Self::Error> {
        Self::try_from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `TEMP` Layout Conversion Functions =====================================

impl ToBytes<1> for Temp {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // DATA @ Temp[7:0]:
        val[0] |= self.data as u8;
        val
    }
}

impl FromBytes<1> for Temp {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // DATA @ Temp[7:0]:
          data: val[0],
        }
    }
}

impl From<Temp> for u8 {
    fn from(value: Temp) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Temp {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `TEMPCOLD` Layout Conversion Functions =================================

impl ToBytes<1> for Tempcold {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // THRESH @ Tempcold[7:0]:
        val[0] |= self.thresh as u8;
        val
    }
}

impl FromBytes<1> for Tempcold {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // THRESH @ Tempcold[7:0]:
          thresh: val[0],
        }
    }
}

impl From<Tempcold> for u8 {
    fn from(value: Tempcold) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Tempcold {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `TEMPHOT` Layout Conversion Functions ==================================

impl ToBytes<1> for Temphot {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // THRESH @ Temphot[7:0]:
        val[0] |= self.thresh as u8;
        val
    }
}

impl FromBytes<1> for Temphot {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // THRESH @ Temphot[7:0]:
          thresh: val[0],
        }
    }
}

impl From<Temphot> for u8 {
    fn from(value: Temphot) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Temphot {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `VERSION` Layout Conversion Functions ==================================

impl ToBytes<1> for Version {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // MAJOR @ Version[7:4]:
        val[0] |= 0x0; // Fixed value.
        // MINOR @ Version[3:0]:
        val[0] |= 0x0; // Fixed value.
        val
    }
}

impl FromBytes<1> for Version {
    fn from_le_bytes(_val: &[u8; 1]) -> Self {
        Self {
        }
    }
}

impl From<Version> for u8 {
    fn from(value: Version) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Version {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `VOVCH` Layout Conversion Functions ====================================

impl ToBytes<1> for Vovch {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // THRESH @ Vovch[5:0]:
        val[0] |= (self.thresh & 0x3F) as u8;
        val
    }
}

impl FromBytes<1> for Vovch {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // THRESH @ Vovch[5:0]:
          thresh: val[0] & 0x3F,
        }
    }
}

impl From<Vovch> for u8 {
    fn from(value: Vovch) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Vovch {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}

// ==== `VOVDIS` Layout Conversion Functions ===================================

impl ToBytes<1> for Vovdis {
    #[allow(clippy::cast_possible_truncation)]
    fn to_le_bytes(&self) -> [u8; 1] {
        let mut val: [u8; 1] = [0; 1];
        // THRESH @ Vovdis[5:0]:
        val[0] |= (self.thresh & 0x3F) as u8;
        val
    }
}

impl FromBytes<1> for Vovdis {
    fn from_le_bytes(val: &[u8; 1]) -> Self {
        Self {
          // THRESH @ Vovdis[5:0]:
          thresh: val[0] & 0x3F,
        }
    }
}

impl From<Vovdis> for u8 {
    fn from(value: Vovdis) -> Self {
        Self::from_le_bytes(value.to_le_bytes())
    }
}

impl From<u8> for Vovdis {
    fn from(value: u8) -> Self {
        Self::from_le_bytes(&value.to_le_bytes())
    }
}
