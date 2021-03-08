#include <rtdef.h>
#include <rthw.h>
#include <rtservice.h>

static rt_tick_t rt_tick = 0;
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
extern rt_uint32_t rt_thread_ready_priority_group;

void rt_tick_increace(void)
{
    rt_thread_t thread;

    ++rt_tick;
    
    /* 获得当前线程控制块 */
    thread = rt_thread_self();
    /* 时间片递减 */
    --thread->remaining_tick;
    /* 如果时间片用完，则重置时间片，然后让出处理器 */
    if(thread->remaining_tick == 0)
    {
        /* 重置时间片 */
        thread->remaining_tick = thread->init_tick;
        /* 让出处理器 */
        rt_thread_yield();
    }
    
    
    rt_timer_check();
}

rt_tick_t rt_tick_get(void)
{
    /* return the global tick */
    return rt_tick;
}

