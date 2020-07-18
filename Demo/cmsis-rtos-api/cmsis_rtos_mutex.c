/********************************************************************
 *@file    cmsis_rtos_mutex.c                                                     
 *@brief   测试使用CMSIS-RTOS 标准API创建互斥锁进行任务间同步
 *@author  Mculover666
 *@date    2020年7月17日11:57:49
 *@note
 *         使用 CMSIS-RTOS v1.02标准
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
        HAL_Delay(1000);    //死循环占用CPU
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
        HAL_Delay(2000);    //死循环占用CPU
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


如果将互斥锁注释掉，则结果变为：

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
task1 get mutex,doing sth...
task1 finish do sth!
task2 get mutex,doing sth...
task1 get mutex,doing sth...（task2还在使用时，被高优先级任务task1抢占）
task1 finish do sth!
task2 finish do sth!
task1 get mutex,doing sth...
task1 finish do sth!
task2 get mutex,doing sth...
task1 get mutex,doing sth...
task1 finish do sth!
task2 finish do sth!



*********************************************************/
