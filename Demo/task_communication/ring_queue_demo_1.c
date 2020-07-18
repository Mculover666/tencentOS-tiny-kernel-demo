/*******************************************************************
 *@file    ring_queue_demo_1.c                                                    
 *@brief   
 *         测试环形队列（ring queue）的使用
 *@author  Mculover666
 *@date    2020年7月18日10:24:27
 *@note
 *         可以将此Demo与prio_queue_demo_1.c比较。
*******************************************************************/
#include <tos_k.h>

#define STK_SIZE_TASK_DEMO  512
k_stack_t task_demo_stack[STK_SIZE_TASK_DEMO];
k_task_t task_demo;

typedef struct item_st {
    int a;
    int b;
    int c;
} item_t;

#define RING_QUEUE_ITEM_MAX 5

uint8_t ring_q_buffer[RING_QUEUE_ITEM_MAX * sizeof(item_t)];

k_ring_q_t ring_q;

void entry_task_demo(void *arg)
{
    k_err_t err;
    int i;
    item_t item;
    size_t item_size;
    
    //创建环形队列
    tos_ring_q_create(&ring_q, ring_q_buffer, RING_QUEUE_ITEM_MAX, sizeof(item_t));
    
    //数据入队
    for(i = 0;i < RING_QUEUE_ITEM_MAX; i++)
    {
        item.a = i;
        item.b = i;
        item.c = i;
        
        err = tos_ring_q_enqueue(&ring_q, &item, sizeof(item_t));
        if(err == K_ERR_NONE)
        {
            printf("enqueue a item: %d %d %d\n", item.a, item.b, item.c);
        }
        else
        {
            printf("ring queue enqueue fail,err = %d\r\n", err);
        }
    }
    
    //队列满之后，继续入队
    err = tos_ring_q_enqueue(&ring_q, &item, sizeof(item_t));
    if(err == K_ERR_RING_Q_FULL)
    {
        printf("ring queue is full: %s\n", tos_ring_q_is_full(&ring_q) ? "TRUE" : "FALSE");
    }
    else
    {
        printf("ring queue enqueue fail,err = %d\r\n", err);
    }
    
    //数据出队
    for(i = 0; i < RING_QUEUE_ITEM_MAX; ++i)
    {
        err = tos_ring_q_dequeue(&ring_q, &item, &item_size);
        if(err == K_ERR_NONE)
        {
            printf("dequeue a item(%d bytes): %d %d %d\n", item_size, item.a, item.b, item.c);
        }
        else
        {
            printf("ring queue dequeue fail,err = %d\r\n", err);
        }
    }
    
    //没有数据后继续出队
    err = tos_ring_q_dequeue(&ring_q, &item, &item_size);
    if(err == K_ERR_RING_Q_EMPTY)
    {
        printf("ring queue is empty: %s\n", tos_ring_q_is_empty(&ring_q) ? "TRUE" : "FALSE");
    }
    else
    {
        printf("ring queue dequeue fail,err = %d\r\n", err);
    }
    

}


void application_entry(void *arg)
{
    tos_task_create(&task_demo, "task_demo", entry_task_demo, NULL,
                            2, task_demo_stack, STK_SIZE_TASK_DEMO, 0);

    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
enqueue a item: 0 0 0
enqueue a item: 1 1 1
enqueue a item: 2 2 2
enqueue a item: 3 3 3
enqueue a item: 4 4 4
ring queue is full: TRUE
dequeue a item(12 bytes): 0 0 0
dequeue a item(12 bytes): 1 1 1
dequeue a item(12 bytes): 2 2 2
dequeue a item(12 bytes): 3 3 3
dequeue a item(12 bytes): 4 4 4
ring queue is empty: TRUE


*********************************************************/
