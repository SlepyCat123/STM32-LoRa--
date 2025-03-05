#include "stm32f10x_pulseCapture.h"
/*******************************************************************************
  * @file   stm32f10x_pulseCapture.c
  * @author  GAN
  * @version V1.0.0
  * @date    2022/10/07
  * @brief   Lora模块驱动，调用文档：stm32f10x_scom.c
  *****************************************************************************/
PulseCapture_Typedef PulseCapture_Base[Pulse_CAPTURE_NUM];
static uint16_t                Flag1,Flag2,Flag3,Flag4,Flag5,Flag6,Flag7,Flag8;

PulseCapture_Data_Struct          Pulse1_Data,Pulse2_Data,Pulse3_Data,Pulse4_Data,Pulse5_Data,Pulse6_Data,Pulse7_Data,Pulse8_Data;

static __INLINE void __pulseCaptur_Disable_IRQ(void);    //关中断函数
static __INLINE void __pulseCapture_Restore_IRQ(void);    //开中断函数
/* --------------------------- 中断  存储变量 ---------------------- */
static  uint32_t           __pulseCaptur_CPU_PRIMASK_REG_SAVE_VALUE;

/*****************************************************************/	
static __INLINE void __pulseCaptur_Disable_IRQ(void)
{
    __pulseCaptur_CPU_PRIMASK_REG_SAVE_VALUE = __get_PRIMASK();
	  __disable_irq();
}

/*****************************************************************
  * @brief   开中断                                              *
  * @param   void                                                *
  * @retval  void                                                *
*****************************************************************/	
static __INLINE void __pulseCaptur_Restore_IRQ(void)
{
    __set_PRIMASK(__pulseCaptur_CPU_PRIMASK_REG_SAVE_VALUE) ;
}



// 结构体初始化
ErrorStatus PulseCapture_StructInit(PulseCapture_InitTypedef *init)
{
	init->enable   =    ENABLE;
	init->mode     =    PulseCapture_Mode_High;
	init->polarity =    PulseCapture_Polarity_Positive;
	init->precision=    PulseCapture_Precision_0_5;
	init->EXTI_IRQPreemptionPriority =PulseCapture_PREEMPTIONPRIORITY_DEFAULT;
	init->EXTI_IRQSubPriority        =PulseCapture_SUBPRIORITY_DEFAULT ;    
	
}

// 测时通道初始化
ErrorStatus PulseCapture_Init(PulseCapture_Typedef *pCx, PulseCapture_InitTypedef *init)
{
	 GPIO_InitTypeDef           GPIO_InitStructure;
	 TIM_TimeBaseInitTypeDef 		TIM_InitStructure;
	 EXTI_InitTypeDef EXTI_InitStructure;
 	 NVIC_InitTypeDef NVIC_InitStructure;
	
	    if((pCx== NULL)||(init == NULL))
		{
			return ERROR;
		}
    //1.填充 通道变量 硬件设置  (三个引脚和对应的SCOM)
		if(pCx == Pulse_CAPTURE1)
		{
			pCx -> Hardware.EXTI_GPIO_PinSourcex  =   Pulse_CAPTURE1_EXTI_GPIO_PinSourcex;
			pCx -> Hardware.EXTI_GPIO_PortSourcex =   Pulse_CAPTURE1_EXTI_GPIO_PortSourcex;
			pCx -> Hardware.EXTI_IRQn             =   Pulse_CAPTURE1_EXTI_IRQn;
			pCx -> Hardware.EXTI_LINEx            =   Pulse_CAPTURE1_EXTI_LINEx;
			pCx ->Hardware.GPIOx                  =   Pulse_CAPTURE1_GPIOx;
			pCx ->Hardware.Pinx                   =   Pulse_CAPTURE1_PINx ;
			pCx ->Hardware.TIMx                   =   Pulse_CAPTURE1_TIMx;
		}
	  else if(pCx == Pulse_CAPTURE2)
		{
			pCx -> Hardware.EXTI_GPIO_PinSourcex  =   Pulse_CAPTURE2_EXTI_GPIO_PinSourcex;
			pCx -> Hardware.EXTI_GPIO_PortSourcex =   Pulse_CAPTURE2_EXTI_GPIO_PortSourcex;
			pCx -> Hardware.EXTI_IRQn             =   Pulse_CAPTURE2_EXTI_IRQn;
			pCx -> Hardware.EXTI_LINEx            =   Pulse_CAPTURE2_EXTI_LINEx;
			pCx ->Hardware.GPIOx                  =   Pulse_CAPTURE2_GPIOx;
			pCx ->Hardware.Pinx                   =   Pulse_CAPTURE2_PINx ;
			pCx ->Hardware.TIMx                   =   Pulse_CAPTURE2_TIMx;
		}
//	  else if(pCx == Pulse_CAPTURE3)
//		{
//			pCx -> Hardware.EXTI_GPIO_PinSourcex  =   Pulse_CAPTURE3_EXTI_GPIO_PinSourcex;
//			pCx -> Hardware.EXTI_GPIO_PortSourcex =   Pulse_CAPTURE3_EXTI_GPIO_PortSourcex;
//			pCx -> Hardware.EXTI_IRQn             =   Pulse_CAPTURE3_EXTI_IRQn;
//			pCx -> Hardware.EXTI_LINEx            =   Pulse_CAPTURE3_EXTI_LINEx;
//			pCx ->Hardware.GPIOx                  =   Pulse_CAPTURE3_GPIOx;
//			pCx ->Hardware.Pinx                   =   Pulse_CAPTURE3_PINx ;
//			pCx ->Hardware.TIMx                   =   Pulse_CAPTURE3_TIMx;
//		
//	  else if(pCx == Pulse_CAPTURE4)
//		{
//			pCx -> Hardware.EXTI_GPIO_PinSourcex  =   Pulse_CAPTURE4_EXTI_GPIO_PinSourcex;
//			pCx -> Hardware.EXTI_GPIO_PortSourcex =   Pulse_CAPTURE4_EXTI_GPIO_PortSourcex;
//			pCx -> Hardware.EXTI_IRQn             =   Pulse_CAPTURE4_EXTI_IRQn;
//			pCx -> Hardware.EXTI_LINEx            =   Pulse_CAPTURE4_EXTI_LINEx;
//			pCx ->Hardware.GPIOx                  =   Pulse_CAPTURE4_GPIOx;
//			pCx ->Hardware.Pinx                   =   Pulse_CAPTURE4_PINx ;
//			pCx ->Hardware.TIMx                   =   Pulse_CAPTURE4_TIMx;
//		}
//	  else if(pCx == Pulse_CAPTURE5)
//		{
//			pCx -> Hardware.EXTI_GPIO_PinSourcex  =   Pulse_CAPTURE5_EXTI_GPIO_PinSourcex;
//			pCx -> Hardware.EXTI_GPIO_PortSourcex =   Pulse_CAPTURE5_EXTI_GPIO_PortSourcex;
//			pCx -> Hardware.EXTI_IRQn             =   Pulse_CAPTURE5_EXTI_IRQn;
//			pCx -> Hardware.EXTI_LINEx            =   Pulse_CAPTURE5_EXTI_LINEx;
//			pCx ->Hardware.GPIOx                  =   Pulse_CAPTURE5_GPIOx;
//			pCx ->Hardware.Pinx                   =   Pulse_CAPTURE5_PINx ;
//			pCx ->Hardware.TIMx                   =   Pulse_CAPTURE5_TIMx;
//		}
//	  else if(pCx == Pulse_CAPTURE6)
//		{
//			pCx -> Hardware.EXTI_GPIO_PinSourcex  =   Pulse_CAPTURE6_EXTI_GPIO_PinSourcex;
//			pCx -> Hardware.EXTI_GPIO_PortSourcex =   Pulse_CAPTURE6_EXTI_GPIO_PortSourcex;
//			pCx -> Hardware.EXTI_IRQn             =   Pulse_CAPTURE6_EXTI_IRQn;
//			pCx -> Hardware.EXTI_LINEx            =   Pulse_CAPTURE6_EXTI_LINEx;
//			pCx ->Hardware.GPIOx                  =   Pulse_CAPTURE6_GPIOx;
//			pCx ->Hardware.Pinx                   =   Pulse_CAPTURE6_PINx ;
//			pCx ->Hardware.TIMx                   =   Pulse_CAPTURE6_TIMx;
//		}
//	  else if(pCx == Pulse_CAPTURE7)
//		{
//			pCx -> Hardware.EXTI_GPIO_PinSourcex  =   Pulse_CAPTURE7_EXTI_GPIO_PinSourcex;
//			pCx -> Hardware.EXTI_GPIO_PortSourcex =   Pulse_CAPTURE7_EXTI_GPIO_PortSourcex;
//			pCx -> Hardware.EXTI_IRQn             =   Pulse_CAPTURE7_EXTI_IRQn;
//			pCx -> Hardware.EXTI_LINEx            =   Pulse_CAPTURE7_EXTI_LINEx;
//			pCx ->Hardware.GPIOx                  =   Pulse_CAPTURE7_GPIOx;
//			pCx ->Hardware.Pinx                   =   Pulse_CAPTURE7_PINx ;
//			pCx ->Hardware.TIMx                   =   Pulse_CAPTURE7_TIMx;
//		}
//	  else if(pCx == Pulse_CAPTURE8)
//		{
//			pCx -> Hardware.EXTI_GPIO_PinSourcex  =   Pulse_CAPTURE8_EXTI_GPIO_PinSourcex;
//			pCx -> Hardware.EXTI_GPIO_PortSourcex =   Pulse_CAPTURE8_EXTI_GPIO_PortSourcex;
//			pCx -> Hardware.EXTI_IRQn             =   Pulse_CAPTURE8_EXTI_IRQn;
//			pCx -> Hardware.EXTI_LINEx            =   Pulse_CAPTURE8_EXTI_LINEx;
//			pCx ->Hardware.GPIOx                  =   Pulse_CAPTURE8_GPIOx;
//			pCx ->Hardware.Pinx                   =   Pulse_CAPTURE8_PINx ;
//			pCx ->Hardware.TIMx                   =   Pulse_CAPTURE8_TIMx;
//		}
     //2参数设置
		pCx->Memory.enable      =    init->enable;
		pCx->Memory.polarity    =    init->polarity;
		pCx->Memory.precision   =    init->precision;
		pCx->Memory.mode        =    init->mode;
		pCx->Memory.fresh       =    RESET;
		
		//3硬件配置
		GPIO_StructInit(&GPIO_InitStructure);
		GPIO_InitStructure.GPIO_Pin                          = pCx->Hardware.Pinx;					
  	GPIO_InitStructure.GPIO_Speed                        = GPIO_Speed_50MHz;
  	GPIO_InitStructure.GPIO_Mode                         = GPIO_Mode_IN_FLOATING;  
  	GPIO_Init(pCx->Hardware.GPIOx,&GPIO_InitStructure);
		
		GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,pCx->Hardware.EXTI_GPIO_PinSourcex);//设置IO口与中断线的映射关系
  	EXTI_InitStructure.EXTI_Line                         = pCx->Hardware.EXTI_LINEx;
  	EXTI_InitStructure.EXTI_Mode                         = EXTI_Mode_Interrupt;	
		EXTI_InitStructure.EXTI_Trigger                      = EXTI_Trigger_Rising_Falling;
		EXTI_InitStructure.EXTI_LineCmd                      = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  																													//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
		
		NVIC_InitStructure.NVIC_IRQChannel                   =pCx->Hardware.EXTI_IRQn;			
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = init->EXTI_IRQPreemptionPriority;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority        = init->EXTI_IRQSubPriority;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd                = ENABLE;																					          //使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 
				return SUCCESS;
}
// 使能测时通道，使能后自动测量并更新数据
ErrorStatus PulseCapture_Enable(PulseCapture_Typedef *pCx)
{
		 if(pCx== NULL)
	 {
		 return ERROR;
	 }
	 pCx->Memory.enable = ENABLE;
	 return SUCCESS;

}

// 失能测时通道
ErrorStatus PulseCapture_Disable(PulseCapture_Typedef *pCx)
{
	if(pCx== NULL)
	 {
		 return ERROR;
	 }
	 pCx->Memory.enable = DISABLE;
	 return SUCCESS;
}
//// 读取最近一次完整测量得到的时间值
//ErrorStatus PulseCapture_Read(PulseCapture_Typedef *pCx, PulseCapture_Result *result);

//void PulseCapturel_IRQHandler(void)
//{
//	static uint16_t            StartTime1=0;
//	static uint16_t            EndTime1=0;
//	static uint16_t            EdgeNum1=0;
//	uint32_t                    PulseCaptureDatel=0;
//	
//	TIM_TimeBaseInit(TIM_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
//	 TIM_Cmd(TIM_TypeDef* TIMx, FunctionalState NewState);
//	
//	if (EXTI_GetITStatus(Pulse_CAPTURE1.Hardware.EXTI_Line) != RESET)
//	{
//	 EdgeNum1=Fresh;
//   StartTime1=TIM_GetCounter(Pulse_CAPTURE1_TIMx );
//			while(EXTI_GetITStatus(Pulse_CAPTURE1.Hardware.EXTI_Line) != RESET)
//			{

//			}
//			EndTime1=TIM_GetCounter(Pulse_CAPTURE1_TIMx );
//			EdgeNum1=NoFresh;
//			PulseCaptureDatel=EndTime1-StartTime1;
//	}
//	
//}


 //中断服务程序1函数
 void Pulse_CAPTURE1_IRQHandler(void)
 {
	 static uint16_t Start_High_Time = 0,Start_Low_Time = 0;
	 static uint16_t Finsh_High_Time = 0,Finsh_Low_Time = 0;
	 
	 if(EXTI_GetITStatus(Pulse_CAPTURE1->Hardware.EXTI_LINEx) == SET && Pulse_CAPTURE1->Memory.enable == ENABLE)
	 {
		 EXTI_ClearITPendingBit(Pulse_CAPTURE1->Hardware.EXTI_LINEx);
		 switch(Pulse_CAPTURE1->Memory.mode)
		 {
			 case PulseCapture_Mode_High:
				 switch(Pulse_CAPTURE1->Memory.polarity)
				 {
					 case  PulseCapture_Polarity_Positive:
						 if(Flag1 == 0)
						 {
							 if(1 == GPIO_ReadInputDataBit(Pulse_CAPTURE1->Hardware.GPIOx,Pulse_CAPTURE1->Hardware.Pinx))
							 {
								 Start_High_Time = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
								 Flag1 += 1;
							 }
						 }
						 else if(Flag1 == 1)
						 {
							 if(0 == GPIO_ReadInputDataBit(Pulse_CAPTURE1->Hardware.GPIOx,Pulse_CAPTURE1->Hardware.Pinx))
							 {
							 Finsh_High_Time = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
							 Flag1 = 0;
							 Pulse1_Data.Fresh = SET;
							 if(Start_High_Time > Finsh_High_Time)
							 {
								 Pulse1_Data.HighlevelTime = 65535 + Finsh_High_Time - Start_High_Time;
							 }
							 else if(Finsh_High_Time > Start_High_Time)
							 {
								 Pulse1_Data.HighlevelTime = Finsh_High_Time - Start_High_Time;
							 }
						 }
						 }
						 break;
					 case PulseCapture_Polarity_Negative:
						 if(Flag1 == 0)
						 {
							 if(0 == GPIO_ReadInputDataBit(Pulse_CAPTURE1->Hardware.GPIOx,Pulse_CAPTURE1->Hardware.Pinx))
							 {
								 Start_High_Time = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
								 Flag1 += 1;
							 }
						 }
						 else if(Flag1 == 1)
						 {
							 if(1 == GPIO_ReadInputDataBit(Pulse_CAPTURE1->Hardware.GPIOx,Pulse_CAPTURE1->Hardware.Pinx))
							 {
							 Finsh_High_Time = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
							 Flag1 = 0;
							 Pulse1_Data.Fresh = SET;
							 if(Start_High_Time > Finsh_High_Time)
							 {
								 Pulse1_Data.HighlevelTime = 65535 + Finsh_High_Time - Start_High_Time;
							 }
							 else if(Finsh_High_Time > Start_High_Time)
							 {
								 Pulse1_Data.HighlevelTime = Finsh_High_Time - Start_High_Time;
							 }
						 }
						 }
						 break;					
				 }
			 case   PulseCapture_Mode_Low:
				 switch(Pulse_CAPTURE1->Memory.mode)
				 {
					 case PulseCapture_Mode_High:
						 if(Flag1 == 0)
						 {
							 if(0 == GPIO_ReadInputDataBit(Pulse_CAPTURE1->Hardware.GPIOx,Pulse_CAPTURE1->Hardware.Pinx))
							 {
								 Start_Low_Time = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
								 Flag1 += 1;
							 }
						 }
						 else if(Flag1 == 1)
						 {
  						 if(1 == GPIO_ReadInputDataBit(Pulse_CAPTURE1->Hardware.GPIOx,Pulse_CAPTURE1->Hardware.Pinx))
							 {
							 Finsh_Low_Time = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
							 Flag1 = 0;
							 Pulse1_Data.Fresh = SET;
							 if(Start_Low_Time > Finsh_Low_Time)
							 {
								 Pulse1_Data.LowlevelTime = 65535 + Finsh_Low_Time - Start_Low_Time;
							 }
							 else if(Finsh_Low_Time > Start_Low_Time)
							 {
								 Pulse1_Data.LowlevelTime = Finsh_Low_Time - Start_Low_Time;
							 }
						 }
						 }
						 break;
					 case PulseCapture_Polarity_Negative:
						 if(Flag1 == 0)
						 {
							 if(1 == GPIO_ReadInputDataBit(Pulse_CAPTURE1->Hardware.GPIOx,Pulse_CAPTURE1->Hardware.Pinx))
							 {
								 Start_Low_Time = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
								 Flag1 += 1;
							 }
						 }
						 else if(Flag1 == 1)
						 {
							 if(0 == GPIO_ReadInputDataBit(Pulse_CAPTURE1->Hardware.GPIOx,Pulse_CAPTURE1->Hardware.Pinx))
							 {							 
							 Finsh_Low_Time = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
							 Flag1 = 0;
							 Pulse1_Data.Fresh = SET;
							 if(Start_Low_Time > Finsh_Low_Time)
							 {
								 Pulse1_Data.LowlevelTime = 65535 + Finsh_Low_Time - Start_Low_Time;
							 }
							 else if(Finsh_Low_Time > Start_Low_Time)
							 {
								 Pulse1_Data.LowlevelTime = Finsh_Low_Time - Start_Low_Time;
							 }
							 }
						 }
					default:break;				
				 }
			 case     PulseCapture_Mode_Period :
				 switch(Pulse_CAPTURE1->Memory.mode)
				 {
					 case PulseCapture_Mode_High:
						 if(Flag1 == 0)
						 {
							 if(1 == GPIO_ReadInputDataBit(Pulse_CAPTURE1->Hardware.GPIOx,Pulse_CAPTURE1->Hardware.Pinx))
							 {
								 Start_High_Time = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
								 Flag1 += 1;
							 }
						 }
						 else if(Flag1 == 1)
						 {
							 if(0 == GPIO_ReadInputDataBit(Pulse_CAPTURE1->Hardware.GPIOx,Pulse_CAPTURE1->Hardware.Pinx))
							 {
							 Finsh_High_Time = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
							 Start_Low_Time  = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
							 Flag1 += 1;
							 }
 						 }
						 else if(Flag1 == 2)
						 {
							 if(1 == GPIO_ReadInputDataBit(Pulse_CAPTURE1->Hardware.GPIOx,Pulse_CAPTURE1->Hardware.Pinx))
							 {
							 Finsh_Low_Time = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
							 Flag1 = 0;
							 Pulse1_Data.Fresh = SET;
							 if(Start_High_Time > Finsh_High_Time)
							 {
								 Pulse1_Data.HighlevelTime = 65535 + Finsh_High_Time - Start_High_Time;
							 }
							 else if(Finsh_High_Time > Start_High_Time)
							 {
								 Pulse1_Data.HighlevelTime = Finsh_High_Time - Start_High_Time;
							 }
							 if(Start_Low_Time > Finsh_Low_Time)
							 {
								 Pulse1_Data.LowlevelTime = 65535 + Finsh_Low_Time - Start_Low_Time;
							 }
							 else if(Finsh_Low_Time > Start_Low_Time)
							 {
								 Pulse1_Data.LowlevelTime = Finsh_Low_Time - Start_Low_Time;
							 }
							 Pulse1_Data.CycleTime     = Pulse1_Data.HighlevelTime + Pulse1_Data.LowlevelTime;            
						 }
					 }
						 break;
					 case PulseCapture_Polarity_Negative:
						 if(Flag1 == 0)
						 {
							 if(0 == GPIO_ReadInputDataBit(Pulse_CAPTURE1->Hardware.GPIOx,Pulse_CAPTURE1->Hardware.Pinx))
							 {
								 Start_High_Time = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
								 Flag1 += 1;
							 }
						 }
						 else if(Flag1 == 1)
						 {
							 if(1 == GPIO_ReadInputDataBit(Pulse_CAPTURE1->Hardware.GPIOx,Pulse_CAPTURE1->Hardware.Pinx))
							 {
							 Finsh_High_Time = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
							 Start_Low_Time  = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
							 Flag1 += 1;
 						 }
					 }
						 else if(Flag1 == 2)
						 {
							 if(0 == GPIO_ReadInputDataBit(Pulse_CAPTURE1->Hardware.GPIOx,Pulse_CAPTURE1->Hardware.Pinx))
							 {
							 Finsh_Low_Time = TIM_GetCounter(Pulse_CAPTURE1->Hardware.TIMx);
							 Flag1 = 0;
							 Pulse1_Data.Fresh = SET;
								 
							 if(Start_High_Time > Finsh_High_Time)
							 {
								 Pulse1_Data.HighlevelTime = 65535 + Finsh_High_Time - Start_High_Time;
							 }
							 else if(Finsh_High_Time > Start_High_Time)
							 {
								 Pulse1_Data.HighlevelTime = Finsh_High_Time - Start_High_Time;
							 }
							 if(Start_Low_Time > Finsh_Low_Time)
							 {
								 Pulse1_Data.LowlevelTime = 65535 + Finsh_Low_Time - Start_Low_Time;
							 }
							 else if(Finsh_Low_Time > Start_Low_Time)
							 {
								 Pulse1_Data.LowlevelTime = Finsh_Low_Time - Start_Low_Time;
							 }
							 Pulse1_Data.CycleTime     = Pulse1_Data.HighlevelTime + Pulse1_Data.LowlevelTime;            
						 }
					 }
					default:break;			
				 }				  
		 }
	 }
 }
//*************************************************************************************************

 //中断服务程序1函数
 void Pulse_CAPTURE2_IRQHandler(void)
 {
	 static uint16_t Start_High_Time = 0,Start_Low_Time = 0;
	 static uint16_t Finsh_High_Time = 0,Finsh_Low_Time = 0;
	 
	 if(EXTI_GetITStatus(Pulse_CAPTURE2->Hardware.EXTI_LINEx) == SET && Pulse_CAPTURE2->Memory.enable == ENABLE)
	 {
		 EXTI_ClearITPendingBit(Pulse_CAPTURE2->Hardware.EXTI_LINEx);
		 switch(Pulse_CAPTURE2->Memory.mode)
		 {
			 case PulseCapture_Mode_High:
				 switch(Pulse_CAPTURE2->Memory.polarity)
				 {
					 case  PulseCapture_Polarity_Positive:
						 if(Flag2 == 0)
						 {
							 if(1 == GPIO_ReadInputDataBit(Pulse_CAPTURE2->Hardware.GPIOx,Pulse_CAPTURE2->Hardware.Pinx))
							 {
								 Start_High_Time = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
								 Flag2 += 1;
							 }
						 }
						 else if(Flag2 == 1)
						 {
							 if(0 == GPIO_ReadInputDataBit(Pulse_CAPTURE2->Hardware.GPIOx,Pulse_CAPTURE2->Hardware.Pinx))
							 {
							 Finsh_High_Time = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
							 Flag2 = 0;
							 Pulse2_Data.Fresh = SET;
							 if(Start_High_Time > Finsh_High_Time)
							 {
								 Pulse2_Data.HighlevelTime = 65535 + Finsh_High_Time - Start_High_Time;
							 }
							 else if(Finsh_High_Time > Start_High_Time)
							 {
								 Pulse2_Data.HighlevelTime = Finsh_High_Time - Start_High_Time;
							 }
						 }
						 }
						 break;
					 case PulseCapture_Polarity_Negative:
						 if(Flag2 == 0)
						 {
							 if(0 == GPIO_ReadInputDataBit(Pulse_CAPTURE2->Hardware.GPIOx,Pulse_CAPTURE2->Hardware.Pinx))
							 {
								 Start_High_Time = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
								 Flag2 += 1;
							 }
						 }
						 else if(Flag2 == 1)
						 {
							 if(1 == GPIO_ReadInputDataBit(Pulse_CAPTURE2->Hardware.GPIOx,Pulse_CAPTURE2->Hardware.Pinx))
							 {
							 Finsh_High_Time = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
							 Flag2 = 0;
							 Pulse2_Data.Fresh = SET;
							 if(Start_High_Time > Finsh_High_Time)
							 {
								 Pulse2_Data.HighlevelTime = 65535 + Finsh_High_Time - Start_High_Time;
							 }
							 else if(Finsh_High_Time > Start_High_Time)
							 {
								 Pulse2_Data.HighlevelTime = Finsh_High_Time - Start_High_Time;
							 }
						 }
						 }
						 break;					
				 }
			 case   PulseCapture_Mode_Low:
				 switch(Pulse_CAPTURE2->Memory.mode)
				 {
					 case PulseCapture_Mode_High:
						 if(Flag2 == 0)
						 {
							 if(0 == GPIO_ReadInputDataBit(Pulse_CAPTURE2->Hardware.GPIOx,Pulse_CAPTURE2->Hardware.Pinx))
							 {
								 Start_Low_Time = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
								 Flag2 += 1;
							 }
						 }
						 else if(Flag2 == 1)
						 {
  						 if(1 == GPIO_ReadInputDataBit(Pulse_CAPTURE2->Hardware.GPIOx,Pulse_CAPTURE2->Hardware.Pinx))
							 {
							 Finsh_Low_Time = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
							 Flag2 = 0;
							 Pulse2_Data.Fresh = SET;
							 if(Start_Low_Time > Finsh_Low_Time)
							 {
								 Pulse2_Data.LowlevelTime = 65535 + Finsh_Low_Time - Start_Low_Time;
							 }
							 else if(Finsh_Low_Time > Start_Low_Time)
							 {
								 Pulse2_Data.LowlevelTime = Finsh_Low_Time - Start_Low_Time;
							 }
						 }
						 }
						 break;
					 case PulseCapture_Polarity_Negative:
						 if(Flag2 == 0)
						 {
							 if(1 == GPIO_ReadInputDataBit(Pulse_CAPTURE2->Hardware.GPIOx,Pulse_CAPTURE2->Hardware.Pinx))
							 {
								 Start_Low_Time = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
								 Flag2 += 1;
							 }
						 }
						 else if(Flag2 == 1)
						 {
							 if(0 == GPIO_ReadInputDataBit(Pulse_CAPTURE2->Hardware.GPIOx,Pulse_CAPTURE2->Hardware.Pinx))
							 {							 
							 Finsh_Low_Time = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
							 Flag2 = 0;
							 Pulse2_Data.Fresh = SET;
							 if(Start_Low_Time > Finsh_Low_Time)
							 {
								 Pulse2_Data.LowlevelTime = 65535 + Finsh_Low_Time - Start_Low_Time;
							 }
							 else if(Finsh_Low_Time > Start_Low_Time)
							 {
								 Pulse2_Data.LowlevelTime = Finsh_Low_Time - Start_Low_Time;
							 }
							 }
						 }
					default:break;				
				 }
			 case     PulseCapture_Mode_Period :
				 switch(Pulse_CAPTURE2->Memory.mode)
				 {
					 case PulseCapture_Mode_High:
						 if(Flag2 == 0)
						 {
							 if(1 == GPIO_ReadInputDataBit(Pulse_CAPTURE2->Hardware.GPIOx,Pulse_CAPTURE2->Hardware.Pinx))
							 {
								 Start_High_Time = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
								 Flag2 += 1;
							 }
						 }
						 else if(Flag2 == 1)
						 {
							 if(0 == GPIO_ReadInputDataBit(Pulse_CAPTURE2->Hardware.GPIOx,Pulse_CAPTURE2->Hardware.Pinx))
							 {
							 Finsh_High_Time = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
							 Start_Low_Time  = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
							 Flag2 += 1;
							 }
 						 }
						 else if(Flag2 == 2)
						 {
							 if(1 == GPIO_ReadInputDataBit(Pulse_CAPTURE2->Hardware.GPIOx,Pulse_CAPTURE2->Hardware.Pinx))
							 {
							 Finsh_Low_Time = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
							 Flag2 = 0;
							 Pulse2_Data.Fresh = SET;
							 if(Start_High_Time > Finsh_High_Time)
							 {
								 Pulse2_Data.HighlevelTime = 65535 + Finsh_High_Time - Start_High_Time;
							 }
							 else if(Finsh_High_Time > Start_High_Time)
							 {
								 Pulse2_Data.HighlevelTime = Finsh_High_Time - Start_High_Time;
							 }
							 if(Start_Low_Time > Finsh_Low_Time)
							 {
								 Pulse2_Data.LowlevelTime = 65535 + Finsh_Low_Time - Start_Low_Time;
							 }
							 else if(Finsh_Low_Time > Start_Low_Time)
							 {
								 Pulse2_Data.LowlevelTime = Finsh_Low_Time - Start_Low_Time;
							 }
							 Pulse2_Data.CycleTime     = Pulse2_Data.HighlevelTime + Pulse2_Data.LowlevelTime;            
						 }
					 }
						 break;
					 case PulseCapture_Polarity_Negative:
						 if(Flag2 == 0)
						 {
							 if(0 == GPIO_ReadInputDataBit(Pulse_CAPTURE2->Hardware.GPIOx,Pulse_CAPTURE2->Hardware.Pinx))
							 {
								 Start_High_Time = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
								 Flag2 += 1;
							 }
						 }
						 else if(Flag2 == 1)
						 {
							 if(1 == GPIO_ReadInputDataBit(Pulse_CAPTURE2->Hardware.GPIOx,Pulse_CAPTURE2->Hardware.Pinx))
							 {
							 Finsh_High_Time = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
							 Start_Low_Time  = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
							 Flag2 += 1;
 						 }
					 }
						 else if(Flag2 == 2)
						 {
							 if(0 == GPIO_ReadInputDataBit(Pulse_CAPTURE2->Hardware.GPIOx,Pulse_CAPTURE2->Hardware.Pinx))
							 {
							 Finsh_Low_Time = TIM_GetCounter(Pulse_CAPTURE2->Hardware.TIMx);
							 Flag2 = 0;
							 Pulse2_Data.Fresh = SET;
								 
							 if(Start_High_Time > Finsh_High_Time)
							 {
								 Pulse2_Data.HighlevelTime = 65535 + Finsh_High_Time - Start_High_Time;
							 }
							 else if(Finsh_High_Time > Start_High_Time)
							 {
								 Pulse2_Data.HighlevelTime = Finsh_High_Time - Start_High_Time;
							 }
							 if(Start_Low_Time > Finsh_Low_Time)
							 {
								 Pulse2_Data.LowlevelTime = 65535 + Finsh_Low_Time - Start_Low_Time;
							 }
							 else if(Finsh_Low_Time > Start_Low_Time)
							 {
								 Pulse2_Data.LowlevelTime = Finsh_Low_Time - Start_Low_Time;
							 }
							 Pulse2_Data.CycleTime     = Pulse2_Data.HighlevelTime + Pulse2_Data.LowlevelTime;            
						 }
					 }
					default:break;			
				 }				  
		 }
	 }
 }
//*************************************************************************************************
 
 ErrorStatus PulseCapture_PrecisionSelect(PulseCapture_Typedef *pCx, PulseCapture_Precision PRE)
 {
	 	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	  TIM_OCInitTypeDef  TIM_OCInitStructure;
	 switch(PRE)
	 {
		 case PulseCapture_Precision_0_014:
			 {   
				 TIM_TimeBaseStructure.TIM_Period = 1; 
			 }
		 case PulseCapture_Precision_0_125:
		 {
				 TIM_TimeBaseStructure.TIM_Period = 9; 			 
		 }
		 case PulseCapture_Precision_0_5:
		 {
				 TIM_TimeBaseStructure.TIM_Period = 36; 			 
		 }
     case PulseCapture_Precision_1_0:
		 {
				 TIM_TimeBaseStructure.TIM_Period = 72; 			 
		 }
		 case PulseCapture_Precision_10:
		 {
				 TIM_TimeBaseStructure.TIM_Period = 720; 			 
		 }
    default:break;
	 }
//   TIM_TimeBaseStructure.TIM_Period = 999;       //当定时器从0计数到999，即为1000次，为一个定时周期
   TIM_TimeBaseStructure.TIM_Prescaler = 0;	    //设置预分频：不预分频，即为72MHz
   TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1 ;	//设置时钟分频系数：不分频
   TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //向上计数模式

   TIM_TimeBaseInit(pCx->Hardware.TIMx, &TIM_TimeBaseStructure);
 
 }
 