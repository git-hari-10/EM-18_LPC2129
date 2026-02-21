#include "delay.h"
#define D  0xff
#define RS 1<<10
#define E  1<<11

void lcd_str(unsigned char*);
void lcd_init(void);
void lcd_cmd(unsigned char);
void lcd_write(unsigned char);

void lcd_init(){
	IODIR0 |= D|RS|E;
	lcd_cmd(0x38);
	lcd_cmd(0x0C);
	lcd_cmd(0x06);
	lcd_cmd(0x01);
}

void lcd_cmd(unsigned char command){
	IOCLR0 = D;
	IOSET0 = command;
	IOCLR0 = RS;
	IOSET0 = E;
	delay_ms(5);
	IOCLR0 = E;
}

void lcd_write(unsigned char data){
	IOCLR0 = D;
	IOSET0 = data;
	IOSET0 = RS;
	IOSET0 = E;
	delay_ms(5);
	IOCLR0 = E;
}

void lcd_str(unsigned char *s)
{
	while(*s)
		lcd_write(*s++);
}
