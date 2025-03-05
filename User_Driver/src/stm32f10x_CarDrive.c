/** ******************************************************************************
  * @file  stm32f10x_CarDrive.c
#include "stm32f10x.h"                  // Device header
  * @author  W.Dong
  * @version  V1.0.0
  * @date  17/06/2019
  * @brief  This file provides main functions.
  ******************************************************************************/

#include "stm32f10x_CarDrive.h"
#include "math.h"
/*------------------------------- External variables -----------------------------*/


/*------------------------------- External Functions -----------------------------*/

/*-------------------------- Private typedef ---------------------------------*/
typedef struct __Car_TypeDef_Struct		 
{
	  Motor_TypeDef_Struct *MOTORL;
	  Motor_TypeDef_Struct *MOTORR;	
	  FunctionalState       enable;
	  float			            speed; //��ʼ���ٶ�
	  float                 speedMax;   //Car����ٶ�
	  float                 speedMin; 	//Car��С�ٶ�       
}Car_TypeDef_Struct;


Car_TypeDef_Struct   Car;  
/*--------------------------- Private define ---------------------------------*/								
	
#define    DELTA_SPEED                         (0.05f)
/* --------------------------Private macro -----------------------------------*/

/******************************************************************************************
  * @brief  ��Ĭ�ϲ������ Car_InitStruct                                                 * 
  * @param  CarInit : Car_InitTypeDef ���͵ı���                                          *
  * @retval : None                                                                        *
******************************************************************************************/
void Car_StructInit(Car_InitTypeDef_Struct* CarInit)
{
    CarInit->enable   = CAR_ENABLE_DEFAULT;
	  CarInit->speed    = CAR_SPEED_DEFAULT;
	  CarInit->speedMax = CAR_SPEED_MAX;
	  CarInit->speedMin = CAR_SPEED_MIN;
}

/*-----------------------------------------------------------------------------------------------
 + ʵ�ֹ��ܣ���ʼ��
 + ��    ��: CarInit
 + ���ز���: ��
-----------------------------------------------------------------------------------------------*/
ErrorStatus CarDrive_Init(Car_InitTypeDef_Struct*  CarInit)
{
	  Motor_InitTypeDef_Struct       MotorInit;
	
    Motor_StructInit(&MotorInit);

	  Car.MOTORL = CAR_MOTOR_LEFT;
	  Car.MOTORR = CAR_MOTOR_RIGHT;
	
	  Car.enable   = CarInit->enable;
    Car.speed    = CarInit->speed;
	  Car.speedMax = CarInit->speedMax;
	  Car.speedMin = CarInit->speedMin;

	  MotorInit.enable   = CarInit->enable;
    MotorInit.speed    = CarInit->speed;
	  MotorInit.speedMax = CarInit->speedMax;
	  MotorInit.speedMin = CarInit->speedMin;
	
	  if( SUCCESS == Motor_Init(Car.MOTORL,&MotorInit))
	      return Motor_Init(Car.MOTORR,&MotorInit);
		else
			  return ERROR;
}

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
void CarDrive_Control(float run_speed,float turn_speed)
{
		float speedL;
		float speedR;
	  float speed;
	
	  if(run_speed > Car.speedMax)
			  run_speed = Car.speedMax;                    
	  if(run_speed < (-1.0f)*Car.speedMax)
			  run_speed = (-1.0f)*Car.speedMax;		        //car_run�ٶ��޶�

	  if(turn_speed > Car.speedMax)
			  turn_speed = Car.speedMax;
	  if(turn_speed < (-1.0f)*Car.speedMax)
			  turn_speed = (-1.0f)*Car.speedMax;			     //car_turn�ٶ��޶�	

    if(fabs(run_speed) < DELTA_SPEED)
		{
		    if(turn_speed <= 0)                             //��ת
				{
				    speedL = 0.0f;
					  speedR = (-1.0f) * turn_speed;				
				}
				else
				{
				    speedL = turn_speed;                      //��ת
					  speedR = 0.0f;					
				}		
		}
    else
		{
		    speed = run_speed*(1 - fabs(turn_speed));    //turnԽ��,speedԽС,ת��Խ����
		
				if(turn_speed >= 0)                        //��ת
				{
						speedL = run_speed;   
						speedR = speed;
				}
				else
				{                                           //��ת
						speedR = run_speed;				
				}
	  }
		Motor_SpeedCtrl(Car.MOTORL,speedL);
		Motor_SpeedCtrl(Car.MOTORR,speedR);		
}	

/*-----------------------------------------------------------------------------------------------
 + ʵ�ֹ��ܣ�����Car ����ٶ�
 + ��    ��: ��
 + ���ز���: ��
-----------------------------------------------------------------------------------------------*/
void CarDrive_SetSpeedMAX(float  speedMax)
{
	  if(speedMax > 1.0f)
			  speedMax = 1.0f;		
	  if(speedMax < 0.0f)
			  speedMax = 0.0f;		

		Car.speedMax = speedMax;
    Motor_SetMaxSpeed(Car.MOTORL,speedMax);
		Motor_SetMaxSpeed(Car.MOTORR,speedMax);
}

/*-----------------------------------------------------------------------------------------------
 + ʵ�ֹ��ܣ�����Car ��С�ٶ�
 + ��    ��: ��
 + ���ز���: ��
-----------------------------------------------------------------------------------------------*/
void CarDrive_SetSpeedMIN(float  speedMin)
{
	  if(speedMin > 1.0f)
			  speedMin = 1.0f;		
	  if(speedMin < 0.0f)
			  speedMin = 0.0f;		

		Car.speedMin = speedMin;
    Motor_SetMinSpeed(Car.MOTORL,speedMin);
		Motor_SetMinSpeed(Car.MOTORR,speedMin);
}





/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
