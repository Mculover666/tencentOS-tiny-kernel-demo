/************************************************************************
 *@file    task_demo_5.c                                                      
 *@brief
 *         创建一个静态任务、一个动态任务从，测试系统提供的打印所有任务信息API
 *
 *@note    此Demo中使用到了动态Task，需要使能 TOS_CFG_TASK_DYNAMIC_CREATE_EN 
 *@author  Mculover666
 *@date    2020年12月25日11:25:57
*************************************************************************/

#include <tos_k.h>

k_task_t	*task1;
k_task_t    task2;
k_stack_t	task2_stack[256];

void task1_entry(void *arg)
{
    printf("task1 start!\r\n");
    
    while (1) {
        printf("task1 is running...\r\n");
        
        /* 打印系统中所有任务信息 */
        tos_task_info_display();
        
        tos_task_delay(2000);
    }
}

void task2_entry(void *arg)
{
    printf("task2 start!\r\n");

    while (1) {
        printf("task2 is running...\r\n");
        
        /* 打印系统中所有任务信息 */
        tos_task_info_display();
              
        tos_task_delay(2000);
    }
}

void application_entry(void *arg)
{
    k_err_t err;
    
    //创建任务task1
     err = tos_task_create_dyn(&task1, "task1", task1_entry, NULL, 3, 256, 10);
    
    if (err != K_ERR_NONE) {
        printf("create dyn task1 fail, err is %d\r\n", err);
        return;
    } else {
        printf("create dyn task1 success\r\n");
    }
    
    //创建任务task2
    tos_task_create(&task2, "task2", task2_entry, NULL, 2, task2_stack, sizeof(task2_stack), 10);
    printf("create task2 success\r\n");

    return;
}


/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
create dyn task1 success
task2 start!
task2 is running...
tsk name: task2
tsk stat: RUNNING
stk size: 256
stk base: 0x20001210
stk top : 0x20001310

tsk name: task1
tsk stat: READY
stk size: 256
stk base: 0x20001690
stk top : 0x20001790

tsk name: application_entry
tsk stat: READY
stk size: 4096
stk base: 0x20000100
stk top : 0x20001100

tsk name: idle
tsk stat: READY
stk size: 512
stk base: 0x200013f8
stk top : 0x200015f8

create task2 success
task1 start!
task1 is running...
tsk name: task2
tsk stat: SLEEP
stk size: 256
stk base: 0x20001210
stk top : 0x20001310

tsk name: task1
tsk stat: RUNNING
stk size: 256
stk base: 0x20001690
stk top : 0x20001790

tsk name: idle
tsk stat: READY
stk size: 512
stk base: 0x200013f8
stk top : 0x200015f8

task2 is running...
tsk name: task2
tsk stat: RUNNING
stk size: 256
stk base: 0x20001210
stk top : 0x20001310

tsk name: task1
tsk stat: SLEEP
stk size: 256
stk base: 0x20001690
stk top : 0x20001790

tsk name: idle
tsk stat: READY
stk size: 512
stk base: 0x200013f8
stk top : 0x200015f8
*********************************************************/
