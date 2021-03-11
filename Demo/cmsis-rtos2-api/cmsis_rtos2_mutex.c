/********************************************************************
 *@file    cmsis_rtos_mutex.c                                                     
 *@brief   ����ʹ��CMSIS-RTOS2 ��׼API�������������������ͬ��
 *@author  Mculover666
 *@date    2021��3��10��15:29:37
 *@note
 *         ʹ�� CMSIS-RTOS v2.1.3 ��׼
*********************************************************************/

#include <cmsis_os2.h>

osMutexId_t sync_mutex_id;

void task1_entry(void *arg)
{
    while(1)
    {
        osMutexAcquire(sync_mutex_id, osWaitForever);
        
        printf("task1 get mutex,doing sth...\r\n");
        HAL_Delay(1000);    //��ѭ��ռ��CPU
        printf("task1 finish do sth!\r\n");
        
        osMutexRelease(sync_mutex_id);
        
        osDelay(1000);
    }
}
osThreadDef(task1, osPriorityHigh, 1, 512);

void task2_entry(void *arg)
{
    
    while(1)
    {
        osMutexAcquire(sync_mutex_id, osWaitForever);
        
        printf("task2 get mutex,doing sth...\r\n");
        HAL_Delay(2000);    //��ѭ��ռ��CPU
        printf("task2 finish do sth!\r\n");
        
        osMutexRelease(sync_mutex_id);
        
        osDelay(1000);
    }
}
osThreadDef(task2, osPriorityNormal, 1, 512);

void application_entry(void *arg)
{
    sync_mutex_id = osMutexNew(NULL);

    osThreadNew(task1_entry, NULL, osThread(task1));
    osThreadNew(task2_entry, NULL, osThread(task2));
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
task1 get mutex,doing sth...
task1 finish do sth!
task2 get mutex,doing sth...
task2 finish do sth!
task1 get mutex,doing sth...
task1 finish do sth!
task1 get mutex,doing sth...
task1 finish do sth!
task2 get mutex,doing sth...


�����������ע�͵���������Ϊ��

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
task1 get mutex,doing sth...
task1 finish do sth!
task2 get mutex,doing sth...
task1 get mutex,doing sth...��task2����ʹ��ʱ���������ȼ�����task1��ռ��
task1 finish do sth!
task2 finish do sth!
task1 get mutex,doing sth...
task1 finish do sth!
task2 get mutex,doing sth...
task1 get mutex,doing sth...
task1 finish do sth!
task2 finish do sth!



*********************************************************/
