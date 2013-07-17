#include "wibc.h"
#if 0
s32 wibc_strncmp(u8 *s1, u8 *s2, s32 len) 
{
	s32 ii = 0;
	//u8 tmp[50];
	//sprintf(tmp, "strncmp:%d\n", len);
	//wibc_puts(UARTDBG_MODULE, tmp);
	//wibc_puts(UARTDBG_MODULE, s1);
	while (ii < len) {
		if (s1[ii] != s2[ii]) return -1;
		ii++;
	}
	return 0;
}
#endif

int wibc_strcpy(char *s1, char *s2, int len)
{
	int ii = 0;
	while (ii<len) {
		s1[ii] = s2[ii];
		ii++;
	}
	s1[ii]='\0';
	return ii;
}

int wibc_strtok(char *str, char *dlmts, int str_len,
			char tokens[][10])
{
	int tkncnt = 0;
	char *str_base;
	int ii=0;
	int substr_pos = 0;
	str_base = str;

	/* find substr */
	while(ii<str_len) {
		if(str_base[ii] == dlmts[0]) {
			substr_pos += wibc_strcpy(tokens[tkncnt], 
					str_base+substr_pos, (ii-substr_pos));
			substr_pos+=1;
			tkncnt++;
		}
		ii++;
	}

	/* search for last substr */
	ii = str_len;
	while(ii>=0) {
		if(str_base[ii] == dlmts[0]) {
			wibc_strcpy(tokens[tkncnt],
				str_base+ii+1,
				(str_len - ii));	
			tkncnt++;
			break;
		}
		ii--;
	}

	/* str doesn't have substr */
	if (tkncnt == 0) {
		wibc_strcpy(tokens[tkncnt], str_base, str_len);
		tkncnt++;
	}
	return tkncnt;
}

int wibc_strlen(const char *str)
{
	int ii = 0;
	while(str[ii] != '\0') ii++;
	return ii;
}

int wibc_strncmp(const s8 *s1, const s8 *s2, s32 len) 
{
	s32 ii =0;
	
	while(ii < len) {
		if (s1[ii] != s2[ii]) return -1;
		ii++;
	}
	return 0;
}