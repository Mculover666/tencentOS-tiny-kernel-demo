/********************************************************************
 *@file    mmheap_demo_1.c                                                      
 *@brief   测试基于mmblk静态内存池管理机制
 *@author  Mculover666
 *@date    2020年7月25日16:15:25
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
    
    /* 打印出一个块的大小 */
    printf("block size is %d bytes\r\n", sizeof(blk_t));
    
    /* 申请一个块 */
    err = tos_mmblk_alloc(&mmblk_pool, (void*)&ptr);
    if (err != K_ERR_NONE) {
        printf("a mmblk alloc fail, err = %d\r\n", err);
        return;
    }
    else {
        printf("a mmblk alloc success\r\n");
    }
    
    /* 使用该块 */
    ptr->id = 1;
    ptr->payload = "hello";
    printf("mmblk id:%d payload:%s\r\n", ptr->id, ptr->payload);
    
    /* 使用完毕之后释放 */
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
    
    //初始化静态内存池
    err = tos_mmblk_pool_create(&mmblk_pool, mmblk_pool_buffer, BLK_NUM, sizeof(blk_t));
    if (err != K_ERR_NONE) {
        printf("mmblk pool create fail, err = %d\r\n", err);
        return;
    }
    else {
        printf("mmblk pool create success\r\n");
    }

    //创建任务
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
