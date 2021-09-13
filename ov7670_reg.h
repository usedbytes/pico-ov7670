#ifndef __OV7670_REG_H__
#define __OV7670_REG_H__

#define OV7670_ADDR 0x21 << 1
#define OV7670_R_ADDR (OV7670_ADDR | 1)
#define OV7670_W_ADDR OV7670_ADDR

/*
 * Register names from:  http://www.voti.nl/docs/OV7670.pdf 
 * Application note: https://www.fer.unizg.hr/_download/repository/OV7670new.pdf 
 */
#define REG_PID     0x0A
#define REG_VER     0x0B
#define REG_COM3    0x0C
#define REG_COM4    0x0D
#define REG_COM5    0x0E
#define REG_COM6    0x0F
#define REG_AECH    0x10
#define REG_CLKRC   0x11
#define     CLKRC_PLL_EN        (1 << 7)
#define     CLKRC_EXT_CLK       (1 << 6)
#define     CLKRC_SCALE_MASK    0x1F
#define     CLKRC_SET_SCALE(x)  (0x1F & (x << 0))
#define REG_COM7    0x12
#define     COM7_SCCB_RST       (1 << 7)
#define     COM7_SIZE_CIF       (1 << 5)
#define     COM7_SIZE_QVGA      (1 << 4)
#define     COM7_SIZE_QCIF      (1 << 3)
#define     COM7_FMT_RGB        (1 << 2)
#define     COM7_COLOR_BAR      (1 << 1)
#define     COM7_FMT_RAW        (1 << 0)
#define REG_COM8    0x13
#define REG_COM9    0x14
#define REG_COM10   0x15
#define     COM10_PCLK_BLANK    (1 << 5)
#define REG_RSVD    0x16
#define REG_HSTART  0x17
#define REG_HSTOP   0x18
#define REG_VSTART  0x19
#define REG_VSTOP   0x1A
#define REG_PSHIFT  0x1B
#define REG_MIDH    0x1C
#define REG_MIDL    0x1D
#define REG_MVFP    0x1E
#define REG_LAEC    0x1F
#define REG_ADCCTR0 0x20
#define REG_ADCCTR1 0x21
#define REG_ADCCTR2 0x22
#define REG_ADCCTR3 0x23
#define REG_AEW     0x24
#define REG_AEB     0x25
#define REG_VPT     0x26
#define REG_BBIAS   0x27
#define REG_GBBIAS  0x28
#define REG_RSVD2   0x29
#define REG_EXHCH   0x2A
#define REG_EXHCL   0x2B
#define REG_RBIAS   0x2C
#define REG_ADVFL   0x2D
#define REG_ADVFH   0x2E
#define REG_YAVE    0x2F
#define REG_HSYST   0x30
#define REG_HSYEN   0x31
#define REG_HREF    0x32
#define REG_CHLF    0x33
#define REG_ARBLM   0x34
#define REG_RSVD3   0x35
#define REG_RSVD4   0x36
#define REG_ADC     0x37
#define REG_ACOM    0x38
#define REG_OFON    0x39
#define REG_TSLB    0x3A
#define REG_COM11   0x3B
#define REG_COM12   0x3C
#define REG_COM13   0x3D
#define REG_COM14   0x3E
#define REG_EDGE    0x3F
#define REG_COM15   0x40
#define COM15_RANGE_MASK    (3 << 6)
#define COM15_RANGE_LOW     (0 << 6)
#define COM15_RANGE_MID     (2 << 6)
#define COM15_RANGE_HIGH    (3 << 6)
#define COM15_RGB_MASK      (3 << 4)
#define COM15_RGB_NORM      (0 << 4)
#define COM15_RGB565        (1 << 4)
#define COM15_RGB555        (3 << 4)
#define REG_COM16   0x41
#define REG_COM17   0x42
#define REG_AWBC1   0x43
#define REG_AWBC2   0x44
#define REG_AWBC3   0x45
#define REG_AWBC4   0x46
#define REG_AWBC5   0x47
#define REG_AWBC6   0x48
#define REG_RSVD5   0x49
#define REG_RSVD6   0x4A
#define REG_REG4B   0x4B
#define REG_DNSTH   0x4C
#define REG_DMPOS   0x4D
#define REG_RSVD7   0x4E
#define REG_MTX1    0x4F
#define REG_MTX2    0x50
#define REG_MTX3    0x51
#define REG_MTX4    0x52
#define REG_MTX5    0x53
#define REG_MTX6    0x54
#define REG_BRIGHT  0x55
#define REG_CONTR   0x56
#define REG_CONTRC  0x57
#define REG_MTXS    0x58
#define REG_AWBC7   0x59
#define REG_AWBC8   0x5A
#define REG_AWBC9   0x5B
#define REG_AWBC10  0x5C
#define REG_AWBC11  0x5D
#define REG_AWBC12  0x5E
#define REG_BLMT    0x5F
#define REG_RLMT    0x60
#define REG_GLMT    0x61
#define REG_LCC1    0x62
#define REG_LCC2    0x63
#define REG_LCC3    0x64
#define REG_LCC4    0x65
#define REG_LCC5    0x66
#define REG_MANU    0x67
#define REG_MANV    0x68
#define REG_GFIX    0x69
#define REG_GGAIN   0x6A
#define REG_DBLV    0x6B
#define REG_AWBCTL3 0x6C
#define REG_AWBCTL2 0x6D
#define REG_AWBCTL1 0x6E
#define REG_AWBCTL0 0x6F
#define REG_XSCALE  0x70
#define XSCALE_MASK     0x7F
#define REG_YSCALE  0x71
#define YSCALE_MASK     0x7F
#define REG_SCDCW   0x72
#define REG_SCPCLK  0x73
#define REG_REG74   0x74
#define REG_REG75   0x75
#define REG_REG76   0x76
#define REG_REG77   0x77
#define REG_RSVD9   0x79
#define REG_SLOP    0x7A
#define REG_GAM1    0x7B
#define REG_GAM2    0x7C
#define REG_GAM3    0x7D
#define REG_GAM4    0x7E
#define REG_GAM5    0x7F
#define REG_GAM6    0x80
#define REG_GAM7    0x81
#define REG_GAM8    0x82
#define REG_GAM9    0x83
#define REG_GAM10   0x84
#define REG_GAM11   0x85
#define REG_GAM12   0x86
#define REG_GAM13   0x87
#define REG_GAM14   0x88
#define REG_GAM15   0x89
/* Reserved 0x8A - 0x9C */
#define REG_BD50ST  0x9D
#define REG_BD60ST  0x9E
#define REG_HRL     0x9F
#define REG_LRL     0xA0
#define REG_DSPC3   0xA1
#define REG_SCPDLY  0xA2
#define REG_RSVD10  0xA3
#define REG_NTCTL   0xA4
#define REG_AEGCMAX 0xA5
#define REG_LPH     0xA6
#define REG_UPL     0xA7
#define REG_TPL     0xA8
#define REG_TPH     0xA9
#define REG_NALG    0xAA
#define REG_RSVD11  0xAB
#define REG_STROPT  0xAC
#define REG_STR_R   0xAD
#define REG_STR_G   0xAE
#define REG_STR_B   0xAF
#define REG_RSVD12  0xB0
#define REG_ABLC1   0xB1
#define REG_RSVD13  0xB2
#define REG_THL_ST  0xB3
#define REG_RSVD14  0xB4
#define REG_THL_DLT 0xB5
/* Reserved 0xB6 - 0xBD */
#define REG_ADCHB  0xBE
#define REG_ADCHR  0xBF
#define REG_ADCHGB 0xC0
#define REG_ADCHGR 0xC1
/* Reserved 0xC2 - 0xC8 */
#define REG_SATCTR 0xC9

#endif /* __OV7670_REG_H__ */
