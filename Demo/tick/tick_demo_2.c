/***************************************************************************************
 *@file    tick_demo_2.c                                              
 *@brief   
 *         ʹ�÷Ƕ�������ʱ����tos_task_delay��������ʱ���Ȼ���
 *@author  Mculover666
 *@date    2020��7��6��17:50:12
 *@note    
 *         �˳��򲻱䣬����������֤��ϵͳ�в����ڿ�������ʱ�����ĺ��
 *         1. ��tos_sys.c�н�knl_idle_init �д�����������Ĵ������Σ���Ϊreturn 0
 *         2. ��tos_config.h��ʹ�����һ���Ĺ��ܣ�
 *            #define TOS_CFG_FAULT_BACKTRACE_EN      1u
 *         3. ���ж��ļ��������жϴ����� HardFault_Handler����ֹ��ͻ��
***************************************************************************************/

#include <tos_k.h>

k_task_t	task1;
k_task_t	task2;
k_stack_t	task1_stack[256];
k_stack_t	task2_stack[256];


void task1_entry(void *arg)
{
    printf("task1 start...\r\n");
    while(1)
    {
        printf("task1 is running...\r\n");
        tos_task_delay(1000);
    }
}

void task2_entry(void *arg)
{
    printf("task2 start...\r\n");
    while(1)
    {
        printf("task2 is running...\r\n");
        tos_task_delay(1000);
    }
}

void application_entry(void *arg)
{
    //��������
    tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 0);
    printf("task1 create success\r\n");
    tos_task_create(&task2, "task2", task2_entry, NULL, 3, task2_stack, sizeof(task2_stack), 10);
    printf("task2 create success\r\n");
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
task1 create success
task2 create success
task1 start...
task1 is running...
task2 start...
task2 is running...


================== Dump Fault Information ==================
  THUMB:     TRUE
  ON TASK:   FALSE
  STK OVRF:  FALSE
  EXT STK:   FALSE
  PC:        08000292
  SP:        2000a580
  STK START: 2000a180
  STK LIMIT: 2000a580
  COD START: 08000000
  COD LIMIT: 08004470


====================== CPU Registers =======================
  R0 : 200013dc  R1 : 20000024  R2 : ffffffb8  R3 : 10000000
  R12: 0000000d  LR : fffffffd  PC : 08000292  PSR: 2100000e


====================== Dump Call Stack =====================
  8000292


====================== Fault Diagnosis =====================
Bus fault: precise data access violation
The bus fault occurred address is ffffffb8

*********************************************************/
