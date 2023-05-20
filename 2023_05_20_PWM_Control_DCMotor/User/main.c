#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "DCMotor.h"
#include "Key.h"

uint8_t KeyNum;
int8_t Speed;
uint8_t Flag = 0;//0表示正传，1表示反转

int main(void)
{
	OLED_Init();
	Motor_Init();
	Key_Init();
	
	Motor_SetSpeed(20);
	OLED_ShowString(1, 1, "Speed:");
	
	while(1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum == 1 && Flag == 0)
		{
			Speed += 20;
			if (Speed >= 80)
			{
				Flag = 1;
			}
		}
		else if (KeyNum == 1 && Flag == 1)
		{
			Speed -= 20;
			if(Speed <= -80)
			{
				Flag = 0;
			}
		}
		Motor_SetSpeed(Speed);
		OLED_ShowSignedNum(1, 7, Speed, 3);
	}
}
