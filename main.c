#include<lpc21xx.h>
#include "lcd.h"
#include "uart.h"

void projTopicScroll(unsigned char *);
void voterIDScan(void);

int main()
{
	unsigned char T[] = "                MODERN VOTING MACHINE USING LPC2129 & RFID      ";
	lcd_init();
	while(1)              
	{
			projTopicScroll(T);
			voterIDScan();
	}
}

void projTopicScroll(unsigned char *s)
{
	unsigned char i,j;
	for(i=0;s[i+15]!='\0';i++)
	{
		lcd_cmd(0x01);
		lcd_cmd(0x80);
		for(j=0;j<16;j++)
			lcd_write(s[i+j]);
		lcd_cmd(0xC0);
		lcd_str("==> SCAN  ID <==");
		delay_ms(180);
	}
}

void voterIDScan()
{
	unsigned char i,TAG[13];
	UART1_config();
	for(i=0;i<13;i++)
		TAG[i] = UART1_Rxchr();
	TAG[i] = '\0';
	UART1_Txstr(TAG);
}

