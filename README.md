[TOC]

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

## 第三步：新建文件组

创建文件：

1. User文件夹：main.c
2. Doc文件夹：readme.txt

添加文件组：

1. 最左侧的Project目录里，在“Target 1”上右击，选择“Manage Project Item”。
2. 在弹出的窗口“Manage Project Items”中，点击Groups文件右侧New按钮，添加group，包括user，rtt/ports，rtt/source，doc。
3. 选中user group，点击Add Files，在弹出的串口中，选择添加User文件夹下的main.c文件。
   <img src=".\README.assets\image-20210221085507790.png" alt="image-20210221085507790" style="zoom: 80%;" />
4. 选中doc group，点击Add Files，在弹出的窗口中，选择添加Doc文件夹下的readme.txt文件。
5. 点击窗口“Manage Project Items”中的OK，保存所有设置。（一定要点击OK，不然窗口内所有设置无效）
6. 设置结束的工程目录
   <img src=".\README.assets\image-20210221090434956.png" alt="image-20210221090434956" style="zoom:80%;" />

编写[main.c](./01-NewProject/User/main.c)代码，点击菜单栏Project -> build Target，若没有错误、警告，则工程可用。

调试配置

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

### 2.1.4 总结

| 模型       | 事件响应 | 事件处理 | 特点                       |
| ---------- | -------- | -------- | -------------------------- |
| 轮询系统   | 主程序   | 主程序   | 轮询响应事件，轮询处理事件 |
| 前后台系统 | 中断     | 主程序   | 实时响应事件，轮询处理事件 |
| 多线程系统 | 中断     | 线程     | 实时响应事件，实时处理事件 |

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

修改[main.c](./02-PollingSystem/User/main.c)文件后，编译代码。打开Debug（菜单栏Debug -> Start/Stop Debug Session）运行程序；打开Logic Analyzer工具（菜单栏View -> Analysis Windows -> Logic Analyzer）；在代码界面中，选择需要添加到逻辑分析仪工具的变量（选择变量 -> 右击 -> Add flag1 to -> LogicAnalyzer）。选择添加的flag1和flag2变量，右击选择Bit模式。

<img src=".\README.assets\image-20210221181315617.png" alt="image-20210221181315617" style="zoom:67%;" /><img src=".\README.assets\image-20210221181530872.png" alt="image-20210221181530872" style="zoom:80%;" />

点击运行，获得波形图如下

<img src=".\README.assets\image-20210221182415721.png" alt="image-20210221182415721" style="zoom:80%;" />





