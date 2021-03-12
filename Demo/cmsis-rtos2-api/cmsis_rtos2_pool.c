/********************************************************************
 *@file    cmsis_rtos2_pool.c                                                     
 *@brief   测试使用CMSIS-RTOS v2标准API使用静态内存池
 *@author  Mculover666
 *@date    2021年3月12日19:04:31
 *@note
 *         使用 CMSIS-RTOS v2.1.3标准
*********************************************************************/

#include <cmsis_os2.h>

typedef struct blk_st {
    int   id;
    char* payload;
} blk_t;

#define MMBLK_BLK_NUM 10

osMemoryPoolId_t mem_pool_id;

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
    
    blk_t *ptr = NULL;
    osStatus_t err;
    
    /* 打印出一个块的大小 */
    printf("block size is %d bytes\r\n", sizeof(blk_t));
    
    /* 申请一个块 */
    ptr = osMemoryPoolAlloc(mem_pool_id, 0);
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
    err = osMemoryPoolFree(mem_pool_id, ptr);
    if (err != osOK) {
        printf("a mmblk free fail, err = %d\r\n", err);
        return;
    }
    else {
        printf("a mmblk free success\r\n");
    }
    
    /* 销毁内存池 */
    err  = osMemoryPoolDelete(mem_pool_id);
    if (err != osOK) {
        printf("mmblk pool delete fail\r\n");
        return;
    }
    else {
        printf("mmblk pool delete success\r\n");
    }
    
    list_mmheap_info();
    
    while (1) {
        tos_task_delay(1000);
    }
}

#define STK_SIZE_TASK1      1024
osThreadDef(task1, osPriorityNormal, 1, STK_SIZE_TASK1);

void application_entry(void *arg)
{
    list_mmheap_info();
    
    //初始化静态内存池
    mem_pool_id = osMemoryPoolNew(MMBLK_BLK_NUM, sizeof(blk_t), NULL);
    if (mem_pool_id == NULL) {
        printf("mmblk pool create fail\r\n");
        return;
    }
    else {
        printf("mmblk pool create success\r\n");
    }
    
    list_mmheap_info();

    //创建任务
    osThreadNew(task1_entry, NULL, osThread(task1));

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
