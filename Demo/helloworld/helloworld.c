/********************************************************************
 *@file    helloword.c                                                      
 *@brief   ���������Ƿ���Ա������л�����
 *@author  Mculover666
 *@date    2020��7��4��12:27:49
 *@note    
 *         1. ϵͳ�趨��С����ջΪ K_TASK_STK_SIZE_MIN, �������С
 *         2. ʵ�ʲ��ԣ���������printfʱ������ջ��С���200
*********************************************************************/

#include <tos_k.h>

k_task_t	task1;
k_task_t	task2;
k_stack_t	task1_stack[200];
k_stack_t	task2_stack[256];

void task1_entry(void *arg)
{
    while(1)
    {
        printf("task1 is running...\r\n");
        tos_task_delay(1000);
    }
}

void task2_entry(void *arg)
{
    while(1)
    {
        printf("task2 is running...\r\n");
        tos_task_delay(1000);
    }
}

void application_entry(void *arg)
{
    k_err_t ret;
    
    printf("K_TASK_STK_SIZE_MIN is %d bytes\r\n", K_TASK_STK_SIZE_MIN);
    
    //��������
    ret = tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 10);
    if(ret != K_ERR_NONE) {
        printf("task1 create fail, err code = %d\r\n", ret);
    }
    else {
        printf("task1 create success\r\n");
    }
    
    ret = tos_task_create(&task2, "task2", task2_entry, NULL, 3, task2_stack, sizeof(task2_stack), 10);
    if(ret != K_ERR_NONE) {
        printf("task2 create fail, err code = %d\r\n", ret);
    }
    else {
        printf("task2 create success\r\n");
    }
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
K_TASK_STK_SIZE_MIN is 68 bytes
task1 create success
task2 create success
task1 is running...
task2 is running...
task1 is running...
task2 is running...
task1 is running...
task2 is running...
task1 is running...
task2 is running...
*********************************************************/
