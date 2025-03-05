#include "delay.h"
#include "includes.h"
#include "stm32f10x_LoraSBUS.h"
#include "stm32f10x_CarDrive.h"
#include "Task_Data_input.h"
#include "Task_Data_output.h"
#include "Task_Data_Remap.h"
#include "init.h"

void RCC_Configuration(void);


/********* ���� ���ȼ�  ��ջ ���ƿ� ��������*********/
 
#define   START_TASK_PRIO		    (6)
#define   START_STK_SIZE 		    (128)
OS_TCB    START_TaskTCB;
CPU_STK   START_TASK_STK[START_STK_SIZE];
void start_task(void *p_arg);

int main(void)
{
    OS_ERR err;	
	  CPU_SR_ALLOC();   //ΪCPU_CRITICAL_ENTER()��CPU_CRITICAL_EXIT()����һ������
	
	  RCC_Configuration();
	
	  delay_init();
		
	    //todo:  ��ʼ��
	  OSInit(&err);		    //��ʼ��UCOSIII
	  OS_CRITICAL_ENTER();	//�����ٽ���	
	//������ʼ����
	  OSTaskCreate((OS_TCB* 	  )&START_TaskTCB,		    //������ƿ�
				         (CPU_CHAR*	  )"start_task", 		      //��������
                 (OS_TASK_PTR )start_task, 			      //������
                 (void*		    )0,					            //���ݸ��������Ĳ���
                 (OS_PRIO	    )START_TASK_PRIO,       //�������ȼ�
                 (CPU_STK*    )&START_TASK_STK[0],	  //�����ջ����ַ
                 (CPU_STK_SIZE)START_STK_SIZE/10,	    //�����ջ�����λ
                 (CPU_STK_SIZE)START_STK_SIZE,		    //�����ջ��С
                 (OS_MSG_QTY  )0,					            //�����ڲ���Ϣ�����ܹ����յ������Ϣ��Ŀ,Ϊ0ʱ��ֹ������Ϣ
                 (OS_TICK	    )0,					            //��ʹ��ʱ��Ƭ��תʱ��ʱ��Ƭ���ȣ�Ϊ0ʱΪĬ�ϳ��ȣ�
                 (void*   	  )0,					            //�û�����Ĵ洢��
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //����ѡ��
                 (OS_ERR* 	  )&err);				          //��Ÿú�������ʱ�ķ���ֵ
								 
	  OS_CRITICAL_EXIT();	//�˳��ٽ���	 
	  OSStart(&err);      //����UCOSIII	
}

//��ʼ������
void start_task(void *p_arg)
{
    OS_ERR    err;
	  CPU_SR_ALLOC();
	
	  p_arg = p_arg;
	  CPU_Init();	  
    
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//ͳ������                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//���ʹ���˲����жϹر�ʱ��
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //��ʹ��ʱ��Ƭ��ת��ʱ��
	 //ʹ��ʱ��Ƭ��ת���ȹ���,ʱ��Ƭ����Ϊ1��ϵͳʱ�ӽ��ģ���1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif	
	
RemoteCar_Init();
	  OS_CRITICAL_ENTER();	//�����ٽ���
	//����TASK1����
    task_CreateInputTask();

	//����TASK2����
    task_CreateRemapTask();
    
    //����TASK3����
    task_CreateOutputTask();
		
	  OS_CRITICAL_EXIT();	//�˳��ٽ���
	  OSTaskDel((OS_TCB*)0,&err);	//ɾ��start_task��������
}

//������


void RCC_Configuration(void)
{
	ErrorStatus              HSEStartUpStatus;
	
  /* RCC system reset(for debug purpose) */
  RCC_DeInit();

  /* Enable HSE */
  RCC_HSEConfig(RCC_HSE_ON);

  /* Wait till HSE is ready */
  HSEStartUpStatus = RCC_WaitForHSEStartUp();

  if (HSEStartUpStatus == SUCCESS)
  {
    /* Enable Prefetch Buffer */
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

    /* Flash 2 wait state */
    FLASH_SetLatency(FLASH_Latency_2);

    /* HCLK = SYSCLK */
    RCC_HCLKConfig(RCC_SYSCLK_Div1);

    /* PCLK2 = HCLK */
    RCC_PCLK2Config(RCC_HCLK_Div1);

    /* PCLK1 = HCLK/16 */
    RCC_PCLK1Config(RCC_HCLK_Div2);

    /* PLLCLK = 8MHz * 9 = 72 MHz */
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

    /* Enable PLL */
    RCC_PLLCmd(ENABLE);

    /* Wait till PLL is ready */
    while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
    {}

    /* Select PLL as system clock source */
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

    /* Wait till PLL is used as system clock source */
    while (RCC_GetSYSCLKSource() != 0x08)
    {}
  }
	// next two lines should move to initial code, and add low OS at Hardware!! 
 	  RCC_LSICmd(ENABLE);
  	while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY)==RESET);
		
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);
 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE, ENABLE);	
 		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);		
 		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
 		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	
		RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);		
}
