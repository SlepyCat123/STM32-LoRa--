//#include "HCSR04.h"

//ErrorStatus HC_SR04_Init(HCSR_Typedef_Struct *HCSRX)
//{
//	    if(HCSRX==NULL)
//		{
//			return ERROR;
//		}
//    //1.��� ͨ������ Ӳ������  (�������źͶ�Ӧ��SCOM)
//		if(HCSRX == &HCSR1_BASE)
//	
//	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	//����GPIOB������ʱ��	
//	GPIO_InitTypeDef                  GPIO_InitStructure;					//����ṹ��
//	GPIO_InitStructure.GPIO_Mode    =       GPIO_Mode_Out_PP;		//����GPIO��Ϊ�������
//	GPIO_InitStructure.GPIO_Pin     =       Trig;						//����GPIO��5
//	GPIO_InitStructure.GPIO_Speed   =       GPIO_Speed_50MHz;		//����GPIO���ٶ�50Mhz
//	GPIO_Init(GPIOB,&GPIO_InitStructure);					//��ʼ��GPIOB
//	
//	GPIO_InitStructure.GPIO_Mode    =       GPIO_Mode_IPD;			//����GPIO��Ϊ��������ģʽ
//	GPIO_InitStructure.GPIO_Pin     =       Echo;						//����GPIO��6
//	GPIO_Init(GPIOB,&GPIO_InitStructure);					//��ʼ��GPIOB
//	GPIO_WriteBit(GPIOB,GPIO_Pin_5,0);						//����͵�ƽ
//	Delay_us(15);											//��ʱ15΢��
//}

//uint16_t sonar_mm(void)									//��ಢ���ص�λΪ���׵ľ�����
//{
//	uint32_t    Distance,Distance_mm = 0;
//	GPIO_SetBits(GPIOB,Trig);
//	//GPIO_WriteBit(GPIOB,Trig,1);						//����ߵ�ƽ
//	Delay_us(15);										//��ʱ15΢��
//	GPIO_ResetBits(GPIOB,Trig);
//	//GPIO_WriteBit(GPIOB,Trig,0);						//����͵�ƽ
//	while(GPIO_ReadInputDataBit(GPIOB,Echo)==0);		//�ȴ��͵�ƽ����
//	HCSR_time=0;												//��ʱ����
//	while(GPIO_ReadInputDataBit(GPIOB,Echo)==1);		//�ȴ��ߵ�ƽ����
//	HCSR_time_end=HCSR_time;										//��¼����ʱ��ʱ��
//	if(HCSR_time_end/100<38)									//�ж��Ƿ�С��38���룬����38����ľ��ǳ�ʱ��ֱ�ӵ������淵��0
//	{
//		Distance=(HCSR_time_end*346)/2;						//������룬25��C�����е�����Ϊ346m/s
//		Distance_mm=Distance/100;						//��Ϊ�����time_end�ĵ�λ��10΢�룬����Ҫ�ó���λΪ���׵ľ����������ó���100
//	}
//	return Distance_mm;									//���ز����
//}

////float sonar(void)										//��ಢ���ص�λΪ�׵ľ�����
////{
////	uint32_t Distance,Distance_mm = 0;
////	float Distance_m=0;
////	GPIO_WriteBit(GPIOB,Trig,1);					//����ߵ�ƽ
////	Delay_us(15);
////	GPIO_WriteBit(GPIOB,Trig,0);					//����͵�ƽ
////	while(GPIO_ReadInputDataBit(GPIOB,Echo)==0);
////	HCSR_time=0;
////	while(GPIO_ReadInputDataBit(GPIOB,Echo)==1);
////	HCSR_time_end=HCSR_time;
////	if(HCSR_time_end/100<38)
////	{
////		Distance=(HCSR_time_end*346)/2;
////		Distance_mm=Distance/100;
////		Distance_m=Distance_mm/1000;
////	}
////	return Distance_m;
////}

//void TIM3_IRQHandler(void)			//�����жϺ�����������ʱ��ÿ10΢�����time��1
//{							
//	if (TIM_GetITStatus(TIM3, TIM_IT_Update) == SET)		//��ȡTIM3��ʱ���ĸ����жϱ�־λ
//	{
//		HCSR_time++;
//		TIM_ClearITPendingBit(TIM3, TIM_IT_Update);			//��������жϱ�־λ
//	}
//}
