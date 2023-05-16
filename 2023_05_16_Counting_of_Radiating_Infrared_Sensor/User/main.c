#include "stm32f10x.h"                  // Device header
#include "OLED.h"
#include "Radiating_Infrared_Sensor.h"

int main(void)
{
	OLED_Init();
	RadiatingInfraredSensor_Init();
	
	
	OLED_ShowString(1, 1, "Count:");
	
	while(1)
	{
		OLED_ShowNum(1, 7, RadiatingInfraredSensor_Get(), 5);
	}
}
