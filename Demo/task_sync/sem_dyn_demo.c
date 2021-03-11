/********************************************************
 *@file    sem_dyn_demo.c                                              
 *@brief   
 *         ����ʹ�ö�̬�ź������������ͬ��
 *@author  Mculover666
 *@date    2021��3��10��16:21:14
*********************************************************/

#include <tos_k.h>

k_task_t	task1;
k_task_t	task2;
k_stack_t	task1_stack[256];
k_stack_t	task2_stack[256];

k_sem_t *sync_sem;

/**
 *@brief   ��ӡ��ǰmmeheapʹ�����
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
    k_err_t err;
    
    printf("task1 start\r\n");
    while(1)
    {
        printf("task1 is waiting sync sem forever...\r\n");
        err = tos_sem_pend(sync_sem, TOS_TIME_FOREVER);
        if (err != K_ERR_NONE) {
            printf("task1 get sync sem fail, err is %d!\r\n", err);
            return;
        }
        printf("task1 get sync sem success!\r\n");
    }
}

void task2_entry(void *arg)
{
    int n;
    k_err_t err;
    
    printf("task2 start...\r\n");
    for (n = 0; n < 10; n++) {
        printf("task2 will post sync sem...\r\n\r\n");
        tos_sem_post(sync_sem);
        tos_sleep_ms(1000);
    }
    
    err = tos_sem_destroy(sync_sem);
    if (err != K_ERR_NONE) {
        printf("sem destroy fail\r\n");
    }
    printf("sem destroy success\r\n");
    
    list_mmheap_info();
}

void application_entry(void *arg)
{
    k_err_t err;
    
    list_mmheap_info();
    
    //�����ź���
    err = tos_sem_create_max_dyn(&sync_sem, 0, 1);
    if (err != K_ERR_NONE) {
        printf("sync sem create fail\r\n");
        return;
    }
    printf("sync sem create success\r\n");
    
    list_mmheap_info();
    
    //��������
    tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 10);
    printf("task1 create success\r\n");
    tos_task_create(&task2, "task2", task2_entry, NULL, 3, task2_stack, sizeof(task2_stack), 10);
    printf("task2 create success\r\n");
    
    while (1) {
        printf("task1 and task2 finish!\r\n");
        tos_task_delay(1000);
    
    }
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
sync sem create success
task1 create success
task2 create success
task1 start

task1 is waiting sync sem forever...
task2 start...(<------��ʱtask1�����ȴ��ź�����task2�ŵ���ִ��)
task2 will post sync sem...
task1 get sync sem!(<----------��ʱtask2�ͷ��ź���������task1ִ��)

task1 is waiting sync sem forever...
task2 will post sync sem...
task1 get sync sem!

task1 is waiting sync sem forever...
task2 will post sync sem...
task1 get sync sem!

task1 is waiting sync sem forever...
task2 will post sync sem...
task1 get sync sem!

task1 is waiting sync sem forever...
task2 will post sync sem...
task1 get sync sem!

task1 is waiting sync sem forever...

*********************************************************/
