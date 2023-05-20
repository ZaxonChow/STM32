#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Servo.h"
#include "Key.h"

uint8_t KeyNum;//
float Angle = 0;//上电零度

int main(void)
{
	OLED_Init();
	Servo_Init();
	Key_Init();
	
	OLED_ShowString(1, 1, "Angle:000");
	Servo_SetAngle(Angle);//上电零度
	
	while(1)
	{
		KeyNum = Key_GetNum();
		if (KeyNum == 1)
		{
			Angle += 30;
			if (Angle > 180)
			{
				Angle = 0;
			}
			Servo_SetAngle(Angle);//舵机角度
			OLED_ShowNum(1, 7, Angle, 3);
		}
	}
}
