/*******************************************************************
 *@file    prio_queue_demo_1.c                                                    
 *@brief   
 *         测试优先级队列（prio queue）的使用
 *@author  Mculover666
 *@date    2020年7月18日11:24:27
 *@note
 *         可以将此Demo与ring_queue_demo_1.c比较。
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

#define PRIO_QUEUE_ITEM_MAX 5

uint8_t prio_q_buffer[PRIO_QUEUE_ITEM_MAX * sizeof(item_t)];
uint8_t mgr_pool[TOS_PRIO_Q_MGR_ARRAY_SIZE(PRIO_QUEUE_ITEM_MAX)];

k_prio_q_t prio_q;

void entry_task_demo(void *arg)
{
    k_err_t err;
    int i;
    item_t item;
    size_t item_size;
    k_prio_t item_prio;
    
    //创建优先级队列
    tos_prio_q_create(&prio_q, mgr_pool, prio_q_buffer, PRIO_QUEUE_ITEM_MAX, sizeof(item_t));
    
    //数据入队
    for(i = PRIO_QUEUE_ITEM_MAX;i > 0; i--)
    {
        item.a = i;
        item.b = i;
        item.c = i;
        
        err = tos_prio_q_enqueue(&prio_q, &item, sizeof(item), i);
        if(err == K_ERR_NONE)
        {
            printf("enqueue a item: %d %d %d\n", item.a, item.b, item.c);
        }
        else
        {
            printf("prio queue enqueue fail,err = %d\r\n", err);
        }
    }
    
    //队列满之后，继续入队
    err = tos_prio_q_enqueue(&prio_q, &item, sizeof(item_t), i);
    if(err == K_ERR_PRIO_Q_FULL)
    {
        printf("prio queue is full: %s\n", tos_prio_q_is_full(&prio_q) ? "TRUE" : "FALSE");
    }
    else
    {
        printf("prio queue enqueue fail,err = %d\r\n", err);
    }
    
    //数据出队
    for(i = 0; i < PRIO_QUEUE_ITEM_MAX; ++i)
    {
        err = tos_prio_q_dequeue(&prio_q, &item, &item_size, &item_prio);
        if(err == K_ERR_NONE)
        {
            printf("dequeue a item[piro %d]: %d %d %d\n", item_prio, item.a, item.b, item.c);
        }
        else
        {
            printf("prio queue dequeue fail,err = %d\r\n", err);
        }
    }
    
    //没有数据后继续出队
    err = tos_prio_q_dequeue(&prio_q, &item, &item_size, &item_prio);
    if(err == K_ERR_PRIO_Q_EMPTY)
    {
        printf("prio queue is empty: %s\n", tos_prio_q_is_empty(&prio_q) ? "TRUE" : "FALSE");
    }
    else
    {
        printf("prio queue dequeue fail,err = %d\r\n", err);
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
enqueue a item: 5 5 5
enqueue a item: 4 4 4
enqueue a item: 3 3 3
enqueue a item: 2 2 2
enqueue a item: 1 1 1
prio queue is full: TRUE
dequeue a item[piro 1]: 1 1 1
dequeue a item[piro 2]: 2 2 2
dequeue a item[piro 3]: 3 3 3
dequeue a item[piro 4]: 4 4 4
dequeue a item[piro 5]: 5 5 5
prio queue is empty: TRUE

*********************************************************/
