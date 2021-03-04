#ifndef __RT_THREAD_H__
#define __RT_THREAD_H__

#include <rtservice.h>
#include <rtdef.h>
#include <rthw.h>

/**************************************************************
 * 线程接口
 **************************************************************/
rt_err_t rt_thread_init(struct rt_thread    *thread,
                        const char          *name,
                        void                (*entry)(void *parameter),
                        void                *parameter,
                        void                *stack_start,
                        rt_uint32_t         stack_size,
                        rt_uint8_t          priority);
void rt_thread_delay(rt_tick_t tick);
rt_err_t rt_thread_startup(rt_thread_t thread);
rt_err_t rt_thread_resume(rt_thread_t thread);
rt_thread_t rt_thread_self(void);

/**************************************************************
 * 调度接口
 **************************************************************/
void rt_system_scheduler_init(void);
void rt_system_scheduler_start(void);
void rt_schedule_insert_thread(rt_thread_t thread);
void rt_schedule_remove_thread(rt_thread_t thread);
void rt_schedule(void);

/**************************************************************
 * 内核对象结构
 **************************************************************/
void rt_object_init(struct rt_object         *object,
                    enum rt_object_class_type type,
                    const char               *name);

/**************************************************************
 * 内核服务相关的接口
 **************************************************************/
char *rt_strncpy(char *dst, const char *src, rt_ubase_t n);
int __rt_ffs(int value);

/**************************************************************
 * 内核服务相关的接口
 **************************************************************/
void rt_thread_idle_init(void);

/**************************************************************
 * 中断接口
 **************************************************************/
void rt_interrupt_enter(void);
void rt_interrupt_leave(void);

/**************************************************************
 * 时钟相关接口
 **************************************************************/
void rt_tick_increace(void);
#endif /* __RT_THREAD_H__ */
