/********************************************************************
 *@file    task_demo_4.c                                                      
 *@brief
 *         task2（高优先级）启动之后动态创建一个task1（低优先级）
 *         动态任务task1打印5次之后结束运行，系统回收其任务栈空间
 *
 *@note    此Demo中使用到了动态Task，需要使能 TOS_CFG_TASK_DYNAMIC_CREATE_EN 
 *@author  Mculover666
 *@date    2020年12月19日23:21:04
*********************************************************************/

#include <tos_k.h>

k_task_t	*task1;
k_task_t    task2;
k_stack_t	task2_stack[256];

int list_mmheap_info(void);

void task1_entry(void *arg)
{
    int n;
    
    printf("task1 start!\r\n");
    
    for (n = 0; n < 5; n++) {
        printf("task1 is running...\r\n");
        tos_task_delay(2000);
    }
}

void task2_entry(void *arg)
{
    k_err_t err;
    
    printf("task2 start!\r\n");
    
    /* 在未创建动态之前打印堆使用情况 */
    list_mmheap_info();
    
    err = tos_task_create_dyn(&task1, "task1", task1_entry, NULL, 3, 256, 10);
    
    if (err != K_ERR_NONE) {
        printf("create dyn task1 fail, err is %d\r\n", err);
        return;
    } else {
        printf("create dyn task1 success\r\n");
    }
    
    while (1) {
        printf("task2 is running...\r\n");
         
        //在创建动态任务之后打印堆使用情况
        list_mmheap_info();
        
        tos_task_delay(2000);
    }
}

void application_entry(void *arg)
{
    //创建任务task2
    tos_task_create(&task2, "task2", task2_entry, NULL, 2, task2_stack, sizeof(task2_stack), 10);

    return;
}

/**
 *@brief   打印当前mmeheap使用情况
 *@param   none
 *@retval  none
*/
int list_mmheap_info(void)
{
    k_err_t err;
    k_mmheap_info_t mmheap_info;

    err = tos_mmheap_check(&mmheap_info);
    if (err != K_ERR_NONE) {
        printf("current mmheap info check fail, err = %d\r\n", err);
        return -1;
    }
    else {
        printf("current mmheap info:\r\n\tused: %d[0x%08x] free:%d[0x%08x]\r\n\r\n", mmheap_info.used, mmheap_info.used, mmheap_info.free, mmheap_info.free);
        return 0;
    }
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
task2 start!
current mmheap info:
	used: 0[0x00000000] free:32760[0x00007ff8]

create dyn task1 success
task2 is running...
current mmheap info:
	used: 400[0x00000190] free:32352[0x00007e60]

task1 start!
task1 is running...
task2 is running...
current mmheap info:
	used: 400[0x00000190] free:32352[0x00007e60]

task1 is running...
task2 is running...
current mmheap info:
	used: 400[0x00000190] free:32352[0x00007e60]

task1 is running...
task2 is running...
current mmheap info:
	used: 400[0x00000190] free:32352[0x00007e60]

task1 is running...
task2 is running...
current mmheap info:
	used: 400[0x00000190] free:32352[0x00007e60]

task1 is running...
task2 is running...
current mmheap info:
	used: 400[0x00000190] free:32352[0x00007e60]

task2 is running...
current mmheap info:
	used: 0[0x00000000] free:32760[0x00007ff8]

task2 is running...
current mmheap info:
	used: 0[0x00000000] free:32760[0x00007ff8]


*********************************************************/
