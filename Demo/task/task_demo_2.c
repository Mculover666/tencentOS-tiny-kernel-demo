/********************************************************************
 *@file    task_demo_2.c                                                      
 *@brief
 *         task1（高优先级）每隔3s打印一个"M"
 *         task1 运行3次之后把 task2 挂起，运行6次之后把 task2 恢复
 *         task2（低优先级）每隔1s打印一个"Y"
 *
 *@author  Mculover666
 *@date    2020年7月4日13:24:38
*********************************************************************/

#include <tos_k.h>

k_task_t	task1;
k_task_t	task2;
k_stack_t	task1_stack[256];
k_stack_t	task2_stack[256];

void task1_entry(void *arg)
{
    int time = 0;
    
    /* 测试任务入口函数中的局部变量是否会被自动初始化为0（结果：不会） */
    printf("time is %d\r\n", time);
    
    while(1) {
        if(time == 3) {
            /* 主动挂起 task2 */
            tos_task_suspend(&task2);
        }
        if(time == 6) {
            /* 恢复 task2 */
            tos_task_resume(&task2);
        }
        printf("M");
        time += 1;
        tos_task_delay(3000);
    }
}

void task2_entry(void *arg)
{
    while(1) {
        printf("Y");
        tos_task_delay(1000);
    }
}

void application_entry(void *arg)
{
    //创建任务
    tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 10);
    tos_task_create(&task2, "task2", task2_entry, NULL, 3, task2_stack, sizeof(task2_stack), 10);

    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
time is 0
MYYYMYYYMYYYMMMMYYYMYYYMYYYMY

*********************************************************/
