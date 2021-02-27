#include <rtdef.h>
#include <rtconfig.h>
#include <rtthread.h>
#include <rthw.h>
#include "ARMCM3.h"

uint32_t flag1;
uint32_t flag2;

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
/* 线程栈*/
ALIGN(RT_ALIGN_SIZE)
rt_uint8_t rt_flag1_thread_stack[512];
rt_uint8_t rt_flag2_thread_stack[512];

/*******************************************************
 * 线程 1
 *******************************************************/
void flag1_thread_entry(void *p_arg)
{
    while(1)
    {
#if 0
        flag1 = 1;
        delay(100);
        flag1 = 0;
        delay(100);
        
        /* 线程切换，这里是手动切换 */
        rt_schedule();

#else
        flag1 = 1;
        rt_thread_delay(2);
        flag1 = 0;
        rt_thread_delay(2);
#endif
    }
}

/*******************************************************
 * 线程 2
 *******************************************************/
void flag2_thread_entry(void *p_arg)
{
    while(1)
    {
#if 0
        flag2 = 1;
        delay(100);
        flag2 = 0;
        delay(100);
        
        /* 线程切换，这里是手动切换 */
        rt_schedule();
#else
        flag2 = 1;
        rt_thread_delay(2);
        flag2 = 0;
        rt_thread_delay(2);
#endif
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
                    sizeof(rt_flag1_thread_stack) );  /* 线程栈大小，单位为字节 */
    /* 将线程插入到就绪列表 */
    rt_list_insert_before( &(rt_thread_priority_table[0]),&(rt_flag1_thread.tlist) );

    /* 初始化线程 */
    rt_thread_init( &rt_flag2_thread,                 /* 线程控制块 */
                    "rt_flag2_thread",                /* 线程名字，字符串形式 */
                    flag2_thread_entry,               /* 线程入口地址 */
                    RT_NULL,                          /* 线程形参 */
                    &rt_flag2_thread_stack[0],        /* 线程栈起始地址 */
                    sizeof(rt_flag2_thread_stack) );  /* 线程栈大小，单位为字节 */
    /* 将线程插入到就绪列表 */
    rt_list_insert_before( &(rt_thread_priority_table[1]),&(rt_flag2_thread.tlist) );

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
