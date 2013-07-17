
/* commands 	-> from host.
 * reply		-> from radio.
 * events		-> from radio.
 * */
#define WIBC_DNTCMD_ETER_PROTO 	0x00
#define WIBC_DNTCMD_EXIT_PROTO	0x01
#define WIBC_DNTCMD_SOFT_RESET	0X02
#define WIBC_DNTCMD_GET_REG	0x03
#define WIBC_DNTCMD_SET_REG	0x04
#define WIBC_DNTCMD_TXDATA	0x05
#define WIBC_DNTCMD_DISCOVER	0x06
#define WIBC_DNTCMD_REMGET_REG	0x0a
#define WIBC_DNTCMD_REMSET_REG	0x0b

/* reply commands same as above but, bit_4 set */
#define WIBC_DNTCMD_REPLYBIT	0x10

#define WIBC_DNTCMD_JOINREPLY	0x0c
#define WIBC_DNTCMD_REMLEAVE	0x0d

/* events.. */
#define WIBC_DNTEVNT_RXDATA	0x26
#define WIBC_DNTEVNT_ANNOUNCE	0x27
#define WIBC_DNTEVNT_RXEVET	0x28

#define WIBC_DNTEVNT_JOINREQ	0x2c


/* TX status */
#define TXSTAT_ACK	0x00
#define TXSTAT_NOACK	0X01
#define TXSTAT_NOLINK	0x02
#define TXSTAT_NOACK_FC_ERR	0X03

/* RSSI signal strength */
#define NO_RSSI_NOACK	0x7f
#define NO_RSSI_PKT	0x7e

/* announce status */
#define ANNSTAT_RA0	0xa0
#define ANNSTAT_BA2	0XA2
#define ANNSTAT_RA3	0XA3
#define ANNSTAT_RA4	0XA4
#define ANNSTAT_RA5	0XA5
#define ANNSTAT_BA7	0XA7
#define ANNSTAT_BA8	0XA8
#define ANNSTAT_BA9	0XA9


/* message header size */
#define WIBC_DNTHDR_SIZE	6
typedef struct {
	u8 sop;
	u8 len;
	u8 cmd;
	u8 mac[3];
	u8 data[16];
	u8 rsvd[2];
}wibc_msg_t;


