/***********************************************************************
 *@file    barrier.c                                              
 *@brief   
 *         测试使用栅栏进行任务间同步
 *@author  Mculover666
 *@date    2020年7月12日09:45:21
 *@note    
 *         假设有这样的业务场景:
 *         共有三个勇士，此三个勇士分头去寻找三个武器的碎片，
 *         任意勇士找到自己的那块武器碎片时，都在原地等待，
 *         直到所有的小伙伴都找到了自己的武器碎片后，才各自采取下一步行动。
 *         用代码看具体如何使用栅栏来完成这个模型。
***********************************************************************/
#include <tos_k.h>

#define STK_SIZE_TASK_WARRIOR   512

k_stack_t stack_task_warrior_0[STK_SIZE_TASK_WARRIOR];
k_stack_t stack_task_warrior_1[STK_SIZE_TASK_WARRIOR];
k_stack_t stack_task_warrior_2[STK_SIZE_TASK_WARRIOR];

k_task_t task_warrior_0;
k_task_t task_warrior_1;
k_task_t task_warrior_2;

k_barrier_t barrier;

void entry_task_warrior_0(void *arg)
{
    printf("warrior 0: I'm searching the fragment\n");
    tos_task_delay(1000);
    printf("warrior 0: I have done my job, waitting other buddies done their job\n");
    tos_barrier_pend(&barrier);
    printf("warrior 0: all buddies find their fragment, do my next job\n");
}

void entry_task_warrior_1(void *arg)
{
    printf("warrior 1: I'm searching the fragment\n");
    tos_task_delay(1500);
    printf("warrior 1: I have done my job, waitting other buddies done their job\n");
    tos_barrier_pend(&barrier);
    printf("warrior 1: all buddies find their fragment, do my next job\n");
}

void entry_task_warrior_2(void *arg)
{
    printf("warrior 2: I'm searching the fragment\n");
    tos_task_delay(2000);
    printf("warrior 2: I have done my job, waitting other buddies done their job\n");
    tos_barrier_pend(&barrier);
    printf("warrior 2: all buddies find their fragment, do my next job\n");
}

void application_entry(void *arg)
{
    /* 创建栅栏 */
    tos_barrier_create(&barrier, 3);
    
    tos_task_create(&task_warrior_0, "warrior_0", entry_task_warrior_0, NULL,
                                4, stack_task_warrior_0, STK_SIZE_TASK_WARRIOR, 0);
    tos_task_create(&task_warrior_1, "warrior_1", entry_task_warrior_1, NULL,
                                4, stack_task_warrior_1, STK_SIZE_TASK_WARRIOR, 0);
    tos_task_create(&task_warrior_2, "warrior_2", entry_task_warrior_2, NULL,
                                4, stack_task_warrior_2, STK_SIZE_TASK_WARRIOR, 0);
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
warrior 0: I'm searching the fragment
warrior 1: I'm searching the fragment
warrior 2: I'm searching the fragment
warrior 0: I have done my job, waitting other buddies done their job
warrior 1: I have done my job, waitting other buddies done their job
warrior 2: I have done my job, waitting other buddies done their job
warrior 2: all buddies find their fragment, do my next job
warrior 0: all buddies find their fragment, do my next job
warrior 1: all buddies find their fragment, do my next job


*********************************************************/
