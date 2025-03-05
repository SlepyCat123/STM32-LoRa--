/*******************************************************************************
  * @file    stm32f10x_Lora.h
  * @author  GAN
  * @version V1.0.0
  * @date    2022/10/07
  * @brief   Lora模块驱动的数据结构与函数声明.
*******************************************************************************/
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F10X_LORA_H
#define __STM32F10X_LORA_H	
/* Includes ------------------------------------------------------------------*/	 
#include "stm32f10x_scom.h"

//typedef SCOM_READ_DATA_Struct     Lora_READ_DATA_Struct;
//typedef SCOM_WRITE_DATA_Struct    Lora_WRITE_DATA_Struct;

typedef SCOM_USART_Parm           Lora_USART_Parm; 
typedef void (*Lora_CallBack)(void);
typedef  SCOM_WRITE_DATA_Struct  WRITEStruct;
typedef  SCOM_READ_DATA_Struct   READStruct;
/*------------------ 结构声明 ---------------------------------  */ 
typedef enum __Lora_TransMode_Enum  //传输模式
{
	 Transparent_mode  =  0,      /*透明传输模式*/
	 Directional_mode  =  1        /*定向传输模式*/
	
} Lora_TransMode_Enum ; 

typedef enum __Lora_commMode_Enum
{
	 Lora_commMode_Rx   =  USART_Mode_Rx,      /*串口接收模式*/
	 Lora_commMode_Tx   =  USART_Mode_Tx,      /*串口发送模式*/
	 Lora_commMode_RTx  =  USART_Mode_Tx|USART_Mode_Rx 	
	
} Lora_USARTMode_Enum ; 

typedef struct __Lora_Register_TypeDef_Struct //lora寄存器结构体声明
{  
    FunctionalState                     EnableLora;
    FunctionalState                     EnableDMA;	

    Lora_TransMode_Enum                 TransMode;
	  Lora_USARTMode_Enum                 USARTMode;
    uint16_t                            Address;
    uint16_t                            Com_Channel;

    Lora_USART_Parm	                    USART_Parm;
	READStruct             LoraRxdata;
  WRITEStruct            LoraTxdata;	
	
	  Lora_CallBack                      rx_CallBack;
    Lora_CallBack                      tx_CallBack;
	
} Lora_Register_Typedef_Struct;

typedef struct _Lora_Hardware_Struct
{  
    SCOM_TypeDef_Struct*    SCOMx;
		GPIO_TypeDef *          MD0_GPIO;
		uint16_t                MD0_GPIO_Pin;  
		GPIO_TypeDef *          MD1_GPIO;
		uint16_t                MD1_GPIO_Pin;  
		GPIO_TypeDef *          AUX_GPIO;
		uint16_t                AUX_GPIO_Pin;  	
} Lora_Hardware_Struct;

typedef struct _Lora_Typedef_Struct
{  
   Lora_Hardware_Struct                  LoraHardware;         //硬件设置              
	 Lora_Register_Typedef_Struct          LoraRegister;         //参数设置
} Lora_Typedef_Struct;

typedef struct _Lora_InitTypedef_Struct
{  
    FunctionalState                      EnableLora;
    FunctionalState                      EnableDMA;	
	
	  Lora_TransMode_Enum                  TransMode;	
	  Lora_USARTMode_Enum                  USARTMODE;  	
    uint16_t                             Address;
    uint16_t                             Com_Channel; 	
	
    uint32_t                             Lora_USART_BaudRate; 	
    uint16_t                             Lora_USART_WordLength;	
	  uint16_t                             Lora_USART_StopBits;
    uint16_t                             Lora_USART_Parity; 	
    uint16_t                             Lora_USART_HardwareFlowControl;
		uint8_t	                             Lora_USART_PreemptionPriority;
		uint8_t	                             Lora_USART_SubPriority;			
		uint8_t	                             Lora_DMA_PreemptionPriority;
		uint8_t	                             Lora_DMA_SubPriority;	 
} Lora_InitTypedef_Struct;


/*------------------ 宏定义 ---------------------------------  */ 
/** @defgroup Lora_Exported_Macros
  * @{
  */
/* -----用于填充 Lora_InitTypeDef_Struct Lora_Init_Struct的默认参数 --- */
#define Lora_TRANSMODE_DEFAULT                 Transparent_mode 
#define Lora_ADDRESS_DEFAULT                   (0x1234)   
#define Lora_COMCHANNEL_DEFAULT                (0x17) 
#define Lora_USARTMODE_DEFAULT                 Lora_commMode_RTx
#define Lora_ENABLE_DEFAULT                    ENABLE
#define Lora_DMA_ENABLE_DEFAULT                ENABLE
#define Lora_BAUDRATE_DEFAULT                  115200
#define Lora_PARITY_DEFAULT                    USART_Parity_No
#define Lora_WORDLENGTH_DEFAULT                USART_WordLength_8b
#define Lora_STOPBIT_DEFAULT                   USART_StopBits_1
#define Lora_HARDWAREFLOWCONTROL_DEFAULT       USART_HardwareFlowControl_None
#define Lora_DATAFRESH_DEFAULT                 RESET
#define Lora_SCOMPREEMPTIONPRIORITY_DEFAULT    3
#define Lora_SCOMSUBPRIORITY_DEFAULT           3
#define Lora_DMAPREEMPTIONPRIORITY_DEFAULT     0
#define Lora_DMASUBPRIORITY_DEFAULT            0
#define Lora_USARTmode_DEFAULT                 Lora_commMode_RTx

extern Lora_Typedef_Struct           Lora1_BASE;
#define Lora1                        (&Lora1_BASE)      /* Lora1 selected */
#define Lora1_SCOMx                  SCOM3
#define Lora1_MD0_GPIO               GPIOB
#define Lora1_Md0_GPIO_Pin           GPIO_Pin_8
#define Lora1_MD1_GPIO               GPIOB
#define Lora1_Md1_GPIO_Pin           GPIO_Pin_9
#define Lora1_AUX_GPIO               GPIOB
#define Lora1_AUX_GPIO_Pin           GPIO_Pin_7


extern Lora_Typedef_Struct           Lora2_BASE;
#define Lora2                        (&Lora2_BASE)      /* Lora2 selected */
#define Lora2_SCOMx                  SCOM2
#define Lora2_MD0_GPIO               GPIOA
#define Lora2_Md0_GPIO_Pin           GPIO_Pin_11
#define Lora2_MD1_GPIO               GPIOA
#define Lora2_Md1_GPIO_Pin           GPIO_Pin_12
#define Lora2_AUX_GPIO               GPIOA
#define Lora2_AUX_GPIO_Pin           GPIO_Pin_13

extern Lora_Typedef_Struct            Lora3_BASE;
#define Lora3                        (&Lora3_BASE)      /* Lora3 selected */
#define Lora3_SCOMx                  SCOM1
#define Lora3_MD0_GPIO               GPIOC
#define Lora3_Md0_GPIO_Pin           GPIO_Pin_11
#define Lora3_MD1_GPIO               GPIOC
#define Lora3_Md1_GPIO_Pin           GPIO_Pin_12
#define Lora3_AUX_GPIO               GPIOC
#define Lora3_AUX_GPIO_Pin           GPIO_Pin_13

/******************************************************************************
* @brief  用默认参数初始化Lora_Init_Struct                                    *                                                
* @param  Lora_Init_Struct：指向 Lora_InitTypedef_Struct类型的结构体数据      *
* @retval void.                                                               *
******************************************************************************/
void Lora_StructInit(Lora_InitTypedef_Struct *Lora_Init_Struct);

/******************************************************************************
* @brief  用Lora_Init_Struct 初始化Lora模块                                   *                                                
* @param  Lorax，选择初始化的Lora模块，x可以是1到 3                           *
* @param  Lora_Init_Struct： 初始化的Lora_InitTypeDef_Struct 结构数据         *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/
ErrorStatus Lora_Init(Lora_Typedef_Struct* Lorax, Lora_InitTypedef_Struct *Lora_Init_Struct);

/******************************************************************************
* @brief  打开 Lora                         	      		              	      *
* @param  Lorax，选择初始化的Lora模块，x可以是1到 3                           *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/ 
ErrorStatus Lora_Open(Lora_Typedef_Struct* Lorax);

/******************************************************************************
* @brief  关闭 Lora                         	      		              	      *
* @param  Lorax，选择初始化的Lora模块，x可以是1到 3                           *
* @retval ERROR or SUCCESS.                                                   *
******************************************************************************/ 
ErrorStatus Lora_Close(Lora_Typedef_Struct* Lorax);

/*****************************************************************************************
  * @brief   向Lora写入数据.                                                             *
  * @param   Lorax:  写入数据的Lora，x可以是1到 3            .                           *
  * @param   write_data: 指向Lora_WRITE_DATA_Struct类型的数据结构，存储写入放入数据      *	
	*              len                         串口写入数据的有效长度                      *
  *              data[len]                   串口写入数据                                *
  * @retval  ERROR or SUCCESS.                                                           *
*****************************************************************************************/
ErrorStatus Lora_WriteData(Lora_Typedef_Struct *Lorax,WRITEStruct *write_data);
	
/*****************************************************************************************
  * @brief   从Lora读取数据.                                                             *
  * @param   Lorax:  读取数据的Lora，x可以是1到 3            .                           *
  * @param   ReadData: 指向Lora_READ_DATA_Struct类型的数据结构，用于存储取回的数据       *	
  *              Fresh                       接收数据更新标志                            *
	*              len                         串口读入数据的有效长度                      *
  *              data[len]                   串口读入数据                                *
  * @retval  ERROR or SUCCESS.                                                           *
*****************************************************************************************/	
ErrorStatus Lora_ReadData(Lora_Typedef_Struct *Lorax,READStruct * ReadData);


#endif