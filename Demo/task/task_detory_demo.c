/********************************************************
 *@file    task_detory_demo.c                                                      
 *@brief   ����������ں����˳�֮���Ƿ��Զ�����
 *@author  Mculover666
 *@date    2021��9��1��14:11:33
*********************************************************/

#include <tos_k.h>

k_task_t	task1;
k_stack_t	task1_stack[256];

void task1_entry(void *arg)
{
    printf("task1 start!\r\n");
    
    printf("task1 end!\r\n");
}

void application_entry(void *arg)
{
    k_err_t err;
    
    tos_task_info_display();
    
    err = tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 10);
    if (err != K_ERR_NONE) {
        printf("task1 create fail, err is %d\r\n", err);
    }
    printf("task1 create success\r\n");
    
    tos_task_info_display();
    
    // for task 1 running
    tos_sleep_ms(2000);
    
    tos_task_info_display();

    return;
}

/********************************************************
result:



*********************************************************/
