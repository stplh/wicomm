#include "wibc.h"

s32 wibc_cmd_help(s32 argc, s8 argv[][10]);
s32 wibc_cmd_tx(s32 argc, s8 argv[][10]);
s32 wibc_cmd_rx(s32 argc, s8 argv[][10]);
s32 wibc_cmd_bc(s32 argc, s8 argv[][10]);

wibc_cmds_t cmds[] = {
	{"tx", wibc_cmd_tx, "usage: tx "},
	{"rx", wibc_cmd_rx, "usage: rx "},
	{"bc", wibc_cmd_bc, "usage: bc "},
	{"help", wibc_cmd_help, "usage: show this menu"},
};

void wibc_console_puti(s32 val)
{
	u8 tmp[10];
	sprintf(tmp, "%02x \n", val);
	wibc_console_puts(tmp);
}

s32 wibc_cmd_bc(s32 argc, s8 argv[][10])
{
	u8 bufbc[13];
	s32 ret;
	wibc_msg_t msg;
	u8 *pchar;
	u8 mac[3] = {0x00,0x00,0x00};
	s32 ii;
	u8 buf[10];
	ret = wibc_uart_rx(UARTWIFI_MODULE, bufbc, 13);
	for (ii=0; ii<13; ii++) {
		wibc_console_puti(bufbc[ii]);
	}
	
	wibc_console_puts( "bc command ..\n");
	msg.sop = 0xfb;
	wibc_console_puti(msg.sop);
	msg.len = 17;
	wibc_console_puti(msg.len);
	msg.cmd = WIBC_DNTCMD_TXDATA;
	wibc_console_puti(msg.cmd);
	msg.mac[0] = 0x00;
	msg.mac[1] = 0x00;
	msg.mac[2] = 0x00;
	for (ii=0; ii<13; ii++) {
		msg.data[ii] = bufbc[ii];
		wibc_console_puti(msg.data[ii]);
	}
	
	pchar = (u8*)&msg;
	for (ii=0; ii<msg.len+2; ii++) {
		wibc_uart_tx(UARTWIFI_MODULE, (pchar+ii), 1);
	}
	wibc_console_puts( "bc done.\n");
}
#ifdef _dis_
s32 wibc_cmd_tx(s32 argc, s8 *argv[])
{
	s32 ii;
	u8 tx_cmd[100] = {0xFB, 0x13, 0x05, 0x00, 0x00, 0x00, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0x31, 0x32, 0x33};
	wibc_console_puts( "tx command... processing..\n");
	wibc_console_puts( tx_cmd);
	for (ii=0; ii<18+2; ii++) {
		//wibc_uart_tx (UARTDBG_MODULE, &tx_cmd[ii], 1);
		wibc_uart_tx (UARTWIFI_MODULE, &tx_cmd[ii], 1);
	}

	wibc_console_puts( "wibc tx done..\n");
}
#else
void wibc_setup_hdr (wibc_msg_t *msg, u8 type, u8 *mac, u8 len)
{
	msg->sop = 0xfb;
	msg->len = len;
	msg->cmd = type;
	msg->mac[0] = mac[0];
	msg->mac[1] = mac[1];
	msg->mac[2] = mac[2];
}
/* cmd: tx uart# macaddr <data>
 */
s32 wibc_cmd_tx(s32 argc, s8 argv[][10])
{
	wibc_msg_t msg;
	u8 *pchar;
	u8 mac[3] = {0x00,0x00,0x00};
	s32 ii;
	u8 buf[10];
	
	wibc_console_puts( "TX command ..\n");
	msg.sop = 0xfb;
	wibc_console_puti(msg.sop);
	msg.len = 20;
	wibc_console_puti(msg.len);
	msg.cmd = WIBC_DNTCMD_TXDATA;
	wibc_console_puti(msg.cmd);
	msg.mac[0] = 0x00;
	msg.mac[1] = 0x00;
	msg.mac[2] = 0x00;
	for (ii=0; ii<16; ii++) {
		msg.data[ii] = ii+1;
		wibc_console_puti(msg.data[ii]);
	}
	
	
	pchar = (u8*)&msg;
	for (ii=0; ii<msg.len+2; ii++) {
		wibc_uart_tx(UARTWIFI_MODULE, (pchar+ii), 1);
	}
	wibc_console_puts( "tx done.\n");
	/* verify txdatareply pkt. 
	wibc_uart_rx(UARTWIFI_MODULE, buf, 2);
	//wibc_console_puti(buf[0]);
	//wibc_console_puti(buf[1]);
	if (buf[0] == 0xfb) {
		wibc_uart_tx(UARTWIFI_MODULE, buf, buf[1]);
	}
	for(ii=0; ii<buf[1]+2; ii++) {
		wibc_console_puti(buf[ii]);
	}
	*/
	//for (ii=0; ii<6;ii++) {
	//	wibc_uart_rx(UARTWIFI_MODULE, buf, 1);
	//	wibc_uart_tx(UARTDBG_MODULE, &buf[0], 1);
	//}
	//wibc_uart_tx(UARTDBG_MODULE, pchar, msg.len+6);
#if 0
	u8 uart_id;
	u8 mac[3];
	u8 *data;
	u8 datalen;
	u8 *pchar;
	s32 ii;

	wibc_console_puts( "in tx..\n");
	wibc_uart_tx(UARTDBG_MODULE, argv[0], wibc_strlen(argv[0]));
	wibc_uart_tx(UARTDBG_MODULE, argv[1], wibc_strlen(argv[1]));
	wibc_uart_tx(UARTDBG_MODULE, argv[2], wibc_strlen(argv[2]));
	wibc_uart_tx(UARTDBG_MODULE, argv[3], wibc_strlen(argv[3]));
	if (argc != 4) return -1;
	sscanf(argv[1], "%d", &uart_id);
	sscanf(argv[2], "%s", mac);
	data = argv[3];
	
	datalen = strlen(data);
	
	/* setup hdr */
	wibc_setup_hdr(&msg,
					WIBC_DNTCMD_TXDATA, 
					mac,
					datalen);
	pchar = (u8*)&msg;
	wibc_uart_tx(UARTDBG_MODULE, "show", 4);
	wibc_console_puti(msg.len);
	wibc_console_puti(uart_id);

	for (ii=0; ii<msg.len+WIBC_DNTHDR_SIZE; ii++) {
		wibc_uart_tx(UARTDBG_MODULE, (pchar+ii), 1);
	}
	wibc_uart_tx(UARTDBG_MODULE, &msg, msg.len + WIBC_DNTHDR_SIZE);
#endif
}
#endif
#ifdef _dis_
s32 wibc_cmd_rx(s32 argc, s8 argv[][10])
{
	u8 buf[100];

	wibc_console_puts("Rx waiting on Wifi module...\n");
	wibc_console_gets(UARTWIFI_MODULE, buf);	
	wibc_console_puts("rx done\n");
	wibc_console_puts(buf);
	wibc_console_puts("\n");
}
#else
s32 wibc_cmd_rx(s32 argc, s8 argv[][10])
{
	u8 buf[100];
	s32 ii;
	s32 reqlen;
	s32 ret;
#ifndef _scantest_
	ret = wibc_uart_rx(UARTWIFI_MODULE, buf, 13);
	for (ii=0; ii<13; ii++) {
		wibc_console_puti(buf[ii]);
	}
#else
	ret = wibc_uart_rx(UARTWIFI_MODULE, buf, 2);
	if (buf[0] != 0xfb) return 0;
	reqlen = buf[1];
	ret = wibc_uart_rx(UARTWIFI_MODULE, buf+2, reqlen); // why +1 ?? TODO
	for (ii=0; ii<reqlen+2; ii++) {
		wibc_console_puti(buf[ii]);
	}
#endif
	//wibc_uart_tx(UARTDBG_MODULE, buf, 6);
	//wibc_console_puts("\n");
}
#endif
s32 wibc_cmd_help(s32 argc, s8 argv[][10])
{	
	s32 ii;
	u8 cmdhelp[50];
	wibc_console_puts("List of commands\n\n");
	for (ii=0; ii<(sizeof(cmds)/sizeof(wibc_cmds_t)); ii++) {
		sprintf(cmdhelp, "   %s \t%s\n", cmds[ii].cmd, cmds[ii].help);
		wibc_console_puts(cmdhelp);
	}
	return 0;
}

#ifdef _dis_
s32 wibc_cmd_proc(u8 *cmd, s32 len)
{
	s32 ii;
	for (ii=0; ii<(sizeof(cmds)/sizeof(wibc_cmds_t)); ii++) {
		if (0 == strncmp(cmd, cmds[ii].cmd, len-1)) break;
	}
	if (ii == sizeof(cmds)/sizeof(wibc_cmds_t))
		wibc_console_puts("Invalid command. Enter 'help' for help\n");
	else
		cmds[ii].fun(1, NULL);
}
#endif

void wibc_cli(void)
{
	s8 tokens[10][10];
	s8 dlmts[] = " ";
	s32 ii;
	s32 len;
	s32 tkncnt;
	u8 tmp[10];
	u8 cmd[MAX_CMD_LEN];

	wibc_console_puts( "\n");
	while (1) {
		wibc_console_puts( "wibccli> ");
		len = wibc_console_gets(cmd);
		cmd[len] = '\0';
		//sprintf(tmp, "rx:%d\n", len);
		//wibc_console_puts( tmp);
		if(cmd[0] == '\r') continue;
#ifdef _dis_
		wibc_cmd_proc(cmd, len);
#else
		tkncnt = wibc_strtok(cmd, dlmts, wibc_strlen(cmd), tokens);
		for (ii=0; ii<tkncnt; ii++) {
			wibc_console_puts( tokens[ii]);
			wibc_console_puts( "\n");
		}

		for(ii=0; ii<(sizeof(cmds)/sizeof(wibc_cmds_t)); ii++) {
			if(0 == wibc_strncmp(cmds[ii].cmd, tokens[0], wibc_strlen(tokens[0]) - 1)) break;
		}

		if (ii == sizeof(cmds)/sizeof(wibc_cmds_t))
			wibc_console_puts("Invalid command. Enter 'help' for help\n");
		else
			cmds[ii].fun(tkncnt, tokens);
#endif

#ifdef _dis_
		tkncnt=0;
		tokens[tkncnt] = strtok(cmd, " \n");
		if(!tokens[tkncnt]) continue;

		while(tokens[tkncnt])
			tokens[++tkncnt] = strtok(NULL, " \n");

		for(ii=0; ii<(sizeof(cmds)/sizeof(wibc_cmds_t)); ii++) {
			if(0 == strcmp(cmds[ii].cmd, tokens[0])) break;
		}

		if (ii == sizeof(cmds)/sizeof(wibc_cmds_t))
			wibc_console_puts("Invalid command. Enter 'help' for help\n");
		else
			cmds[ii].fun(tkncnt, tokens);
#endif
	}
}