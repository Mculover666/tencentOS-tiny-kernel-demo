/********************************************************************
 *@file    cmsis_rtos2_sem.c                                                     
 *@brief   测试使用CMSIS-RTOS 标准API创建信号量进行任务间同步
 *@author  Mculover666
 *@date    2021年3月10日14:47:38
 *@note
 *         使用 CMSIS-RTOS v2.1.3标准
*********************************************************************/

#include <cmsis_os2.h>

osSemaphoreId_t sync_sem_id;

void task1_entry(void *arg)
{
    while(1)
    {
        printf("task1 is waiting sem forever...\r\n");
        osSemaphoreAcquire(sync_sem_id, osWaitForever);
        printf("task1 get sem!\r\n");
    }
}
osThreadDef(task1, osPriorityNormal, 1, 512);

void task2_entry(void *arg)
{
    
    while(1)
    {
        printf("task2 will release a sem...\r\n");
        osSemaphoreRelease(sync_sem_id);
        osDelay(1000);
    }
}
osThreadDef(task2, osPriorityNormal, 1, 512);

void application_entry(void *arg)
{
    sync_sem_id = osSemaphoreNew(1, 0, NULL);

    osThreadNew(task1_entry, NULL, osThread(task1));
    osThreadNew(task2_entry, NULL, osThread(task2));
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
task1 is waiting sem forever...
task1 get sem!
task1 is waiting sem forever...
task2 will release a sem...
task1 get sem!
task1 is waiting sem forever...
task2 will release a sem...
task1 get sem!
task1 is waiting sem forever...
task2 will release a sem...
task1 get sem!
task1 is waiting sem forever...
task2 will release a sem...
task1 get sem!
task1 is waiting sem forever...

*********************************************************/
