/********************************************************************
 *@file    cmsis_rtos_sem.c                                                     
 *@brief   ����ʹ��CMSIS-RTOS ��׼API�����ź������������ͬ��
 *@author  Mculover666
 *@date    2020��7��17��11:57:49
 *@note
 *         ʹ�� CMSIS-RTOS v1.02��׼
*********************************************************************/

#include <cmsis_os.h>

osSemaphoreId sync_sem_id;
osSemaphoreDef(sync_sem);

void task1_entry(void *arg)
{
    while(1)
    {
        printf("task1 is waiting sem forever...\r\n");
        osSemaphoreWait(sync_sem_id, osWaitForever);
        printf("task1 get sem!\r\n");
    }
}
osThreadDef(task1_entry, osPriorityNormal, 1, 512);

void task2_entry(void *arg)
{
    
    while(1)
    {
        printf("task2 will release a sem...\r\n");
        osSemaphoreRelease(sync_sem_id);
        osDelay(1000);
    }
}
osThreadDef(task2_entry, osPriorityNormal, 1, 512);

void application_entry(void *arg)
{
    sync_sem_id = osSemaphoreCreate(osSemaphore(sync_sem), 0);

    osThreadCreate(osThread(task1_entry), NULL);
    osThreadCreate(osThread(task2_entry), NULL);
    
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
