/********************************************************************
 *@file    mmheap_demo_1.c                                                      
 *@brief   ���Ի���mmheap�ڴ�ѹ����㷨�Ķ�̬�ڴ�������
 *@author  Mculover666
 *@date    2020��7��25��08:23:03
*********************************************************************/

#include <tos_k.h>

k_task_t	task1;
k_stack_t	task1_stack[512];

/**
 *@brief   ��ӡ��ǰmmeheapʹ�����
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
    void *ptr = NULL;
    size_t size;
    
    /* ������С�����ֵ */
    printf("K_MMHEAP_BLK_SIZE_MAX is %d(0x%08x) bytes\r\n\r\n", K_MMHEAP_BLK_SIZE_MAX, K_MMHEAP_BLK_SIZE_MAX);
    
    /* ��ӡ��ǰ�ڴ�ʹ����� */
    list_mmheap_info();
    
    /* ����һ���ڴ�ʹ�� */
    size = 128;
    ptr = tos_mmheap_alloc(size);
    if (ptr == NULL) {
        printf("%d bytes mem alloc fail\r\n", size);
    }
    else {
        printf("%d bytes mem alloc success, ptr is 0x%08x\r\n\r\n", size, (uint32_t)ptr);
    }
    
    /* ��ӡ��ǰ�ڴ�ʹ����� */
    list_mmheap_info();
    
    /* �ͷ�������ڴ� */
    tos_mmheap_free(ptr);
    printf("mem free success\r\n\r\n");
    
    /* ��ӡ��ǰ�ڴ�ʹ����� */
    list_mmheap_info();
    
    while (1) {
        tos_task_delay(1000);
    }
}

void application_entry(void *arg)
{   
    //��������
    tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 10);

    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
K_MMHEAP_BLK_SIZE_MAX is 1073741824(0x40000000) bytes

current mmheap info:
	used: 0[0x00000000] free:32760[0x00007ff8]

128 bytes mem alloc success, ptr is 0x200016dc

current mmheap info:
	used: 128[0x00000080] free:32628[0x00007f74]

mem free success

current mmheap info:
	used: 0[0x00000000] free:32760[0x00007ff8]

*********************************************************/
