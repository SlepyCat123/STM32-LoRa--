#ifndef __STM32F10X_Pulse_CAPTURE_H
#define __STM32F10X_Pulse_CAPTURE_H

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"
#include "string.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_tim.h"

#define Pulse_CAPTURE_NUM   (8)  //预设8个通道
#define PulseCapture_PREEMPTIONPRIORITY_DEFAULT        (3)
#define PulseCapture_SUBPRIORITY_DEFAULT               (3)



typedef enum PulseCapture_Polarity
{
    PulseCapture_Polarity_Positive,      // 输入信号未反相
    PulseCapture_Polarity_Negative       // 输入信号反相
} PulseCapture_Polarity;

typedef enum PulseCapture_Precision_Enum
{
    PulseCapture_Precision_0_014,       // 0.014us精度
    PulseCapture_Precision_0_125,       // 0.125us精度
    PulseCapture_Precision_0_5,         // 0.5us精度
    PulseCapture_Precision_1_0,          // 1us精度
    PulseCapture_Precision_10          // 10us精度
} PulseCapture_Precision;

typedef enum PulseCapture_Mode
{
    PulseCapture_Mode_High,              // 测量高电平时间
    PulseCapture_Mode_Low,               // 测量低电平时间
    PulseCapture_Mode_Period             // 测量周期
} PulseCapture_Mode;

// 测时通道硬件结构体
typedef struct PulseCapture_Hardware_Struct
{
    GPIO_TypeDef               *GPIOx;
    uint16_t                    Pinx;
	
    uint32_t                    EXTI_LINEx;                //中断线/中断程序号/中断口/中断源
    uint8_t                     EXTI_IRQn;
    uint8_t                     EXTI_GPIO_PortSourcex;
    uint8_t                     EXTI_GPIO_PinSourcex;
	
	  TIM_TypeDef                *TIMx;//一般使用TIM6/7,因为只有测时间功能
	
} PulseCapture_Hardware;

typedef struct PulseCapture_Result_Struct //存储测时数据
{
    FlagStatus       fresh; // 测时数据是否已更新
	
    union
    {
        float highTime;
        float lowTime;
        struct periodTime
        {
            float period;
            float duty;
        } periodTime;
    } Time;
} PulseCapture_Result;

//测量数据结构体 
typedef struct __PulseCapture_Data_Struct
{	
    FlagStatus                        Fresh;				  //更新标志位
	  PulseCapture_Result               TestMemory;  	  //数据 	
	  uint16_t             	            HighlevelTime;  //高电平时间
	  uint16_t             	            LowlevelTime;   //低电平时间
		float                            Time_ans;
			uint16_t                          CycleTime;
}PulseCapture_Data_Struct;

// 测时通道参数结构体
typedef struct PulseCapture_Memory_Struct
{
    FunctionalState              enable;
    PulseCapture_Polarity        polarity;
    PulseCapture_Precision       precision;  //精度
    PulseCapture_Mode            mode;
    FlagStatus                   fresh;     // 测时数据是否已更新
    uint16_t                     highTicks; // 测量得到的定时器计数值，根据精度计算出实际时间
    uint16_t                     lowTicks;
		float                        Time_ans;
} PulseCapture_Memory;

// 测时通道结构体
typedef struct  PulseCapture_Struct
{
    PulseCapture_Hardware    Hardware;
    PulseCapture_Memory      Memory;
} PulseCapture_Typedef;

// 测时通道初始化结构体
typedef struct  PulseCapture_InitTypedef
{
    FunctionalState           enable;
    PulseCapture_Polarity     polarity;
    PulseCapture_Precision    precision;
    PulseCapture_Mode         mode;
	 uint16_t                           EXTI_IRQPreemptionPriority;    
	 uint16_t                           EXTI_IRQSubPriority;	
	
} PulseCapture_InitTypedef;



extern PulseCapture_Typedef PulseCapture_Base[Pulse_CAPTURE_NUM];


#if(Pulse_CAPTURE_NUM >= 1)
#define Pulse_CAPTURE1                       (&PulseCapture_Base[0])
#define Pulse_CAPTURE1_GPIOx                 (GPIOE)
#define Pulse_CAPTURE1_PINx                  (GPIO_Pin_1)
#define Pulse_CAPTURE1_EXTI_LINEx            (EXTI_Line1)
#define Pulse_CAPTURE1_EXTI_IRQn             (EXTI1_IRQn)
#define Pulse_CAPTURE1_EXTI_GPIO_PortSourcex (GPIO_PortSourceGPIOE)
#define Pulse_CAPTURE1_EXTI_GPIO_PinSourcex  (GPIO_PinSource1)
#define Pulse_CAPTURE1_TIMx                  (TIM6 )
#endif

#if(Pulse_CAPTURE_NUM >= 2)
#define Pulse_CAPTURE2                       (&PulseCapture_Base[1])
#define Pulse_CAPTURE2_GPIOx                 (GPIOA)
#define Pulse_CAPTURE2_PINx                  (GPIO_Pin_1)
#define Pulse_CAPTURE2_EXTI_LINEx            (EXTI_Line1)
#define Pulse_CAPTURE2_EXTI_IRQn             (EXTI1_IRQn)
#define Pulse_CAPTURE2_EXTI_GPIO_PortSourcex (GPIO_PortSourceGPIOA)
#define Pulse_CAPTURE2_EXTI_GPIO_PinSourcex  (GPIO_PinSource1)
#define Pulse_CAPTURE2_TIMx                  (TIM7)
#endif

#if(Pulse_CAPTURE_NUM >= 3)
#define Pulse_CAPTURE3                       (&PulseCapture_Base[2])
#define Pulse_CAPTURE3_GPIOx                 (GPIOA)
#define Pulse_CAPTURE3_PINx                  (GPIO_Pin_2)
#define Pulse_CAPTURE3_EXTI_LINEx            (EXTI_Line_2)
#define Pulse_CAPTURE3_EXTI_IRQn             (EXTI2_IRQn)
#define Pulse_CAPTURE3_EXTI_GPIO_PortSourcex (GPIO_PortSourceGPIOA)
#define Pulse_CAPTURE3_EXTI_GPIO_PinSourcex  (GPIO_PinSource2)
#define Pulse_CAPTURE3_TIMx                  (TIM6)
#endif

#if(Pulse_CAPTURE_NUM >= 4)
#define Pulse_CAPTURE4                       (&PulseCapture_Base[3])
#define Pulse_CAPTURE4_GPIOx                 (GPIOA)
#define Pulse_CAPTURE4_PINx                  (GPIO_Pin_3)
#define Pulse_CAPTURE4_EXTI_LINEx            (EXTI_Line_3)
#define Pulse_CAPTURE4_EXTI_IRQn             (EXTI3_IRQn)
#define Pulse_CAPTURE4_EXTI_GPIO_PortSourcex (GPIO_PortSourceGPIOA)
#define Pulse_CAPTURE4_EXTI_GPIO_PinSourcex  (GPIO_PinSource3)
#define Pulse_CAPTURE4_TIMx                  (TIM7)
#endif

#if(Pulse_CAPTURE_NUM >= 5)
#define Pulse_CAPTURE5                       (&PulseCapture_Base[4])
#define Pulse_CAPTURE5_GPIOx                 (GPIOA)
#define Pulse_CAPTURE5_PINx                  (GPIO_Pin_4)
#define Pulse_CAPTURE5_EXTI_LINEx            (EXTI_Line_4)
#define Pulse_CAPTURE5_EXTI_IRQn             (EXTI4_IRQn)
#define Pulse_CAPTURE5_EXTI_GPIO_PortSourcex (GPIO_PortSourceGPIOA)
#define Pulse_CAPTURE5_EXTI_GPIO_PinSourcex  (GPIO_PinSource4)
#define Pulse_CAPTURE5_TIMx                  (TIM6)
#endif

#if(Pulse_CAPTURE_NUM >= 6)
#define Pulse_CAPTURE6                       (&PulseCapture_Base[5])
#define Pulse_CAPTURE6_GPIOx                 (GPIOA)
#define Pulse_CAPTURE6_PINx                  (GPIO_Pin_5)
#define Pulse_CAPTURE6_EXTI_LINEx            (EXTI_Line_5)
#define Pulse_CAPTURE6_EXTI_IRQn             (EXTI9_5_IRQn)
#define Pulse_CAPTURE6_EXTI_GPIO_PortSourcex (GPIO_PortSourceGPIOA)
#define Pulse_CAPTURE6_EXTI_GPIO_PinSourcex  (GPIO_PinSource5)
#define Pulse_CAPTURE6_TIMx                  (TIM7)
#endif

#if(Pulse_CAPTURE_NUM >= 7)
#define Pulse_CAPTURE7                       (&PulseCapture_Base[6])
#define Pulse_CAPTURE7_GPIOx                 (GPIOA)
#define Pulse_CAPTURE7_PINx                  (GPIO_Pin_6)
#define Pulse_CAPTURE7_EXTI_LINEx            (EXTI_Line_6)
#define Pulse_CAPTURE7_EXTI_IRQn             (EXTI9_5_IRQn)
#define Pulse_CAPTURE7_EXTI_GPIO_PortSourcex (GPIO_PortSourceGPIOA)
#define Pulse_CAPTURE7_EXTI_GPIO_PinSourcex  (GPIO_PinSource6)
#define Pulse_CAPTURE7_TIMx                  (TIM6)
#endif

#if(Pulse_CAPTURE_NUM >= 8)
#define Pulse_CAPTURE8                       (&PulseCapture_Base[7])
#define Pulse_CAPTURE8_GPIOx                 (GPIOA)
#define Pulse_CAPTURE8_PINx                  (GPIO_Pin_7)
#define Pulse_CAPTURE8_EXTI_LINEx            (EXTI_Line_7)
#define Pulse_CAPTURE8_EXTI_IRQn             (EXTI9_5_IRQn)
#define Pulse_CAPTURE8_EXTI_GPIO_PortSourcex (GPIO_PortSourceGPIOA)
#define Pulse_CAPTURE8_EXTI_GPIO_PinSourcex  (GPIO_PinSource7)
#define Pulse_CAPTURE8_TIMx                  (TIM7)
#endif

#define Pulse_CAPTURE_DEFAULT_ENABLE        (ENABLE)
#define Pulse_CAPTURE_DEFAULT_POLARITY      (PulseCapture_Polarity_Positive)
#define Pulse_CAPTURE_DEFAULT_PRECISION     (PulseCapture_Precision_1us)
#define Pulse_CAPTURE_DEFAULT_MODE          (PulseCapture_Mode_High)

// 结构体初始化
ErrorStatus PulseCapture_StructInit(PulseCapture_InitTypedef *init);

// 测时通道初始化
ErrorStatus PulseCapture_Init(PulseCapture_Typedef *pCx, PulseCapture_InitTypedef *init);

// 使能测时通道，使能后自动测量并更新数据
ErrorStatus PulseCapture_Enable(PulseCapture_Typedef *pCx);

// 失能测时通道
ErrorStatus PulseCapture_Disable(PulseCapture_Typedef *pCx);

// 读取最近一次完整测量得到的时间值
ErrorStatus PulseCapture_Read(PulseCapture_Typedef *pCx, PulseCapture_Result *result);

//改变精度
ErrorStatus PulseCapture_PrecisionSelect(PulseCapture_Typedef *pCx, PulseCapture_Precision PRE);

void PulseTimel_IRQHandler(void);
void PulseTime2_IRQHandler(void);
void PulseTime3_IRQHandler(void);
void PulseTime4_IRQHandler(void);
void PulseTime5_IRQHandler(void);
void PulseTime6_IRQHandler(void);
void PulseTime7_IRQHandler(void);
void PulseTime8_IRQHandler(void);

#endif
