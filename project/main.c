#include "delay.h"
#include "includes.h"
#include "stm32f10x_LoraSBUS.h"
#include "stm32f10x_CarDrive.h"
#include "Task_Data_input.h"
#include "Task_Data_output.h"
#include "Task_Data_Remap.h"
#include "init.h"

void RCC_Configuration(void);


/********* 任务 优先级  堆栈 控制块 函数声明*********/
 
#define   START_TASK_PRIO		    (6)
#define   START_STK_SIZE 		    (128)
OS_TCB    START_TaskTCB;
CPU_STK   START_TASK_STK[START_STK_SIZE];
void start_task(void *p_arg);

int main(void)
{
    OS_ERR err;	
	  CPU_SR_ALLOC();   //为CPU_CRITICAL_ENTER()和CPU_CRITICAL_EXIT()申请一个变量
	
	  RCC_Configuration();
	
	  delay_init();
		
	    //todo:  初始化
	  OSInit(&err);		    //初始化UCOSIII
	  OS_CRITICAL_ENTER();	//进入临界区	
	//创建开始任务
	  OSTaskCreate((OS_TCB* 	  )&START_TaskTCB,		    //任务控制块
				         (CPU_CHAR*	  )"start_task", 		      //任务名字
                 (OS_TASK_PTR )start_task, 			      //任务函数
                 (void*		    )0,					            //传递给任务函数的参数
                 (OS_PRIO	    )START_TASK_PRIO,       //任务优先级
                 (CPU_STK*    )&START_TASK_STK[0],	  //任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	    //任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		    //任务堆栈大小
                 (OS_MSG_QTY  )0,					            //任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	    )0,					            //当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void*   	  )0,					            //用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR* 	  )&err);				          //存放该函数错误时的返回值
								 
	  OS_CRITICAL_EXIT();	//退出临界区	 
	  OSStart(&err);      //开启UCOSIII	
}

//开始任务函数
void start_task(void *p_arg)
{
    OS_ERR    err;
	  CPU_SR_ALLOC();
	
	  p_arg = p_arg;
	  CPU_Init();	  
    
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif	
	
RemoteCar_Init();
	  OS_CRITICAL_ENTER();	//进入临界区
	//创建TASK1任务
    task_CreateInputTask();

	//创建TASK2任务
    task_CreateRemapTask();
    
    //创建TASK3任务
    task_CreateOutputTask();
		
	  OS_CRITICAL_EXIT();	//退出临界区
	  OSTaskDel((OS_TCB*)0,&err);	//删除start_task任务自身
}

//任务函数


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
