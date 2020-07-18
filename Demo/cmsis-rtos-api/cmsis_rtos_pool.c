/********************************************************************
 *@file    cmsis_rtos_pool.c                                                     
 *@brief   测试使用CMSIS-RTOS 标准API使用静态内存池
 *@author  Mculover666
 *@date    2020年7月17日17:41:49
 *@note
 *         使用 CMSIS-RTOS v1.02标准
*********************************************************************/

#include <cmsis_os.h>

#define STK_SIZE_TASK1      1024

#define MMBLK_BLK_NUM       5

//typedef struct {
//  uint8_t Idx;
//} MEM_BLOCK;

#define MEM_BLOCK uint8_t
 
osPoolDef (MemPool, MMBLK_BLK_NUM, MEM_BLOCK);

//记录分配到的地址
void *p[MMBLK_BLK_NUM] = {NULL};


void task1_entry(void *arg)
{
    osPoolId   MemPool_Id;
    MEM_BLOCK *addr;
    osStatus   status;
    int i = 0;
    
    MemPool_Id = osPoolCreate (osPool (MemPool));
    if(MemPool_Id != NULL)
    {
        printf("MeMPool create success!\r\n");
        for(i = 0; i < MMBLK_BLK_NUM;i++)
        {
            p[i] = (MEM_BLOCK *)osPoolCAlloc (MemPool_Id);
            if (p[i] != NULL)
            {
                  printf("mem block calloc success, %d\r\n", i);
                //addr = NULL;
//                  status = osPoolFree (MemPool_Id, addr);
//                  if (status==osOK)
//                   {
//                        printf("mem block free success, %d\r\n", i);
//                   }
            }
            else
            {
                 printf("mem block calloc fail, %d\r\n", i);
                 break;
            }
        }
    }
    else
    {
         printf("MeMPool create fail!\r\n");
    }
}
osThreadDef(task1_entry, osPriorityNormal, 1, STK_SIZE_TASK1);


void application_entry(void *arg)
{

    osThreadCreate(osThread(task1_entry), NULL);
    
    return;
}

/********************************************************
result:


*********************************************************/
