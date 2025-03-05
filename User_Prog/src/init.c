
#include "init.h"
	#include "stm32f10x_LoraSBUS.h"
#include "stm32f10x_CarDrive.h"





void RemoteCar_Init(void)
{
	LoraSBUS_InitTypedef_Struct SBUS_Init;
	Car_InitTypeDef_Struct Car_Init;
    LoraSBUS_StructInit(&SBUS_Init);
    SBUS_Init.Lorax=Lora1;
    LoraSBUS_Init(LoraSBUS1,&SBUS_Init);
	  LoraSBUS_Open(LoraSBUS1);
	Car_StructInit(&Car_Init);
	  CarDrive_Init(&Car_Init);
	
}


/* ©2019-2020 HANGZHOU . All rights reserved. */
