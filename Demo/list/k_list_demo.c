/**
 * @brief	TencentOS-tiny˫���������
 * @author	Mculover666
 * @date	2020/6/2
*/
#include <tos_k.h>

typedef struct node
{
	uint8_t  data;
	k_list_t list;
}node_t;

#define LIST_LEN	10

void double_list_test(void *args)
{
	int i;
	
	/* ���ڹ����Զ���ڵ��е�˫��ڵ� */
	k_list_t list;
	
	/* ����10������ڵ� */
	node_t node_pool[LIST_LEN];
	
	/* ��������ʼ���Զ���ڵ���������˫��ڵ� */
	tos_list_init(&list);
	for(i = 0;i < LIST_LEN;i++)
	{
		tos_list_init(&node_pool[i].list);
		node_pool[i].data = i;
	}
	
	/* ����һ������LIST_LEN���ڵ��˫������ */
	for(i = 0; i < LIST_LEN;i++)
	{
		tos_list_add_tail(&node_pool[i].list, &list);
	}
	
	/* ������ӡ���нڵ� */
	k_list_t *cur;
	node_t *n;
	//for(cur = list.next;cur != &list;cur = cur->next)
	TOS_LIST_FOR_EACH(cur, &list)
	{
		n = TOS_LIST_ENTRY(cur, node_t, list);
		printf("n = %d\n", n->data);
	}
	
	return;
}

void application_entry(void *arg)
{
    double_list_test(NULL);
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
n = 0
n = 1
n = 2
n = 3
n = 4
n = 5
n = 6
n = 7
n = 8
n = 9
*********************************************************/
