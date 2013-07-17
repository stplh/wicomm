#include "wibc.h"

void wibc_uart_txready_wait (s32 uart_id)
{
	while(!UARTTransmitterIsReady(uart_id));
}

void wibc_uart_txcomp_wait (s32 uart_id)
{
	while(!UARTTransmissionHasCompleted(uart_id));
}

void wibc_uart_tx_byte (s32 uart_id, const u8 ch)
{
	UARTSendDataByte(uart_id, ch);
}

void wibc_uart_tx (s32 uart_id, const u8 *buf, s32 size)
{
	while(size) {	
		wibc_uart_txready_wait(uart_id);
		wibc_uart_tx_byte(uart_id, *buf);
		buf++;
		size--;
	}
	wibc_uart_txcomp_wait(uart_id);
}

void wibc_uart_rxready_wait (s32 uart_id)
{
	while(!UARTReceivedDataIsAvailable(uart_id));
}

u32 wibc_uart_rx_byte (s32 uart_id)
{
	return UARTGetDataByte(uart_id);
}

#ifdef _dis_
s32 wibc_uart_rx (s32 uart_id, u8 *buf)
{
	s32 rxchars = 0;
	u8 ch;

	while(1) {
		wibc_uart_rxready_wait(uart_id);
		ch = wibc_uart_rx_byte(uart_id);
		
		wibc_uart_tx(UARTDBG_MODULE, &ch, 1);
		if (uart_id == UARTDBG_MODULE) {
			/* echo back */
			wibc_uart_txready_wait(uart_id);
			wibc_uart_tx_byte(uart_id, ch);
		}
		if (ch == '\n') break; 

		*buf = ch;
		buf++;
		rxchars++;
	}

	return rxchars;
}
#else
s32 wibc_uart_rx (s32 uart_id, u8 *buf, s32 size)
{
	s32 rxcnt = 0;
	u8 ch;

	while (1) {
		wibc_uart_rxready_wait(uart_id);
		ch = wibc_uart_rx_byte(uart_id);

		if (uart_id == UARTDBG_MODULE) {
			/* ECHO on console */
			wibc_uart_tx(uart_id, &ch, 1);
			/* console uart tx called with size = 0 */
			if (ch == '\n') break;
		}
		*buf = ch;
		buf++;
		rxcnt++;
		/* else.. for wifi comm, depends on size */
		if (rxcnt == size) break;
	}

	return rxcnt;
}
#endif
/* console display wrappers */
void wibc_console_puts(u8 *buf)
{
	s32 size;
	size = strlen(buf);
	wibc_uart_tx(UARTDBG_MODULE, buf, size);
}

s32 wibc_console_gets(u8 *buf)
{
	return wibc_uart_rx(UARTDBG_MODULE, buf, 0);
}

void wibc_uart_init (s32 uart_id)
{
	UARTConfigure(uart_id, 
			UART_ENABLE_PINS_TX_RX_ONLY);

	UARTSetFifoMode(uart_id, 
			UART_INTERRUPT_ON_TX_NOT_FULL | 
			UART_INTERRUPT_ON_RX_NOT_EMPTY);

	UARTSetLineControl(uart_id, 
			UART_DATA_SIZE_8_BITS | 
			UART_PARITY_NONE | 
			UART_STOP_BITS_1);
	UARTSetDataRate(uart_id, 
			GetPeripheralClock(), 9600);
	UARTEnable(uart_id, UART_ENABLE_FLAGS(UART_PERIPHERAL|
						UART_RX|
						UART_TX));
}

