#ifndef __RT_THREAD_H__
#define __RT_THREAD_H__

#include <rtservice.h>
#include <rtdef.h>
#include <rthw.h>

/**************************************************************
 * 线程接口
 **************************************************************/
rt_err_t rt_thread_init(struct rt_thread *thread,
                        const char *name,
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
#endif /* __RT_THREAD_H__ */
