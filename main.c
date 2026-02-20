#include<lpc21xx.h>
#include "lcd.h"
#include "uart.h"

void projTopicScroll(unsigned char *);
void voterIDScan(void);

int main()
{
	//unsigned char T[] = "                MODERN VOTING MACHINE USING LPC2129 & RFID      ";
	lcd_init();
	UART1_config();
	while(1)              
	{
			//projTopicScroll(T);
			voterIDScan();
	}
}

void projTopicScroll(unsigned char *s)
{
	static unsigned char i=0;
	unsigned char j;
	
	lcd_cmd(0x01);
	lcd_cmd(0x80);
	for(j=0;j<16;j++)
		lcd_write(s[i+j]);
	i++;
	lcd_cmd(0xC0);
	lcd_str("==> SCAN  ID <==");
	delay_ms(150);
	
	if(s[i+15] == '\0') 
		i=0;
}

void voterIDScan()
{
	static unsigned char TAG[15];
	static unsigned char i=0;
	
	if(U1LSR&1)
	{
		TAG[i++] = U1RBR;
		if(i==12)
		{
			TAG[i] = '\0';
			lcd_cmd(0x80);
			lcd_str(TAG);
		}
}

