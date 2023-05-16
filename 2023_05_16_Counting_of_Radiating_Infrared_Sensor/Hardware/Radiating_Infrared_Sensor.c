#include "stm32f10x.h"                  // Device header
#include "Delay.h"

uint16_t Sensor_Count;

void RadiatingInfraredSensor_Init(void)
{
	//配置时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;//上拉输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource14);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line14;//指定中断线
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_Init(&EXTI_InitStructure);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStrycture;
	NVIC_InitStrycture.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStrycture.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStrycture.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStrycture.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStrycture);
}

uint16_t RadiatingInfraredSensor_Get(void)
{
	return Sensor_Count;
}

void EXTI15_10_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line14) == SET)//返回值位SET、RESET
	{
		Sensor_Count++;
		Delay_ms(50);
		EXTI_ClearITPendingBit(EXTI_Line14);//清除中断标志位
	}
}

