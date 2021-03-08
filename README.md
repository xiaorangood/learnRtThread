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
		- [3.9.2 定义全局变量](#392-定义全局变量)
		- [3.9.3 初始化先调度器](#393-初始化先调度器)
		- [3.9.4 启动调度器](#394-启动调度器)
		- [3.9.5 系统调度](#395-系统调度)
	- [3.11 主函数实现](#311-主函数实现)
	- [3.12 实验现象](#312-实验现象)
- [第4章 临界段保护](#第4章-临界段保护)
- [第5章 对象容器](第5章-对象容器)
- [第6章 空闲线程与阻塞延时](#第6章-空闲线程与阻塞延时)
  - [6.1 增改的文件](#61-增改的文件)
  - [6.2 实现空闲线程](#62-实现空闲线程)
  - [6.3 实现阻塞延时](#63-实现阻塞延时)
  - [6.4 SysTick_Handler中断服务程序](#64-systick_handler中断服务程序)
  - [6.5 实验结果](#65-实验结果)

- [第7章 多优先级](#第7章-多优先级)
	- [7.1 线程就绪列表和线程就绪优先级组](#71-线程就绪列表和线程就绪优先级组)
	- [7.2 添加宏定义](#72-添加宏定义)
	- [7.3 其他修改的文件](#73-其他修改的文件)

- [第8章 定时器](#第8章-定时器)

  - [8.1 增加的宏定义](#81-增加的宏定义)
  - [8.2 实现定时器](#82-实现定时器)
    - [8.2.1 创建系统定时器列表](#821-创建系统定时器列表)
    - [8.2.2 系统定时器列表初始化](#822-系统定时器列表初始化)
    - [8.2.3 定时器成员初始化函数](#823-定时器成员初始化函数)
    - [8.2.4 定时器删除函数](#824-定时器删除函数)
    - [8.2.5 定时器停止函数](#825-定时器停止函数)
    - [8.2.6 定时器控制函数](#826-定时器控制函数)
    - [8.2.7 定时器启动函数](#827-定时器启动函数)
    - [8.2.8 定时器扫描函数](#828-定时器扫描函数)

  - [8.3 需要修改的文件或函数](#83-需要修改的文件或函数)
  - [8.4 实验现象](#84-实验现象)

- [第9章 时间片](#第9章-时间片)



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

代码产生指令：

```assembly
; AREA表示一个新的数据段或代码段
; .text表示段名，段名两边用“|”包括
; CODE表示伪代码
; READONLY表示只读
; ALIGN=2表示接着指令以2^2=4字节对齐
; 
    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    REQUIRE8
    PRESERVE8
```

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

根据在[rtdef.h](./03-MultiThreadSystem/rtthread/3.0.3/include/rtdef.h)文件中定义的线程控制块结构体（struct rt_thread），对内部各个数值赋初值。在[thread.c](./03-MultiThreadSystem/rtthread/3.0.3/src/thread.c)文件中定义线程初始化。将thread.c文件添加到rtt/source的group中。

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



# 第4章 临界段保护

临界段是一段在执行时不能被中断的代码，常出现在对全局变量的操作。

赋值03-MultiThreadSystem文件夹，重命名为04-MaskInterrupt。

CPS中断关闭指令：

```assembly
CPAID I ; PRIMASK=1		关中断
CPSIE I ; PRIMASK=0		开中断
CPSID F ; FAULTMASK=1	关异常
CPSIE F ; FAULTMASK=0	开异常
```

Corttex-M内核中断屏蔽寄存器组

| 寄存器    | 描述                                                         |
| --------- | ------------------------------------------------------------ |
| PRIMASK   | 1比特寄存器。<br />置1后，屏蔽所有可屏蔽异常，只剩下NMI和硬FAULT可以响应。<br />默认值为0，表示没有关中断。 |
| FAULTMASK | 1比特寄存器。<br />置1后，只响应NMI；其他异常，包括硬FAULT，也被忽略。<br />默认值为0，表示没有关闭异常 |
| BASEPRI   | 最多9比特寄存器。<br />所有优先级大于等于此数值的中断都被屏蔽（优先级号越大，优先级越低）。<br />默认值0，不屏蔽任何中断 |

在[rtthread\3.0.3\libcpu\arm\cortex-m3\context_rvds.s](.\04-MaskInterrupt\rtthread\3.0.3\libcpu\arm\cortex-m3\context_rvds.s)中定义开中断和关中断函数。

在[rtthread\3.0.3\include\rthw.h](04-MaskInterrupt\rtthread\3.0.3\include\rthw.h)中声明开中断和关中断函数。

使用临界段代码是注意事项：通过关中断时保存、开中断时恢复寄存器，来避免中断嵌套

```C
// 关中断, level1 = 0, PRIMASK=1
level1 = rt_hw_interrupt_disable();
{
    //执行临界段代码1
    // 关中断，level2 = 1， PRIMASK=1
    level2 = rt_hw_interrupt_disable();
    {
    	//执行临界段代码2
    }
    //  开中断，结束临界段代码, level2 = 1, PRIMASK = 1
    rt_hw_interrupt_enable(level2);
}
// 开中断，结束临界段代码, level1 = 0, PRIMASK = 0
rt_hw_interrupt_enable(level1);
```

<p  align="right"><a href="#目录">回到目录</a></p>



# 第5章 对象容器

复制04-MaskInterrupt重命名为05-ObjectContainer.

需要新建的文件：

1. rtthread\3.0.3\src\object.c文件：定义对象容器及其操作。添加到工程的rrt/src的group
2. rtthread\3.0.3\src\kservice.c文件：一般性公共操作。添加到工程的rrt/src的group

定义内核对象，修改对应文件

- [rtconfig.h](.\05-ObjectContainer\User\rtconfig.h)文件中，添加内核对象最长名字的宏定义RT_NAME_MAX
- [rtdef.h](.\05-ObjectContainer\rtthread\3.0.3\include\rtdef.h)文件中，添加
  - 内核对象结构体定义：struct rt_object
  - 内核对象结构体指针类型：rt_object_t
  - 内核对象类型美剧类型：enum rt_object_class_type
  - 在原线程控制块类型rt_thread开始处添加定义：
    - 对象名：name
    - 对象类型：type
    - 对象状态：flag
    - 对象的双向链表节点：list

定义对象容器，即内核对象信息的数组：

- 每次创建的对象，都要放到对象容器中管理
- 对象容器就是一个全局数组变量
- 在[rtdef.h](.\05-ObjectContainer\rtthread\3.0.3\include\rtdef.h)文件中定义内核对象信息列表结构体：struct rt_object_information，包括
  - 对象信息列表的类型：type（与内核对象类型不同）
  - 对象双向列表节点：object_list
  - 对象控制块大小：object_size
- 在[object.c](.\05-ObjectContainer\rtthread\3.0.3\src\object.c)文件中定义容器：
  - 对象信息的枚举类型：enum rt_object_info_type
  - 对象容器的定义：static struct rt_object_information rt_object_container[RT_Object_Info_Unknown]
  - 定义对象信息执行自身的宏：_OBJ_CONTAINER_LIST_INIT
  - 通过RT_USING_XXXX的宏定义，决定容器的维度大小

容器接口的实现：

- 在[kservice.c](.\05-ObjectContainer\rtthread\3.0.3\src\kservice.c)文件中，实现字符串拷贝的定义，用于复制内核对象名字，并在[rtthread.h](.\05-ObjectContainer\rtthread\3.0.3\include\rtthread.h)文件中声明
- 在[object.c](.\05-ObjectContainer\rtthread\3.0.3\src\object.c)文件中，定义2个函数
  - 在对象容器(数组）中，获取指向对象信息（数组元素）的指针：rt_object_get_information
  - 初始化内核对象，将内核对象插入容器中：rt_object_init（由于对容器操作，需要临界段保护）
- 在[rtthread.h](.\05-ObjectContainer\rtthread\3.0.3\include\rtthread.h)文件中声明对象初始化函数：rt_object_init

由于线程控控制块多一段信息，需要修改线程控制块的初始化函数：rt_thread_init

- 在[thread.c](./05-ObjectContainer/rtthread/3.0.3/src/thread.c)文件中修改线程控初始化函数的定义：
  - 输入参数增加一个 name的char*类型
  - 在函数起始处增加调用内核对象初始化函数：rt_object_init

- 在[rtthread.h](.\05-ObjectContainer\rtthread\3.0.3\include\rtthread.h)文件中，修改线程控制块初始化函数的声明
- 在[main.c](.\05-ObjectContainer\User\main.c)文件中，修改线程控制块初始化函数的调用

<p  align="right"><a href="#目录">回到目录</a></p>





# 第6章 空闲线程与阻塞延时

第5章的线程函数中，使用的软件延时，不能达到最大发挥CPU的目的，通过线程的阻塞延时实现延时。

复制05-ObjectContainer文件夹，并重命名为06-BlockDelay。

## 6.1 增改的文件

新增的文件：

1. rtthread\3.0.3\src\idle.c文件：用于空闲栈的定义。
2. rtthread\3.0.3\src\irq.c文件：用于定义中断函数。
3. rtthread\3.0.3\src\clock.c文件：存放时基更新函数。

需要修改的文件：

1. rtthread\3.0.3\include\rtdef.h
2. rtthread\3.0.3\include\rtservice.h
3. rtthread\3.0.3\include\rtthread.h
4. rtthread\3.0.3\src\scheduler.c
5. rtthread\3.0.3\src\thread.c
6. User\main.c
7. User\rtconfig.h

<p  align="right"><a href="#目录">回到目录</a></p>

## 6.2 实现空闲线程

在[idle.c](.\06-BlockDelay\rtthread\3.0.3\src\idle.c)文件中，实现空闲线程：

- 定义空闲线程栈：rt_thread_stack
- 定义空闲线程的线程控制块：idle
- 定义空闲线程的线程函数，线程函数名：rt_thread_idle_entry
- 实现空闲线程的初始化
  - 函数名：rt_thread_idle_init
  - 调用线程初始化函数：rt_thread_init
  - 将空闲线程的线程控制块插入到线程就绪列表最后一个元素中：rt_thread_priority_table[RT_THREAD_PRIORITY_MAX-1]

在[rtthread.h](.\06-BlockDelay\rtthread\3.0.3\include\rtthread.h)中，声明空闲线程初始化函数rt_thread_idle_init

<p  align="right"><a href="#目录">回到目录</a></p>

## 6.3 实现阻塞延时

阻塞延时就是当需要延时时，线程不再占用CPU资源；当延时结束后，再次占用CPU资源。

当阻塞延时时，CPU资源由其他线程使用；当所有线程都阻塞延时时，由空闲线程占用CPU资源。

在[rtdef.h](.\06-BlockDelay\rtthread\3.0.3\include\rtdef.h)文件中，对线程控制块增加字段

- 增加线程控制块中字段remaining_tick，用于存放是剩余延时时间。

在[thread.c](.\06-BlockDelay\rtthread\3.0.3\src\thread.c)文件中增代码

- 增加阻塞延时函数
  - 函数名：rt_thread_delay
  - 流程：获取当前线程控制块 -> 设置延时剩余时间 -> 进行系统调度
- 由于阻塞延时函数使用到了在[scheduler.c](.\06-BlockDelay\rtthread\3.0.3\src\scheduler.c)中定义的当前线程rt_current_thread指针，因此需要在本文件开始出声明这个外部变量。

在[scheduler.c](.\06-BlockDelay\rtthread\3.0.3\src\scheduler.c)文件中，修改系统调度函数rt_schedule

- 声明外部定义的三个线程控制块变量
  - [idle.c](.\06-BlockDelay\rtthread\3.0.3\src\idle.c)中定义的idle
  - [main.c](.\06-BlockDelay\User\main.c)中定义的rt_flag1_thread
  - [main.c](.\06-BlockDelay\User\main.c)中定义的rt_flag2_thread

- 修改rt_schedule函数的调度逻辑
  - 若当前线程时空闲线程idle
    - 若线程1的线程控制块rt_flag1_thread中，remaining_tick为0时，从当前线程切换到线程1，并更新当前线程指针rt_current_thread
    - 若线程2的线程控制块rt_flag2_thread中，remaining_tick为0时，从当前线程切换到线程2，并更新当前线程指针rt_current_thread
    - 其余情况，则直接将函数返回
  - 若当前线程不是空闲线程idle
    - 若当前线程为线程1
      - 若线程2的线程控制块rt_flag2_thread中，remaining_tick为0时，从当前线程切换到线程2，并更新当前线程指针rt_current_thread
      - 若当前线程的线程控制块中，remaining_tick不为0时，则从当前线程切换到空闲线程，并更新当前线程指针rt_current_thread
      - 其余情况，则直接返回
    - 若但钱线程为线程2
      - 若线程1的线程控制块rt_flag1_thread中，remaining_tick为0时，从当前线程切换到线程1，并更新当前线程指针rt_current_thread
      - 若当前线程的线程控制块中，remaining_tick不为0时，则从当前线程切换到空闲线程，并更新当前线程指针rt_current_thread
      - 其余情况，则直接返回
    - 其余情况，则直接返回
  - 调用上下文切换函数rt_hw_context_switch

<p  align="right"><a href="#目录">回到目录</a></p>

## 6.4 SysTick_Handler中断服务程序

通过该中断服务程序，将remaining_tick进行周期性递减，使得系统调度函数中可以判断remaining_tick的数值。

在irq.c文件中，实现：

- 中断进入：rt_interrupt_enter
- 中断退出：rt_interrupt_leave
- 两个函数中，由一个变量用来纪律嵌套的中断数。

在clock.c文件中，实现更新时基rt_tick_increace函数

- 对线程控制块优先列表rt_thread_priority_table中的所有线程变量
- 检查线程中的remaining_tick数值，当大于0的时候自减

在[main.c](.\06-BlockDelay\User\main.c)文件中，

- 实现SysTick的中断服务程序SysTick_Handler，依次调用
  - 进入中断rt_interrupt_enter
  - 更新时基rt_tick_increace
  - 离开中断rt_interrupt_leave
- 在rtconfig.h文件中，定义RT_TICK_PER_SECOND
- 在主函数中，配置systick的中断
  - 关中断
  - SysTick_Config配置SysTick定时器
  - 初始化空闲进程rt_thread_idle_init
- 在线程入口函数flag1_thread_entry和flag2_thread_entry中，调用rt_thread_delay延时函数延时

<p  align="right"><a href="#目录">回到目录</a></p>

## 6.5 实验结果

延时20ms翻转，周期40ms。

<img src=".\README.assets\image-20210227140449036.png" alt="image-20210227140449036" style="zoom:80%;" />

<p  align="right"><a href="#目录">回到目录</a></p>



# 第7章 多优先级

将06-BlockDelay复制，并更名为07-ThreadPriority

## 7.1 线程就绪列表和线程就绪优先级组

线程就绪优先级组：用一个bit表示对应优先级，在就绪列表中有没有线程。

在scheduled.c文件中，定义线程就绪优先级组变量：`rt_uint32_t rt_thread_ready_priority_group;`

在kservie.c文件中，定义`__rt_ffs`函数，被置1的最小比特位。通过`__lowest_bit_bitmap`数组，可以快速判断8bit中哪一个bit是最小。

在rtthread.h文件中，声明`__rt_ffs`函数

<p  align="right"><a href="#目录">回到目录</a></p>

## 7.2 添加宏定义

在rtdef.h文件中，添加：

- 线程控制块结构体中增加的字段
  - 当前优先级：current_priority
  - 初始优先级：init_priority
  - 当前优先级掩码：number_mask
  - 线程错误码：error
  - 线程状态：stat
- RT-Thread 线程状态的定义，包括初始化、挂起、Ready等

<p  align="right"><a href="#目录">回到目录</a></p>

## 7.3 其他修改的文件

在schedule.c文件中，

- 增加全局变量rt_current_priority，来表示当前线程的优先级

- 修改调度器初始化函数（rt_system_scheduler_init），增加初始化当前线程优先级，修改后，函数流程为
  - 对线程就绪列表（rt_thread_priority_table）中每个元素，调用列表初始化函数（rt_list_init）
  - 设置当前线程优先级变量（rt_current_priority）为最低优先级，即RT_THRAD_PRIORITY_MAX - 1
  - 设置当前线程变量（rt_current_thread）为NULL
  - 设置线程就绪优先级组（rt_thread_ready_priority_group）为0
- 修改调度器启动函数（rt_system_scheduler_start）
  - 获取当前最高优先级及当前最高优先级，对应最新的线程。
  - 设置最高优先级最新线程为将要调用的线程
  - 调用函数切换到新线程（rt_hw_context_switch_to）
- 修改系统调度函数（rt_schedule）
  - 关中断
  - 获取最高优先级最新线程
  - 若该线程与当前线程不一样，则
    - 设置当前线程优先级
    - 设置原线程指针为档期那线程，当前线程为最高优先级最新线程
    - 调用上线文切换函数（rt_hw_context_switch）
  - 开中断
- 添加调度器插入线程（rt_schedul_insert_thread），在rtthread.h文件中声明
  - 关中断
  - 改变线程状态为READY
  - 将线程插入就绪列表（rt_list_insert_befor）
  - 设置线程就绪优先级组中对应的位
  - 关中断
- 添加调度器删除线程函数（rt_schedule_remove_thread），在rtthread.h文件中声明
  - 关中断
  - 将调用链表移除函数（rt_list_remove）将线程从就绪列表中删除
  - 判断对应优先级是否位空，若为空，则将线程就绪优先级组对应的位清除
  - 开中断

在thread.c文件中

- 声明为外部变量的当前线程指针（rt_current_thread）

- 修改线程初始化函数（rt_thread_init）
  - 增加行数形参：priority
  - 设置thread对象中新增加的字段
    - 初始优先级和当前优先级为形参priority的数值
    - 当前优先级掩码为0
    - 线程错误码为RT_EOK
    - 线程状态为RT_THRAD_INIT
- 添加线程启动函数（rt_thread_startup），在rtthread.h文件中声明
  - 将原来线程插入线程就绪列表这个函数行为替代
  - 在函数中设置
    - 当前优先级为初始优先级
    - 当前优先级掩码为1左移优先级位
    - 改变线程状态位挂起
    - 恢复线程（rt_thread_resume）
    - 有当前线程（rt_thread_slef），则进行系统调度（rt_schedule）
- 添加恢复线程函数（rt_thread_resume），在rtthread.h文件中声明
  - 如若线程非挂起状态，则返回错误代码
  - 否则，
    - 关闭中断
    - 将线程从挂起线程列表中移除（rt_list_remove）
    - 使用调度器插入线程将线程插入线程就绪列表中
    - 开中断
- 添加获取当前线程函数（rt_thread_resume），返回声明为外部变量的当前线程指针（rt_current_thread）
- 修改阻塞延时函数（rt_thread_delay）
  - 关中断
  - 获取当前线程控制块，设置剩余remaining_tick为传入形参数值
  - 改变线程状态为挂起
  - 将线程就绪优先级组对应比特位清零
  - 开中断
  - 系统调度（rt_schedule）

在idle.c文件中

- 修改空闲线程初始化函数（rt_thread_idle_init）：
  - 增加线程初始化函数的实参：RT_THREAD_PRIORITY_MAX - 1
  - 将原调用链表插入函数（rt_list_insert_before）直接将线程控制块链接到就绪列表，替换为线程启动函数（rt_thread_startup）；线程启动函数中的线程恢复函数（rt_thread_resume）会将线程插入就绪列表。

在clock.c文件中

- 修改时基更新函数，当remaining_tick为0时，则将对那个bit位置的就绪优先级组置位

在main.c文件中

- 将线程初始函数，增加优先级实参
- 使用线程启动函数替换链表插入函数。

<p  align="right"><a href="#目录">回到目录</a></p>



## 第8章 定时器

第7章的remaining_tick方案，在时基中断来临时，需要对线程就绪列表所有线程扫描，比较慢。

若每个线程内置一个定时器，需要延时时将线程挂起，并开启定时器，然后插入定时器列表。

定时器列表是一个双线列表，对时间升序，每次时机中断来临时，就扫描系统定时器列表的定时器，就不用全局扫描。

复制07-ThreadPriority重命名为08-Timer

## 8.1 增加的宏定义

在rtdef.h文件中增加如下定义：

- 系统定时器列表大小：RT_TIMER_SKIP_LIST_LEVEL
- 定义定时器结构体
  - rt_object类型的成员：parent
  - 定时器双向列表节点：row
  - 超时函数：timeout_func
  - 超时函数形参：parameter
  - 定时器初始tick数值：init_tick
  - 定时器超时时，系统的tick数值：timeout_tick
- 定时器对象的flag宏定义，包括
  - 定时器是否激活：falg变量的bit0用来表示；置位为激活
  - 定时器模式：falg变量的bit1用来表示，置位表示周期，清零表示单次
  - 定时器类型：falg变量的bit3用来表示，置位表示软定时器，清零表示硬件定时器。软件回调函数在定时器线程中调用，硬件定时器在中断处理函数
- 定时器控制命令宏定义：RT_TIMER_CTRL开头的四个宏，实现定时器设置时间、获取时间、设置一次定时或周期定时。

在redef.h文件中，修改定义

- 在线程控制块结构体中，内置定时器成员

<p  align="right"><a href="#目录">回到目录</a></p>

## 8.2 实现定时器

创建文件timer.c。

### 8.2.1 创建系统定时器列表

一个rt_list类型的数组，数组的大小由宏定义RT_TIMER_SKIP_LIST_LEVEL决定。

`rt_timer_list`

### 8.2.2 系统定时器列表初始化

`rt_system_timer_init`

该操作是对使得系统定时器列表中，每个元素的next成员和prev成员指向自己。

### 8.2.3 定时器成员初始化函数

`rt_timer_init`

初始化定时器结构体内的内容，包括parent成员，以及超时函数、tick相关参数，定时器列表row。

### 8.2.4 定时器删除函数

`_rt_timer_remove`

该函数入参为一个定时器对象，将该对象的双向列表从列表中移除

### 8.2.5 定时器停止函数

`rt_timer_stop`

步骤：

- 判断timer状态是否为激活状态，若不是，则返回错误
- 关中断
- 调用_rt_timer_remove，将定时器从定时器列表中删除
- 开中断
- 将定时器的状态设置为非激活状态

### 8.2.6 定时器控制函数

`rt_timer_control`

根据控制宏定义，设置对应的对象成员；入参由定时器timer、命令、参数；参数类型为void*类型。

### 8.2.7 定时器启动函数

将线程对象的定时器的双向列表，按照延时时间做升序排序插入系统定时器列表rt_timer_list中

入参：定时器timer

步骤：

- 关中断，将timer从系统定时器列表中移除，开中断
- 设置timer的状态为非active状态
- 获取系统tick数值，计算并设置timeout时间
- 关中断
- 查找位置插入
- 设置定时器标志位激活状态
- 开中断
- 返回状态。

### 8.2.8 定时器扫描函数

`rt_timer_check`查询延时是否到期，如果到期就让线程就绪。

步骤：获取系统时间tick数值，将系统定时器列表中，时间小于当前时间的timer。调用timer超时函数。若timer时周期的，设置下一次的时间，否则 设置tiemr位非激活。

<p  align="right"><a href="#目录">回到目录</a></p>

## 8.3 需要修改的文件或函数

在thread.c文件中

- 添加超时函数`rt_thread_timeout`，步骤有：
  - 获取timer对应的线程
  - 设置错误码位超时
  - 从挂起列表中删除，插入就绪列表
  - 系统调度`rt_schedule`

- 修改线程初始化函数rt_thread_init，调用定时器初始化函数初始化该线程的timer（rt_timer_init）

- 修改线程延时函数rt_thread_delay，调用线程睡眠函数（rt_thread_sleep）

- 定义线程睡眠函数rt_thread_sleep，不走有

  - 关中断，获取当前线程控制块rt_current_thread
  - 调用rt_thread_suspend函数挂起线程
  - 设置当前线程的timer内容，并启动
  - 开中断，并执行系统调度：rt_schedule

- 定义线程挂起函数rt_thread_suspend，步骤有

  - 判断为就绪状态，否则返回
  - 关中断，线程从就绪列表移除，对应定时器调用停止定时器函数，从系统定时器列表移除，开中断。

在clock.c文件中

- 修改实际增加函数rt_tick_increace，自增系统tick变量，调用定时器扫描函数rt_timer_check
- 增加tick数值获取函数rt_tick_get，返回全局变量rt_tick；

在main.c函数中修改

- 增加第3个线程的定义，包括，线程控制块，线程栈，线程入口函数
- 在设置SysTick后，调用rt_system_timer_init初始化定时器
- 在第二个线程初始化后面，增加第3个心出初始化，或调用rt_thread_startup函数插入就绪列表
- 设置第3个线程的延时时间为3

<p  align="right"><a href="#目录">回到目录</a></p>

## 8.4 实验现象

flga1延时40ms，周期80ms；flag2延时20毫秒，周期40毫秒；flga3延时30毫秒，周期60毫秒。

<img src=".\README.assets\image-20210305082949435.png" alt="image-20210305082949435" style="zoom:80%;" />

<p  align="right"><a href="#目录">回到目录</a></p>

# 第9章 时间片

将08-Timer复制，并重命名为09-TimeSlice。

- 在线程控制块中，添加记录时间片的两个变量：剩余时间片remaining_tick、初始时间片init_tick
- 将clock.c文件中的SysTick更新函数（rt_tick_increace）进行修改
  - 获取当前线程的线程控制块
  - 增加剩余时间片的自减
  - 当剩余时间片为0时
    - 将剩余时间片重置为初始时间片
    - 掉用新定义的让渡处理器函数：rt_thread_yeild函数
- 在thread.c文件中，定义rt_thread_yeild函数，并在rtthread.h中声明
  - 关中断，并获取当前线程的线程控制块
  - 如果当前线程为就绪状态、且有同一优先级的其他线程，则
    - 将当前线程的线程控制块从线程就绪列表中移除
    - 将线程控制块加插入到线程就绪列表中，当前优先级的末尾
    - 开中断
    - 执行调度：rt_schedule
    - 返回
  - 开中断
  - 返回
- 修改thread.c文件中的rt_thread_init函数，增加tick形参。
- 修改idle.c文件中，空闲线程的初始化实参
- 修改main.c文件
  - 修改线程实参
  - 修改thread2和thread3为同一个优先级，且设置时间片。

实验结果：

thread1的延时时timer的时间，时间片没有影响。thread2和thread3时同一个优先级，不能同时翻转flag；两个线程的翻转时间，时时间片的时间。

<img src=".\README.assets\image-20210308213838318.png" alt="image-20210308213838318" style="zoom:67%;" />

<p  align="right"><a href="#目录">回到目录</a></p>

