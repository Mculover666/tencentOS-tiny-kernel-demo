/*******************************************************************
 *@file    prio_message_queue_demo_1.c                                                      
 *@brief   
 *         测试消息队列（Message Queue）的使用
 *@author  Mculover666
 *@date    2020年7月12日10:24:27
 *@note
 *         1. 可以将此Demo与prio_message_queue_demo_1.c比较。
*******************************************************************/
#include <tos_k.h>

#define STK_SIZE_TASK_RECEIVER      512
#define STK_SIZE_TASK_SENDER        512

#define MESSAGE_MAX     10

k_stack_t stack_task_receiver[STK_SIZE_TASK_RECEIVER];
k_stack_t stack_task_sender[STK_SIZE_TASK_SENDER];

uint8_t msg_pool[MESSAGE_MAX * sizeof(void *)];

k_task_t task_receiver;
k_task_t task_sender;

k_msg_q_t msg_q;

void entry_task_receiver(void *arg)
{
    k_err_t err;
    void *msg_received;

    while (K_TRUE) {
        err = tos_msg_q_pend(&msg_q, &msg_received, TOS_TIME_FOREVER);
        if (err == K_ERR_NONE) {
            printf("receiver: msg incoming[%s]\n", (char *)msg_received);
        }
    }
}

void entry_task_sender(void *arg)
{
    char *msg_prio_0 = "msg 0 without priority";
    char *msg_prio_1 = "msg 1 without priority";
    char *msg_prio_2 = "msg 2 without priority";

    printf("sender: post a message 2 without priority\n");
    tos_msg_q_post(&msg_q, msg_prio_2);

    printf("sender: post a message 1 without priority\n");
    tos_msg_q_post(&msg_q, msg_prio_1);

    printf("sender: post a message 0 without priority\n");
    tos_msg_q_post(&msg_q, msg_prio_0);
}

void application_entry(void *arg)
{
    //创建优先级消息队列
    tos_msg_q_create(&msg_q, msg_pool, MESSAGE_MAX);
    
    //创建任务
    (void)tos_task_create(&task_receiver, "receiver", entry_task_receiver, NULL,
                            5, stack_task_receiver, STK_SIZE_TASK_RECEIVER, 0);
    
    tos_task_create(&task_sender, "sender", entry_task_sender, NULL,
                            4, stack_task_sender, STK_SIZE_TASK_SENDER, 0);

    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
sender: post a message 2 without priority
sender: post a message 1 without priority
sender: post a message 0 without priority
receiver: msg incoming[msg 2 without priority]
receiver: msg incoming[msg 1 without priority]
receiver: msg incoming[msg 0 without priority]

*********************************************************/
