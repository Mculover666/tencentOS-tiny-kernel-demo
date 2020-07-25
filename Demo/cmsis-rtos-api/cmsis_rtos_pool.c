/********************************************************************
 *@file    cmsis_rtos_pool.c                                                     
 *@brief   测试使用CMSIS-RTOS 标准API使用静态内存池
 *@author  Mculover666
 *@date    2020年7月25日20:15:49
 *@note
 *         使用 CMSIS-RTOS v1.02标准
*********************************************************************/

#include <cmsis_os.h>

typedef struct blk_st {
    int   id;
    char* payload;
} blk_t;

#define MMBLK_BLK_NUM 10

osPoolDef (MemPool, MMBLK_BLK_NUM, blk_t);
osPoolId mem_pool_id;

void task1_entry(void *arg)
{   
    
    blk_t *ptr = NULL;
    osStatus err;
    
    /* 打印出一个块的大小 */
    printf("block size is %d bytes\r\n", sizeof(blk_t));
    
    /* 申请一个块 */
    ptr = osPoolAlloc(mem_pool_id);
    if (ptr == NULL) {
        printf("a mmblk alloc fail\r\n");
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
    err = osPoolFree(mem_pool_id, ptr);
    if (err != osOK) {
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

#define STK_SIZE_TASK1      1024
osThreadDef(task1_entry, osPriorityNormal, 1, STK_SIZE_TASK1);

void application_entry(void *arg)
{
    //初始化静态内存池
    mem_pool_id = osPoolCreate(osPool(MemPool));
    if (mem_pool_id == NULL) {
        printf("mmblk pool create fail\r\n");
        return;
    }
    else {
        printf("mmblk pool create success\r\n");
    }

    //创建任务
    osThreadCreate(osThread(task1_entry), NULL);

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
