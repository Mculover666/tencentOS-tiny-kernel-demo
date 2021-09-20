/**
 * @brief	TencentOS-tiny�����������
 * @author	Mculover666
 * @date	2021/9/20
*/
#include <tos_k.h>

typedef struct node
{
	uint8_t  data;
	k_slist_t list;
}node_t;

#define LIST_LEN	10

void single_list_test()
{
	int i;
	
	/* ͷ��� */
	k_slist_t slist;
	
	/* ����10������ڵ� */
	node_t node_pool[LIST_LEN];
    
    /* ��ʼ������ͷ��� */
    tos_slist_init(&slist);
	
	/* ����һ������LIST_LEN���ڵ��˫������ */
	for(i = 0; i < LIST_LEN;i++)
	{
		node_pool[i].data = i;
        
        // ͷ�巨
        tos_slist_add_head(&node_pool[i].list, &slist);
	}
	
	/* ������ӡ���нڵ� */
	k_slist_t *cur;
	node_t *n;
	//for(cur = slist.next;cur != NULL;cur = cur->next)
	TOS_SLIST_FOR_EACH(cur, &slist)
	{
		n = TOS_SLIST_ENTRY(cur, node_t, list);
		printf("n = %d\n", n->data);
	}
	
	return;
}

void application_entry(void *arg)
{
    single_list_test();
    
    return;
}

/********************************************************
result:

TencentOS-tiny Port on STM32L431RCT6 By Mculover666
n = 9
n = 8
n = 7
n = 6
n = 5
n = 4
n = 3
n = 2
n = 1
n = 0
*********************************************************/
