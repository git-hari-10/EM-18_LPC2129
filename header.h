void title(void)
{
	unsigned char T[] =   // PROJECT TITLE
	"                MODERN VOTING MACHINE USING LPC2129 & RFID      ";
	unsigned char i,j;
	lcd_init();
	while(1)              // SCROLLING LOGIC
	{
		for(i=0;T[i+15]!='\0';i++)
		{
			lcd_cmd(0x01);
			lcd_cmd(0x80);
			for(j=0;j<16;j++)
				lcd_write(T[i+j]);
			lcd_cmd(0xC0);
			lcd_str("==> SCAN-ID  <==");
			delay_ms(180);
		}
	}
}
