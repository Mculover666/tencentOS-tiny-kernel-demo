/********************************************************
 *@file    sem_demo_1.c                                              
 *@brief   
 *         测试使用信号量的flag功能进行任务间同步
 *@author  Mculover666
 *@date    2020年7月11日16:10:28
*********************************************************/

#include <tos_k.h>

k_task_t	task1;
k_task_t	task2;
k_stack_t	task1_stack[256];
k_stack_t	task2_stack[256];

k_sem_t sync_sem;

void task1_entry(void *arg)
{
    printf("task1 start\r\n");
    while(1)
    {
        printf("task1 is waiting sync sem forever...\r\n");
        tos_sem_pend(&sync_sem, TOS_TIME_FOREVER);
        printf("task1 get sync sem!\r\n");
    }
}

void task2_entry(void *arg)
{
    printf("task2 start...\r\n");
    while(1)
    {
        printf("task2 will post sync sem...\r\n\r\n");
        tos_sem_post(&sync_sem);
        tos_sleep_ms(1000);
    }
}

void application_entry(void *arg)
{
    //创建信号量
    tos_sem_create_max(&sync_sem, 0, 1);
    printf("sync sem create success\r\n");
    
    //创建任务
    tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 10);
    printf("task1 create success\r\n");
    tos_task_create(&task2, "task2", task2_entry, NULL, 3, task2_stack, sizeof(task2_stack), 10);
    printf("task2 create success\r\n");
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
sync sem create success
task1 create success
task2 create success
task1 start

task1 is waiting sync sem forever...
task2 start...(<------此时task1阻塞等待信号量，task2才得以执行)
task2 will post sync sem...
task1 get sync sem!(<----------此时task2释放信号量，唤醒task1执行)

task1 is waiting sync sem forever...
task2 will post sync sem...
task1 get sync sem!

task1 is waiting sync sem forever...
task2 will post sync sem...
task1 get sync sem!

task1 is waiting sync sem forever...
task2 will post sync sem...
task1 get sync sem!

task1 is waiting sync sem forever...
task2 will post sync sem...
task1 get sync sem!

task1 is waiting sync sem forever...

*********************************************************/
