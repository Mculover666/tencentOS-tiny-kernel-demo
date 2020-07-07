/******************************************************************************
 *@file    tick_demo_4.c                                              
 *@brief   
 *         task1��tsk2�����ö�����ʱ�����ó�CPU�������ȼ���ͬ
 *         ͨ����tos_config.h�п��غ� TOS_CFG_ROUND_ROBIN_EN ���۲�ʵ����
 *@author  Mculover666
 *@date    2020��7��7��11:54:00
*******************************************************************************/

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
        HAL_Delay(1000);
    }
}

void task2_entry(void *arg)
{
    printf("task2 start...\r\n");
    while(1)
    {
        printf("task2 is running...\r\n");
        HAL_Delay(1000);
    }
}

void application_entry(void *arg)
{
    //��������
    tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 10);
    printf("task1 create success\r\n");
    tos_task_create(&task2, "task2", task2_entry, NULL, 2, task2_stack, sizeof(task2_stack), 10);
    printf("task2 create success\r\n");
    
    return;
}

/********************************************************
result(#define TOS_CFG_ROUND_ROBIN_EN 0u):

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
task1 create success
task2 create success
task1 start...
task1 is running...
task1 is running...
task1 is running...
task1 is running...



result(#define TOS_CFG_ROUND_ROBIN_EN 1u):

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
task1 create success
task2 create success
task1 start...
task1 is running...
task2 start...
task2 is running...
task1 is running...
task2 is running...
task1 is running...
task2 is running...
task1 is running...
task2 is running...
*********************************************************/
