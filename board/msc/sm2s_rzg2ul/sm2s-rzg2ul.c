#include <common.h>
#include <cpu_func.h>
#include <hang.h>
#include <image.h>
#include <init.h>
#include <malloc.h>
#include <netdev.h>
#include <dm.h>
#include <dm/platform_data/serial_sh.h>
#include <asm/processor.h>
#include <asm/mach-types.h>
#include <asm/io.h>
#include <linux/bitops.h>
#include <linux/errno.h>
#include <asm/arch/sys_proto.h>
#include <asm/gpio.h>
#include <asm/arch/gpio.h>
#include <asm/arch/rmobile.h>
#include <asm/arch/rcar-mstp.h>
#include <asm/arch/sh_sdhi.h>
#include <i2c.h>
#include <mmc.h>
#include <wdt.h>
#include <rzg2l_wdt.h>
#include "../common/boardinfo.h"
#include "../common/boardinfo_fdt.h"
#include "../common/som_variant.h"
#include <serial.h>


DECLARE_GLOBAL_DATA_PTR;

const board_info_t *binfo = NULL;

static variant_record_t variants[] = {
		FEATURE_RECORD ("92NON70E",
				REVISION_RECORD("10", SZ_512M, 0),
				),
		FEATURE_RECORD ("14N02C1I",
				REVISION_RECORD("10", SZ_2G, 0),
				),
		{ NULL },
};

#define ENV_FDTFILE_MAX_SIZE 		64

#define PFC_BASE	0x11030000

#define ETH_CH0		(PFC_BASE + 0x300c)
#define ETH_CH1		(PFC_BASE + 0x3010)
#define I2C_CH1                (PFC_BASE + 0x1870)
#define ETH_PVDD_3300	0x00
#define ETH_PVDD_1800	0x01
#define ETH_PVDD_2500	0x02
#define ETH_MII_RGMII	(PFC_BASE + 0x3018)

/* CPG */
#define CPG_BASE					0x11010000
#define CPG_CLKON_BASE				(CPG_BASE + 0x500)
#define CPG_RESET_BASE				(CPG_BASE + 0x800)
#define CPG_RESET_ETH				(CPG_RESET_BASE + 0x7C)
#define CPG_RESET_I2C                           (CPG_RESET_BASE + 0x80)
#define CPG_RST_USB				(CPG_BASE + 0x878)
#define CPG_CLKON_USB				(CPG_BASE + 0x578)

/* PFC */
#define	PFC_P10				(PFC_BASE + 0x0010)
#define	PFC_PM10			(PFC_BASE + 0x0120)
#define	PFC_PMC10			(PFC_BASE + 0x0210)

#define	PFC_P16				(PFC_BASE + 0x0016)
#define	PFC_P22				(PFC_BASE + 0x0022)
#define	PFC_PM16			(PFC_BASE + 0x012C)
#define	PFC_PM22			(PFC_BASE + 0x0144)
#define	PFC_PMC16			(PFC_BASE + 0x0216)
#define	PFC_PMC22			(PFC_BASE + 0x0222)

#define	PFC_P1D				(PFC_BASE + 0x001D)
#define	PFC_PM1D			(PFC_BASE + 0x013A)
#define	PFC_PMC1D			(PFC_BASE + 0x021D)

#define PFC_PWPR			(PFC_BASE + 0x3014)
#define PFC_PMC15			(PFC_BASE + 0x0215)
#define PFC_PFC15			(PFC_BASE + 0x0454)
#define PFC_PFC16			(PFC_BASE + 0x0458)

#define USBPHY_BASE		0x11c40000
#define USB0_BASE		0x11c50000
#define USB1_BASE		0x11c70000
#define USBF_BASE		0x11c60000
#define USBPHY_RESET		(USBPHY_BASE + 0x000u)
#define COMMCTRL		0x800
#define HcRhDescriptorA		0x048
#define LPSTS			0x102

#define RPC_CMNCR		0x10060000

/* WDT */
#define WDT_INDEX		0

typedef struct variant_key
{
	char	feature[BI_FEATURE_LEN + 1];
	char	revision[BI_REVISION_LEN + 1];
} t_variant_key;


static int read_string(char* buff, int buff_len)
{
	int idx = 0;

	while (idx < buff_len) {
		buff[idx] = serial_getc();
		putc(buff[idx]);
		if (buff[idx] == '\r' || buff[idx] == '\n' || buff[idx] == ' ')
			break;
		idx++;
	}

	buff[idx] = '\0';

	return idx;
}

static int readin_variant_key(t_variant_key *key)
{
	int ret;

	printf("Enter feature key for basic board initialization and hit <enter>.\n");
	printf("feature? > ");

	ret = read_string(key->feature, sizeof(key->feature));
	if (ret == 0)
		return -EINVAL;

	printf("\n");

	printf("Enter revision key for basic board initialization and hit <enter>.\n");
	printf("revision? > ");

	ret = read_string(key->revision, sizeof(key->revision));
	if (ret == 0)
		return -EINVAL;

	printf("\n");

	return 0;
}

void s_init(void)
{
	/* SD1 power control : P0_3 = 1 P6_1 = 1	*/
	*(volatile u8 *)(PFC_PMC10) &= 0xF7;	/* Port func mode 0b00	*/
	*(volatile u8 *)(PFC_PMC16) &= 0xFD;	/* Port func mode 0b00	*/
	*(volatile u16 *)(PFC_PM10) = (*(volatile u16 *)(PFC_PM10) & 0xFF3F) | 0x0080; /* Port output mode 0b10 */
	*(volatile u16 *)(PFC_PM16) = (*(volatile u16 *)(PFC_PM16) & 0xFFF3) | 0x0008; /* Port output mode 0b10 */
	*(volatile u8 *)(PFC_P10) = (*(volatile u8 *)(PFC_P10) & 0xF7) | 0x08; /* P0_3  output 1	*/
	*(volatile u8 *)(PFC_P16) = (*(volatile u8 *)(PFC_P16) & 0xFD) | 0x02; /* P6_1  output 1	*/

	/********************************************************************/
	/* TODO: Change the voltage setting according to the SW1-3 setting	*/
	/********************************************************************/
	/* can go in board_eht_init() once enabled */
	*(volatile u32 *)(ETH_CH0) = (*(volatile u32 *)(ETH_CH0) & 0xFFFFFFFC) | ETH_PVDD_1800;
	*(volatile u32 *)(ETH_CH1) = (*(volatile u32 *)(ETH_CH1) & 0xFFFFFFFC) | ETH_PVDD_3300;
	/* Enable RGMII for only ETH{0} */
	*(volatile u32 *)(ETH_MII_RGMII) = (*(volatile u32 *)(ETH_MII_RGMII) & 0xFFFFFFFC);
	/* ETH CLK */
	*(volatile u32 *)(CPG_RESET_ETH) = 0x30001;
	/* I2C CLK */
	*(volatile u32 *)(CPG_RESET_I2C) = 0xF000F;
	/* I2C pin non GPIO enable */
	*(volatile u32 *)(I2C_CH1) = 0x01010101;

	*(volatile u32 *)(RPC_CMNCR) = 0x01FFF300;
}

static void board_usb_init(void)
{
	/*Enable USB*/
	(*(volatile u32 *)CPG_RST_USB) = 0x000f000f;
	(*(volatile u32 *)CPG_CLKON_USB) = 0x000f000f;

	/* Setup  */
	/* Disable GPIO Write Protect */
	(*(volatile u32 *)PFC_PWPR) &= ~(0x1u << 7);    /* PWPR.BOWI = 0 */
	(*(volatile u32 *)PFC_PWPR) |= (0x1u << 6);     /* PWPR.PFCWE = 1 */

	/* set P5_0 as Func.1 for VBUSEN */
	(*(volatile u8 *)PFC_PMC15) |= (0x1u << 0);
	(*(volatile u8 *)PFC_PFC15) &= ~(0x7u << 0);
	(*(volatile u8 *)PFC_PFC15) |= (0x1u << 0);

	/* set P5_2 as Func.1 for OVERCUR */
	(*(volatile u8 *)PFC_PMC15) |= 0x4;
	(*(volatile u8 *)PFC_PFC15) &= ~(0x7u << 8);
	(*(volatile u8 *)PFC_PFC15) |= (0x1u << 8);

	/* set P6_0 as Func.1 for VBUSEN */
	(*(volatile u8 *)PFC_PMC16) |= (0x1u << 0);
	(*(volatile u8 *)PFC_PFC16) &= ~(0x7u << 0);
	(*(volatile u8 *)PFC_PFC16) |= (0x1u << 0);

	/* set P5_4 as Func.5 for OVERCUR */
	(*(volatile u8 *)PFC_PMC15) = (*(volatile u8 *)PFC_PMC15 & 0xEF) | 0x10;
	(*(volatile u32 *)PFC_PFC15) &= ~(0x7u << 16);
	(*(volatile u32 *)PFC_PFC15) |= (0x5u << 16);

	/* Enable write protect */
	(*(volatile u32 *)PFC_PWPR) &= ~(0x1u << 6);    /* PWPR.PFCWE = 0 */
	(*(volatile u32 *)PFC_PWPR) |= (0x1u << 7);     /* PWPR.BOWI = 1 */

	/*Enable 2 USB ports*/
	(*(volatile u32 *)USBPHY_RESET) = 0x00001000u;
	/*USB0 is HOST*/
	(*(volatile u32 *)(USB0_BASE + COMMCTRL)) = 0;
	/*USB1 is HOST*/
	(*(volatile u32 *)(USB1_BASE + COMMCTRL)) = 0;
	/* Set USBPHY normal operation (Function only) */
	(*(volatile u16 *)(USBF_BASE + LPSTS)) |= (0x1u << 14);		/* USBPHY.SUSPM = 1 (func only) */
	/* Overcurrent is not supported */
	(*(volatile u32 *)(USB0_BASE + HcRhDescriptorA)) |= (0x1u << 12);       /* NOCP = 1 */
	(*(volatile u32 *)(USB1_BASE + HcRhDescriptorA)) |= (0x1u << 12);       /* NOCP = 1 */
}

int board_early_init_f(void)
{

	return 0;
}

int board_init(void)
{
	t_variant_key key;
	bool input_binfo = false;
	const revision_record_t *rev;

#if 0 
	//CONFIG_TARGET_SMARC_RZG2UL
	struct udevice *dev;
	struct udevice *bus;
	const u8 pmic_bus = 0;
	const u8 pmic_addr = 0x58;
	u8 data;
	int ret;

	ret = uclass_get_device_by_seq(UCLASS_I2C, pmic_bus, &bus);
	if (ret)
		hang();

	ret = i2c_get_chip(bus, pmic_addr, 1, &dev);
	if (ret)
		hang();

	ret = dm_i2c_read(dev, 0x2, &data, 1);
	if (ret)
		hang();

	if ((data & 0x08) == 0) {
		printf("SW_ET0_EN: ON\n");
		*(volatile u32 *)(ETH_CH0) = (*(volatile u32 *)(ETH_CH0) & 0xFFFFFFFC) | ETH_PVDD_1800;
	} else {
		printf("SW_ET0_EN: OFF\n");
		*(volatile u32 *)(ETH_CH0) = (*(volatile u32 *)(ETH_CH0) & 0xFFFFFFFC) | ETH_PVDD_3300;
	}
#endif
	/* adress of boot parameters */
	gd->bd->bi_boot_params = CONFIG_SYS_TEXT_BASE + 0x50000;
	board_usb_init();
	binfo = bi_read();
	if (binfo == NULL) {
			printf("Warning: failed to initialize boardinfo!\n");
	} else{
		rev = find_revision_record(variants, bi_get_feature(binfo), bi_get_revision(binfo));
		if (rev == NULL) {
			printf("Warning: the content of the ID-EEPROM indicates \n"
					"   a module variant that is not supported by the software used!\n");
			printf("The current content is: \n");
			bi_print(binfo);

			printf("If the feature and revision keys should now be overwritten \n"
					"   with new contents press <o|O>? \n");

			while (true) {
				char ch = serial_getc();

				if (ch == 'o' || ch == 'O')
					break;

				hang();
			}

			input_binfo = true;
		}
	}

	if (input_binfo) {
		while (true) {
			print_variants(variants);

			if (readin_variant_key(&key) == 0) {
				rev = find_revision_record(variants, key.feature, key.revision);
				if (rev) {
					bi_set_feature(binfo, key.feature);
					bi_set_revision(binfo, key.revision);

					if (bi_save(binfo)) {
						printf("Error: the variant information could not be saved!\n");
					}
					else
						break;
				}
			}
		}
	}

	if (rev && (rev->dram_size[0] > 0) ) 
	{
		//updates ram size and reinit
		set_board_sdram_size(rev->dram_size[0], rev->dram_size[1]);

		dram_init_banksize();
	}
	return 0;
}

void reset_cpu(void)
{
#ifdef CONFIG_RENESAS_RZG2LWDT
	struct udevice *wdt_dev;
	if (uclass_get_device(UCLASS_WDT, WDT_INDEX, &wdt_dev) < 0) {
		printf("failed to get wdt device. cannot reset\n");
		return;
	}
	if (wdt_expire_now(wdt_dev, 0) < 0) {
		printf("failed to expire_now wdt\n");
	}
#endif // CONFIG_RENESAS_RZG2LWDT
}

int board_late_init(void)
{
	printf("sm2s board late init...\n");

#ifdef CONFIG_RENESAS_RZG2LWDT
	rzg2l_reinitr_wdt();
#endif // CONFIG_RENESAS_RZG2LWDT

        if (binfo) {
                const char *fdt;
                char buff[ENV_FDTFILE_MAX_SIZE];

#if defined(CONFIG_ENV_VARS_UBOOT_RUNTIME_CONFIG)
                env_set("bi_company", bi_get_company(binfo));
                env_set("bi_form_factor", bi_get_form_factor(binfo));
                env_set("bi_platform", bi_get_platform(binfo));
                env_set("bi_processor", bi_get_processor(binfo));
                env_set("bi_feature", bi_get_feature(binfo));
                env_set("bi_serial", bi_get_serial(binfo));
                env_set("bi_revision", bi_get_revision(binfo));
#endif

                fdt = env_get("fdt_module");
                if ( (fdt == NULL) || (!strcmp(fdt, "undefined")) ) {
                        snprintf(buff, ENV_FDTFILE_MAX_SIZE, "%s-%s-%s-%s-%s-module.dtb",
                                        bi_get_company(binfo), bi_get_form_factor(binfo), bi_get_platform(binfo),
                                        bi_get_processor(binfo), bi_get_feature(binfo));
                        env_set("fdt_module", buff);
						env_set("name_fdt", buff);
						env_set("default_device_tree", buff);
                }
        }

	return 0;
}
