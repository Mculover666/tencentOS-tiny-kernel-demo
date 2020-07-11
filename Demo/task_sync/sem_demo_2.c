/********************************************************
 *@file    sem_demo_1.c                                              
 *@brief   
 *         ����ʹ���ź�������Դ�������ܽ��������ͬ��
 *@author  Mculover666
 *@date    2020��7��11��16:23:48
 *@note    
 *         ������������Demo
 *         1. ����ֿ�����Ϊ5
 *         2. ���������ʽ�����3s����һ����û�п�λ�Ͷ����ȴ�
 *         3. ���������ʽϿ죬1s����һ����û�в�Ʒ�Ͷ����ȴ�
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
    //�����ź���
    tos_sem_create(&full_sem, 5);
    tos_sem_create(&empty_sem, 0);
    
    //��������
    tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 10);
    tos_task_create(&task2, "task2", task2_entry, NULL, 3, task2_stack, sizeof(task2_stack), 10);
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
consume a item(<--------------�տ�ʼ��ʱ����5����λ��0����λ)
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
