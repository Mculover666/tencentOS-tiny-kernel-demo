#include <tos_k.h>

k_task_t	task1;
k_task_t	task2;
k_stack_t	task1_stack[256];
k_stack_t	task2_stack[256];

void task1_entry(void *arg)
{
	while(1)
	{
		printf("task1 is running...\r\n");
		tos_task_delay(1000);
	}
}

void task2_entry(void *arg)
{
	while(1)
	{
		printf("task2 is running...\r\n");
		tos_task_delay(1000);
	}
}

void application_entry(void *arg)
{
  //创建任务
  tos_task_create(&task1, "task1", task1_entry, NULL, 2, task1_stack, sizeof(task1_stack), 10);
  tos_task_create(&task2, "task2", task2_entry, NULL, 3, task2_stack, sizeof(task2_stack), 10);
    
  return;
}
