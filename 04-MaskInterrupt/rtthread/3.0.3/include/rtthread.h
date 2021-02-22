#ifndef __RT_THREAD_H__
#define __RT_THREAD_H__

#include <rtservice.h>
#include <rtdef.h>
#include <rthw.h>

/**************************************************************
 * 线程接口
 **************************************************************/
rt_err_t rt_thread_init(struct rt_thread *thread,
                        void (*entry)(void *parameter),
                        void             *parameter,
                        void             *stack_start,
                        rt_uint32_t       stack_size);

/**************************************************************
 * 调度接口
 **************************************************************/
void rt_system_scheduler_init(void);
void rt_system_scheduler_start(void);
void rt_schedule(void);
#endif /* __RT_THREAD_H__ */
