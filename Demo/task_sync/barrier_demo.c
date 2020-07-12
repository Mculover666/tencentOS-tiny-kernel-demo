/***********************************************************************
 *@file    barrier.c                                              
 *@brief   
 *         ����ʹ��դ�����������ͬ��
 *@author  Mculover666
 *@date    2020��7��12��09:45:21
 *@note    
 *         ������������ҵ�񳡾�:
 *         ����������ʿ����������ʿ��ͷȥѰ��������������Ƭ��
 *         ������ʿ�ҵ��Լ����ǿ�������Ƭʱ������ԭ�صȴ���
 *         ֱ�����е�С��鶼�ҵ����Լ���������Ƭ�󣬲Ÿ��Բ�ȡ��һ���ж���
 *         �ô��뿴�������ʹ��դ����������ģ�͡�
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
    /* ����դ�� */
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
