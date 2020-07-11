/********************************************************
 *@file    event_demo_1.c                                              
 *@brief   
 *         测试使用事件进行任务间同步
 *@author  Mculover666
 *@date    2020年7月11日17:45:28
 *@note    
 *         一个任务等待多个事件中的一个
*********************************************************/

#include <tos_k.h>

k_task_t	task1;
k_task_t	task2;
k_stack_t	task1_stack[256];
k_stack_t	task2_stack[256];

k_event_t   sync_event;

//监听事件列表
const k_event_flag_t event_eeny     = (k_event_flag_t)(1 << 0);
const k_event_flag_t event_meeny    = (k_event_flag_t)(1 << 1);
const k_event_flag_t event_miny     = (k_event_flag_t)(1 << 2);
const k_event_flag_t event_moe      = (k_event_flag_t)(1 << 3);

//保存匹配到的事件值
k_event_flag_t  flag_match;

void task1_entry(void *arg)
{
    k_err_t err;
    
    while(1) {
        //等待四个事件中的任何一个
        err = tos_event_pend(&sync_event, 
                            event_eeny | event_meeny | event_miny | event_moe, 
                            &flag_match,
                            TOS_TIME_FOREVER,
                            TOS_OPT_EVENT_PEND_ANY | TOS_OPT_EVENT_PEND_CLR);
        
        if (err == K_ERR_NONE) {
            // 有事件到达，判断具体是哪个事件
            if (flag_match == event_eeny) {
                printf("eeny comes\n");
            }
            if (flag_match == event_meeny) {
                printf("meeny comes\n");    
            }
            if (flag_match == event_miny) {
                printf("miny comes\n");
            }
            if (flag_match == event_moe) {
                printf("moe comes\n");
            }
            if (flag_match == (event_eeny | event_meeny | event_miny | event_moe)) {
                printf("all come\n");
            }
        }
    }
}

void task2_entry(void *arg)
{
    int i = 1;

    while (K_TRUE) {
        if (i % 2 == 0) {
            printf("task2_trigger:\n");
            printf("eeny will come\n");
            // 发送eeny事件，task1会被唤醒
            tos_event_post(&sync_event, event_eeny);
        }
        if (i % 3 == 0) {
            printf("task2_trigger:\n");
            printf("meeny will come\n");
            // 发送eeny事件，task1会被唤醒
            tos_event_post(&sync_event, event_meeny);
        }
        if (i % 4 == 0) {
            printf("task2_trigger:\n");
            printf("miny will come\n");
            // 发送eeny事件，task1会被唤醒
            tos_event_post(&sync_event, event_miny);
        }
        if (i % 5 == 0) {
            printf("task2_trigger:\n");
            printf("moe will come\n");
            // 发送eeny事件，task1会被唤醒
            tos_event_post(&sync_event, event_moe);
        }
        if (i % 6 == 0) {
            printf("task2_trigger:\n");
            printf("all will come\n");
            // 同时发送四个事件，因为task1的优先级高于task2，因此这里task1会被唤醒
            tos_event_post(&sync_event, event_eeny | event_meeny | event_miny | event_moe);
        }
        tos_sleep_ms(2000);
        ++i;
    }
}

void application_entry(void *arg)
{
    //创建事件集
    tos_event_create(&sync_event, (k_event_flag_t)0u);
    
    //创建任务
    tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 10);
    tos_task_create(&task2, "task2", task2_entry, NULL, 3, task2_stack, sizeof(task2_stack), 10);
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
task2_trigger:
eeny will come
eeny comes
task2_trigger:
meeny will come
meeny comes
task2_trigger:
eeny will come
eeny comes
task2_trigger:
miny will come
miny comes
task2_trigger:
moe will come
moe comes
task2_trigger:
eeny will come
eeny comes
task2_trigger:
meeny will come
meeny comes
task2_trigger:
all will come
all come
task2_trigger:
eeny will come
eeny comes
task2_trigger:
miny will come
miny comes

*********************************************************/
