/********************************************************
 *@file    completion_demo.c                                              
 *@brief   
 *         测试使用完成量进行任务间同步
 *@author  Mculover666
 *@date    2020年7月11日19:56:51
*********************************************************/

#include <tos_k.h>

k_task_t	task1;
k_task_t	task2;
k_stack_t	task1_stack[256];
k_stack_t	task2_stack[256];

k_completion_t  sync_completion;

void task1_entry(void *arg)
{
    k_err_t ret;
    
    while(1) {
        ret = tos_completion_pend(&sync_completion);
        //需要手动清除标志位
        tos_completion_reset(&sync_completion);
        if (ret != K_ERR_NONE) {
            printf("completion pend fail, err = %d\r\n", ret);
        }
        printf("task 1 get completion!\r\n");
    }
}

void task2_entry(void *arg)
{
    while (1) {
       tos_completion_post(&sync_completion);
       tos_sleep_ms(2000);
    }
}

void application_entry(void *arg)
{
    //创建完成量
    tos_completion_create(&sync_completion);
    
    //创建任务
    tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 10);
    tos_task_create(&task2, "task2", task2_entry, NULL, 3, task2_stack, sizeof(task2_stack), 10);
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
task 1 get completion!(每1s一次)
task 1 get completion!
task 1 get completion!
task 1 get completion!
task 1 get completion!


*********************************************************/
