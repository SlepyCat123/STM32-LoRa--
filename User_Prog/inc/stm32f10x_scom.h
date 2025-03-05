/******************************************************************************
  * @file    stm32f10x_scom.h
  * @author  W. Dong
  * @version V1.0.1
  * @date    23/09/2022
  * @brief   ����ͨ�����ݽṹ�뺯������.
  *****************************************************************************/

#ifndef __STM32F10X_SCOM_H
#define __STM32F10X_SCOM_H	

/* Includes ------------------------------------------------------------------*/	 

#include "stm32f10x.h" 	
#include <string.h>

/** @addtogroup My_Driver
  * @{
  */
	
/** @defgroup An example of using SCOM functions
  * @{
  */
	 
/**
  * @}
  */ 
	
/** @addtogroup SCOM
  * @{
  */ 

/** @defgroup SCOM_Exported_Types 
  * @{
  */ 
#define RX_BUFFER_MAX_SIZE                       32
#define TX_BUFFER_MAX_SIZE                       32	
typedef void (*SCOM_CallBack)(void);
typedef  USART_InitTypeDef             SCOM_USART_Parm;  

typedef enum __SCOM_Comm_Mode_Enum
{  
	 Comm_TX,                        /*����ģʽ*/
	 Comm_RX,                        /*����ģʽ*/
   Comm_RTX                        /*�շ�ģʽ*/
}SCOM_Comm_Mode_Enum;



/** 
  * @brief    SCOM SCOM_READ_DATA structure definition
  */	
typedef struct __SCOM_READ_DATA_Struct
{  
	 FlagStatus   Fresh;                     /*�������ݸ��±�־*/
	 uint8_t      len;                       /*���ڶ������ݵ���Ч����*/
   uint8_t      data[RX_BUFFER_MAX_SIZE];  /*���ڶ�������*/
}SCOM_READ_DATA_Struct;


/** 
  * @brief    SCOM SCOM_WRITE_DATA structure definition
  */	

typedef struct __SCOM_WRITE_DATA_Struct
{  
	 uint8_t      len;                         /*����д�����ݵ���Ч����*/
   uint8_t      data[TX_BUFFER_MAX_SIZE];    /*����д������*/
}  SCOM_WRITE_DATA_Struct;

/** 
  * @brief  SCOM Register structure definition   
  */

typedef struct __SCOMRegister_TypeDef_Struct
{
		FunctionalState                enable_SCOM;         /*����ʹ�ܱ�־*/
		FunctionalState                enable_DMA;          /*DMAʹ�ܱ�־*/				
		SCOM_Comm_Mode_Enum            commMode;			      /*ͨ��ģʽ*/
		SCOM_USART_Parm                USART_Parm;			/*���ڳ�ʼ���ṹ��*/
		FlagStatus                     USART_txAllowFlag;   /*���ڷ��������־*/
    SCOM_CallBack                  rx_CallBack;
    SCOM_CallBack                  tx_CallBack;
} SCOMRegister_TypeDef_Struct;

/** 
  * @brief  SCOM Hardware structure definition   
  */
typedef struct __SCOMHardware_TypeDef_Struct
{	
		/*USART Hardware*/ 
		USART_TypeDef*                USARTx;
		uint8_t                       USARTx_IRQn;		
		GPIO_TypeDef *                tx_GPIOx;
		uint16_t                      tx_GPIO_Pin;			
		GPIO_TypeDef *                rx_GPIOx;
		uint16_t                      rx_GPIO_Pin;
		/* DMA  Hardware */
		DMA_Channel_TypeDef *         rx_DMAy_Channelx;
		uint8_t                       rx_DMAy_Channelx_IRQn;	
		DMA_Channel_TypeDef *         tx_DMAy_Channelx;
		uint8_t                       tx_DMAy_Channelx_IRQn;	
} SCOMHardware_TypeDef_Struct;


/** 
  * @brief  SCOM Type structure definition 
  */

typedef struct __SCOM_TypeDef_Struct
{	
	 SCOMHardware_TypeDef_Struct   SCOM_Hardware;	
	 SCOMRegister_TypeDef_Struct   SCOM_Operating;
}SCOM_TypeDef_Struct;

/** 
  * @brief  SCOM Init structure definition 
  */
typedef struct __SCOM_InitTypeDef_Struct
{
		FunctionalState             enable_SCOM;
		FunctionalState             enable_DMA;	
		SCOM_Comm_Mode_Enum         commMode;			       	
		SCOM_USART_Parm             usartInitParm;		
		uint8_t	                    SCOM_USART_PreemptionPriority;
		uint8_t	                    SCOM_USART_SubPriority;			
		uint8_t	                    SCOM_DMA_PreemptionPriority;
		uint8_t	                    SCOM_DMA_SubPriority;						
}SCOM_InitTypeDef_Struct;

/** @defgroup SCOM_Exported_Macros
  * @{
  */


extern SCOM_TypeDef_Struct SCOM1_BASE;
#define SCOM1                         (&SCOM1_BASE)      /* SCOM1 selected */
#define SCOM1_USART                   USART3           

extern SCOM_TypeDef_Struct SCOM2_BASE;
#define SCOM2                        (&SCOM2_BASE)      /* SCOM2 selected */
#define SCOM2_USART                   USART2    

extern SCOM_TypeDef_Struct SCOM3_BASE;
#define SCOM3                        (&SCOM3_BASE)      /* SCOM3 selected */
#define SCOM3_USART                   USART1   

#define ENABLE_SCOM_DEFAULT                      ENABLE
#define ENABLE_DMA_DEFAULT                       ENABLE
#define SCOM_COMMMODE_DEFAULT                    Comm_RTX

#define SCOM_USART_PREEMPTIONPRIORITY_DEFAULT    (3)
#define SCOM_USART_SUBPRIORITY_DEFAULT           (3)
#define SCOM_DMA_PREEMPTIONPRIORITY_DEFAULT      (0)
#define SCOM_DMA_SUBPRIORITY_DEFAULT             (0)

#define SCOM_BAUDRATE_DEFAULT                    (9600)
#define SCOM_WORDLENGTH_DEFAULT                  USART_WordLength_8b
#define SCOM_STOPBIT_DEFAULT                     USART_StopBits_1
#define SCOM_PARITY_DEFAULT                      USART_Parity_No
#define SCOM_HARDWAREFLOWCONTROL_DEFAULT         USART_HardwareFlowControl_None
    
/**
  * @}
  */
	
/** @defgroup SCOM_Exported_Functions
  * @{
  */

/*******************************************************************************************     
  * @brief  ��Ĭ�ϲ������ SCOM_InitStruct.                                                *
  * @param  SCOM_InitStruct : ��Ҫ����ʼ���� SCOM_InitTypeDef_structure ���͵����ݽṹ     *
  * @retval  None                                                                          *
*******************************************************************************************/
void SCOM_StructInit(SCOM_InitTypeDef_Struct*   SCOMx_InitStruct);

/*******************************************************************************************
  * @brief  ���ݳ�ʼ�����SCOM_InitStruct ��ʼ������ SCOMx                                 *
  * @param  SCOMx: ָ����Ҫ��ʼ���Ĵ��ڣ�x ������1 to 3                                    *
  * @param  SCOM_InitStruct : �Ѿ�����ʼ���� SCOM_InitTypeDef_Struct ���͵����ݽṹ        *
  * @retval ERROR or SUCCESS.                                                              *
*******************************************************************************************/
ErrorStatus SCOM_Init(SCOM_TypeDef_Struct* SCOMx, SCOM_InitTypeDef_Struct* SCOMx_InitStruct);

/******************************************************************************************
  * @brief  �򿪴���.                                                                     *
  * @param  SCOMx: ָ����Ҫ�򿪵Ĵ��ڣ�x ������1 to 3            .                        *
  * @retval ERROR or SUCCESS.                                                             *
******************************************************************************************/
ErrorStatus SCOM_Open(SCOM_TypeDef_Struct* SCOMx);

/******************************************************************************************
  * @brief  �رմ���.                                                                     *
  * @param  SCOMx: ָ����Ҫ�򿪵Ĵ��ڣ�x ������1 to 3                                     *
  * @retval ERROR or SUCCESS.                                                             *
******************************************************************************************/
ErrorStatus SCOM_Off(SCOM_TypeDef_Struct* SCOMx);

/*****************************************************************************************
  * @brief   �Ӵ��ڶ�ȡ����.                                                             *
  * @param   SCOMx:  ��ȡ���ݵĴ��ڣ�x ������1 to 3.                                     *
  * @param   pdata: ָ��SCOM_READ_DATA_Struct���͵����ݽṹ�����ڴ洢ȡ�صĴ�������      *	
  *              Fresh                       �������ݸ��±�־                            *
	*              len                         ���ڶ������ݵ���Ч����                      *
  *              data[len]                   ���ڶ�������                                *
  * @retval  ERROR or SUCCESS.                                                           *
*****************************************************************************************/
ErrorStatus SCOM_ReadData(SCOM_TypeDef_Struct*SCOMx, SCOM_READ_DATA_Struct* pdata);

/*****************************************************************************************
  * @brief   ��ָ���Ĵ���д������ �����ڷ��������־SETʱ������д�����ݷ���              *
  * @param   SCOMx: д�����ݵĴ��ڣ�x ������1 to 3.                                      *
  * @param   pdata: ָ�� SCOM_WRITE_DATA_Struct ���͵Ĵ���д������.                      *                                                *
  * @retval  ERROR or SUCCESS.                                                           *
*****************************************************************************************/	
	
ErrorStatus SCOM_WriteData(SCOM_TypeDef_Struct* SCOMx, SCOM_WRITE_DATA_Struct* pdata);


/**
  * @}
  */
/** @defgroup SCOM_Internaled_Functions
  * @{
**/

/****************************************************************************************
  * @brief   �����жϾ���ִ�еķ�����(Receive interrupt and send interrupt)           *
  * @param   SCOMx:�ж����ݵĴ��ڣ�x ������1 to 3.                                      *
  * @retval  ERROR or SUCCESS.                                                          *
****************************************************************************************/
ErrorStatus SCOM_IRQHandler(SCOM_TypeDef_Struct* SCOMx);

/****************************************************************************************
  * @brief  ���� ����DMA�жϾ���ִ�еķ�����                                          *
  * @param  SCOMx:�ж����ݵĴ��ڣ�x ������1 to 3.                                       *
  * @retval ERROR or SUCCESS.                                                           *
****************************************************************************************/
ErrorStatus	SCOM_TX_DMA_IRQHandler(SCOM_TypeDef_Struct *SCOMx);	

/**
  * @}
  */

#endif                /*__STM32F10X_SCOM_H */



/********* (C) COPYRIGHT 2020 HANGZHOU NORMAL UNIVERSITY   *****END OF FILE****/
