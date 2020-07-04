/********************************************************
 *@file    irq_demo_1.c                                                      
 *@brief   
 *         task1�����ȼ���ִ�У�1s��ӡһ��
 *         task2�����ȼ���1s��ӡһ��
 *         ���԰����ж��Ƿ�����
 *@author  Mculover666
 *@date    2020��7��4��17:15:11
*********************************************************/

#include <tos_k.h>

k_task_t	task1;
k_task_t	task2;
k_stack_t	task1_stack[256];
k_stack_t	task2_stack[256];

/* USER CODE BEGIN 2 */
/**
 * @brief    EXIT�жϻص�����
 * @param GPIO_Pin ���� �����жϵ�����
 * @retval    none
*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
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
    
     /* task1����ѭ�����ж�֮��᷵�ص��˴���������2���� */
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
    tos_task_create(&task2, "task2", task2_entry, NULL, 3, task2_stack, sizeof(task2_stack), 10);

    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
task1 start...
task1 is running...
task2 start...
task2 is running...
key 2 press!
task1 is running...
task2 is running...
task1 is running...
task2 is running...
*********************************************************/
