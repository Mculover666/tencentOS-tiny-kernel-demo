/********************************************************
 *@file    mutex_dyn_demo_1.c                                                      
 *@brief
 *         使用动态互斥锁对共享资源进行保护
 *@author  Mculover666
 *@date    2021年3月10日20:42:24
*********************************************************/
#include "tos_k.h"

#define TASK1_STACK_SIZE    256
#define TASK1_PRIO  4
k_task_t task1;
k_stack_t task1_stack[TASK1_STACK_SIZE];

#define TASK2_STACK_SIZE    256
#define TASK2_PRIO  5
k_task_t task2;
k_stack_t task2_stack[TASK2_STACK_SIZE];

k_mutex_t *mutex;
uint8_t share_number = 0;   //共享数据

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

void task1_entry(void *arg)
{
    int n;
    k_err_t err;
    
    printf("task1 start...\r\n");

    for (n = 0; n < 10; n++) {
        err = tos_mutex_pend(mutex);
        if (err != K_ERR_NONE) {
            printf("task1 get mutex fail\r\n");
        }
        printf("task1 get mutex success\r\n");
        
        share_number += 1;
        printf("task1: share number is %d\r\n", share_number);
        
        err = tos_mutex_post(mutex);
        if (err != K_ERR_NONE) {
            printf("task1 release mutex\r\n");
        }
        printf("task1 release mutex success\r\n");
        
        tos_task_delay(500);
    }
}

void task2_entry(void *arg)
{
    int n;
    k_err_t err;
    
    printf("task2 start...\r\n");
    
    for (n = 0; n < 10; n++) {
        err = tos_mutex_pend(mutex);
        if (err != K_ERR_NONE) {
            printf("task2 get mutex fail\r\n");
        }
        printf("task2 get mutex success\r\n");
        
        HAL_Delay(5000);
        
        tos_mutex_post(mutex);
        if (err != K_ERR_NONE) {
            printf("task2 release mutex\r\n");
        }
        printf("task2 release mutex success\r\n");
        
        //tos_task_delay(1000);
    }
    
    /* 删除互斥锁 */
    err = tos_mutex_destroy(mutex);
    if (err != K_ERR_NONE) {
        printf("mutex destroy fail, err is %d\r\n", err);
    } else {
        printf("mutex destroy success\r\n");
    }
    
    list_mmheap_info();
}

void application_entry(void *arg)
{
    k_err_t err;
    
    list_mmheap_info();
    
    /* 创建互斥锁 */
    err = tos_mutex_create_dyn(&mutex);
    if (err != K_ERR_NONE) {
        printf("mutex create fail, err is %d\r\n", err);
        return;
    } else {
        printf("mutex create success\r\n");
    }
    
    list_mmheap_info();
    
    /* 创建任务1 */
    err = tos_task_create(&task1, "task1", task1_entry, NULL, TASK1_PRIO, task1_stack, sizeof(task1_stack), 10);
    if (err != K_ERR_NONE) {
        printf("task1 create fail, err is %d\r\n", err);
        return;
    } else {
        printf("task1 create success\r\n");
    }
    
    err = tos_task_create(&task2, "task2", task2_entry, NULL, TASK2_PRIO, task2_stack, sizeof(task2_stack), 10);
    if (err != K_ERR_NONE) {
        printf("task2 create fail, err is %d\r\n", err);
        return;
    } else {
        printf("task2 create success\r\n");
    }

    return;
}

/********************************************************
result(将锁的使用屏蔽):

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
mutex create success
task1 create success
task2 create success
task1 start...
task1: share number is 1
task2 start...
task2: share number is 3
task1: share number is 4
task2: share number is 6
task1: share number is 7
task2: share number is 9
task1: share number is 10
task2: share number is 12
task1: share number is 13
task2: share number is 15
task1: share number is 16
task2: share number is 18
task1: share number is 19
task2: share number is 21
task1: share number is 22
task2: share number is 24
task1: share number is 25
task2: share number is 27
task1: share number is 28
task2: share number is 30

result(将锁的使用打开):

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
mutex create success
task1 create success
task2 create success
task1 start...
task1: share number is 1
task2 start...
task1: share number is 2
task1: share number is 3
task1: share number is 4
task1: share number is 5
task1: share number is 6
task1: share number is 7
task1: share number is 8
task1: share number is 9
task1: share number is 10
task2: share number is 12
task2: share number is 14
task2: share number is 16
task2: share number is 18
task2: share number is 20
task2: share number is 22
task2: share number is 24
task2: share number is 26
task2: share number is 28
task2: share number is 30

*********************************************************/
