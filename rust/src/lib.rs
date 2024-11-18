//! Driver crate for the AEM10900 Energy Harvester
//!
//! The driver is built on top of [`embedded-hal`], which means it is portable
//! and can be used on any platform that implements the `embedded-hal` API (also async)
//!
//! [`embedded-hal`]: https://crates.io/crates/embedded-hal
#![no_std]

#[cfg(feature = "async")]
use maybe_async::must_be_async as maybe_async_attr;
#[cfg(not(feature = "async"))]
use maybe_async::must_be_sync as maybe_async_attr;

#[cfg(not(feature = "async"))]
use embedded_hal as i2c_type;
#[cfg(feature = "async")]
use embedded_hal_async as i2c_type;

pub mod registers;

mod config;
pub use config::Aem10900Config;

mod error;
pub use error::Error;

mod device;
pub use device::{Aem10900, ApmData};
