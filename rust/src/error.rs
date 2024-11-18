use core::fmt::{self, Display, Formatter};
use crate::i2c_type;

/// Errors that can occur when using the AEM10900
pub enum Error<I2C>
where
    I2C: i2c_type::i2c::ErrorType,
{
    /// I2C error occured during a communication transaction
    Communication(I2C::Error),
    /// Wrong configuration error
    Config(&'static str),
    /// No data available
    NoData,
    /// Value does not exist
    Value(&'static str),
    /// Generic AEM10900 error
    Generic,
}

impl<I2C> Display for Error<I2C>
where
    I2C: i2c_type::i2c::ErrorType,
    I2C::Error: core::fmt::Debug,
{
    fn fmt(&self, f: &mut Formatter<'_>) -> core::fmt::Result {
        write!(f, "{:?}", self)
    }
}

// We can't derive this implementation, as the compiler will complain that the
// associated error type doesn't implement `Debug`.
impl<I2C> fmt::Debug for Error<I2C>
where
    I2C: i2c_type::i2c::ErrorType,
    I2C::Error: fmt::Debug,
{
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Error::Communication(error) => write!(f, "Communication error ({:?})", error),
            Error::Config(s) => write!(f, "Configuration error ({:?})", s),
            Error::NoData => write!(f, "No Data available error"),
            Error::Value(s) => write!(f, "Value error ({:?})", s),
            Error::Generic => write!(f, "Generic error"),
        }
    }
}

#[cfg(feature = "defmt")]
impl<I2C> defmt::Format for Error<I2C>
where
    I2C: i2c_type::i2c::I2c,
{
    fn format(&self, f: defmt::Formatter) {
        match self {
            Error::Communication(_) => defmt::write!(f, "Communication error"),
            Error::Config(s) => defmt::write!(f, "Configuration error ({:?})", s),
            Error::NoData => defmt::write!(f, "No Data available error"),
            Error::Value(s) => defmt::write!(f, "Value error ({:?})", s),
            Error::Generic => defmt::write!(f, "Generic error"),
        }
    }
}
