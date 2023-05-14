#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"

int main(void)
{
	OLED_Init();
	
	OLED_ShowChar(1, 1, 'S');
	OLED_ShowString(1, 3, "Zaxon Demon");
	OLED_ShowNum(2, 1, 970906, 6);
	OLED_ShowSignedNum(2, 8, 230514, 6);
	OLED_ShowHexNum(3, 1, 0xAA55, 4);
	OLED_ShowBinNum(4, 1, 0xAA55, 16);
	
	OLED_Clear();
	
	while(1)
	{
		
	}
}
