/*********************************************************************
 *@file    countdownlatch_demo.c                                              
 *@brief   
 *         ����ʹ�ü��������������ͬ��
 *@author  Mculover666
 *@date    2020��7��12��09:40:31
 *@note    
 *         ������������ҵ�񳡾�:
 *         ����������ʿ����������ʿ��ͷȥѰ��������������Ƭ��
 *         ֻ����������ʿ���ҵ���Ƭ�󣬷�ʦ���ܽ�������Ƭ�ϳ�Ϊ������
 *         �ô��뿴�������ʹ�ü�������������ģ�͡�
*******************************************************************/
#include <tos_k.h>

#define STK_SIZE_TASK_WIZARD    512
#define STK_SIZE_TASK_WARRIOR   256

k_stack_t stack_task_wizard[STK_SIZE_TASK_WIZARD];
k_stack_t stack_task_warrior_0[STK_SIZE_TASK_WARRIOR];
k_stack_t stack_task_warrior_1[STK_SIZE_TASK_WARRIOR];
k_stack_t stack_task_warrior_2[STK_SIZE_TASK_WARRIOR];

k_task_t task_wizard;
k_task_t task_warrior_0;
k_task_t task_warrior_1;
k_task_t task_warrior_2;

k_countdownlatch_t countdownlatch;

void entry_task_warrior_0(void *arg)
{
    printf("warrior 0: I have done my job\n");
    tos_countdownlatch_post(&countdownlatch);
}

void entry_task_warrior_1(void *arg)
{
    printf("warrior 1: I have done my job\n");
    tos_countdownlatch_post(&countdownlatch);
}

void entry_task_warrior_2(void *arg)
{
    printf("warrior 2: I have done my job\n");
    tos_countdownlatch_post(&countdownlatch);
}

void entry_task_wizard(void *arg)
{
    printf("wizard: I will set 3 warriors to find the fragments\n");
    tos_countdownlatch_create(&countdownlatch, 3);
    (void)tos_task_create(&task_warrior_0, "warrior_0", entry_task_warrior_0, NULL,
                                4, stack_task_warrior_0, STK_SIZE_TASK_WARRIOR, 0);
    (void)tos_task_create(&task_warrior_1, "warrior_1", entry_task_warrior_1, NULL,
                                4, stack_task_warrior_1, STK_SIZE_TASK_WARRIOR, 0);
    (void)tos_task_create(&task_warrior_2, "warrior_2", entry_task_warrior_2, NULL,
                                4, stack_task_warrior_2, STK_SIZE_TASK_WARRIOR, 0);
    printf("wizard: now warriors are on their way, I will wait here until they all done the job\n");
    tos_countdownlatch_pend(&countdownlatch);
    printf("wizard: the warriors all have done their jobs, let's make the weapon\n");
}

void application_entry(void *arg)
{
   tos_task_create(&task_wizard, "wizard", entry_task_wizard, NULL,
                            3, stack_task_wizard, STK_SIZE_TASK_WIZARD, 0);
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
wizard: I will set 3 warriors to find the fragments
wizard: now warriors are on their way, I will wait here until they all done the job
warrior 0: I have done my job
warrior 1: I have done my job
warrior 2: I have done my job
wizard: the warriors all have done their jobs, let's make the weapon

*********************************************************/
