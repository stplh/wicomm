//#ifndef _WIBC_H_
//#define _WIBC_H_

#include <plib.h>
#include "types.h"
#include "wibc_msg.h"

#define	GetPeripheralClock()		(SYS_FREQ/(1 << OSCCONbits.PBDIV))
#define	GetInstructionClock()		(SYS_FREQ)
#define DELAY_COUNT   (4096*8192)
#define SYS_FREQ (80000000L)



#define MAX_CMD_LEN 10

#define UARTDBG_MODULE 	(UART3)
#define UARTWIFI_MODULE (UART2)
#define UARTBC_MODULE	(UART1)


#define MAX_TXDATA 100

typedef struct {
	char cmd[MAX_CMD_LEN];
	int (*fun) (int, char **);
	char *help;
}wibc_cmds_t;

//#endif
