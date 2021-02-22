# 目录

- [第一部分 实现RT-Thread内核](#第一部分-实现rt-thread内核)
- [第1章 创建Keil工程](#第1章-创建keil工程)
	- [第一步：创建文件夹](#第一步创建文件夹)
	- [第二步：新建工程](#第二步新建工程)
	- [第三步：新建文件组](#第三步新建文件组)
	  - [创建的文件](#创建的文件)
	  - [添加文件组](#添加文件组)
	  - [编写main代码](#编写main代码)
- [第2章 裸机系统多线程系统](#第2章-裸机系统多线程系统)
	- [2.1 三种系统比较](#21-三种系统比较)
		- [2.1.1 轮询系统](#211-轮询系统)
		- [2.1.2 前后台系统](#212-前后台系统)
		- [2.1.4 总结](#214-总结)
	- [2.2 轮询系统实现变量延时翻转](#22-轮询系统实现变量延时翻转)

- [第3章 多线程系统](#第3章-多线程系统)
	- [3.1 创建的文件](#31-创建的文件)
	- [3.2 变量的重定义](#32-变量的重定义)
	- [3.3 用户对系统的定义](#33-用户对系统的定义)
	- [3.6 线程切换](#36-线程切换)
	- [3.7 声明栈初始化和上下文切换函数](#37-声明栈初始化和上下文切换函数)
	- [3.8 线程初始化](#38-线程初始化)
	- [3.9 调度器实现](#39-调度器实现)
		- [3.9.1 获得结构体首地址的宏定义](#391-获得结构体首地址的宏定义)
	- [3.11 主函数实现](#311-主函数实现)
	- [3.12 实验现象](#312-实验现象)



# 第一部分 实现RT-Thread内核

# 第1章 创建Keil工程

## 第一步：创建文件夹

&emsp;&emsp;在仓库根目录下，创建01-NewProject文件夹，保存本章节的代码内容。在”01-NewProject\Project“文件夹下创建的工程文件夹目录：

- Doc：工程说明文档
- Project：工程文件
- rtthread/3.0.3
  - bsp：存放板级支持包
  - include：头文件
  - include/libc：头文件
  - libcpu/arm/cortex-m3：处理器内核相关接口文件（STM32F103使用cortex-m3内核，属于ARM内核）
  - libcpu/arm/cortex-m4：处理器内核相关接口文件（STM32F207使用cortex-m3内核，属于ARM内核）
  - libcpu/arm/cortex-m7：处理器内核相关接口文件（STM32F407使用cortex-m3内核，属于ARM内核）
  - src：内核源码
- User：用户代码

本章所有的操作在”01-NewProject“文件夹下进行。

<p  align="right"><a href="#目录">回到目录</a></p>

## 第二步：新建工程

进行操作：

1. keil菜单栏 -> Project -> Create New Project

2. 选择”01-NewProject\Project“文件夹

3. 保存文件名为：My-TR-Thread

4. 紧接着的”Select Device for Target“窗口更加处理器内核选择ARMCM3、ARMCM4、ARMCM7中一个。此处选ARMCM3；并点击OK。

5. 紧接着的”Manage Run-Time Environment“窗口，选择CORE和Startup两个文件；单击OK。

   <img src=".\README.assets\image-20210221083620720.png" alt="image-20210221083620720" style="zoom:67%;" />

6. 创建后的工程目录

   <img src=".\README.assets\image-20210221083845455.png" alt="image-20210221083845455" style="zoom: 80%;" />
<p  align="right"><a href="#目录">回到目录</a></p>

## 第三步：新建文件组

### 创建的文件

1. User文件夹：main.c
2. Doc文件夹：readme.txt

<p  align="right"><a href="#目录">回到目录</a></p>

### 添加文件组

1. 最左侧的Project目录里，在“Target 1”上右击，选择“Manage Project Item”。

2. 在弹出的窗口“Manage Project Items”中，点击Groups文件右侧New按钮，添加group，包括user，rtt/ports，rtt/source，doc。

3. 选中user group，点击Add Files，在弹出的串口中，选择添加User文件夹下的main.c文件。

   <img src=".\README.assets\image-20210221085507790.png" alt="image-20210221085507790" style="zoom: 80%;" />
   
4. 选中doc group，点击Add Files，在弹出的窗口中，选择添加Doc文件夹下的readme.txt文件。

5. 点击窗口“Manage Project Items”中的OK，保存所有设置。（一定要点击OK，不然窗口内所有设置无效）

6. 设置结束的工程目录

   <img src=".\README.assets\image-20210221090434956.png" alt="image-20210221090434956" style="zoom:80%;" />

<p  align="right"><a href="#目录">回到目录</a></p>

### 编写main代码

编写[main.c](./01-NewProject/User/main.c)代码，点击菜单栏Project -> build Target，若没有错误、警告，则工程可用。

<p  align="right"><a href="#目录">回到目录</a></p>

## 调试配置

1. 工程目录窗口中，在Target 1上右击，选择 Options for Target 1

2. 设置仿真模式是软件仿真
   
   窗口中选择Debug标签页，选择Use Simulator

<img src=".\README.assets\image-20210221091713804.png" alt="image-20210221091713804" style="zoom:80%;" />

3. 修改时钟大小
   
窗口中选择Target标签页，设置时钟频率为25Mhz。时钟频率由system_ARMCM3.c文件中的**SYSTEM_CLOCK**宏定义决定，数值单位是Hz。
   
<img src=".\README.assets\image-20210221091853735.png" alt="image-20210221091853735" style="zoom:80%;" />
   
4. 添加头文件路径

   窗口中选择 C/C++ 标签页，在Include Paths中添加头文件的搜索路径。

   ```
    ..\User;..\trrhtread\3.0.3\bsp;..\rtthread\3.0.3\components\finsh;..\rtthread\3.0.3\include\libc;..\rtthread\3.0.3\include
   ```
   <img src=".\README.assets\image-20210221093224514.png" alt="image-20210221093224514" style="zoom:80%;" />
<p  align="right"><a href="#目录">回到目录</a></p>





# 第2章 裸机系统多线程系统

## 2.1 三种系统比较

### 2.1.1 轮询系统

轮询系统是先初始化相关硬件，然后让主程序在一个死循环里不间断循环，每次循环内依次处理每个任务。

比较适合循环执行且不需要外部事件来驱动就可以完成的操作。

```c
int main(void)
{
    /* 硬件初始化 */
    HardWareInit();
    /* 无限循环 */
    while(true)
    {
        /* 处理任务1 */
        DoSomeThing1();
        /* 处理任务2 */
        DoSomeThing2();
        ... ...
        /* 处理任务N */
        DoSomeThingN();
    }
}
```

<p  align="right"><a href="#目录">回到目录</a></p>

### 2.1.2 前后台系统

在轮询系统基础上，加入中断来响应外部事件。中断称为“前台”，无效循环称为“后台”。

中断会打断正常执行流，执行中断服务程序；若处理的事件很快，则直接子啊中断服务程序中处理；如果处理的事件比较繁杂，则设置标志位后返回后台程序中处理。

前后台系统保证了事件不丢失，中断可嵌套大大提高了程序实时响应能力。

```C
int flag1 = 0;
int flag2 = 0;
... ...
int flagN = 0;
int main(void)
{
    /* 硬件初始化 */
    HardWareInit();
    /* 无限循环 */
    while(true)
    {
        /* 处理任务1 */
        if(flag1) DoSomeThing1();
        /* 处理任务2 */
        if(flag2) DoSomeThing2();
        ... ...
        /* 处理任务N */
        if(flagN) DoSomeThingN();
    }
}
```

<p  align="right"><a href="#目录">回到目录</a></p>

### 2.1.3 多线程系统

每一个线程就是一个任务，每个任务都在死循环执行。当事件中断发生时候，中断响应事件并设置CPU寄存器，使得执行流切换到相应的线程。

```C
int flag1 = 0;
int flag2 = 0;
... ...
int flagN = 0;
int main(void)
{
    /* 硬件初始化 */
    HardWareInit();
    /* OS初始化 */
    RTOSInit();
    /* OS启动，开始多线程调度，不再返回 */
    RTOSStart();
}

void ISR1(void)
{
    /* 切换执行任务1 */
}
... ...
void ISRN(void)
{
    /* 切换执行任务1 */
}

void DoSomeThing1(void)
{
    while(true) { /* 处理任务1 */}
}
.... ...
void DoSomeThingN(void)
{
    while(true) { /* 处理任务N */}
}
```

<p  align="right"><a href="#目录">回到目录</a></p>

### 2.1.4 总结

| 模型       | 事件响应 | 事件处理 | 特点                       |
| ---------- | -------- | -------- | -------------------------- |
| 轮询系统   | 主程序   | 主程序   | 轮询响应事件，轮询处理事件 |
| 前后台系统 | 中断     | 主程序   | 实时响应事件，轮询处理事件 |
| 多线程系统 | 中断     | 线程     | 实时响应事件，实时处理事件 |

<p  align="right"><a href="#目录">回到目录</a></p>

## 2.2 轮询系统实现变量延时翻转

将仓库根目录下的“01-NewProject”文件复制，并重命名为“02-PollingSystem”。

任务：实现两个变量延时翻转。每次循环中，每个变量先置位，然后延时，再清零，再延时。

```C
#include "ARMCM3.h"

uint32_t flag1;
uint32_t flag2;

void delay(uint32_t count)
{
    while(count--);
}

int main(void)
{
    while(1)
    {
        /* 任内1实现 flag1 周期为 4 us的翻转 */
        flag1 = 1;
        delay(100);
        flag1 = 0;
        delay(100);
        /* 任内1实现 flag2 周期为 4 us的翻转 */
        flag2 = 1;
        delay(100);
        flag2 = 0;
        delay(100);
    }
}
```

修改[main.c](./02-PollingSystem/User/main.c)文件后，编译代码。

启动逻辑分析仪：

1. 打开Debug（菜单栏Debug -> Start/Stop Debug Session）运行程序；
2. 打开Logic Analyzer工具（菜单栏View -> Analysis Windows -> Logic Analyzer）；
3. 在代码界面中，选择需要添加到逻辑分析仪工具的变量（选择变量 -> 右击 -> Add flag1 to -> LogicAnalyzer）。

<img src=".\README.assets\image-20210221181315617.png" alt="image-20210221181315617" style="zoom:67%;" />

选择添加的flag1和flag2变量，右击选择Bit模式。

<img src=".\README.assets\image-20210221181530872.png" alt="image-20210221181530872" style="zoom:80%;" />

点击运行，获得波形图如下

<img src=".\README.assets\image-20210221182415721.png" alt="image-20210221182415721" style="zoom:80%;" />

<p  align="right"><a href="#目录">回到目录</a></p>

# 第3章 多线程系统

将“02-PollingSystem”文件夹复制，并重命名为“03-MultiThreadSystem”。

## 3.1 创建的文件

相比与第3章的代码，需要新添加的文件有如下所示：

1. rtthread/3.0.3/include/rtdef.h文件：重定义需要使用的类型和RTOS会用得到的宏定义
2. User/rtconfig.h文件：定义用户需要对系统设置的宏定义
3. rtthread/3.0.3/include/rtservice.h文件：实现双向链表的操作
4. rtthread/3.0.3/libcpu/arm/cortex-m3/cpuport.c文件：实现线程栈初始化。
5. rtthread/3.0.3/libcpu/arm/cortex-m3/context_rvds.s文件：实现线程的切换
6. rtthread/3.0.3/include/rthw.h文件：实现线程栈相关函数的声明
7. rtthread/3.0.3/src/thread.c文件：实现线程相关操作、就绪列表的定义
8. rtthread/3.0.3/src/scheduler.c文件：实现线程调度器的实现
9. rtthread/3.0.3/include/rtthread.h文件：实现线程相关操纵的声明

需要修改的文件有：

1. User/main.c文件

<p  align="right"><a href="#目录">回到目录</a></p>

## 3.2 变量的重定义

在[rtdef.h](./03-MultiThreadSystem/rtthread/3.0.3/include/rtdef.h)文件中定义，包括：

1. 重定义数据类型
2. 针对不同编译器，内联函数和字节对齐指令宏定义：rt_inline、ALIGN(n)
3. 计算对齐地址的宏：RT_ALIGN是向上取对齐地址；RT_ALIGN_DOWN是向下取对齐地址
4. 双向链表结构体
5. 线程控制块结构体定义
6. 线程的错误码定义

<p  align="right"><a href="#目录">回到目录</a></p>

## 3.3 用户对系统的定义

在[rtconfig.h](./03-MultiThreadSystem/User/rtconfig.h)文件中，对对齐方式和线程优先级做出定义：

```C
#define RT_ALIGN_SIZE   		4
#define RT_THREAD_PRIORITY_MAX  32
```

<p  align="right"><a href="#目录">回到目录</a></p>

## 3.4 双向链表的操作

在RTOS中，将用到许多的链表操作，在[rtservice.h](./03-MultiThreadSystem/rtthread/3.0.3/include/rtservice.h)中实现双向链表的操作的定义，包括

- 双向链表节点的初始化，将前驱指针和后继指针指向该双向链表节点：
  - 函数名：rt_list_init
  - 输入：当前双向链表节点
- 在指定双向链表节点之前插入节点
  - 函数名：rt_list_insert_before
  - 输入：当前节点；插入的节点
- 在指定双向链表节点之后插入节点
  - 函数名：rt_list_insert_after
  - 输入：当前节点；插入的节点
- 将指定栓下链表节点从链表中移除
  - 函数名：rt_list_remove
  - 输入：要移除的节点
- 判断双向链表是否为空
  - 函数名：rt_list_isempty
  - 输入：双向链表节点

所有双向链表均没有返回值，且定义为内联函数，即“rt_inline”。

<p  align="right"><a href="#目录">回到目录</a></p>

## 3.5 栈的初始化与栈结构定义

在[cpuport.c](./03-MultiThreadSystem/rtthread/3.0.3/libcpu/arm/cortex-m3/cpuport.c)文件总实现栈结构的定义与栈的初始化，并将该源文件添加到Keill工程的rrt/ports的group中。

- 栈中需要定义的全局变量：

  ```C
  rt_uint32_t rt_interrupt_from_thread;			/* 用于存储上一个线程的栈的sp的指针 */
  rt_uint32_t rt_interrupt_to_thread;				/* 用于存储下一个将要运行的线程的栈的sp的指针 */
  rt_uint32_t rt_thread_switch_interrupt_flag;	/* 线程切换的PendSV中断服务函数执行标志 */
  ```

- 栈的帧结构

  - 栈帧结构用于保证线程的CPU寄存器数值。CPU寄存器可以分为自动保存和手动保存
  - 自动保存寄存器在异常时候，也会由RTOS自动保存，包括r0~r3、r12、lr、pc、psr
  - 手动保存寄存器包括r4~r11
  - 由于线程栈是由从高地址到低地址，且自动保存寄存器需要先保存，所以栈结构中先定义手动保存寄存器，再定义自动保存寄存器
  - 每个寄存器占用4字节

- 栈结构初始化

  - 函数名：rt_hw_stack_init
  - 输入：线程程序地址、输入参数列表（赋值给r0）、栈顶地址-4的地址
  - 流程：
    - 获得栈的起始地址，并向低地址做8字节对齐（float用8字节）；
    - 栈指针向下增加一个栈帧结构大小的地址
    - 初始化初始化该栈帧空间的数值为0xdeadbeef
    - 将自动保存寄存器清零，并使得r0数值为参数列表地址，pc为线程程序地址。
    - 返回栈指针。
    - ==实现一个满线程栈==，即栈指针指向最后的一个栈帧结构。

<p  align="right"><a href="#目录">回到目录</a></p>

## 3.6 线程切换

线程切换是通过将原线程的CPU寄存器数据保存，并读出将运行线程的CPU寄存器实现。

相关代码见[context_rvds.s](./03-MultiThreadSystem/rtthread/3.0.3/libcpu/arm/cortex-m3/context_rvds.s)文件。由于牵涉到CPU寄存器的读写，故使用汇编语言编写。

工程中，需要将该文件添加到rtt/ports这个group中。

主要的函数有

- PendSV异常处理函数（PendSV_Handler）流程
  - 保存特殊寄存器，中断相关（MRS     r2, PRIMASK）
  - 关中断（CPSID   I）
  - 读取中断执行标志位（rt_thread_switch_interrupt_flag变量）
    - 若中断标志位为0，则执行PendSV中断退出程序
    - 若中断标志位为1，则将标志位清零后继续执行
  - 读取前线程的指向栈指针数值（rt_interrupt_from_thread）
    - 若指针数值为0，则执行跳转到下文切换（switch_to_thread）程序
    - 若指针数值非0，则继续执行，执行上文保存程序
  - 上文保存程序（自动CPU寄存器已保存，需要手动保存手动CPU寄存器）
    - 获取线程栈指针（ MRS     r1, psp）
    - 保存手动CPU寄存器（STMFD   r1!, {r4 - r11}）
    - 更新线程栈指针
  - 下文切换（switch_to_thread）程序
    - 加载rt_interrupt_to_thread变量的地址
    - 加载rt_interrupt_to_thread变量的内容（这个变量指向sp栈指针）
    - 加载栈指针
    - 将线程栈指针r1(操作之前先递减)指向的内容加载到CPU寄存器r4~r11
    - 将线程栈指针更新到psp
  - PendSV中断退出程序
    - 恢复中断（MSR     PRIMASK, r2）
    - 确保异常返回使用的堆栈指针是psp，即LR寄存器的位2要置位。（ORR     lr, lr, #0x04）
    - 异常返回。
- rt_hw_context_switch_to处理函数，用于开启第一次线程切换
  - 输入：r0，切换到的线程栈指针的地址
  - 流程
    - 保存r0到rt_interrupt_to_thread
    - 保存0到rt_interrupt_from_thread
    - 设置中断标志rt_thread_switch_interrupt_flag为1
    - 设置PendSV异常的优先权（对NVIC_SYSPRI2寄存器设置数值为NVIC_PENDSV_PRI）
    - 触发PenSV异常（对NVIC_INT_CTRL寄存器设置数值为NVIC_PENDSVSET），执行PendSV_Handler
    - 开中断，永远不返回
- rt_hw_context_switch处理函数，用于线程切换
  - 输入：
    - r0，上文线程栈指针的地址
    - r1，下文线程栈指针的地址
  - 流程：
    - 读取中断标志位rt_thread_switch_interrupt_flag
      - 若标志位为1，说明有中断，但还没有进行上下文切换，则指执行更新下一个线程程序
      - 若标志为非1，则据徐指向
    - 更新rt_interrupt_from_thread数值为上一个线程的栈指针的地址
    - 执行更新下一个线程程序
      - 更新rt_interrupt_to_thread数值。
    - 触发PendSV异常程序，执行PendSV_Handler

<p  align="right"><a href="#目录">回到目录</a></p>

## 3.7 声明栈初始化和上下文切换函数

在[rthw.h](./03-MultiThreadSystem/rtthread/3.0.3/include/rthw.h)文件中声明三个函数：

```c
rt_uint8_t *rt_hw_stack_init(void       *tentry,
                             void       *parameter,
                             rt_uint8_t *stack_addr); 
void rt_hw_context_switch(rt_uint32_t from, rt_uint32_t to);
void rt_hw_context_switch_to(rt_uint32_t to);
```

<p  align="right"><a href="#目录">回到目录</a></p>

## 3.8 线程初始化

根据在[rtdef.h](./03-MultiThreadSystem/rtthread/3.0.3/include/rtdef.h)文件中定义的线程控制块结构体（struct rt_thread），对内部各个数值赋初值。在[thread.c](rtthread/3.0.3/src/thread.c)文件中定义线程初始化。将thread.c文件添加到rtt/source的group中。

- 函数名：rt_thread_init
- 输入参数
  - 指向线程控制块的指针
  - 线程函数指针
  - 线程函数参数的指针
  - 栈空间的起始位置
  - 栈空间的大小
- 返回：初始化状态，使用线程错误码
- 流程：
  - 初始化线程控制块双向链表
  - 依次设置线程函数，线程函数参数，栈地址，栈大小数据
  - 设置栈顶指针，通过栈初始化函数（rt_hw_stack_init），传输的栈顶指针为（thread->stack_addr + thread->stack_size - 4）

<p  align="right"><a href="#目录">回到目录</a></p>

## 3.9 调度器实现

相关代码见[scheduler.c](./03-MultiThreadSystem/rtthread/3.0.3/src/scheduler.c)文件，将文件添加到rtt/source的group中

### 3.9.1 获得结构体首地址的宏定义

```C
/* 已知一个结构体里面的成员的地址，反推出该结构体的首地址 */
#define rt_container_of(ptr, type, member) \
    ((type *)((char *)(ptr) - (unsigned long)(&((type *)0)->member)))

#define rt_list_entry(node, type, member) \
    rt_container_of(node, type, member)
```

`(unsigned long)(&((type *)0)->member))`：获取结构体成员相对于结构体首地址的偏移；

`ptr`为特定结构体成员。

`rt_container_of`获得ptr所指结构体的首地址。

<p  align="right"><a href="#目录">回到目录</a></p>

### 3.9.2 定义全局变量

- 指向当前线程控制块的指针：rt_current_thread
- 线程就绪列表：rt_thread_priority_table[RT_THREAD_PRIORITY_MAX]
- 线程休眠列表：rt_thread_defunct

<p  align="right"><a href="#目录">回到目录</a></p>

### 3.9.3 初始化先调度器

- 函数名：rt_system_scheduler_init
- 输入返回参数：无
- 流程：调用双向列表初始化函数（rt_list_init），依次初始化rt_thread_priority_table数组各个元素，rt_thread_defunct，将rt_current_thread设置为NULL

<p  align="right"><a href="#目录">回到目录</a></p>

### 3.9.4 启动调度器

- 函数名：rt_system_scheduler_start
- 输入返回参数：无
- 流程：
  - 指定rt_thread_priority_table[0]指向的下一个节点对应的线程控制块为第一个线程
  - 设置rt_current_thread指针为该线程控制块
  - 调用rt_hw_context_switch_to函数切换到该线程

<p  align="right"><a href="#目录">回到目录</a></p>

### 3.9.5 系统调度

- 函数名：rt_schedule
- 输入返回参数：无
- 流程：（本实验实现两个线程的轮流调度）
  - 将当前线程的指针rt_current_thread赋值给from_thread指针
  - 获得下一个线程的线程控制块地址，并赋值给rt_current_thread线程控制块指针
  - 调用rt_hw_context_switch切换上下文函数，传入上一个线程的栈指针，以及下一个线程的栈指针

<p  align="right"><a href="#目录">回到目录</a></p>

## 3.10 线程操作相关函数声明

在[rtthread.h](./03-MultiThreadSystem/rtthread/3.0.3/include/rtthread.h)文件，声明以下函数

```C
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
```

<p  align="right"><a href="#目录">回到目录</a></p>

## 3.11 主函数实现

在[main.c](./03-MultiThreadSystem/User/main.c)文件中实现通过线程调度实现两个任务切换。

定义的全局变量

- 线程1控制块rt_flag1_thread
- 线程2控制块rt_flag2_thread
- 线程1栈空间数组rt_flag1_thread_stack[512]
- 线程2栈空间数组rt_flag2_thread_stack[512]

线程1的线程函数：flag1_thread_entry

- 置位flag1，延时，清零flag1，延时
- 手动调用线程切换程序

线程1的线程函数：flag2_thread_entry

- 置位flag2，延时，清零flag2，延时
- 手动调用线程切换程序

主函数流程流程：硬件初始化

- 调度器初始化
- 初始化线程rt_flag1_thread
- rt_flag1_thread插入线程就绪列表元素第一个元素
- 初始化线程rt_flag2_thread
- rt_flag2_thread插入线程就绪列表元素第二个元素
- 启动系统调度器

<p  align="right"><a href="#目录">回到目录</a></p>

## 3.12 实验现象

由于时手动调度的，虽然使用了多线程的加构，但是逻辑分析仪的显示与轮询系统结果一致。

<img src=".\README.assets\image-20210222224913083.png" alt="image-20210222224913083" style="zoom:80%;" />

<p  align="right"><a href="#目录">回到目录</a></p>

