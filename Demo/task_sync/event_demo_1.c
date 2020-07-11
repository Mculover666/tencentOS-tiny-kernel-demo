/********************************************************
 *@file    event_demo_1.c                                              
 *@brief   
 *         ����ʹ���¼����������ͬ��
 *@author  Mculover666
 *@date    2020��7��11��17:45:28
 *@note    
 *         һ������ȴ�����¼��е�һ��
*********************************************************/

#include <tos_k.h>

k_task_t	task1;
k_task_t	task2;
k_stack_t	task1_stack[256];
k_stack_t	task2_stack[256];

k_event_t   sync_event;

//�����¼��б�
const k_event_flag_t event_eeny     = (k_event_flag_t)(1 << 0);
const k_event_flag_t event_meeny    = (k_event_flag_t)(1 << 1);
const k_event_flag_t event_miny     = (k_event_flag_t)(1 << 2);
const k_event_flag_t event_moe      = (k_event_flag_t)(1 << 3);

//����ƥ�䵽���¼�ֵ
k_event_flag_t  flag_match;

void task1_entry(void *arg)
{
    k_err_t err;
    
    while(1) {
        //�ȴ��ĸ��¼��е��κ�һ��
        err = tos_event_pend(&sync_event, 
                            event_eeny | event_meeny | event_miny | event_moe, 
                            &flag_match,
                            TOS_TIME_FOREVER,
                            TOS_OPT_EVENT_PEND_ANY | TOS_OPT_EVENT_PEND_CLR);
        
        if (err == K_ERR_NONE) {
            // ���¼�����жϾ������ĸ��¼�
            if (flag_match == event_eeny) {
                printf("eeny comes\n");
            }
            if (flag_match == event_meeny) {
                printf("meeny comes\n");    
            }
            if (flag_match == event_miny) {
                printf("miny comes\n");
            }
            if (flag_match == event_moe) {
                printf("moe comes\n");
            }
            if (flag_match == (event_eeny | event_meeny | event_miny | event_moe)) {
                printf("all come\n");
            }
        }
    }
}

void task2_entry(void *arg)
{
    int i = 1;

    while (K_TRUE) {
        if (i % 2 == 0) {
            printf("task2_trigger:\n");
            printf("eeny will come\n");
            // ����eeny�¼���task1�ᱻ����
            tos_event_post(&sync_event, event_eeny);
        }
        if (i % 3 == 0) {
            printf("task2_trigger:\n");
            printf("meeny will come\n");
            // ����eeny�¼���task1�ᱻ����
            tos_event_post(&sync_event, event_meeny);
        }
        if (i % 4 == 0) {
            printf("task2_trigger:\n");
            printf("miny will come\n");
            // ����eeny�¼���task1�ᱻ����
            tos_event_post(&sync_event, event_miny);
        }
        if (i % 5 == 0) {
            printf("task2_trigger:\n");
            printf("moe will come\n");
            // ����eeny�¼���task1�ᱻ����
            tos_event_post(&sync_event, event_moe);
        }
        if (i % 6 == 0) {
            printf("task2_trigger:\n");
            printf("all will come\n");
            // ͬʱ�����ĸ��¼�����Ϊtask1�����ȼ�����task2���������task1�ᱻ����
            tos_event_post(&sync_event, event_eeny | event_meeny | event_miny | event_moe);
        }
        tos_sleep_ms(2000);
        ++i;
    }
}

void application_entry(void *arg)
{
    //�����¼���
    tos_event_create(&sync_event, (k_event_flag_t)0u);
    
    //��������
    tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 10);
    tos_task_create(&task2, "task2", task2_entry, NULL, 3, task2_stack, sizeof(task2_stack), 10);
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
task2_trigger:
eeny will come
eeny comes
task2_trigger:
meeny will come
meeny comes
task2_trigger:
eeny will come
eeny comes
task2_trigger:
miny will come
miny comes
task2_trigger:
moe will come
moe comes
task2_trigger:
eeny will come
eeny comes
task2_trigger:
meeny will come
meeny comes
task2_trigger:
all will come
all come
task2_trigger:
eeny will come
eeny comes
task2_trigger:
miny will come
miny comes

*********************************************************/
