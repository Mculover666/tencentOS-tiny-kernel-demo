/********************************************************
 *@file    stopwatch_demo_1.c                                                      
 *@brief
 *         利用计时表进行超时判定
 *@author  Mculover666
 *@date    2020年8月4日13:24:38
*********************************************************/
#include <tos_k.h>

k_task_t	task1;
k_stack_t	task1_stack[256];

k_stopwatch_t stopwatch;

void task1_entry(void *arg)
{
    tos_stopwatch_countdown(&stopwatch, 5000);
    
    do{
        if (tos_stopwatch_remain(&stopwatch) == 0) {
            printf("timeout!\r\n");
            break;
        }
        printf("working...\r\n");
        tos_task_delay(800);
    }while(1);
    
    return;
}

void application_entry(void *arg)
{
    //创建计时表
    tos_stopwatch_create(&stopwatch);
    
    //创建任务
    tos_task_create(&task1, "task1", task1_entry, NULL, 4, task1_stack, sizeof(task1_stack), 10);

    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
working...
working...
working...
working...
working...
working...
working...
timeout!


*********************************************************/
