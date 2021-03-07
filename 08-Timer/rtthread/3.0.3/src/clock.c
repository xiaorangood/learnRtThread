#include <rtdef.h>
#include <rthw.h>
#include <rtservice.h>

static rt_tick_t rt_tick = 0;
extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];
extern rt_uint32_t rt_thread_ready_priority_group;

void rt_tick_increace(void)
{
    ++rt_tick;
    
    rt_timer_check();
}

rt_tick_t rt_tick_get(void)
{
    /* return the global tick */
    return rt_tick;
}

