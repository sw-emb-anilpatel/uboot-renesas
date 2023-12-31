// SPDX-License-Identifier: GPL-2.0+
/*
 * Copyright (c) 2021, Renesas Electronics Corporation. All rights reserved.
 */

#ifndef _RZF_DEV_SPI_MULTI_REG_H_
#define _RZF_DEV_SPI_MULTI_REG_H_

#define	SPI_MULTI_BASE				(0x10060000)
#define	SPI_MULTI_BUF				(0x10070000)

#define SPIM_CMNCR					(SPI_MULTI_BASE + 0x00000000)	/* Common control register */
#define SPIM_SSLDR					(SPI_MULTI_BASE + 0x00000004)	/* SSL delay register */
#define SPIM_DRCR					(SPI_MULTI_BASE + 0x0000000C)	/* Data read control register */
#define SPIM_DRCMR					(SPI_MULTI_BASE + 0x00000010)	/* Data read command setting register */
#define SPIM_DREAR					(SPI_MULTI_BASE + 0x00000014)	/* Data read extended address setting register */
#define SPIM_DROPR					(SPI_MULTI_BASE + 0x00000018)	/* Data read option setting register */
#define SPIM_DRENR					(SPI_MULTI_BASE + 0x0000001C)	/* Data read enable setting register */
#define SPIM_SMCR					(SPI_MULTI_BASE + 0x00000020)	/* Manual mode control register */
#define SPIM_SMCMR					(SPI_MULTI_BASE + 0x00000024)	/* Manual mode command setting register */
#define SPIM_SMADR					(SPI_MULTI_BASE + 0x00000028)	/* Manual mode address setting register */
#define SPIM_SMOPR					(SPI_MULTI_BASE + 0x0000002C)	/* Manual mode option setting register */
#define SPIM_SMENR					(SPI_MULTI_BASE + 0x00000030)	/* Manual mode enable setting register */
#define SPIM_SMRDR0					(SPI_MULTI_BASE + 0x00000038)	/* Manual mode read data register 0 */
#define SPIM_SMRDR1					(SPI_MULTI_BASE + 0x0000003C)	/* Manual mode read data register 1 */
#define SPIM_SMWDR0					(SPI_MULTI_BASE + 0x00000040)	/* Manual mode write data register 0 */
#define SPIM_SMWDR1					(SPI_MULTI_BASE + 0x00000044)	/* Manual mode write data register 1 */
#define SPIM_CMNSR					(SPI_MULTI_BASE + 0x00000048)	/* Common status register */
#define SPIM_DRDMCR					(SPI_MULTI_BASE + 0x00000058)	/* Data read dummy cycle setting register */
#define SPIM_DRDRENR				(SPI_MULTI_BASE + 0x0000005C)	/* Data read DDR enable register */
#define SPIM_SMDMCR					(SPI_MULTI_BASE + 0x00000060)	/* Manual mode dummy cycle setting register */
#define SPIM_SMDRENR				(SPI_MULTI_BASE + 0x00000064)	/* Manual mode DDR enable register */
#define SPIM_PHYCNT					(SPI_MULTI_BASE + 0x0000007C)	/* PHY control register */
#define SPIM_PHYOFFSET1				(SPI_MULTI_BASE + 0x00000080)	/* PHY offset register 1 */
#define SPIM_PHYOFFSET2				(SPI_MULTI_BASE + 0x00000084)	/* PHY offset register 2 */
#define SPIM_PHYINT					(SPI_MULTI_BASE + 0x00000088)	/* PHY interrupt register */
#define SPIM_PHYADJ1				(SPI_MULTI_BASE + 0x00000070)	/* PHY adjustment register 1 */
#define SPIM_PHYADJ2				(SPI_MULTI_BASE + 0x00000074)	/* PHY adjustment register 2 */

#define CMNCR_BSZ_FLASH_NUM_1				(0 << 0)
#define CMNCR_BSZ_FLASH_NUM_2				(1 << 0)
#define CMNCR_IO0FV_OUT0					(0 << 8)
#define CMNCR_IO0FV_OUT1					(1 << 8)
#define CMNCR_IO0FV_OUT_PREV				(2 << 8)
#define CMNCR_IO0FV_HIZ						(3 << 8)
#define CMNCR_IO2FV_OUT0					(0 << 12)
#define CMNCR_IO2FV_OUT1					(1 << 12)
#define CMNCR_IO2FV_OUT_PREV				(2 << 12)
#define CMNCR_IO2FV_HIZ						(3 << 12)
#define CMNCR_IO3FV_OUT0					(0 << 14)
#define CMNCR_IO3FV_OUT1					(1 << 14)
#define CMNCR_IO3FV_OUT_PREV				(2 << 14)
#define CMNCR_IO3FV_HIZ						(3 << 14)
#define CMNCR_DEF_DATA						(1 << 24)
#define CMNCR_MOIIO0_OUT0					(0 << 16)
#define CMNCR_MOIIO0_OUT1					(1 << 16)
#define CMNCR_MOIIO0_OUT_PREV				(2 << 16)
#define CMNCR_MOIIO0_HIZ					(3 << 16)
#define CMNCR_MOIIO1_OUT0					(0 << 18)
#define CMNCR_MOIIO1_OUT1					(1 << 18)
#define CMNCR_MOIIO1_OUT_PREV				(2 << 18)
#define CMNCR_MOIIO1_HIZ					(3 << 18)
#define CMNCR_MOIIO2_OUT0					(0 << 20)
#define CMNCR_MOIIO2_OUT1					(1 << 20)
#define CMNCR_MOIIO2_OUT_PREV				(2 << 20)
#define CMNCR_MOIIO2_HIZ					(3 << 20)
#define CMNCR_MOIIO3_OUT0					(0 << 22)
#define CMNCR_MOIIO3_OUT1					(1 << 22)
#define CMNCR_MOIIO3_OUT_PREV				(2 << 22)
#define CMNCR_MOIIO3_HIZ					(3 << 22)
#define CMNCR_MD							(1 << 31)
#define SSLDR_SCKDL_1_5						(0 << 0)
#define SSLDR_SCKDL_2_5						(1 << 0)
#define SSLDR_SCKDL_3_5						(2 << 0)
#define SSLDR_SCKDL_4_5						(3 << 0)
#define SSLDR_SCKDL_5_5						(4 << 0)
#define SSLDR_SCKDL_6_5						(5 << 0)
#define SSLDR_SCKDL_7_5						(6 << 0)
#define SSLDR_SCKDL_8_5						(7 << 0)
#define SSLDR_SLNDL_1QSPIn					(0 << 8)
#define SSLDR_SLNDL_2QSPIn					(1 << 8)
#define SSLDR_SLNDL_3QSPIn					(2 << 8)
#define SSLDR_SLNDL_4QSPIn					(3 << 8)
#define SSLDR_SLNDL_5QSPIn					(4 << 8)
#define SSLDR_SLNDL_6QSPIn					(5 << 8)
#define SSLDR_SLNDL_7QSPIn					(6 << 8)
#define SSLDR_SLNDL_8QSPIn					(7 << 8)
#define SSLDR_SPNDL_1QSPIn					(0 << 16)
#define SSLDR_SPNDL_2QSPIn					(1 << 16)
#define SSLDR_SPNDL_3QSPIn					(2 << 16)
#define SSLDR_SPNDL_4QSPIn					(3 << 16)
#define SSLDR_SPNDL_5QSPIn					(4 << 16)
#define SSLDR_SPNDL_6QSPIn					(5 << 16)
#define SSLDR_SPNDL_7QSPIn					(6 << 16)
#define SSLDR_SPNDL_8QSPIn					(7 << 16)
#define DRCR_SSLE							(1 << 0)
#define DRCR_RBE							(1 << 8)
#define DRCR_RCF							(1 << 9)
#define DRCR_RBURST_1_DATALEN				(0 << 16)
#define DRCR_RBURST_2_DATALEN				(1 << 16)
#define DRCR_RBURST_3_DATALEN				(2 << 16)
#define DRCR_RBURST_4_DATALEN				(3 << 16)
#define DRCR_RBURST_5_DATALEN				(4 << 16)
#define DRCR_RBURST_6_DATALEN				(5 << 16)
#define DRCR_RBURST_7_DATALEN				(6 << 16)
#define DRCR_RBURST_8_DATALEN				(7 << 16)
#define DRCR_RBURST_9_DATALEN				(8 << 16)
#define DRCR_RBURST_10_DATALEN				(9 << 16)
#define DRCR_RBURST_11_DATALEN				(10 << 16)
#define DRCR_RBURST_12_DATALEN				(11 << 16)
#define DRCR_RBURST_13_DATALEN				(12 << 16)
#define DRCR_RBURST_14_DATALEN				(13 << 16)
#define DRCR_RBURST_15_DATALEN				(14 << 16)
#define DRCR_RBURST_16_DATALEN				(15 << 16)
#define DRCR_RBURST_17_DATALEN				(16 << 16)
#define DRCR_RBURST_18_DATALEN				(17 << 16)
#define DRCR_RBURST_19_DATALEN				(18 << 16)
#define DRCR_RBURST_20_DATALEN				(19 << 16)
#define DRCR_RBURST_21_DATALEN				(20 << 16)
#define DRCR_RBURST_22_DATALEN				(21 << 16)
#define DRCR_RBURST_23_DATALEN				(22 << 16)
#define DRCR_RBURST_24_DATALEN				(23 << 16)
#define DRCR_RBURST_25_DATALEN				(24 << 16)
#define DRCR_RBURST_26_DATALEN				(25 << 16)
#define DRCR_RBURST_27_DATALEN				(26 << 16)
#define DRCR_RBURST_28_DATALEN				(27 << 16)
#define DRCR_RBURST_29_DATALEN				(28 << 16)
#define DRCR_RBURST_30_DATALEN				(29 << 16)
#define DRCR_RBURST_31_DATALEN				(30 << 16)
#define DRCR_RBURST_32_DATALEN				(31 << 16)
#define DRCR_SSLN							(1 << 24)
#define DREAR_EAC_EXADDR24					(0 << 0)
#define DREAR_EAC_EXADDR25					(1 << 0)
#define DREAR_EAC_EXADDR26					(2 << 0)
#define DREAR_EAC_EXADDR27					(3 << 0)
#define DRENR_OPDE_NO_OUT					(0 << 4)
#define DRENR_OPDE_OPD3_OUT					(8 << 4)
#define DRENR_OPDE_OPD32_OUT				(12 << 4)
#define DRENR_OPDE_OPD321_OUT				(14 << 4)
#define DRENR_OPDE_OPD3210_OUT				(15 << 4)
#define DRENR_ADE_NO_OUT					(0 << 8)
#define DRENR_ADE_ADD23_OUT					(7 << 8)
#define DRENR_ADE_ADD31_OUT					(15 << 8)
#define DRENR_ADE_OCTA_FLASH				(12 << 8)
#define DRENR_ADE_HYPER_FLASH				(4 << 8)
#define DRENR_OCDE							(1 << 12)
#define DRENR_CDE							(1 << 14)
#define DRENR_DME							(1 << 15)
#define DRENR_DRDB_1BIT						(0 << 16)
#define DRENR_DRDB_4BIT						(2 << 16)
#define DRENR_OPDB_1BIT						(0 << 20)
#define DRENR_OPDB_4BIT						(2 << 20)
#define DRENR_ADB_1BIT						(0 << 24)
#define DRENR_ADB_4BIT						(2 << 24)
#define DRENR_OCDB_1BIT						(0 << 28)
#define DRENR_OCDB_4BIT						(2 << 28)
#define DRENR_CDB_1BIT						(0 << 30)
/* #define DRENR_CDB_4BIT						(2 << 30) */
#define DRENR_CDB_4BIT						(0x80000000)
#define SMCR_SPIE							(1 << 0)
#define SMCR_SPIWE							(1 << 1)
#define SMCR_SPIRE							(1 << 2)
#define SMCR_SSLKP							(1 << 8)
#define SMENR_SPIDE_NO_SEND					(0 << 0)
#define SMENR_SPIDE_8BIT_SEND				(8 << 0)
#define SMENR_SPIDE_16BIT_SEND				(12 << 0)
#define SMENR_SPIDE_32BIT_SEND				(15 << 0)
#define SMENR_OPDE_NO_OUT					(0 << 4)
#define SMENR_OPDE_OPD3_OUT					(8 << 4)
#define SMENR_OPDE_OPD32_OUT				(12 << 4)
#define SMENR_OPDE_OPD321_OUT				(14 << 4)
#define SMENR_OPDE_OPD3210_OUT				(15 << 4)
#define SMENR_ADE_NO_OUT					(0 << 8)
#define SMENR_ADE_ADR23_16_OUT				(4 << 8)
#define SMENR_ADE_ADR23_8_OUT				(6 << 8)
#define SMENR_ADE_ADR23_0_OUT				(7 << 8)
#define SMENR_ADE_ADR31_0_OUT				(15 << 8)
#define SMENR_OCDE							(1 << 12)
#define SMENR_CDE							(1 << 14)
#define SMENR_DME							(1 << 15)
#define SMENR_SPIDB_1BIT					(0 << 16)
#define SMENR_SPIDB_4BIT					(2 << 16)
#define SMENR_OPDB_1BIT						(0 << 20)
#define SMENR_OPDB_4BIT						(2 << 20)
#define SMENR_ADB_1BIT						(0 << 24)
#define SMENR_ADB_4BIT						(2 << 24)
#define SMENR_OCDB_1BIT						(0 << 28)
#define SMENR_OCDB_4BIT						(2 << 28)
#define SMENR_CDB_1BIT						(0 << 30)
#define SMENR_CDB_4BIT						(2 << 30)
#define CMNSR_TEND							(1 << 0)
#define CMNSR_SSLF							(1 << 1)
#define DRDRENR_DRDRE						(1 << 0)
#define DRDRENR_OPDRE						(1 << 4)
#define DRDRENR_ADDRE						(1 << 8)
#define DRDRENR_HYPE_HYPER					(5 << 12)
#define DRDRENR_HYPE_OCTA					(4 << 12)
#define DRDRENR_HYPE_SPI					(0 << 12)
#define SMDRENR_SPIDRE						(1 << 0)
#define SMDRENR_OPDRE						(1 << 4)
#define SMDRENR_ADDRE						(1 << 8)
#define SMDRENR_HYPE_HYPER_FLASH			(5 << 12)
#define SMDRENR_HYPE_OCTA_FLASH				(4 << 12)
#define SMDRENR_HYPE_SPI_FLASH				(0 << 12)
#define PHYCNT_PHYMEM_SDR_MODE				(0 << 0)
#define PHYCNT_PHYMEM_DDR_MODE				(1 << 0)
#define PHYCNT_PHYMEM_HYPER_FLASH			(3 << 0)
#define PHYCNT_WBUF							(1 << 2)
#define PHYCNT_WBUF2						(1 << 4)
#define PHYCNT_CKSEL_SLOW					(0 << 16)
#define PHYCNT_CKSEL_FAST					(3 << 16)
#define PHYCNT_HS							(1 << 18)
#define PHYCNT_OCT							(1 << 21)
#define PHYCNT_EXDS							(1 << 21)
#define PHYCNT_OCTA_HYPER_FLASH				(0 << 22)
#define PHYCNT_OCTA_ALTE					(1 << 22)
#define PHYCNT_OCTA_ORDER					(2 << 22)
#define PHYCNT_ALT_ALIGN					(1 << 30)
#define PHYCNT_CAL							(1 << 31)
#define PHYCNT_DEF_DATA						(0x00000260)
#define PHYOFFSET1_DDRTMG_SPIDRE_1			(2 << 28)
#define PHYOFFSET1_DDRTMG_SPIDRE_0			(3 << 28)
#define PHYOFFSET1_DEF_DATA					(0x01511144)
#define PHYOFFSET2_OCTTMG_HYPER_FLASH		(4 << 8)
#define PHYOFFSET2_OCTTMG_OCTA_FLASH		(3 << 8)
#define PHYOFFSET2_DEF_DATA					(0x00000431)
#define PHYINT_INT							(1 << 0)
#define PHYINT_WPVAL						(1 << 1)
#define PHYINT_RSTVAL						(1 << 2)
#define PHYINT_INTEN						(1 << 24)
#define PHYINT_WPEN							(1 << 25)
#define PHYINT_RSTEN						(1 << 26)

#define DREAR_EAV_ADDRE_DATA				(2 << 16)

#define DRCMR_CMD_FAST_READ_3B						(0x0B << 16)
#define DRCMR_CMD_QUAD_OUTPUT_FAST_READ_3B			(0x6B << 16)
#define DRCMR_CMD_QUAD_INPUT_OUTPUT_FAST_READ_3B	(0xEB << 16)
#define DRCMR_CMD_FAST_READ_4B						(0x0C << 16)
#define DRCMR_CMD_QUAD_OUTPUT_FAST_READ_4B			(0x6C << 16)
#define DRCMR_CMD_QUAD_INPUT_OUTPUT_FAST_READ_4B	(0xEC << 16)

#endif	/* _RZF_DEV_SPI_MULTI_REG_H_ */

