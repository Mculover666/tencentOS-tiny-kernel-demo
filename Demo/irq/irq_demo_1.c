/********************************************************
 *@file    irq_demo_1.c                                               
 *@brief   
 *         task1�����ȼ���ִ�У�Ȼ�����
 *         task2�����ȼ�����ѭ��ִ�д�ӡ
 *         1. ���԰����ж��Ƿ�����
 *         2. ���жϳ����лָ�task1�����������ã�ʵ��Ӧ���б�������д����
 *            �����жϷ���ʱ�Ƿ���Ե��ȵ������ȼ�����ִ��
 *@author  Mculover666
 *@date    2020��7��5��18:08:38
*********************************************************/

#include <tos_k.h>

k_task_t	task1;
k_task_t	task2;
k_stack_t	task1_stack[256];
k_stack_t	task2_stack[256];

/* USER CODE BEGIN 2 */
/**
 * @brief    EXIT�жϻص�����
 * @param    GPIO_Pin ���� �����жϵ�����
 * @retval   none
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    /* �ָ������ȼ�����task1����Ϊ�����ж��У����Բ��ᷢ������ */
    tos_task_resume(&task1);
    printf("task1 is resumed\r\n");
    
    /* �ж��ĸ����Ŵ������ж� */
    switch(GPIO_Pin)
    {
        case GPIO_PIN_2:
            /* ����GPIO2�������ж� */
            printf("key 2 press!\r\n");
            break;
        default:
            break;
    }
}
/* USER CODE END 2 */


void task1_entry(void *arg)
{
    printf("task1 start...\r\n");
    printf("task1 will be suspend\r\n");
    tos_task_suspend(&task1);
    while(1)
    {
        printf("task1 is running...\r\n");
        tos_task_delay(1000);
    }
}

void task2_entry(void *arg)
{
    printf("task2 start...\r\n");
    
    while(1)
    {
        printf("task2 is running...\r\n");
        tos_task_delay(1000);
    }
}

void application_entry(void *arg)
{
    //��������
    tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 0);
    printf("task1 create success\r\n");
    tos_task_create(&task2, "task2", task2_entry, NULL, 3, task2_stack, sizeof(task2_stack), 10);
    printf("task2 create success\r\n");
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
task1 create success
task2 create success
task1 start...
task1 will be suspend
task2 start...
task2 is running...
task2 is running...
task2 is running...
task1 is resumed
key 2 press!
task1 is running...��ͨ���˴����Կ����жϷ��غ󣬸����ȼ�����ִ�У�
task2 is running...
task1 is running...
task2 is running...
*********************************************************/
