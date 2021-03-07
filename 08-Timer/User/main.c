#include <rtdef.h>
#include <rtconfig.h>
#include <rtthread.h>
#include <rthw.h>
#include "ARMCM3.h"

uint32_t flag1;
uint32_t flag2;
uint32_t flag3;

extern rt_list_t rt_thread_priority_table[RT_THREAD_PRIORITY_MAX];

/*******************************************************
 * 软件延时
 *******************************************************/
void delay(uint32_t count)
{
    while(count--);
}

/*******************************************************
 * 定义线程相关变量
 *******************************************************/
/* 线程控制块 */
struct rt_thread rt_flag1_thread;
struct rt_thread rt_flag2_thread;
struct rt_thread rt_flag3_thread;
/* 线程栈*/
ALIGN(RT_ALIGN_SIZE)
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];
rt_uint8_t rt_flag3_thread_stack[512];

/*******************************************************
 * 线程 1
 *******************************************************/
void flag1_thread_entry(void *p_arg)
{
    while(1)
    {
        flag1 = 1;
        rt_thread_delay(4);
        flag1 = 0;
        rt_thread_delay(4);
    }
}

/*******************************************************
 * 线程 2
 *******************************************************/
void flag2_thread_entry(void *p_arg)
{
    while(1)
    {
        flag2 = 1;
        rt_thread_delay(2);
        flag2 = 0;
        rt_thread_delay(2);
    }
}

/*******************************************************
 * 线程 3
 *******************************************************/
void flag3_thread_entry(void *p_arg)
{
    while(1)
    {
        flag3 = 1;
        rt_thread_delay(3);
        flag3 = 0;
        rt_thread_delay(3);
    }
}

/*******************************************************
 * 主函数
 *******************************************************/
int main(void)
{
    /* 硬件初始化 */
    /* 将硬件相关的初始化放在这里，如果是软件仿真则没有相关初始化代码 */
    /* 关中断 */
    rt_hw_interrupt_disable();
    
    /* SysTick中断频率设置 */
    SysTick_Config( SystemCoreClock / RT_TICK_PER_SECOND );
    
    /* 系统定时器列表初始化 */
    rt_system_timer_init();

    /* 调度器初始化 */
    rt_system_scheduler_init();
    
    /* 初始化空闲线程 */
    rt_thread_idle_init();

    /* 初始化线程 */
    rt_thread_init( &rt_flag1_thread,                 /* 线程控制块 */
                    "rt_flag1_thread",                /* 线程名字，字符串形式 */
                    flag1_thread_entry,               /* 线程入口地址 */
                    RT_NULL,                          /* 线程形参 */
                    &rt_flag1_thread_stack[0],        /* 线程栈起始地址 */
                    sizeof(rt_flag1_thread_stack),    /* 线程栈大小，单位为字节 */
                    2);                               /* 优先级 */
    /* 将线程插入到就绪列表 */
    rt_thread_startup(&rt_flag1_thread);

    /* 初始化线程 */
    rt_thread_init( &rt_flag2_thread,                 /* 线程控制块 */
                    "rt_flag2_thread",                /* 线程名字，字符串形式 */
                    flag2_thread_entry,               /* 线程入口地址 */
                    RT_NULL,                          /* 线程形参 */
                    &rt_flag2_thread_stack[0],        /* 线程栈起始地址 */
                    sizeof(rt_flag2_thread_stack),    /* 线程栈大小，单位为字节 */
                    3);                               /* 优先级 */
    /* 将线程插入到就绪列表 */
    rt_thread_startup(&rt_flag2_thread);
    
    /* 初始化线程 */
    rt_thread_init( &rt_flag3_thread,                 /* 线程控制块 */
                    "rt_flag3_thread",                /* 线程名字，字符串形式 */
                    flag3_thread_entry,               /* 线程入口地址 */
                    RT_NULL,                          /* 线程形参 */
                    &rt_flag3_thread_stack[0],        /* 线程栈起始地址 */
                    sizeof(rt_flag3_thread_stack),    /* 线程栈大小，单位为字节 */
                    4);                               /* 优先级 */
    /* 将线程插入到就绪列表 */
    rt_thread_startup(&rt_flag3_thread);

    /* 启动系统调度器 */
    rt_system_scheduler_start(); 
}

void SysTick_Handler(void)
{
    /* 进入中断 */
    rt_interrupt_enter();
    /* 更新时基 */
    rt_tick_increace();
    /* 离开中断 */
    rt_interrupt_leave();
}
