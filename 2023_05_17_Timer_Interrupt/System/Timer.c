#include "stm32f10x.h"                  // Device header

//extern uint16_t Num;//外部变量

void Timer_Init(void)
{
	//开启时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);//TIM2在APB1上
	//选择时基单元的时钟
	TIM_InternalClockConfig(TIM2);//内部时钟
	//配置时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;//分频
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;//计数模式
	//公式：CK_PSC/(PSC+1)/(ARR+1)
	//72M/10000/7200 = 10k
	//10k的频率计1w个数，实现1s
	TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;//
	TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;//
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0;//高级定时器重复计数器
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	//使能更新中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);//开启TIM2更新中断到NVIC的通路
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;//响应优先级
	NVIC_Init(&NVIC_InitStructure);
	
	//启动定时器
	TIM_Cmd(TIM2, ENABLE);
}

/*
void TIM2_IRQHandler(void)
{
	//检查中断标志位
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		Num++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}		
}
*/