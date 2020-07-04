/********************************************************************
 *@file    task_demo_3.c                                                      
 *@brief
 *         task1（高优先级）每隔3s打印一个"M"
 *         task2（低优先级）每隔1s打印一个"Y"
 *         task2 运行3次之后把 调度器上锁，运行6次之后把调度器解锁
 *
 *@author  Mculover666
 *@date    2020年7月4日14:00:16
*********************************************************************/

#include <tos_k.h>

k_task_t	task1;
k_task_t	task2;
k_stack_t	task1_stack[256];
k_stack_t	task2_stack[256];

void task1_entry(void *arg)
{
    while(1) {
        printf("M");
        tos_task_delay(3000);
    }
}

void task2_entry(void *arg)
{
    int time = 0;
    
    while(1) {
        if(time == 3) {
            /* 调度器上锁 */
            tos_knl_sched_lock();
        }
        if(time == 6) {
            /* 调度器解锁 */
            tos_knl_sched_unlock();
        }
        printf("Y");
        time += 1;
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
MYYYMYYYYYYMYYYMYYYMYYYMY

*********************************************************/
