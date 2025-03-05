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
  * @brief   HCSR04ģ�����������ݽṹ�뺯������.
*******************************************************************************/
//#define Echo GPIO_Pin_6		//HC-SR04ģ���Echo�Ž�GPIOB6
//#define Trig GPIO_Pin_5		//HC-SR04ģ���Trig�Ž�GPIOB5

typedef struct _HCSR_Hardware_Struct
{
		GPIO_TypeDef *          Echo_GPIO;
		uint16_t                Echo_GPIO_Pin;
		GPIO_TypeDef *          Trig_GPIO;
		uint16_t                Trig_GPIO_Pin;
	
}HCSR_Hardware_Struct;

typedef struct _HCSR_Memory_Struct
{
  uint16_t time;      //����������������ʱ
	uint16_t time_end ; //�����������洢�ز��ź�ʱ��
}HCSR_Memory_Struct;

typedef struct _HCSR_Typedef_Struct
{  
   HCSR_Hardware_Struct        HCSRHardware;         //Ӳ������              
	 HCSR_Memory_Struct          HCSRMemory;         //��������
} HCSR_Typedef_Struct;

//uint64_t HCSR_time     = 0;	  //����������������ʱ
//uint64_t HCSR_time_end = 0;		//�����������洢�ز��ź�ʱ��
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
* @brief  ��Ĭ�ϲ�����ʼ��HC_SR04_Init                                    *                                                
* @param  HCSR_Init_Struct��ָ�� HCSR_InitTypedef_Struct���͵Ľṹ������      *
* @retval ErrorStatus                                                               *
******************************************************************************/
ErrorStatus HC_SR04_Init(HCSR_Typedef_Struct *HCSRX);
/******************************************************************************
* @brief //��ಢ���ص�λΪ���׵ľ�����                                    *                                                
* @param  void
* @retval uint16_t                                                              *
******************************************************************************/
uint16_t sonar_mm(void);

//float sonar(void);

#endif
