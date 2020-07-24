/*******************************************************************
 *@file   mail_queue_demo_2.c                                                      
 *@brief   
 *         测试邮箱队列（Mail Queue）的使用
 *@author  Mculover666
 *@date    2020年7月19日15:37:15
 *@note
 *         可以将此Demo与prio_mail_queue_demo_1.c比较。
*******************************************************************/
#include <tos_k.h>

#define STK_SIZE_TASK_RECEIVER      512
#define STK_SIZE_TASK_SENDER        512

#define MAIL_MAX     10

k_stack_t stack_task_receiver[STK_SIZE_TASK_RECEIVER];
k_stack_t stack_task_sender[STK_SIZE_TASK_SENDER];

typedef struct mail_st {
    char   *message;
    int     payload;
} mail_t;

uint8_t mailpool[MAIL_MAX * sizeof(mail_t)];

k_task_t task_receiver;
k_task_t task_sender;

k_mail_q_t mail_q;

void entry_task_receiver(void *arg)
{
    k_err_t err;
    mail_t mail;
    size_t mail_size;

    while (K_TRUE) {
        err = tos_mail_q_pend(&mail_q, &mail, &mail_size, TOS_TIME_FOREVER);
        if (err == K_ERR_NONE) {
            printf("receiver: msg incoming[%d bytes][%s], payload[%d]\n", mail_size, mail.message, mail.payload);
        }
    }
}

void entry_task_sender(void *arg)
{
    mail_t mail_0, mail_1, mail_2;

    printf("sender: post a mail 2\n");
    mail_2.message = "mail 2";
    mail_2.payload = 2;
    tos_mail_q_post(&mail_q, &mail_2, sizeof(mail_t));

    printf("sender: post a mail 1\n");
    mail_1.message = "mail 1";
    mail_1.payload = 1;
    tos_mail_q_post_all(&mail_q, &mail_1, sizeof(mail_t));

    printf("sender: post a mail 0\n");
    mail_0.message = "mail 0";
    mail_0.payload = 0;
    tos_mail_q_post(&mail_q, &mail_0, sizeof(mail_t));
}

void application_entry(void *arg)
{
    //创建优先级邮箱队列
    tos_mail_q_create(&mail_q, mailpool, MAIL_MAX, sizeof(mail_t));
    
    //创建任务
    (void)tos_task_create(&task_receiver, "receiver", entry_task_receiver, NULL,
                            5, stack_task_receiver, STK_SIZE_TASK_RECEIVER, 0);
    
    tos_task_create(&task_sender, "sender", entry_task_sender, NULL,
                            4, stack_task_sender, STK_SIZE_TASK_SENDER, 0);

    return;
}

/********************************************************
result:

<待测试...>

*********************************************************/
