#ifndef __OV7670_REG_H__
#define __OV7670_REG_H__

#define OV7670_ADDR 0x21

/*
 * Register names from:  http://www.voti.nl/docs/OV7670.pdf 
 * Application note: https://www.fer.unizg.hr/_download/repository/OV7670new.pdf 
 */
#define OV7670_REG_PID     0x0A
#define OV7670_REG_VER     0x0B
#define OV7670_REG_COM3    0x0C
#define OV7670_REG_COM4    0x0D
#define OV7670_REG_COM5    0x0E
#define OV7670_REG_COM6    0x0F
#define OV7670_REG_AECH    0x10
#define OV7670_REG_CLKRC   0x11
#define     CLKRC_PLL_EN        (1 << 7)
#define     CLKRC_EXT_CLK       (1 << 6)
#define     CLKRC_SCALE_MASK    0x1F
#define     CLKRC_SET_SCALE(x)  (0x1F & (x << 0))
#define OV7670_REG_COM7    0x12
#define     COM7_SCCB_RST       (1 << 7)
#define     COM7_SIZE_CIF       (1 << 5)
#define     COM7_SIZE_QVGA      (1 << 4)
#define     COM7_SIZE_QCIF      (1 << 3)
#define     COM7_FMT_RGB        (1 << 2)
#define     COM7_COLOR_BAR      (1 << 1)
#define     COM7_FMT_RAW        (1 << 0)
#define OV7670_REG_COM8    0x13
#define OV7670_REG_COM9    0x14
#define OV7670_REG_COM10   0x15
#define     COM10_PCLK_BLANK    (1 << 5)
#define OV7670_REG_RSVD    0x16
#define OV7670_REG_HSTART  0x17
#define OV7670_REG_HSTOP   0x18
#define OV7670_REG_VSTART  0x19
#define OV7670_REG_VSTOP   0x1A
#define OV7670_REG_PSHIFT  0x1B
#define OV7670_REG_MIDH    0x1C
#define OV7670_REG_MIDL    0x1D
#define OV7670_REG_MVFP    0x1E
#define OV7670_REG_LAEC    0x1F
#define OV7670_REG_ADCCTR0 0x20
#define OV7670_REG_ADCCTR1 0x21
#define OV7670_REG_ADCCTR2 0x22
#define OV7670_REG_ADCCTR3 0x23
#define OV7670_REG_AEW     0x24
#define OV7670_REG_AEB     0x25
#define OV7670_REG_VPT     0x26
#define OV7670_REG_BBIAS   0x27
#define OV7670_REG_GBBIAS  0x28
#define OV7670_REG_RSVD2   0x29
#define OV7670_REG_EXHCH   0x2A
#define OV7670_REG_EXHCL   0x2B
#define OV7670_REG_RBIAS   0x2C
#define OV7670_REG_ADVFL   0x2D
#define OV7670_REG_ADVFH   0x2E
#define OV7670_REG_YAVE    0x2F
#define OV7670_REG_HSYST   0x30
#define OV7670_REG_HSYEN   0x31
#define OV7670_REG_HREF    0x32
#define OV7670_REG_CHLF    0x33
#define OV7670_REG_ARBLM   0x34
#define OV7670_REG_RSVD3   0x35
#define OV7670_REG_RSVD4   0x36
#define OV7670_REG_ADC     0x37
#define OV7670_REG_ACOM    0x38
#define OV7670_REG_OFON    0x39
#define OV7670_REG_TSLB    0x3A
#define OV7670_REG_COM11   0x3B
#define OV7670_REG_COM12   0x3C
#define OV7670_REG_COM13   0x3D
#define OV7670_REG_COM14   0x3E
#define OV7670_REG_EDGE    0x3F
#define OV7670_REG_COM15   0x40
#define COM15_RANGE_MASK    (3 << 6)
#define COM15_RANGE_LOW     (0 << 6)
#define COM15_RANGE_MID     (2 << 6)
#define COM15_RANGE_HIGH    (3 << 6)
#define COM15_RGB_MASK      (3 << 4)
#define COM15_RGB_NORM      (0 << 4)
#define COM15_RGB565        (1 << 4)
#define COM15_RGB555        (3 << 4)
#define OV7670_REG_COM16   0x41
#define OV7670_REG_COM17   0x42
#define OV7670_REG_AWBC1   0x43
#define OV7670_REG_AWBC2   0x44
#define OV7670_REG_AWBC3   0x45
#define OV7670_REG_AWBC4   0x46
#define OV7670_REG_AWBC5   0x47
#define OV7670_REG_AWBC6   0x48
#define OV7670_REG_RSVD5   0x49
#define OV7670_REG_RSVD6   0x4A
#define OV7670_REG_REG4B   0x4B
#define OV7670_REG_DNSTH   0x4C
#define OV7670_REG_DMPOS   0x4D
#define OV7670_REG_RSVD7   0x4E
#define OV7670_REG_MTX1    0x4F
#define OV7670_REG_MTX2    0x50
#define OV7670_REG_MTX3    0x51
#define OV7670_REG_MTX4    0x52
#define OV7670_REG_MTX5    0x53
#define OV7670_REG_MTX6    0x54
#define OV7670_REG_BRIGHT  0x55
#define OV7670_REG_CONTR   0x56
#define OV7670_REG_CONTRC  0x57
#define OV7670_REG_MTXS    0x58
#define OV7670_REG_AWBC7   0x59
#define OV7670_REG_AWBC8   0x5A
#define OV7670_REG_AWBC9   0x5B
#define OV7670_REG_AWBC10  0x5C
#define OV7670_REG_AWBC11  0x5D
#define OV7670_REG_AWBC12  0x5E
#define OV7670_REG_BLMT    0x5F
#define OV7670_REG_RLMT    0x60
#define OV7670_REG_GLMT    0x61
#define OV7670_REG_LCC1    0x62
#define OV7670_REG_LCC2    0x63
#define OV7670_REG_LCC3    0x64
#define OV7670_REG_LCC4    0x65
#define OV7670_REG_LCC5    0x66
#define OV7670_REG_MANU    0x67
#define OV7670_REG_MANV    0x68
#define OV7670_REG_GFIX    0x69
#define OV7670_REG_GGAIN   0x6A
#define OV7670_REG_DBLV    0x6B
#define OV7670_REG_AWBCTL3 0x6C
#define OV7670_REG_AWBCTL2 0x6D
#define OV7670_REG_AWBCTL1 0x6E
#define OV7670_REG_AWBCTL0 0x6F
#define OV7670_REG_XSCALE  0x70
#define XSCALE_MASK     0x7F
#define OV7670_REG_YSCALE  0x71
#define YSCALE_MASK     0x7F
#define OV7670_REG_SCDCW   0x72
#define OV7670_REG_SCPCLK  0x73
#define OV7670_REG_REG74   0x74
#define OV7670_REG_REG75   0x75
#define OV7670_REG_REG76   0x76
#define OV7670_REG_REG77   0x77
#define OV7670_REG_RSVD9   0x79
#define OV7670_REG_SLOP    0x7A
#define OV7670_REG_GAM1    0x7B
#define OV7670_REG_GAM2    0x7C
#define OV7670_REG_GAM3    0x7D
#define OV7670_REG_GAM4    0x7E
#define OV7670_REG_GAM5    0x7F
#define OV7670_REG_GAM6    0x80
#define OV7670_REG_GAM7    0x81
#define OV7670_REG_GAM8    0x82
#define OV7670_REG_GAM9    0x83
#define OV7670_REG_GAM10   0x84
#define OV7670_REG_GAM11   0x85
#define OV7670_REG_GAM12   0x86
#define OV7670_REG_GAM13   0x87
#define OV7670_REG_GAM14   0x88
#define OV7670_REG_GAM15   0x89
/* Reserved 0x8A - 0x9C */
#define OV7670_REG_BD50ST  0x9D
#define OV7670_REG_BD60ST  0x9E
#define OV7670_REG_HRL     0x9F
#define OV7670_REG_LRL     0xA0
#define OV7670_REG_DSPC3   0xA1
#define OV7670_REG_SCPDLY  0xA2
#define OV7670_REG_RSVD10  0xA3
#define OV7670_REG_NTCTL   0xA4
#define OV7670_REG_AEGCMAX 0xA5
#define OV7670_REG_LPH     0xA6
#define OV7670_REG_UPL     0xA7
#define OV7670_REG_TPL     0xA8
#define OV7670_REG_TPH     0xA9
#define OV7670_REG_NALG    0xAA
#define OV7670_REG_RSVD11  0xAB
#define OV7670_REG_STROPT  0xAC
#define OV7670_REG_STR_R   0xAD
#define OV7670_REG_STR_G   0xAE
#define OV7670_REG_STR_B   0xAF
#define OV7670_REG_RSVD12  0xB0
#define OV7670_REG_ABLC1   0xB1
#define OV7670_REG_RSVD13  0xB2
#define OV7670_REG_THL_ST  0xB3
#define OV7670_REG_RSVD14  0xB4
#define OV7670_REG_THL_DLT 0xB5
/* Reserved 0xB6 - 0xBD */
#define OV7670_REG_ADCHB  0xBE
#define OV7670_REG_ADCHR  0xBF
#define OV7670_REG_ADCHGB 0xC0
#define OV7670_REG_ADCHGR 0xC1
/* Reserved 0xC2 - 0xC8 */
#define OV7670_REG_SATCTR 0xC9

#endif /* __OV7670_REG_H__ */
