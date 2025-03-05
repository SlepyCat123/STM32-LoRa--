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
	
typedef struct __Car_InitTypeDef_Struct  //��ʼ���ṹ�壨���ϲ���Ըı�Ĳ�����
{
	  FunctionalState         					  enable;
	  float			                          speed; //��ʼ���ٶ�
	  float                               speedMax;  
	  float                               speedMin; 
}Car_InitTypeDef_Struct;


/*------��ʼ������------*/
#define CAR_MOTOR_LEFT                  MOTOR2
#define CAR_MOTOR_RIGHT                 MOTOR1

#define CAR_ENABLE_DEFAULT 			  	    ENABLE 	    
#define CAR_SPEED_DEFAULT			         (0.0f)
#define CAR_SPEED_MAX			             (1.0f)
#define CAR_SPEED_MIN			         	   (0.0f) 


/*-----------------------------------------------------------------------------------------------
 + ʵ�ֹ��ܣ�����car�����ٶȼ�����
 + ��    ��: run_speed����������  float��ǰ��������ٶ�
 +            run_speed = 0     ֹͣ
 +            run_speed >0      ǰ��
 +            run_speed < 0     ����
 +            turn_speed����������  float������ת�ٶ�
 +            turn_speed = 0     ֱ��
 +            turn_speed >0      ��ת
 +            turn_speed < 0     ��ת
 + ���ز���:��
-----------------------------------------------------------------------------------------------*/
void CarDrive_Control(float run_speed,float turn_speed);

/******************************************************************************************
  * @brief  ��Ĭ�ϲ������ Car_InitStruct                                                 * 
  * @param  CarInit : Car_InitTypeDef ���͵ı���                                          *
  * @retval : None                                                                        *
******************************************************************************************/
void Car_StructInit(Car_InitTypeDef_Struct* CarInit);

/*-----------------------------------------------------------------------------------------------
 + ʵ�ֹ��ܣ���ʼ��
 + ��    ��: CarInit
 + ���ز���: ERROR or SUCCESS
-----------------------------------------------------------------------------------------------*/
ErrorStatus CarDrive_Init(Car_InitTypeDef_Struct*  CarInit);

/*-----------------------------------------------------------------------------------------------
 + ʵ�ֹ��ܣ�����Car ����ٶ�
 + ��    ��: ��
 + ���ز���: ��
-----------------------------------------------------------------------------------------------*/
void CarDrive_SetSpeedMAX(float  speedMax);

/*-----------------------------------------------------------------------------------------------
 + ʵ�ֹ��ܣ�����Car ��С�ٶ�
 + ��    ��: ��
 + ���ز���: ��
-----------------------------------------------------------------------------------------------*/
void CarDrive_SetSpeedMIN(float  speedMin);

#endif /*__STM32F10X_CARDRIVE_H */

