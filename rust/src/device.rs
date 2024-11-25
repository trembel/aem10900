use crate::i2c_type;
use crate::maybe_async_attr;
use crate::registers::*;
use crate::Aem10900Config;
use crate::Error;
use heapless::Vec;

pub struct Aem10900<I2C> {
    pub i2c: I2C,
    pub dev_adr: u8,
    pub conf: Aem10900Config,
}

impl<I2C> Aem10900<I2C>
where
    I2C: i2c_type::i2c::I2c,
{
    /// Creates a new instance of `Aem10900`
    ///
    /// Requires the I2C device and it's device address
    pub fn new(i2c: I2C, dev_adr: u8) -> Self {
        Self {
            i2c,
            dev_adr,
            conf: Aem10900Config::default(),
        }
    }

    /// Allow direct access to the I2C bus
    pub fn bus(&mut self) -> &mut I2C {
        &mut self.i2c
    }

    /// Function to write (consecutive) registers to the device
    #[maybe_async_attr]
    pub async fn write_regs(&mut self, start_adr: u8, write: &[u8]) -> Result<(), Error<I2C>> {
        let mut write_buf: Vec<u8, 26> = Vec::new();
        write_buf.push(start_adr).unwrap();
        write_buf.extend_from_slice(write).unwrap();
        self.i2c
            .write(self.dev_adr, &write_buf)
            .await
            .map_err(Error::Communication)
    }
    /// Function to read (consecutive) registers from the device
    #[maybe_async_attr]
    pub async fn read_regs(&mut self, start_adr: u8, read: &mut [u8]) -> Result<(), Error<I2C>> {
        self.i2c
            .write_read(self.dev_adr, &[start_adr], read)
            .await
            .map_err(Error::Communication)
    }

    /// Initialize function
    #[maybe_async_attr]
    pub async fn init(&mut self) -> Result<(), Error<I2C>> {
        self.check_connection().await?;
        self.write_cfg_regs().await?;
        self.verify_cfg_regs().await?;
        Ok(())
    }

    /// Function polling the part number registers, to check whether the communication with the AEM10900 works
    #[maybe_async_attr]
    async fn check_connection(&mut self) -> Result<(), Error<I2C>> {
        let mut part_number: [u8; 5] = [0; 5];
        self.read_regs(Pn0::ADDRESS, &mut part_number).await?;

        // TODO: Somehow part number is wrong
        if part_number != [0x00, 0x77, 0x2D, 0x33, 0x8F] {
            return Err(Error::Config("Part Number"));
        }
        // if Pn0::default() != Pn0::from_le_bytes(&[part_number[0]]) {
        //     return Err(Error::Config("Pn0"));
        // }
        // if Pn1::default() != Pn1::from_le_bytes(&[part_number[0]]) {
        //     return Err(Error::Config("Pn1"));
        // }
        // if Pn2::default() != Pn2::from_le_bytes(&[part_number[0]]) {
        //     return Err(Error::Config("Pn2"));
        // }
        // if Pn3::default() != Pn3::from_le_bytes(&[part_number[0]]) {
        //     return Err(Error::Config("Pn3"));
        // }
        // if Pn4::default() != Pn4::from_le_bytes(&[part_number[0]]) {
        //     return Err(Error::Config("Pn4"));
        // }

        Ok(())
    }

    /// Function writing all config registers to the AEM10900
    #[maybe_async_attr]
    async fn write_cfg_regs(&mut self) -> Result<(), Error<I2C>> {
        let mut byte_arr: [u8; 11] = [0; 11];
        byte_arr[0] = self.conf.mpptcfg.to_le_bytes()[0];
        byte_arr[1] = self.conf.vovdis.to_le_bytes()[0];
        byte_arr[2] = self.conf.vovch.to_le_bytes()[0];
        byte_arr[3] = self.conf.tempcold.to_le_bytes()[0];
        byte_arr[4] = self.conf.temphot.to_le_bytes()[0];
        byte_arr[5] = self.conf.pwr.to_le_bytes()[0];
        byte_arr[6] = self.conf.sleep.to_le_bytes()[0];
        byte_arr[7] = self.conf.stomon.to_le_bytes()[0];
        byte_arr[8] = self.conf.apm.to_le_bytes()[0];
        byte_arr[9] = self.conf.irqen.to_le_bytes()[0];
        byte_arr[10] = self.conf.ctrl.to_le_bytes()[0];

        self.write_regs(Mpptcfg::ADDRESS, &byte_arr).await
    }

    /// Function comparing all config registers in the AEM10900 to the config struct
    #[maybe_async_attr]
    async fn verify_cfg_regs(&mut self) -> Result<(), Error<I2C>> {
        let mut byte_arr: [u8; 11] = [0; 11];

        self.read_regs(Mpptcfg::ADDRESS, &mut byte_arr).await?;

        if self.conf.mpptcfg
            != Mpptcfg::try_from_le_bytes(&[byte_arr[0]])
                .map_err(|_| Error::Value("Mpptcfg could not be extracted"))?
        {
            return Err(Error::Config("Mpptcfg"));
        }
        if self.conf.vovdis != Vovdis::from_le_bytes(&[byte_arr[1]]) {
            return Err(Error::Config("Vovdis"));
        }
        if self.conf.vovch != Vovch::from_le_bytes(&[byte_arr[2]]) {
            return Err(Error::Config("Vovch"));
        }
        if self.conf.tempcold != Tempcold::from_le_bytes(&[byte_arr[3]]) {
            return Err(Error::Config("Tempcold"));
        }
        if self.conf.temphot != Temphot::from_le_bytes(&[byte_arr[4]]) {
            return Err(Error::Config("Temphot"));
        }
        if self.conf.pwr != Pwr::from_le_bytes(&[byte_arr[5]]) {
            return Err(Error::Config("Pwr"));
        }
        if self.conf.sleep != Sleep::from_le_bytes(&[byte_arr[6]]) {
            return Err(Error::Config("Sleep"));
        }
        if self.conf.stomon
            != Stomon::try_from_le_bytes(&[byte_arr[7]])
                .map_err(|_| Error::Value("Stomon could not be extracted"))?
        {
            return Err(Error::Config("Stomon"));
        }
        if self.conf.apm
            != Apm::try_from_le_bytes(&[byte_arr[8]])
                .map_err(|_| Error::Value("Apm could not be extracted"))?
        {
            return Err(Error::Config("Apm"));
        }
        if self.conf.irqen != Irqen::from_le_bytes(&[byte_arr[9]]) {
            return Err(Error::Config("Irqen"));
        }
        if self.conf.ctrl != Ctrl::from_le_bytes(&[byte_arr[10]]) {
            return Err(Error::Config("Ctrl"));
        }

        Ok(())
    }

    /// Function to readout and clear the IRQ Flag of the AEM10900
    #[maybe_async_attr]
    pub async fn read_irq_flag(&mut self) -> Result<Irqflg, Error<I2C>> {
        let mut byte_arr: [u8; 1] = [0];

        self.read_regs(Irqflg::ADDRESS, &mut byte_arr).await?;
        Ok(Irqflg::from_le_bytes(&byte_arr))
    }

    /// Function to readout the APM Data of the AEM10900, based on the mode set in the configs
    #[maybe_async_attr]
    pub async fn read_apm_data(&mut self) -> Result<ApmData, Error<I2C>> {
        let mut byte_arr: [u8; 3] = [0; 3];

        self.read_regs(Apm0::ADDRESS, &mut byte_arr).await?;
        let apm0 = Apm0::from_le_bytes(&[byte_arr[0]]);
        let apm1 = Apm1::from_le_bytes(&[byte_arr[1]]);
        let apm2 = Apm2::from_le_bytes(&[byte_arr[2]]);

        let data: u32 =
            ((apm2.data & 0x0F) as u32) << 16 | ((apm1.data as u32) << 8) | (apm0.data as u32);

        match self.conf.apm.mode {
            Mode::PowerMeter => {
                let shift = (apm2.data >> 4) & 0x0F;
                // TODO: How to handle different V_SRC...
                // Assume for now V_SRC > 0.7V
                Ok(ApmData::PowerMeterResult((data << shift) as f32 * 0.10166))
            }
            Mode::PulseCounter => Ok(ApmData::PulseCounterResult(data)),
        }
    }

    /// Function to readout the battery voltage of the AEM10900
    #[maybe_async_attr]
    pub async fn read_battery_voltage(&mut self) -> Result<f32, Error<I2C>> {
        let mut byte_arr: [u8; 1] = [0];

        self.read_regs(Sto::ADDRESS, &mut byte_arr).await?;
        let sto = Sto::from_le_bytes(&[byte_arr[0]]);

        // Convert result to a voltage
        Ok(4.8 * (sto.data as f32) / 256.0)
    }

    /// Function to readout the source voltage of the AEM10900
    #[maybe_async_attr]
    pub async fn read_source_voltage(&mut self) -> Result<f32, Error<I2C>> {
        let mut byte_arr: [u8; 1] = [0];

        self.read_regs(Src::ADDRESS, &mut byte_arr).await?;
        let src = Src::from_le_bytes(&[byte_arr[0]]);

        // Convert result to a source voltage
        self.source_voltage_lookup(src)
    }

    /// Function to convert a SRC register reading into a voltage
    fn source_voltage_lookup(&self, src: Src) -> Result<f32, Error<I2C>> {
        // implemented with an array instead of a hash map, as this can be defined const
        const SRC_VOLTAGE_MIN_KEY: u8 = 0x06;
        const SRC_VOLTAGE_MAX_KEY: u8 = 0x3A;
        const TABLE_LENGTH: usize = (SRC_VOLTAGE_MAX_KEY - SRC_VOLTAGE_MIN_KEY + 1) as usize;

        const SOURCE_VOLTAGE_LOOKUP_TABLE: [u16; TABLE_LENGTH] = [
            113, 128, 142, 158, 172, 188, 203, 217, 233, 247, 263, 278, 292, 315, 345, 375, 405,
            435, 465, 495, 525, 555, 585, 615, 645, 675, 705, 735, 765, 795, 825, 855, 885, 915,
            945, 975, 1005, 1035, 1065, 1095, 1125, 1155, 1185, 1215, 1245, 1275, 1305, 1335, 1365,
            1395, 1425, 1455, 1485,
        ];

        if src.data < SRC_VOLTAGE_MIN_KEY || src.data > SRC_VOLTAGE_MAX_KEY {
            return Err(Error::Value("Src.data is not within allowed range"));
        }
        Ok(SOURCE_VOLTAGE_LOOKUP_TABLE[(src.data - SRC_VOLTAGE_MIN_KEY) as usize] as f32 / 1000.0)
    }
}

/// Data Type for the APM Data, depending on the mode (power meter or pulse counter)
pub enum ApmData {
    /// Result of the power meter mode, as float f32
    PowerMeterResult(f32),
    /// Result of the pulse counter mode, as u32
    PulseCounterResult(u32),
}
