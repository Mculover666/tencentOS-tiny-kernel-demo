/********************************************************************
 *@file    cmsis_rtos_mutex.c                                                     
 *@brief   ����ʹ��CMSIS-RTOS ��׼API�������������������ͬ��
 *@author  Mculover666
 *@date    2020��7��17��11:57:49
 *@note
 *         ʹ�� CMSIS-RTOS v1.02��׼
*********************************************************************/

#include <cmsis_os.h>

osMutexId sync_mutex_id;
osMutexDef(sync_mutex);

void task1_entry(void *arg)
{
    while(1)
    {
        osMutexWait(sync_mutex_id, osWaitForever);
        
        printf("task1 get mutex,doing sth...\r\n");
        HAL_Delay(1000);    //��ѭ��ռ��CPU
        printf("task1 finish do sth!\r\n");
        
        osMutexRelease(sync_mutex_id);
        
        osDelay(1000);
    }
}
osThreadDef(task1_entry, osPriorityHigh, 1, 512);

void task2_entry(void *arg)
{
    
    while(1)
    {
        osMutexWait(sync_mutex_id, osWaitForever);
        
        printf("task2 get mutex,doing sth...\r\n");
        HAL_Delay(2000);    //��ѭ��ռ��CPU
        printf("task2 finish do sth!\r\n");
        
        osMutexRelease(sync_mutex_id);
        
        osDelay(1000);
    }
}
osThreadDef(task2_entry, osPriorityNormal, 1, 512);

void application_entry(void *arg)
{
    sync_mutex_id = osMutexCreate(osMutex(sync_mutex));

    osThreadCreate(osThread(task1_entry), NULL);
    osThreadCreate(osThread(task2_entry), NULL);
    
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
