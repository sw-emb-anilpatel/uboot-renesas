/* SPDX-License-Identifier: GPL-2.0+ */
/*
 * Configuration header file for sm2s-rzg2l
 *
 * Copyright (C) 2023 AVNET Embedded, MSC Technologies GmbH
 */

#ifndef __MSC_SM2S_RZG2L_H
#define __MSC_SM2S_RZG2L_H

#include <asm/arch/rmobile.h>

#define CONFIG_REMAKE_ELF

#ifdef CONFIG_SPL
#define CONFIG_SPL_TARGET	"spl/u-boot-spl.scif"
#endif

/* boot option */

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG

/* Generic Interrupt Controller Definitions */
/* RZ/G2L use GIC-v3 */
#define CONFIG_GICV3
#define GICD_BASE	0x11900000
#define GICR_BASE	0x11960000

/* console */
#define CONFIG_SYS_CBSIZE		2048
#define CONFIG_SYS_BARGSIZE		CONFIG_SYS_CBSIZE
#define CONFIG_SYS_MAXARGS		64
#define CONFIG_SYS_BAUDRATE_TABLE	{ 115200, 38400 }

/* PHY needs a longer autoneg timeout */
#define PHY_ANEG_TIMEOUT		20000

/* MEMORY */
#define CONFIG_SYS_INIT_SP_ADDR		CONFIG_SYS_TEXT_BASE

/* SDHI clock freq */
#define CONFIG_SH_SDHI_FREQ		133000000

#define DRAM_RSV_SIZE			0x08000000
#define CONFIG_SYS_SDRAM_BASE		(0x40000000 + DRAM_RSV_SIZE)
#define CONFIG_SYS_SDRAM_SIZE		(0x80000000u - DRAM_RSV_SIZE) //total 2GB
#define CONFIG_SYS_LOAD_ADDR		0x58000000
#define CONFIG_LOADADDR			CONFIG_SYS_LOAD_ADDR // Default load address for tfpt,bootp...
#define CONFIG_VERY_BIG_RAM
#define CONFIG_MAX_MEM_MAPPED		(0x80000000u - DRAM_RSV_SIZE)

#define CONFIG_SYS_MONITOR_BASE		0x00000000
#define CONFIG_SYS_MONITOR_LEN		(1 * 1024 * 1024)
#define CONFIG_SYS_MALLOC_LEN		(64 * 1024 * 1024)
#define CONFIG_SYS_BOOTM_LEN		(64 << 20)

/* The HF/QSPI layout permits up to 1 MiB large bootloader blob */
#define CONFIG_BOARD_SIZE_LIMIT		1048576

/* Set I2C and EEPROM related config required for boardinfo and bootsel*/
#define CONFIG_SYS_I2C_SPEED            100000
#define I2C_GP          0
#define I2C_PM          1
#define I2C_DEV         2
#define I2C_LCD         3
#define I2C_CAM         4
#define BI_EEPROM_I2C_ADDR      0x50
#define PMIC_I2C_ADDR           0x30

/* ENV setting */

#define BOOTDEV_SD \
        "boot_sd=" \
                "run image_addr_check; run fdtaddr_check; run sd_bootargs; mmc dev 0; ext4load mmc 0:2 ${image_addr} boot/Image; ext4load mmc 0:2 ${fdtaddr} boot/${name_fdt}; ext4load mmc 0:2 ${fdtovaddr} boot/${name_overlay}; fdt addr ${fdtaddr}; fdt resize 8192; fdt apply ${fdtovaddr}; booti ${image_addr} - ${fdtaddr}" \
		"\0"

#define BOOTDEV_EMMC \
        "boot_emmc=" \
                "run image_addr_check; run fdtaddr_check; run emmc_bootargs; mmc dev 1; ext4load mmc 1:2 ${image_addr} boot/Image; ext4load mmc 1:2 ${fdtaddr} boot/${name_fdt}; ext4load mmc 1:2 ${fdtovaddr} boot/${name_overlay}; fdt addr ${fdtaddr}; fdt resize 8192; fdt apply ${fdtovaddr}; booti ${image_addr} - ${fdtaddr}" \
                "\0"


#define CONFIG_EXTRA_ENV_SETTINGS \
	BOOTDEV_SD \
	BOOTDEV_EMMC \
	"usb_pgood_delay=2000\0" \
	"bootm_size=0x10000000 \0" \
	"fdtovaddr=0x48c00000 \0" \
	"RR_mem=0 \0" \
	"image_addr_check=if test ${RR_mem} -eq 0; then setenv image_addr 0x4A080000; else setenv image_addr 0x40280000; fi \0" \
	"fdtaddr_check=if test ${RR_mem} -eq 0; then setenv fdtaddr 0x48000000; else setenv image_addr 0x40200000; fi \0" \
	"name_overlay='' \0" \
	"sd_bootargs=setenv bootargs rw rootwait earlycon root=/dev/mmcblk0p2 \0" \
	"emmc_bootargs=setenv bootargs rw rootwait earlycon root=/dev/mmcblk1p2 \0" \
	"bootimage=unzip 0x4A080000 0x48080000; booti 0x48080000 - 0x48000000 \0" \
	"bootcmd_check=if mmc dev 1; then run sd1load; else run emmcload; fi \0"

#define CONFIG_BOOTCOMMAND     "if boardinfo complete; then if bootsel; then if run boot_${bootdev}; then; exit; fi; else echo ERR: Aborting boot OS, invalid boot device!; false; fi; else echo ERR: Aborting boot OS, boardinfo is not complete!; false; fi;"


/* For board */
/* Ethernet RAVB */
#define CONFIG_BITBANGMII_MULTI

#endif /* __MSC_SM2S_RZG2L_H */
