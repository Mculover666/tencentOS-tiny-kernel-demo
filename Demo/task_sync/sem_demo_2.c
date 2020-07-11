/********************************************************
 *@file    sem_demo_1.c                                              
 *@brief   
 *         测试使用信号量的资源计数功能进行任务间同步
 *@author  Mculover666
 *@date    2020年7月11日16:23:48
 *@note    
 *         生产者消费者Demo
 *         1. 假设仓库容量为5
 *         2. 生产者速率较慢，3s生产一个，没有空位就堵塞等待
 *         3. 消费者速率较快，1s消费一个，没有产品就堵塞等待
*********************************************************/

#include <tos_k.h>

k_task_t	task1;  //product task
k_task_t	task2;  //consumer task
k_stack_t	task1_stack[256];
k_stack_t	task2_stack[256];

k_sem_t full_sem;
k_sem_t empty_sem;

void task1_entry(void *arg)
{
    while(1)
    {
        tos_sem_pend(&empty_sem, TOS_TIME_FOREVER);
        printf("product a item\r\n");
        tos_sem_post(&full_sem);
        
        tos_sleep_ms(3000);
    }
}

void task2_entry(void *arg)
{
    while(1)
    {
        tos_sem_pend(&full_sem, TOS_TIME_FOREVER);
        printf("consume a item\r\n");
        tos_sem_post(&empty_sem);
        
        tos_sleep_ms(1000);
    }
}

void application_entry(void *arg)
{
    //创建信号量
    tos_sem_create(&full_sem, 5);
    tos_sem_create(&empty_sem, 0);
    
    //创建任务
    tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 10);
    tos_task_create(&task2, "task2", task2_entry, NULL, 3, task2_stack, sizeof(task2_stack), 10);
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
consume a item(<--------------刚开始的时候有5个满位、0个空位)
product a item
consume a item
consume a item
product a item
consume a item
consume a item
consume a item
product a item
consume a item
consume a item
product a item
consume a item
product a item
consume a item
product a item
consume a item
product a item
consume a item

*********************************************************/
