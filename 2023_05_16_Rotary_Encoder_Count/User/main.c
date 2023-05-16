#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"
#include "Rotary Encoder.h"

int16_t Num;

int main(void)
{
	OLED_Init();
	RotaryEncoder_Init();
	
	OLED_ShowString(1, 1, "Count:");
	
	while(1)
	{
		Num += Encoder_Get();
		OLED_ShowSignedNum(1, 7, Num, 5);
	}
}
