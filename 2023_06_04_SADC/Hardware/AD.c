#include "stm32f10x.h"                  // Device header

void AD_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);//开启ADC1时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);//开启GPIOA时钟，硬件使用PA0口
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//ADCCLK = 72MHz/6 =12MHz
	
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;//模拟输入，ADC专属模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	//选择规则组输入通道
	//在规则组菜单列表第一个位置，写入通道零
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	
	ADC_InitTypeDef ADC_InitStructure;
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;//独立模式
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//数据右对齐
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;//内部软件触发
	//ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//非连续
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;//连续转换
	ADC_InitStructure.ADC_ScanConvMode = DISABLE;//非扫描模式
	ADC_InitStructure.ADC_NbrOfChannel = 1;//通道数，扫描模式下有用
	ADC_Init(ADC1, &ADC_InitStructure);
	
	ADC_Cmd(ADC1, ENABLE);//开启电源
	
	//对ADC校准
	ADC_ResetCalibration(ADC1);//复位校准
	while (ADC_GetResetCalibrationStatus(ADC1) == SET);//返回复位校准的状态，等待校准完成
	ADC_StartCalibration(ADC1);//启动校准
	while (ADC_GetCalibrationStatus(ADC1) == SET);//等待校准完成
	
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);//连续转换启动一次：软件触发ADC1开始转换
}
	
uint16_t AD_GetValue(void)
{
	//ADC_SoftwareStartConvCmd(ADC1, ENABLE);//软件触发ADC1开始转换
	//连续转换不需要等待
	//while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);//等待转换完成
	return ADC_GetConversionValue(ADC1);//读取DR数据寄存器，自动清除EOC
}

