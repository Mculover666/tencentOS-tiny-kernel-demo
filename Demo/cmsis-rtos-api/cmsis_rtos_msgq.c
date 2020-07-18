/********************************************************************
 *@file    cmsis_rtos_msg_q.c                                                     
 *@brief   测试使用CMSIS-RTOS 标准API创建消息队列进行任务间通信
 *@author  Mculover666
 *@date    2020年7月17日14:57:49
 *@note
 *         使用 CMSIS-RTOS v1.02标准
*********************************************************************/

#include <cmsis_os.h>

#define STK_SIZE_TASK_RECEIVER      512
#define STK_SIZE_TASK_SENDER        512

#define MESSAGE_MAX     10

osMessageQId msg_q_id;
osMessageQDef(msg_q,MESSAGE_MAX,uint32_t);

void task_receiver_entry(void *arg)
{
    osEvent event;
    osStatus ret;
    uint32_t value;

    while (1)
    {
        event = osMessageGet(msg_q_id, osWaitForever);
        ret = event.status;
        if (ret == osOK)
        {
            value = event.value.v;
            printf("receiver: msg incoming[%s]\r\n", (char*)value);
        }
    }
}
osThreadDef(task_receiver_entry, osPriorityNormal, 1, STK_SIZE_TASK_RECEIVER);

void task_sender_entry(void *arg)
{
    char *msg_prio_0 = "msg 0";
    char *msg_prio_1 = "msg 1";
    char *msg_prio_2 = "msg 2";

    printf("sender: post a messgae:[%s]\r\n", msg_prio_2);
    osMessagePut(msg_q_id,(uint32_t)msg_prio_2,0);
    
    printf("sender: post a messgae:[%s]\r\n", msg_prio_1);
    osMessagePut(msg_q_id,(uint32_t)msg_prio_1,0);
    
    printf("sender: post a messgae:[%s]\r\n", msg_prio_0);
    osMessagePut(msg_q_id,(uint32_t)msg_prio_0,0);

}
osThreadDef(task_sender_entry, osPriorityNormal, 1, STK_SIZE_TASK_SENDER);

void application_entry(void *arg)
{
    msg_q_id = osMessageCreate(osMessageQ(msg_q),NULL);

    osThreadCreate(osThread(task_receiver_entry), NULL);
    osThreadCreate(osThread(task_sender_entry), NULL);
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
sender: post a messgae:[msg 2]
sender: post a messgae:[msg 1]
sender: post a messgae:[msg 0]
receiver: msg incoming[msg 2]
receiver: msg incoming[msg 1]
receiver: msg incoming[msg 0]

*********************************************************/
