/**
 * @brief	TencentOS-tiny定时器测试
 * @author	Mculover666
 * @date	2020/6/5
*/
#include <tos_k.h>


k_timer_t timer1;
k_timer_t timer2;

void timer1_callback(void *args)
{
	printf("timer1 timeout!\r\n");
	
	return;
}
void timer2_callback(void *args)
{
	printf("timer2 timeout!\r\n");
	
	return;
}


void application_entry(void *arg)
{

	k_err_t ret;
	
    // 周期触发
	ret = tos_timer_create(&timer1,
					 3000,
					 3000,
					 timer1_callback,
					 NULL,
					 TOS_OPT_TIMER_PERIODIC);
	if(ret != K_ERR_NONE)
	{
		printf("timer 1 create fail, err = %d.\r\n", ret);
	}
	
	
    // 单次触发
	ret = tos_timer_create(&timer2,
					 3000,
					 0,
					 timer2_callback,
					 NULL,
					 TOS_OPT_TIMER_ONESHOT);
	if(ret != K_ERR_NONE)
	{
		printf("timer 2 create fail, err = %d.\r\n", ret);
	}
	
	//启动定时器
	tos_timer_start(&timer1);
	tos_timer_start(&timer2);
	
    while (1) {
        //printf("This is a demo task,please use your task entry!\r\n");
        tos_task_delay(1000);
    }
}
