#![no_std]
#![no_main]

use aem10900::{registers, Aem10900};
use defmt::*;
use embassy_executor::Spawner;
use embassy_stm32::i2c::{self, I2c};
use embassy_stm32::time::Hertz;
use embassy_stm32::{bind_interrupts, peripherals};
use embassy_time::Timer;
use {defmt_rtt as _, panic_probe as _};

const AEM10900_ADDRESS: u8 = 0x41;

bind_interrupts!(struct Irqs {
    I2C1_EV => i2c::EventInterruptHandler<peripherals::I2C1>;
    I2C1_ER => i2c::ErrorInterruptHandler<peripherals::I2C1>;
});

#[embassy_executor::main]
async fn main(_spawner: Spawner) -> ! {
    let mut p = embassy_stm32::init(Default::default());

    // Pass peripherals as reference: Allows dropping for low-power features
    let i2c = I2c::new(
        &mut p.I2C1,
        &mut p.PB8,
        &mut p.PB7,
        Irqs,
        &mut p.GPDMA1_CH0,
        &mut p.GPDMA1_CH1,
        Hertz(100_000),
        Default::default(),
    );
    info!("Starting up AEM10900 Test Application\r\n");

    // Load default configuration
    let mut dev = Aem10900::new(i2c, AEM10900_ADDRESS);

    // Change desired configurations
    {
        dev.conf.mpptcfg.ratio = registers::Ratio::R80; // set 80% MPPT ratio
        dev.conf.mpptcfg.timing = registers::Timing::T4ms512ms; // 4ms - 512ms
        dev.conf.vovdis.thresh = ((3.00 - 0.50625) / 0.05625) as u8; // 3V
        dev.conf.vovch.thresh = ((4.20 - 1.2375) / 0.05625) as u8; // 4.2V
                                                                   // dev.conf.tempcold; // no THERMAL resistor mounted
                                                                   // dev.conf.temphot; // no THERMAL resistor mounted
        dev.conf.pwr.keepalen = true; // enable keepalive
        dev.conf.pwr.hpen = true; // enable automatic high-power mode
        dev.conf.pwr.tmonen = false; // disable temperature monitoring
        dev.conf.pwr.stochdis = true; // allow charging of battery
        dev.conf.sleep.en = false; // disable sleep, even if src voltage is low
                                   // dev.conf.sleep.srcthresh; // sleep is disabled
        dev.conf.stomon.rate = registers::Rate::R1024ms; // read battery voltage every second
        dev.conf.apm.en = true; // enable the APM mode
        dev.conf.apm.mode = registers::Mode::PowerMeter; // and set it to power mode
        dev.conf.apm.window = registers::Window::W128ms256ms; // computation window 128ms, refresh rate 256ms
        dev.conf.irqen.i2crdy = false; // disable (as enabled on boot). when IRQ is fired, IC is ready
        dev.conf.irqen.vovdis = false;
        dev.conf.irqen.vovch = false;
        dev.conf.irqen.srcthresh = false;
        dev.conf.irqen.temp = false;
        dev.conf.irqen.apmdone = false;
        dev.conf.ctrl.update = registers::Update::I2c; // Use I2C configuration
    }

    Timer::after_millis(500).await;
    let err = dev.init().await;
    if let Err(e) = err {
        error!("Failed to init AEM10900 with {:?}", e);
        loop {}
    }

    loop {
        let res = dev.get_battery_voltage().await;
        match res {
            Err(e) => error!("Failed to read battery voltage from AEM10900 with {:?}", e),
            Ok(v) => info!("Battery voltage is {:?}", v),
        }
        Timer::after_millis(5000).await;
    }
}
