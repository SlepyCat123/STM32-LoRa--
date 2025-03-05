/*  ******************************************************************************
  * @file    stm32f10x_MapSCOMandSBUS.h
  * @author  W. DONG
  * @version V1.0.0
  * @date    25/01/2020
  * @brief   ����25byte��8bit������SBUS 16byte��11bit ����ת�� ���ݽṹ�뺯������.
  ********************************************************************************/

/* Define to prevent recursive inclusion -------------------------------------*/

#ifndef __STM32F10X_MAPSCOMANDSBUS_H
#define __STM32F10X_MAPSCOMANDSBUS_H	

/* Includes ------------------------------------------------------------------*/	 
#include <stm32f10x.h>

/** @addtogroup My_Driver
  * @{
  */
	

/**
  * @}
  */ 
/* SBUS����֡���*/

typedef struct _SBUSData_Struct              
{  
    uint16_t                  Channel[16];
    uint8_t           	      FlagByte;
} SBUSData_Struct;


/**
  * @}
  */
	
/** @defgroup MapSCOMandSBUS_Exported_Functions Prototypes
  * @{
  */


/*****************************************************************
  * @brief   �� SCOM����ƥ��ΪSBUS����                            *
  * @param   SCOMdata�� ��������ָ�룬Ҫ�����鳤��25byte         *
 	*         SCOMdata[0]                  ���ֽڣ� 0x0F           *
  *         SCOMdata[24]                 β�ֽڣ� 0x00           *
  *         SCOMdata[23]                 ��־�ֽڣ� Ĭ��0x00     *
  *         SCOMdata[1]-SCOMdata[22]     �û�����                *	
  * @param   SBUSdata�� SBUS���ݴ洢ָ�룬���� SBUSData_Struct   *	
  * @retval  ERROR or SUCCESS.                                                *
*****************************************************************/
ErrorStatus Map_SCOMtoSBUS(SBUSData_Struct *SBUSdata,uint8_t *SCOMdata);


/*****************************************************************
  * @brief   ��SBUS����ƥ��Ϊ SCOM����                           *
  * @param   SBUSdata�� SBUS���ݴ洢ָ�룬���� SBUSData_Struct   *	
  *            16byte  11bit���� 	                               *
  * @param   SCOMdata�� ��������ָ�룬Ҫ�����鳤��25byte         *
 	*         SCOMdata[0]                  ���ֽڣ� 0x0F           *
  *         SCOMdata[24]                 β�ֽڣ� 0x00           *
  *         SCOMdata[23]                 ��־�ֽڣ� Ĭ��0x00     *
  *         SCOMdata[1]-SCOMdata[22]     �û�����                *	
  * @retval  ERROR or SUCCESS.                                   *
*****************************************************************/
ErrorStatus Map_SBUStoSCOM(uint8_t *SCOMdata,SBUSData_Struct *SBUSdata);


/**
  * @}
  */

#endif     /*__STM32F10X_MapSCOMandSBUS_H */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/********* (C) COPYRIGHT 2020 HANGZHOU NORMAL UNIVERSITY   *****END OF FILE****/
