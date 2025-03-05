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
	  float			            speed; //初始化速度
	  float                 speedMax;   //Car最大速度
	  float                 speedMin; 	//Car最小速度       
}Car_TypeDef_Struct;


Car_TypeDef_Struct   Car;  
/*--------------------------- Private define ---------------------------------*/								
	
#define    DELTA_SPEED                         (0.05f)
/* --------------------------Private macro -----------------------------------*/

/******************************************************************************************
  * @brief  用默认参数填充 Car_InitStruct                                                 * 
  * @param  CarInit : Car_InitTypeDef 类型的变量                                          *
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
 + 实现功能：初始化
 + 形    参: CarInit
 + 返回参数: 无
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
void CarDrive_Control(float run_speed,float turn_speed)
{
		float speedL;
		float speedR;
	  float speed;
	
	  if(run_speed > Car.speedMax)
			  run_speed = Car.speedMax;                    
	  if(run_speed < (-1.0f)*Car.speedMax)
			  run_speed = (-1.0f)*Car.speedMax;		        //car_run速度限定

	  if(turn_speed > Car.speedMax)
			  turn_speed = Car.speedMax;
	  if(turn_speed < (-1.0f)*Car.speedMax)
			  turn_speed = (-1.0f)*Car.speedMax;			     //car_turn速度限定	

    if(fabs(run_speed) < DELTA_SPEED)
		{
		    if(turn_speed <= 0)                             //左转
				{
				    speedL = 0.0f;
					  speedR = (-1.0f) * turn_speed;				
				}
				else
				{
				    speedL = turn_speed;                      //右转
					  speedR = 0.0f;					
				}		
		}
    else
		{
		    speed = run_speed*(1 - fabs(turn_speed));    //turn越大,speed越小,转弯越厉害
		
				if(turn_speed >= 0)                        //右转
				{
						speedL = run_speed;   
						speedR = speed;
				}
				else
				{                                           //左转
						speedR = run_speed;				
				}
	  }
		Motor_SpeedCtrl(Car.MOTORL,speedL);
		Motor_SpeedCtrl(Car.MOTORR,speedR);		
}	

/*-----------------------------------------------------------------------------------------------
 + 实现功能：设置Car 最大速度
 + 形    参: 无
 + 返回参数: 无
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
 + 实现功能：设置Car 最小速度
 + 形    参: 无
 + 返回参数: 无
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
