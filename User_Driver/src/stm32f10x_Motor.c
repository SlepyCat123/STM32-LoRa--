/*******************************************************************************
  * @file    stm32f10x_Car_Control.c
  * @author  
  * @version V1.0.0
  * @date    08/10/2020
  * @brief  С��˫�ֿ��ƴ���	
*******************************************************************************/
#include "stm32f10x_Motor.h"
#include "math.h"

/*============================================================================*
 * ȫ�ֱ��������������                                                       *
 *============================================================================*/
Motor_TypeDef_Struct   MOTOR1_BASE,MOTOR2_BASE,MOTOR3_BASE,MOTOR4_BASE;


/******************************************************************************************
  * @brief  ��Ĭ�ϲ������ MOTOR_InitStruct                                               * 
  * @param  MOTOR_InitStruct : MOTOR_InitTypeDef ���͵ı���                               *
  * @retval : None                                                                        *
******************************************************************************************/
void Motor_StructInit(Motor_InitTypeDef_Struct* MOTORx_InitStruct)
{
    MOTORx_InitStruct->enable      = MOTOR_ENABLE_DEFAULT;
	  MOTORx_InitStruct->speed       = MOTOR_SPEED_DEFAULT;
	  MOTORx_InitStruct->speedMax    = MOTOR_SPEED_MAX;
	  MOTORx_InitStruct->speedMin    = MOTOR_SPEED_MIN;
	  PWMout_StructInit(&MOTORx_InitStruct->PWMInit);
}


/*******************************************************************************************
  * @brief  ��ʼ��  ��·MOTOR                                                              *
  * @param  MOTORx: ָ����ʼ����MOTOR           MOTOR_TypeDef_Struct *MOTORx               *
            MOTOR_InitStruct : pointer to a MOTOR_InitTypeDef                              *
  * @retval ERROR or SUCCESS .                                                             *
*******************************************************************************************/
ErrorStatus Motor_Init(Motor_TypeDef_Struct *MOTORx,Motor_InitTypeDef_Struct *MOTOR_InitStruct)
{
    GPIO_InitTypeDef            GPIO_InitStructure;	
		
	  if(NULL == MOTORx || MOTOR_InitStruct == NULL)
		    return ERROR;
	
	  if(MOTORx == MOTOR1)
	  {
		    MOTOR1_BASE.HardWare.CtrlIn1_GPIOx    = MOTOR1_IN1_GPIO;
		    MOTOR1_BASE.HardWare.CtrlIn1_GPIO_Pin = MOTOR1_IN1_GPIO_Pin;
		    MOTOR1_BASE.HardWare.CtrlIn2_GPIOx    = MOTOR1_IN2_GPIO;
		    MOTOR1_BASE.HardWare.CtrlIn2_GPIO_Pin = MOTOR1_IN2_GPIO_Pin;
		    MOTOR1_BASE.HardWare.PWMx 			       = MOTOR1_PWM;
	  }
	  else if(MOTORx == MOTOR2)
	  {
		    MOTOR2_BASE.HardWare.CtrlIn1_GPIOx    = MOTOR2_IN1_GPIO;
		    MOTOR2_BASE.HardWare.CtrlIn1_GPIO_Pin = MOTOR2_IN1_GPIO_Pin;
		    MOTOR2_BASE.HardWare.CtrlIn2_GPIOx    = MOTOR2_IN2_GPIO;
		    MOTOR2_BASE.HardWare.CtrlIn2_GPIO_Pin = MOTOR2_IN2_GPIO_Pin;
		    MOTOR2_BASE.HardWare.PWMx 			       = MOTOR2_PWM;
	  }
	  else if(MOTORx == MOTOR3)
	  {
		    MOTOR3_BASE.HardWare.CtrlIn1_GPIOx    = MOTOR3_IN1_GPIO;
		    MOTOR3_BASE.HardWare.CtrlIn1_GPIO_Pin = MOTOR3_IN1_GPIO_Pin;
		    MOTOR3_BASE.HardWare.CtrlIn2_GPIOx    = MOTOR3_IN2_GPIO;
		    MOTOR3_BASE.HardWare.CtrlIn2_GPIO_Pin = MOTOR3_IN2_GPIO_Pin;
		    MOTOR3_BASE.HardWare.PWMx 			       = MOTOR3_PWM;
	  }
	  else if(MOTORx == MOTOR4)
	  {
		    MOTOR4_BASE.HardWare.CtrlIn1_GPIOx    = MOTOR4_IN1_GPIO;
		    MOTOR4_BASE.HardWare.CtrlIn1_GPIO_Pin = MOTOR4_IN1_GPIO_Pin;
		    MOTOR4_BASE.HardWare.CtrlIn2_GPIOx    = MOTOR4_IN2_GPIO;
		    MOTOR4_BASE.HardWare.CtrlIn2_GPIO_Pin = MOTOR4_IN2_GPIO_Pin;
		    MOTOR4_BASE.HardWare.PWMx 			       = MOTOR4_PWM;
	  }	
	    //����ʼ������		
	  MOTORx->Memory.enable     = MOTOR_InitStruct->enable;
	  MOTORx->Memory.speed      = MOTOR_InitStruct->speed;   //��ʼ���ٶ�
	  MOTORx->Memory.speedMax   = MOTOR_InitStruct->speedMax;
	  MOTORx->Memory.speedMin   = MOTOR_InitStruct->speedMin;
	
	    //GPIO��ʼ��
	  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;		
	  GPIO_InitStructure.GPIO_Pin   = MOTORx->HardWare.CtrlIn1_GPIO_Pin;
	  GPIO_Init(MOTORx->HardWare.CtrlIn1_GPIOx,&GPIO_InitStructure);

	  GPIO_InitStructure.GPIO_Pin   = MOTORx->HardWare.CtrlIn2_GPIO_Pin;
	  GPIO_Init(MOTORx->HardWare.CtrlIn2_GPIOx,&GPIO_InitStructure);
	
	    //pwm��ʼ��		
    MOTOR_InitStruct->PWMInit.DutyMAX = MOTORx->Memory.speedMax * 100.0f;	//����ٶ�	
		MOTOR_InitStruct->PWMInit.DutyMIN = MOTORx->Memory.speedMin * 100.0f;    
    MOTOR_InitStruct->PWMInit.Duty    = MOTORx->Memory.speed * 100.0f;
		MOTOR_InitStruct->PWMInit.enable  = MOTORx->Memory.enable;	
	  PWMout_Init(MOTORx->HardWare.PWMx,&MOTOR_InitStruct->PWMInit);
	
	  return SUCCESS;
}


/******************************************************************************************
  * @brief  �����                                           							  * 
  * @param   MOTORx: MOTOR_TypeDef_Struct *MOTORx                            	    	  *
  * @retval : ERROR or SUCCESS                                                            *
******************************************************************************************/
ErrorStatus Motor_Open(Motor_TypeDef_Struct *MOTORx)
{
	  if(MOTORx == NULL)
		    return ERROR;
		
	  MOTORx->Memory.enable = ENABLE;
	  PWMout_On(MOTORx->HardWare.PWMx);	
	  return SUCCESS;	
}
/******************************************************************************************
  * @brief  �ص��                                           							  * 
  * @param   MOTORx: MOTOR_TypeDef_Struct *MOTORx                            	    	  *
  * @retval : ERROR or SUCCESS                                                            *
******************************************************************************************/
ErrorStatus Motor_Close(Motor_TypeDef_Struct *MOTORx)
{
		if(MOTORx == NULL)
		    return ERROR;
		
	  MOTORx->Memory.enable = DISABLE;	
	  PWMout_Off(MOTORx->HardWare.PWMx);	
	  return SUCCESS;
}
/******************************************************************************************
  * @brief  ���õ������ٶ�                                           					  * 
  * @param   MOTORx: MOTOR_TypeDef_Struct *MOTORx                            	    	  *
  * @retval : ERROR or SUCCESS                                                            *
******************************************************************************************/
ErrorStatus Motor_SetMaxSpeed(Motor_TypeDef_Struct *MOTORx,float speed)
{
    if(MOTORx == NULL)
		    return ERROR;
			
		MOTORx->Memory.speedMax = speed;
		if(MOTORx->Memory.speedMax > 1.0f)
			  MOTORx->Memory.speedMax = 1.0f;
		if(MOTORx->Memory.speedMax < 0.0f)
			  MOTORx->Memory.speedMax = 0.0f;		
				
	  PWMout_DutyMaxSetting(MOTORx->HardWare.PWMx,speed*100.0f);	
	  return SUCCESS;
}
/******************************************************************************************
  * @brief  ���õ����С�ٶ�                                             				  * 
  * @param   MOTORx: MOTOR_TypeDef_Struct *MOTORx                            	    	  *
  * @retval : ERROR or SUCCESS                                                            *
******************************************************************************************/
ErrorStatus Motor_SetMinSpeed(Motor_TypeDef_Struct *MOTORx,float speed)
{
	  if(MOTORx == NULL)
		    return ERROR;
	
		MOTORx->Memory.speedMin = speed;
		if(MOTORx->Memory.speedMin > 1.0f)
			  MOTORx->Memory.speedMin = 1.0f;
		if(MOTORx->Memory.speedMin < 0.0f)
			  MOTORx->Memory.speedMin = 0.0f;		
	  PWMout_DutyMinSetting(MOTORx->HardWare.PWMx,speed*100.0f);	
	  return SUCCESS;
}
/*******************************************************************************************
  * @brief  �ı����ٶ�	                                                               *
  * @param  motorx: Motor_TypeDef_Struct *motorx                                           *
  * @param  speed: �������ݣ�ռ�ձ���ֵ��ʵ���ٶȣ�0~1��-1~0��                             *
  * @retval ERROR or SUCCESS .                                                             *
*******************************************************************************************/
ErrorStatus Motor_SpeedCtrl(Motor_TypeDef_Struct *motorx,float speed)
{
    float  fspeed;
	
	  if(motorx == NULL)
		    return ERROR;
	  //�ٶ��޷�		
		fspeed = fabs(speed);
		
		if(fspeed > motorx->Memory.speedMax)
			  fspeed = motorx->Memory.speedMax;
		if(fspeed < motorx->Memory.speedMin)
			  fspeed = motorx->Memory.speedMin;		
		
		if(speed > 0)
		{
				GPIO_SetBits(motorx->HardWare.CtrlIn1_GPIOx,motorx->HardWare.CtrlIn1_GPIO_Pin);
				GPIO_ResetBits(motorx->HardWare.CtrlIn2_GPIOx,motorx->HardWare.CtrlIn2_GPIO_Pin);
				PWMout_DutyCtrl(motorx->HardWare.PWMx,fspeed*100.0f);
		}
    else if(speed < 0)
		{
				GPIO_ResetBits(motorx->HardWare.CtrlIn1_GPIOx,motorx->HardWare.CtrlIn1_GPIO_Pin);
				GPIO_SetBits(motorx->HardWare.CtrlIn2_GPIOx,motorx->HardWare.CtrlIn2_GPIO_Pin);
				PWMout_DutyCtrl(motorx->HardWare.PWMx,fspeed*100.0f);			
		}
    else
    {
				GPIO_SetBits(motorx->HardWare.CtrlIn1_GPIOx,motorx->HardWare.CtrlIn1_GPIO_Pin);
				GPIO_SetBits(motorx->HardWare.CtrlIn2_GPIOx,motorx->HardWare.CtrlIn2_GPIO_Pin);
				PWMout_DutyCtrl(motorx->HardWare.PWMx,0.0f);					
		}	
	
	  return SUCCESS;
}
