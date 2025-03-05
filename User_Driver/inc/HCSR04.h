#ifndef __HCSR04_H
#define __HCSR04_H

#include "stdint.h"
#include "stm32f10x.h"
#include "time.h"
#include "string.h"
/*******************************************************************************
  * @file    HCSR.h
  * @author  GAN
  * @version V1.0.0
  * @date    2022/11/9
  * @brief   HCSR04模块驱动的数据结构与函数声明.
*******************************************************************************/
//#define Echo GPIO_Pin_6		//HC-SR04模块的Echo脚接GPIOB6
//#define Trig GPIO_Pin_5		//HC-SR04模块的Trig脚接GPIOB5

typedef struct _HCSR_Hardware_Struct
{
		GPIO_TypeDef *          Echo_GPIO;
		uint16_t                Echo_GPIO_Pin;
		GPIO_TypeDef *          Trig_GPIO;
		uint16_t                Trig_GPIO_Pin;
	
}HCSR_Hardware_Struct;

typedef struct _HCSR_Memory_Struct
{
  uint16_t time;      //声明变量，用来计时
	uint16_t time_end ; //声明变量，存储回波信号时间
}HCSR_Memory_Struct;

typedef struct _HCSR_Typedef_Struct
{  
   HCSR_Hardware_Struct        HCSRHardware;         //硬件设置              
	 HCSR_Memory_Struct          HCSRMemory;         //参数设置
} HCSR_Typedef_Struct;

//uint64_t HCSR_time     = 0;	  //声明变量，用来计时
//uint64_t HCSR_time_end = 0;		//声明变量，存储回波信号时间
extern HCSR_Typedef_Struct           HCSR1_BASE;
#define HCSR1                        (&HCSR1_BASE)      /* HCSR1 selected */

#define HCSR1_Echo_GPIO               GPIOB
#define HCSR1_Echo_GPIO_Pin           GPIO_Pin_XX
#define HCSR1_Trig_GPIO               GPIOB
#define HCSR1_Trig_GPIO_Pin           GPIO_Pin_XX

extern HCSR_Typedef_Struct           HCSR2_BASE;
#define HCSR2                        (&HCSR2_BASE)      /* HCSR2 selected */

#define HCSR2_Echo_GPIO               GPIOB
#define HCSR2_Echo_GPIO_Pin           GPIO_Pin_XX
#define HCSR2_Trig_GPIO               GPIOB
#define HCSR2_Trig_GPIO_Pin           GPIO_Pin_XX

extern HCSR_Typedef_Struct           HCSR3_BASE;
#define HCSR3                        (&HCSR3_BASE)      /* HCSR3 selected */

#define HCSR3_Echo_GPIO               GPIOB
#define HCSR3_Echo_GPIO_Pin           GPIO_Pin_XX
#define HCSR3_Trig_GPIO               GPIOB
#define HCSR3_Trig_GPIO_Pin           GPIO_Pin_XX

/******************************************************************************
* @brief  用默认参数初始化HC_SR04_Init                                    *                                                
* @param  HCSR_Init_Struct：指向 HCSR_InitTypedef_Struct类型的结构体数据      *
* @retval ErrorStatus                                                               *
******************************************************************************/
ErrorStatus HC_SR04_Init(HCSR_Typedef_Struct *HCSRX);
/******************************************************************************
* @brief //测距并返回单位为毫米的距离结果                                    *                                                
* @param  void
* @retval uint16_t                                                              *
******************************************************************************/
uint16_t sonar_mm(void);

//float sonar(void);

#endif
