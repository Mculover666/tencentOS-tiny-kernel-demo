/********************************************************************
 *@file    mmheap_demo_1.c                                                      
 *@brief   ���Ի���mmblk��̬�ڴ�ع������
 *@author  Mculover666
 *@date    2020��7��25��16:15:25
*********************************************************************/

#include <tos_k.h>

k_task_t	task1;
k_stack_t	task1_stack[512];

typedef struct blk_st {
    int   id;
    char* payload;
} blk_t;

#define BLK_NUM 10

k_mmblk_pool_t mmblk_pool;
uint8_t mmblk_pool_buffer[BLK_NUM * sizeof(blk_t)];

void task1_entry(void *arg)
{   
    blk_t *ptr = NULL;
    k_err_t err;
    
    /* ��ӡ��һ����Ĵ�С */
    printf("block size is %d bytes\r\n", sizeof(blk_t));
    
    /* ����һ���� */
    err = tos_mmblk_alloc(&mmblk_pool, (void*)&ptr);
    if (err != K_ERR_NONE) {
        printf("a mmblk alloc fail, err = %d\r\n", err);
        return;
    }
    else {
        printf("a mmblk alloc success\r\n");
    }
    
    /* ʹ�øÿ� */
    ptr->id = 1;
    ptr->payload = "hello";
    printf("mmblk id:%d payload:%s\r\n", ptr->id, ptr->payload);
    
    /* ʹ�����֮���ͷ� */
    err = tos_mmblk_free(&mmblk_pool, ptr);
    if (err != K_ERR_NONE) {
        printf("a mmblk free fail, err = %d\r\n", err);
        return;
    }
    else {
        printf("a mmblk free success\r\n");
    }
    
    while (1) {
        tos_task_delay(1000);
    }
}

void application_entry(void *arg)
{   
    k_err_t err;
    
    //��ʼ����̬�ڴ��
    err = tos_mmblk_pool_create(&mmblk_pool, mmblk_pool_buffer, BLK_NUM, sizeof(blk_t));
    if (err != K_ERR_NONE) {
        printf("mmblk pool create fail, err = %d\r\n", err);
        return;
    }
    else {
        printf("mmblk pool create success\r\n");
    }

    //��������
    tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 10);

    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
mmblk pool create success
block size is 8 bytes
a mmblk alloc success
mmblk id:1 payload:hello
a mmblk free success

*********************************************************/
