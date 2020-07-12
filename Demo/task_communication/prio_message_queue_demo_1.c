/*******************************************************************
 *@file    prio_message_queue_demo_1.c                                                      
 *@brief   
 *         �������ȼ���Ϣ���У�Message Queue����ʹ��
 *@author  Mculover666
 *@date    2020��7��12��10:24:27
 *@note
 *         1. ���ȼ���Ϣ���������Ϣ������˵������Ϣ������һ�����ȼ��ĸ��
 *            �ϸ����ȼ�����Ϣ��Ƚϵ����ȼ�����Ϣ����ر����������յ���
 *         2. ���Խ���Demo��message_queue_demo_2.c�Ƚϡ�
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

k_prio_msg_q_t prio_msg_q;

void entry_task_receiver(void *arg)
{
    k_err_t err;
    void *msg_received;

    while (K_TRUE) {
        err = tos_prio_msg_q_pend(&prio_msg_q, &msg_received, TOS_TIME_FOREVER);
        if (err == K_ERR_NONE) {
            printf("receiver: msg incoming[%s]\n", (char *)msg_received);
        }
    }
}

void entry_task_sender(void *arg)
{
    char *msg_prio_0 = "msg with priority 0";
    char *msg_prio_1 = "msg with priority 1";
    char *msg_prio_2 = "msg with priority 2";

    printf("sender: post a message with priority 2\n");
    tos_prio_msg_q_post(&prio_msg_q, msg_prio_2, 2);

    printf("sender: post a message with priority 1\n");
    tos_prio_msg_q_post(&prio_msg_q, msg_prio_1, 1);

    printf("sender: post a message with priority 0\n");
    tos_prio_msg_q_post(&prio_msg_q, msg_prio_0, 0);
}

void application_entry(void *arg)
{
    //�������ȼ���Ϣ����
    tos_prio_msg_q_create(&prio_msg_q, msg_pool, MESSAGE_MAX);
    
    //��������
    (void)tos_task_create(&task_receiver, "receiver", entry_task_receiver, NULL,
                            5, stack_task_receiver, STK_SIZE_TASK_RECEIVER, 0);
    
    tos_task_create(&task_sender, "sender", entry_task_sender, NULL,
                            4, stack_task_sender, STK_SIZE_TASK_SENDER, 0);

    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
sender: post a message with priority 2
sender: post a message with priority 1
sender: post a message with priority 0
receiver: msg incoming[msg with priority 0]
receiver: msg incoming[msg with priority 1]
receiver: msg incoming[msg with priority 2]

*********************************************************/
