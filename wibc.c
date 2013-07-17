#include "wibc.h"
#include "config.h"

u8 WIBC_BANNER[]="WiFi Debug tool command line\n\n";

s32 wibc_init (void)
{
	wibc_uart_init(UARTDBG_MODULE);
	wibc_uart_init(UARTWIFI_MODULE);
	wibc_uart_init(UARTBC_MODULE);

	/* additional uart init.. goes here.
	 * wibc_uart_init(MODULESS...);
	 */

	/* TODO all initialization must go here only.
	 */
	return 0;
}

s32 wibc_show_banner(void)
{
	u8 fw_ver[50];
	sprintf(fw_ver, "FW Build Date %s Time %s \n\n",
				__DATE__ ,__TIME__);
	wibc_console_puts("*******************************************\n");
	wibc_console_puts(WIBC_BANNER);
	wibc_console_puts(fw_ver);
}

void main (void)
{
	s32 ret;
	/* 1. init
	 * 2. cli
	 * etc.... TODO
	 */

	ret = wibc_init();
	if (ret) exit(1);
	
	wibc_show_banner();

	do {
		wibc_cli();
	} while (1);
}
