/************************* Copyright (c) 2018   AJS.Sunwaz  *****************************
 *项目名称:	CA9523M
 *描    述:	智慧用电
 *设    计:	AJS.Sunwaz
 *修改日期:	2018-03-09					文档编写
 *说    明:	
*******************************************************************************************/
/* 头文件	--------------------------------------------------------------------*/
#include "beep.h"
/* 宏定义	--------------------------------------------------------------------*/
#define BEEP_TX_PORT									GPIOB
#define BEEP_TX_PIN										GPIO_Pin_8
#define RCC_TX_BEEP_CMD								RCC_AHBPeriphClockCmd
#define RCC_TX_BEEP_CLK								RCC_AHBPeriph_GPIOB
/* 结构体定义	----------------------------------------------------------------*/
/* 内部引用	------------------------------------------------------------------*/
/* 全局变量	------------------------------------------------------------------*/
/* 系统函数	------------------------------------------------------------------*/
/*****************************************************************************
 * 函数功能:		蜂鸣器端口初始化
 * 形式参数:		无
 * 返回参数:		无
 * 更改日期;		2018-03-09				函数编写
 ****************************************************************************/ 
void Beep_Config( void )
{
	GPIO_InitTypeDef		newGPIO_Init;
	
	newGPIO_Init.GPIO_Mode	=	GPIO_Mode_OUT;
	newGPIO_Init.GPIO_OType	=	GPIO_OType_PP;
	newGPIO_Init.GPIO_PuPd	=	GPIO_PuPd_DOWN;
	newGPIO_Init.GPIO_Speed	=	GPIO_Speed_50MHz;
	/*1> BEEP 端口初始化*/
	newGPIO_Init.GPIO_Pin		=	BEEP_TX_PIN;
	RCC_TX_BEEP_CMD( RCC_TX_BEEP_CLK , ENABLE );
	GPIO_Init( BEEP_TX_PORT , &newGPIO_Init );
}

/*****************************************************************************
 * 函数功能:		打开蜂鸣器
 * 形式参数:		无
 * 返回参数:		无
 * 更改日期;		2018-03-09				函数编写
 ****************************************************************************/ 
void Beep_CtlOpen( void )
{
	GPIO_SetBits( BEEP_TX_PORT , BEEP_TX_PIN );
}

/*****************************************************************************
 * 函数功能:		关闭蜂鸣器
 * 形式参数:		无
 * 返回参数:		无
 * 更改日期;		2018-03-09				函数编写
 ****************************************************************************/ 
void Beep_CtlClos( void )
{
	GPIO_ResetBits( BEEP_TX_PORT , BEEP_TX_PIN );
}
/*------------------------------File----------End------------------------------*/
