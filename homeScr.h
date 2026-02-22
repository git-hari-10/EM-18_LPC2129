/* _______________ HOME SCREEN ______________*/

void homeScr()
{
	lcd_cmd(0x80);lcd_str("### VOTE MACHINE ###");
	lcd_cmd(0xC0);lcd_str("------- 2026 -------");
	lcd_cmd(0x94);lcd_str(">> [ SCAN  CARD ] <<");
	lcd_cmd(0xD4);lcd_str("      WAITING...    ");
}

