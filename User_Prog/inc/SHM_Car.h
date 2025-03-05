/**
  ******************************************************************************
  * @file  SHM_Car.h
  * @author   
  * @version  V1.0.0
  * @date  26/05/2020
  * @brief  This file contains all the functions prototypes for shared memory of
  *        Car_Drive.
  ******************************************************************************
  * @copyright
  * 
  * ALL COPYRIGHTS ARE OWNED BY INTERNATIONAL SERVICE OF ROBOTS, in Hangzhou Normal Univ.
  *
  * <h2><center>&copy; COPYRIGHT 2020 HANGZHOU NORMAL UNIVERSITY W. DONG </center></h2>
  */
	
/*-------------- Define to prevent recursive inclusion --------------*/

#ifndef __SHM_CAR_H
#define __SHM_CAR_H

/*---------------------------- Includes ------------------------------*/
#include "stm32f10x.h"
#include "Task_Data_output.h"
#include "stm32f10x_LoraSBUS.h"

/** 
  * @brief  Configuration SHM_CarParam PARAM type enumeration
  */


typedef enum  __SHM_REG_PARAM_TYPE_ENUM
{
	  SHM_InputData_RemoteCtrl_TYPE,    	
	  SHM_Car_Drive_TYPE, 	
} SHM_REG_PARAM_TYPE_ENUM;

typedef struct  __Car_DriveData_STRU
{	 
	  FlagStatus  Fresh; 
	  float       straight;
    float       turn;
	  enum
		{
		    Low_Speed,
		    High_Speed,			
		}gear;
}Car_DriveData_STRU;



typedef struct  __SHM_REG_PARAM_STRU
{	 
    LoraSBUS_READ_DATA_Struct             RCData;         //ң�����ݣ�����Э��ת��ģ��
    Car_DriveData_STRU                    Drive;
} SHM_REG_PARAM_STRU;


/** 
  * @brief  SHM_REG_PARAM_UNION union.
  */

typedef union  __SHM_REG_PARAM_UNION
{	  
    LoraSBUS_READ_DATA_Struct             RCData;
    Car_DriveData_STRU                    Drive;
} SHM_REG_PARAM_UNION;
 
/** @defgroup SHM_ Exported_Macros
  * @{
  */

/**
  * @}
  */
	
/** @defgroup SHM_Car  Exported Functionprotypes
  * @{
  */
	
/*----------------------------------------------------------
 + ʵ�ֹ���:��ʼ��SHM_CarParam
 + ���ز���:��
----------------------------------------------------------*/
void init_SHM_CarParam(void);



/*----------------------------------------------------------
 + ʵ�ֹ���:д��SHM_CarParam
 + data_type��SHM_REG_PARAM_TYPE_ENUM��д������
 + param_union��SHM_REG_PARAM_UNION��д������
 + ���ز���:SUCCESS or ERROR
----------------------------------------------------------*/
ErrorStatus Write_SHM_CarParamIRQ(SHM_REG_PARAM_TYPE_ENUM data_type, SHM_REG_PARAM_UNION *param_union);


/*----------------------------------------------------------
+ ʵ�ֹ���:��ȡSHM_XXX ����
 + data_type��SHM_REG_PARAM_TYPE_ENUM����ȡ����
 + param_union��SHM_REG_PARAM_UNION����ȡ����
 + ���ز���:SUCCESS or ERROR
----------------------------------------------------------*/
ErrorStatus Read_SHM_CarParamIRQ(SHM_REG_PARAM_TYPE_ENUM data_type, SHM_REG_PARAM_UNION *param_union);


/**
  * @brief  Read all SHM parameters when system is None.
  * @param:   param: pointer to a SHM_REG_PARAM_STRU
  * @retval : ERROR or SUCCESS.
  */


#endif /*__SHM_Car_H*/
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */
/********* (C) COPYRIGHT 2020 HANGZHOU NORMAL UNIVERSITY W.DONG *****END OF FILE****/
