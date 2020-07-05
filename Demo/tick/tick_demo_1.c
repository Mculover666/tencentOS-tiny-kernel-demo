/********************************************************
 *@file    tick_demo_1.c                                              
 *@brief   
 *         ʹ�ö�����HAL_Delay()������ʱ����������������
 *@author  Mculover666
 *@date    2020��7��5��21:02:13
*********************************************************/

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
task1 is running...(�˴����Կ���task2�����޷��õ�����)
task1 is running...
task1 is running...
task1 is running...
task1 is running...

*********************************************************/
