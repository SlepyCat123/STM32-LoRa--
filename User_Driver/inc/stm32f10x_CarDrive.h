/********************************************************************************
  * @file    stm32f10x_CarDrive.h
  * @author   DONGWEN
  * @version  V1.0.0
  * @date     25/10/2020
  * @brief   This file contains all the functions prototypes for the stm32f10x_Car_drive 
  *         firmware library.
  ******************************************************************************/

#ifndef __STM32F10X_CARDRIVE_H
#define __STM32F10X_CARDRIVE_H

#include "stm32f10x_Motor.h"
	
typedef struct __Car_InitTypeDef_Struct  //初始化结构体（放上层可以改变的参数）
{
	  FunctionalState         					  enable;
	  float			                          speed; //初始化速度
	  float                               speedMax;  
	  float                               speedMin; 
}Car_InitTypeDef_Struct;


/*------初始化参数------*/
#define CAR_MOTOR_LEFT                  MOTOR2
#define CAR_MOTOR_RIGHT                 MOTOR1

#define CAR_ENABLE_DEFAULT 			  	    ENABLE 	    
#define CAR_SPEED_DEFAULT			         (0.0f)
#define CAR_SPEED_MAX			             (1.0f)
#define CAR_SPEED_MIN			         	   (0.0f) 


/*-----------------------------------------------------------------------------------------------
 + 实现功能：调整car运行速度及方向
 + 形    参: run_speed：数据类型  float，前进或后退速度
 +            run_speed = 0     停止
 +            run_speed >0      前进
 +            run_speed < 0     后退
 +            turn_speed：数据类型  float，左右转速度
 +            turn_speed = 0     直行
 +            turn_speed >0      右转
 +            turn_speed < 0     左转
 + 返回参数:无
-----------------------------------------------------------------------------------------------*/
void CarDrive_Control(float run_speed,float turn_speed);

/******************************************************************************************
  * @brief  用默认参数填充 Car_InitStruct                                                 * 
  * @param  CarInit : Car_InitTypeDef 类型的变量                                          *
  * @retval : None                                                                        *
******************************************************************************************/
void Car_StructInit(Car_InitTypeDef_Struct* CarInit);

/*-----------------------------------------------------------------------------------------------
 + 实现功能：初始化
 + 形    参: CarInit
 + 返回参数: ERROR or SUCCESS
-----------------------------------------------------------------------------------------------*/
ErrorStatus CarDrive_Init(Car_InitTypeDef_Struct*  CarInit);

/*-----------------------------------------------------------------------------------------------
 + 实现功能：设置Car 最大速度
 + 形    参: 无
 + 返回参数: 无
-----------------------------------------------------------------------------------------------*/
void CarDrive_SetSpeedMAX(float  speedMax);

/*-----------------------------------------------------------------------------------------------
 + 实现功能：设置Car 最小速度
 + 形    参: 无
 + 返回参数: 无
-----------------------------------------------------------------------------------------------*/
void CarDrive_SetSpeedMIN(float  speedMin);

#endif /*__STM32F10X_CARDRIVE_H */

