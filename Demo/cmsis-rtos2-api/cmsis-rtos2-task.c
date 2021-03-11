/********************************************************************
 *@file    cmsis-rtos2-task.c                                                     
 *@brief   测试使用CMSIS-RTOS v2标准API创建任务
 *@author  Mculover666
 *@date    2021年3月10日14:30:58
 *@note
 *         使用 CMSIS-RTOS v2.1.3 标准
*********************************************************************/

#include <cmsis_os2.h>

void task1_entry(void *arg)
{
    while(1)
    {
        printf("task1 is running...\r\n");
        osDelay(1000);
    }
}
osThreadDef(task1, osPriorityNormal, 1, 512);

void task2_entry(void *arg)
{
    
    while(1)
    {
        printf("task2 is running...\r\n");
        osDelay(1000);
    }
}
osThreadDef(task2, osPriorityNormal, 1, 512);

void application_entry(void *arg)
{

    osThreadNew(task1_entry, NULL, osThread(task1));
    osThreadNew(task2_entry, NULL, osThread(task2));
    
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
