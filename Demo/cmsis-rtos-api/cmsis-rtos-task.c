/********************************************************************
 *@file    cmsis-rtos-task.c                                                     
 *@brief   ����ʹ��CMSIS-RTOS ��׼API��������
 *@author  Mculover666
 *@date    2020��7��17��09:01:49
 *@note
 *         ʹ�� CMSIS-RTOS v1.02��׼
*********************************************************************/

#include <cmsis_os.h>

void task1_entry(void *arg)
{
    while(1)
    {
        printf("task1 is running...\r\n");
        osDelay(1000);
    }
}
osThreadDef(task1_entry, osPriorityNormal, 1, 512);

void task2_entry(void *arg)
{
    
    while(1)
    {
        printf("task2 is running...\r\n");
        osDelay(1000);
    }
}
osThreadDef(task2_entry, osPriorityNormal, 1, 512);

void application_entry(void *arg)
{

    osThreadCreate(osThread(task1_entry), NULL);
    osThreadCreate(osThread(task2_entry), NULL);
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
task1 is running...
task2 is running...
task1 is running...
task2 is running...
task1 is running...
task2 is running...
task1 is running...
task2 is running...

*********************************************************/
