use crate::registers::*;
use crate::registers::ToBytes;


#[derive(Default, Debug)]
pub struct Aem10900Config {
    pub version: Version,
    pub mpptcfg: Mpptcfg,
    pub vovdis: Vovdis,
    pub vovch: Vovch,
    pub tempcold: Tempcold,
    pub temphot: Temphot,
    pub pwr: Pwr,
    pub sleep: Sleep,
    pub stomon: Stomon,
    pub apm: Apm,
    pub irqen: Irqen,
    pub ctrl: Ctrl,
    pub irqflg: Irqflg,
    pub status: Status,
    pub apm0: Apm0,
    pub apm1: Apm1,
    pub apm2: Apm2,
    pub temp: Temp,
    pub sto: Sto,
    pub src: Src,
    pub pn0: Pn0,
    pub pn1: Pn1,
    pub pn2: Pn2,
    pub pn3: Pn3,
    pub pn4: Pn4,
}

impl ToBytes<25> for Aem10900Config {
    fn to_le_bytes(&self) -> [u8; 25] {
        let mut byte_arr: [u8; 25] = [0; 25];

        byte_arr[0] = self.version.to_le_bytes()[0];
        byte_arr[1] = self.mpptcfg.to_le_bytes()[0];
        byte_arr[2] = self.vovdis.to_le_bytes()[0];
        byte_arr[3] = self.vovch.to_le_bytes()[0];
        byte_arr[4] = self.tempcold.to_le_bytes()[0];
        byte_arr[5] = self.temphot.to_le_bytes()[0];
        byte_arr[6] = self.pwr.to_le_bytes()[0];
        byte_arr[7] = self.sleep.to_le_bytes()[0];
        byte_arr[8] = self.stomon.to_le_bytes()[0];
        byte_arr[9] = self.apm.to_le_bytes()[0];
        byte_arr[10] = self.irqen.to_le_bytes()[0];
        byte_arr[11] = self.ctrl.to_le_bytes()[0];
        byte_arr[12] = self.irqflg.to_le_bytes()[0];
        byte_arr[13] = self.status.to_le_bytes()[0];
        byte_arr[14] = self.apm0.to_le_bytes()[0];
        byte_arr[15] = self.apm1.to_le_bytes()[0];
        byte_arr[16] = self.apm2.to_le_bytes()[0];
        byte_arr[17] = self.temp.to_le_bytes()[0];
        byte_arr[18] = self.sto.to_le_bytes()[0];
        byte_arr[19] = self.src.to_le_bytes()[0];
        byte_arr[20] = self.pn0.to_le_bytes()[0];
        byte_arr[21] = self.pn1.to_le_bytes()[0];
        byte_arr[22] = self.pn2.to_le_bytes()[0];
        byte_arr[23] = self.pn3.to_le_bytes()[0];
        byte_arr[24] = self.pn4.to_le_bytes()[0];

        byte_arr
    }

    fn to_be_bytes(&self) -> [u8; 25] {
        let mut byte_arr: [u8; 25] = [0; 25];

        byte_arr[24] = self.version.to_be_bytes()[0];
        byte_arr[23] = self.mpptcfg.to_be_bytes()[0];
        byte_arr[22] = self.vovdis.to_be_bytes()[0];
        byte_arr[21] = self.vovch.to_be_bytes()[0];
        byte_arr[20] = self.tempcold.to_be_bytes()[0];
        byte_arr[19] = self.temphot.to_be_bytes()[0];
        byte_arr[18] = self.pwr.to_be_bytes()[0];
        byte_arr[17] = self.sleep.to_be_bytes()[0];
        byte_arr[16] = self.stomon.to_be_bytes()[0];
        byte_arr[15] = self.apm.to_be_bytes()[0];
        byte_arr[14] = self.irqen.to_be_bytes()[0];
        byte_arr[13] = self.ctrl.to_be_bytes()[0];
        byte_arr[12] = self.irqflg.to_be_bytes()[0];
        byte_arr[11] = self.status.to_be_bytes()[0];
        byte_arr[10] = self.apm0.to_be_bytes()[0];
        byte_arr[9] = self.apm1.to_be_bytes()[0];
        byte_arr[8] = self.apm2.to_be_bytes()[0];
        byte_arr[7] = self.temp.to_be_bytes()[0];
        byte_arr[6] = self.sto.to_be_bytes()[0];
        byte_arr[5] = self.src.to_be_bytes()[0];
        byte_arr[4] = self.pn0.to_be_bytes()[0];
        byte_arr[3] = self.pn1.to_be_bytes()[0];
        byte_arr[2] = self.pn2.to_be_bytes()[0];
        byte_arr[1] = self.pn3.to_be_bytes()[0];
        byte_arr[0] = self.pn4.to_be_bytes()[0];

        byte_arr
    }
}

impl TryFromBytes<25> for Aem10900Config {
    type Error = FromBytesError;
    fn try_from_le_bytes(val: &[u8; 25]) -> Result<Self, Self::Error> {
        Ok(Self {
            version: Version::from_le_bytes(val[0..0].try_into().unwrap()),
            mpptcfg: Mpptcfg::try_from_le_bytes(val[1..1].try_into().unwrap())?,
            vovdis: Vovdis::from_le_bytes(val[2..2].try_into().unwrap()),
            vovch: Vovch::from_le_bytes(val[3..3].try_into().unwrap()),
            tempcold: Tempcold::from_le_bytes(val[4..4].try_into().unwrap()),
            temphot: Temphot::from_le_bytes(val[5..5].try_into().unwrap()),
            pwr: Pwr::from_le_bytes(val[6..6].try_into().unwrap()),
            sleep: Sleep::from_le_bytes(val[7..7].try_into().unwrap()),
            stomon: Stomon::try_from_le_bytes(val[8..8].try_into().unwrap())?,
            apm: Apm::try_from_le_bytes(val[9..9].try_into().unwrap())?,
            irqen: Irqen::from_le_bytes(val[10..10].try_into().unwrap()),
            ctrl: Ctrl::from_le_bytes(val[11..11].try_into().unwrap()),
            irqflg: Irqflg::from_le_bytes(val[12..12].try_into().unwrap()),
            status: Status::from_le_bytes(val[13..13].try_into().unwrap()),
            apm0: Apm0::from_le_bytes(val[14..14].try_into().unwrap()),
            apm1: Apm1::from_le_bytes(val[15..15].try_into().unwrap()),
            apm2: Apm2::from_le_bytes(val[16..16].try_into().unwrap()),
            temp: Temp::from_le_bytes(val[17..17].try_into().unwrap()),
            sto: Sto::from_le_bytes(val[18..18].try_into().unwrap()),
            src: Src::from_le_bytes(val[19..19].try_into().unwrap()),
            pn0: Pn0::from_le_bytes(val[20..20].try_into().unwrap()),
            pn1: Pn1::from_le_bytes(val[21..21].try_into().unwrap()),
            pn2: Pn2::from_le_bytes(val[22..22].try_into().unwrap()),
            pn3: Pn3::from_le_bytes(val[23..23].try_into().unwrap()),
            pn4: Pn4::from_le_bytes(val[24..24].try_into().unwrap()),
        })
    }

    fn try_from_be_bytes(val: &[u8; 25]) -> Result<Self, Self::Error> {
        Ok(Self {
            version: Version::from_be_bytes(val[24..24].try_into().unwrap()),
            mpptcfg: Mpptcfg::try_from_be_bytes(val[23..23].try_into().unwrap())?,
            vovdis: Vovdis::from_be_bytes(val[22..22].try_into().unwrap()),
            vovch: Vovch::from_be_bytes(val[21..21].try_into().unwrap()),
            tempcold: Tempcold::from_be_bytes(val[20..20].try_into().unwrap()),
            temphot: Temphot::from_be_bytes(val[19..19].try_into().unwrap()),
            pwr: Pwr::from_be_bytes(val[18..18].try_into().unwrap()),
            sleep: Sleep::from_be_bytes(val[17..17].try_into().unwrap()),
            stomon: Stomon::try_from_be_bytes(val[16..16].try_into().unwrap())?,
            apm: Apm::try_from_be_bytes(val[15..15].try_into().unwrap())?,
            irqen: Irqen::from_be_bytes(val[14..14].try_into().unwrap()),
            ctrl: Ctrl::from_be_bytes(val[13..13].try_into().unwrap()),
            irqflg: Irqflg::from_be_bytes(val[12..12].try_into().unwrap()),
            status: Status::from_be_bytes(val[11..11].try_into().unwrap()),
            apm0: Apm0::from_be_bytes(val[10..10].try_into().unwrap()),
            apm1: Apm1::from_be_bytes(val[9..9].try_into().unwrap()),
            apm2: Apm2::from_be_bytes(val[8..8].try_into().unwrap()),
            temp: Temp::from_be_bytes(val[7..7].try_into().unwrap()),
            sto: Sto::from_be_bytes(val[6..6].try_into().unwrap()),
            src: Src::from_be_bytes(val[5..5].try_into().unwrap()),
            pn0: Pn0::from_be_bytes(val[4..4].try_into().unwrap()),
            pn1: Pn1::from_be_bytes(val[3..3].try_into().unwrap()),
            pn2: Pn2::from_be_bytes(val[2..2].try_into().unwrap()),
            pn3: Pn3::from_be_bytes(val[1..1].try_into().unwrap()),
            pn4: Pn4::from_be_bytes(val[0..0].try_into().unwrap()),
        })
    }
}
