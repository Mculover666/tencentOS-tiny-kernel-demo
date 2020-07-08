/********************************************************************
 *@file    helloword.c                                                      
 *@brief   测试任务是否可以被正常切换运行
 *@author  Mculover666
 *@date    2020年7月4日12:27:49
 *@note    
 *         1. 系统设定最小任务栈为 K_TASK_STK_SIZE_MIN, 测试其大小
 *         2. 实际测试，任务中有printf时，任务栈大小最低200
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
    
    //创建任务
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
