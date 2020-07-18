/********************************************************************
 *@file    cmsis-rtos-timer.c                                                     
 *@brief   测试使用CMSIS-RTOS 标准API创建定时器
 *@author  Mculover666
 *@date    2020年7月17日11:31:49
 *@note
 *         使用 CMSIS-RTOS v1.02标准
*********************************************************************/

#include <cmsis_os.h>

void timer1_cb(void *arg)
{
    printf("timer1 is timeout!\r\n");
}

void timer2_cb(void *arg)
{
    printf("timer2 is timeout!\r\n");
}

osTimerDef(timer1, timer1_cb);
osTimerDef(timer2, timer2_cb);

void application_entry(void *arg)
{
    osTimerId timer1;
    osTimerId timer2;
    
    timer1 = osTimerCreate(osTimer(timer1), osTimerOnce, NULL);
    timer2 = osTimerCreate(osTimer(timer2), osTimerPeriodic, NULL);
    
    osTimerStart(timer1, 5000);
    osTimerStart(timer2, 1000);
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
timer2 is timeout!
timer2 is timeout!
timer2 is timeout!
timer2 is timeout!
timer1 is timeout!
timer2 is timeout!
timer2 is timeout!
timer2 is timeout!
timer2 is timeout!

*********************************************************/
