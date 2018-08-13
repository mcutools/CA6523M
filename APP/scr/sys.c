/************************* Copyright (c) 2018   AJS.Sunwaz  *****************************
 *项目名称:	CA9523M
 *描    述:	智慧用电
 *设    计:	AJS.Sunwaz
 *修改日期:	2018-03-12					文档编写
						2018-03-13					BC95程序调试
 *说    明:	
*******************************************************************************************/
/* 头文件	--------------------------------------------------------------------*/
#include "sys.h"
#include "usart.h"
#include "BC95.h"
#include "delay.h"
#include "rtc.h"
#include "nbiot.h"
#include "adc_get.h"
#include "key_led.h"
#include "timer.h"
#include "app.h"
#include "configure.h"
/* 宏定义	--------------------------------------------------------------------*/
/* 结构体定义	----------------------------------------------------------------*/
/* 内部引用	------------------------------------------------------------------*/
/* 全局变量	------------------------------------------------------------------*/
/* 系统函数	------------------------------------------------------------------*/
/*****************************************************************************
 * 函数功能:		网络初始化
 * 形式参数:		无
 * 返回参数:		无
 * 更改日期;		2018-03-14				函数编写
							2018-07-23				函数优化;删除掉NB模块初始化程序
 ****************************************************************************/ 
void Network_Config( void )
{
	network_parameter_flashRead();		 //读取本地配置
  NB_Config();
	while(RTC_Config())
	{
		printf("RTC ERROR!\r\n ");	
		delay_ms(500);
	}
}
/*****************************************************************************
 * 函数功能:	独立看门狗初始化
 * 形式参数:	无
 * 返回参数:	无
 ****************************************************************************/
static void IWDG_Config(void)
{
	if(RCC_GetFlagStatus(RCC_FLAG_IWDGRST) != RESET)
	{
			RCC_ClearFlag();                             //清除标志
	}
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);  //允许访问IWDG_PR和IWDG_RLR寄存器
	IWDG_SetPrescaler(IWDG_Prescaler_256);         //分频值
	IWDG_SetReload(0x0fff);                        //
	IWDG_ReloadCounter();                          //使能重载值o
	IWDG_Enable();                                 //使能看门狗
}
/*****************************************************************************
 * 函数功能:		系统初始化函数
 * 形式参数:		无
 * 返回参数:		无
 * 更改日期;		2018-03-12				函数编写
							2018-03-14				函数添加
							2018-04-18				时钟切换必须放在前面(ADC初始化里面，关闭HSE和LSE)
							2018-06-11				函数优化;将Timer_Config移动到Network_Config之前
 ****************************************************************************/ 
void Sys_Init(void) 
{
	ADC_GetConfig();
	delay_init();
	USART_485_Config();
	delay_ms(200);
	printf("软件版本号:%s\r\n " , SYS_VER);
	Timer_Config();
	Network_Config();
	KeyLED_Config();
	IWDG_Config();
}
/*------------------------------File----------End------------------------------*/
