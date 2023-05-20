#include "stm32f10x.h"                  // Device header

void PWM_Init(void)
{
	//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//TIM2在APB1上
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//开启GPIO时钟
		
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;//复用推挽输出
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//选择时基单元的时钟
	TIM_InternalClockConfig(TIM2);//内部时钟
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//计数模式
	//PWM频率：CK_PSC / (PSC+1) / (ARR+1)
	//72M/36/100 = 20000
	//PWM占空比：Duty = CCR / (ARR+1)
	//
	//PWM分辨率：Reso = 1 / (ARR+1)
	//
	TIM_TimeBaseInitStructure.TIM_Period = 100 - 1;//ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 36 - 1;//PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//高级定时器重复计数器
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	//初始化通道
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);//设置初始值
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;//设置输出模式
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;//设置输出极性
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//设置输出使能
	TIM_OCInitStructure.TIM_Pulse = 0;//设置CCR
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	
	//启动定时器
	TIM_Cmd(TIM2, ENABLE);
}

void PWM_SetCompare3(uint16_t Compare)
{
	TIM_SetCompare3(TIM2, Compare);
}
