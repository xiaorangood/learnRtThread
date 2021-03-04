#include <rtthread.h>

/* 线程栈大小 */
#define IDLE_THREAD_STACK_SIZE      512 

/* 定义空闲线程栈空间 */
ALIGN(RT_ALIGN_SIZE)
static rt_uint8_t rt_thread_stack[IDLE_THREAD_STACK_SIZE];

/* 定义空闲线程的线程控制块 */
struct rt_thread idle;

extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];

rt_ubase_t  rt_idletask_ctr = 0;

/* 定义空闲线程的线程函数 */
void rt_thread_idle_entry(void *parameter)
{
    parameter = parameter;
    while (1)
    {
        rt_idletask_ctr++;
    }
}

/* 初始化空闲线程，系统启动时必须调用*/
void rt_thread_idle_init(void)
{
    /* 初始化线程 */
    rt_thread_init(&idle,
                   "idle",
                   rt_thread_idle_entry,
                   RT_NULL,
                   &rt_thread_stack[0],
                   sizeof(rt_thread_stack),
                   RT_THREAD_PRIORITY_MAX - 1);

    /* 将线程插入到就绪列表 */
//    rt_list_insert_before( &(rt_thread_priority_table[RT_THREAD_PRIORITY_MAX-1]),&(idle.tlist) );
    rt_thread_startup(&idle);
}

















