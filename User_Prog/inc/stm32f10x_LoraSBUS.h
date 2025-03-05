/*********************************************************************************
  * @file    stm32f10x_LoraSBUS.h
  * @author  W. DONG
  * @version V1.0.0
  * @date    22/01/2020
  * @brief   Loraģ���շ�SBUS����  ���ݽṹ�뺯������.
***********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __STM32F10X_LORASBUS_H
#define __STM32F10X_LORASBUS_H	

/* Includes ------------------------------------------------------------------*/	 

#include "stm32f10x_Lora.h"
#include "stm32f10x_MapSCOMandSBUS.h"

/** @addtogroup My_Driver
  * @{
  */
	
	
/** @addtogroup LORASBUS
  * @{
  */ 

/** @defgroup LORA_Exported_Types 
  * @{
  */ 	
	typedef void (*LoraSBUS_CallBack)(void);


typedef SBUSData_Struct           LoraSBUS_WRITE_DATA_Struct; 

typedef struct __LoraSBUS_READ_DATA_Struct
{  
    FlagStatus                          Fresh;
    SBUSData_Struct                     RxData;
} LoraSBUS_READ_DATA_Struct;


typedef struct _LoraSBUS_Register_Typedef_Struct
{ 
	 FunctionalState               EnableLoraSBUS;
   Lora_InitTypedef_Struct       Lora_Init;
	
	    LoraSBUS_CallBack rx_CallBack;
    LoraSBUS_CallBack tx_CallBack;
} LoraSBUS_Register_Typedef_Struct;



typedef struct _LoraSBUS_Typedef_Struct
{  
	 Lora_Typedef_Struct*                     Lorax;            
	 LoraSBUS_Register_Typedef_Struct         LoraSBUSRegister;
} LoraSBUS_Typedef_Struct;


typedef LoraSBUS_Typedef_Struct      LoraSBUS_InitTypedef_Struct;


extern LoraSBUS_Typedef_Struct           LoraSBUS1_BASE;
#define LoraSBUS1                        (&LoraSBUS1_BASE)      /* LoraSBUS1 selected */

extern LoraSBUS_Typedef_Struct           LoraSBUS2_BASE;
#define LoraSBUS2                        (&LoraSBUS2_BASE)      /* LoraSBUS2 selected */

extern LoraSBUS_Typedef_Struct           LoraSBUS3_BASE;
#define LoraSBUS3                        (&LoraSBUS3_BASE)      /* Lora3 selected */

/* -----������� LoraSBUS_InitTypeDef_Struct Lora_Init_Struct��Ĭ�ϲ��� --- */
#define LoraSBUS_HARDWARE_DEFAULT                  NULL

#define LoraSBUS_ADDRESS_DEFAULT                   (0x1234)   
#define LoraSBUS_COMCHANNEL_DEFAULT                (0x17) 

#define LoraSBUS_ENABLE_DEFAULT                    ENABLE
#define LoraSBUS_DMA_ENABLE_DEFAULT                ENABLE

#define LoraSBUS_BAUDRATE_DEFAULT                  115200
#define LoraSBUS_PARITY_DEFAULT                    USART_Parity_No
#define LoraSBUS_WORDLENGTH_DEFAULT                USART_WordLength_8b
#define LoraSBUS_STOPBIT_DEFAULT                   USART_StopBits_1
#define LoraSBUS_HARDWAREFLOWCONTROL_DEFAULT       USART_HardwareFlowControl_None

#define LoraSBUS_USARTPREEMPTIONPRIORITY_DEFAULT    (3)
#define LoraSBUS_USARTSUBPRIORITY_DEFAULT           (3)
#define LoraSBUS_DMAPREEMPTIONPRIORITY_DEFAULT      (0)
#define LoraSBUS_DMASUBPRIORITY_DEFAULT             (0)


/**
  * @}
  */
	
/** @defgroup LoraSBUS_Exported_Functions
  * @{
  */

/**********************************************************************************
* @brief  ��Ĭ�ϲ�����ʼ��LoraSBUS_Init_Struct                                    *                                                
* @param  LoraSBUS_Init_Struct��ָ�� LoraSBUS_InitTypedef_Struct���͵Ľṹ������  *
* @retval void.                                                                   *
**********************************************************************************/
void LoraSBUS_StructInit(LoraSBUS_InitTypedef_Struct *LoraSBUS_Init_Struct);

/******************************************************************************
* @brief  ��Lora_Init_Struct ��ʼ��LoraSBUS                                   *                                                
* @param  LoraSBUSx��ѡ���ʼ����LoraSBUS ��x������1�� LoraSBUS_NUM_USED      *
* @param  LoraSBUS_Init_Struct�� ��ʼ����LoraSBUS_InitTypeDef_Struct �ṹ���� *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/
ErrorStatus LoraSBUS_Init(LoraSBUS_Typedef_Struct* LoraSBUSx, LoraSBUS_InitTypedef_Struct *LoraSBUS_Init_Struct);

/******************************************************************************
* @brief  �� LoraSBUS                         	      		                  *
* @param  Lorax��ѡ���ʼ����LoraSBUS��x������1�� LoraSBUS_NUM_USED           *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/
ErrorStatus LoraSBUS_Open(LoraSBUS_Typedef_Struct* LoraSBUSx);

/******************************************************************************
* @brief  �ر� LoraSBUS                         	      		                  *
* @param  Lorax��ѡ���ʼ����LoraSBUS��x������1�� LoraSBUS_NUM_USED           *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/
ErrorStatus LoraSBUS_Close(LoraSBUS_Typedef_Struct* LoraSBUSx);


/*****************************************************************************************
  * @brief   ��LoraSBUSд������.                                                         *
  * @param   LoraSBUSx:  д�����ݵ�LoraSBUS��x������1�� LoraSBUS_NUM_USED.               *
  * @param   write_data: ָ��LoraSBUS_WRITE_DATA_Struct���͵����ݽṹ���洢д���������  *	
  * @retval  ERROR or SUCCESS.                                                           *
*****************************************************************************************/

ErrorStatus LoraSBUS_WriteData(LoraSBUS_Typedef_Struct *LoraSBUSx,LoraSBUS_WRITE_DATA_Struct *write_data);

/*****************************************************************************************
  * @brief   ��LoraSBUS��ȡ����.                                                         *
  * @param   LoraSBUSx:  ��ȡ���ݵ�LoraSBUS��x������1�� LoraSBUS_NUM_USED.               *
  * @param   ReadData: ָ��LoraSBUS_READ_DATA_Struct���͵����ݽṹ�����ڴ洢ȡ�ص�����   *	
  * @retval  ERROR or SUCCESS.                                                           *
*****************************************************************************************/
ErrorStatus LoraSBUS_ReadData(LoraSBUS_Typedef_Struct *LoraSBUSx,LoraSBUS_READ_DATA_Struct * ReadData);


/**
  * @}
  */

#endif     /*__STM32F10X_LoraSBUS_H */
/**
  * @}
  */


/********* (C) COPYRIGHT 2017 HANGZHOU NORMAL UNIVERSITY   *****END OF FILE****/
