[TOC]

# 第一部分 实现RT-Thread内核

# 01 创建Keil工程

## 第一步：创建文件夹

&emsp;&emsp;在仓库根目录下，创建01-NewProject文件夹，保存本章节的代码内容。在”01-NewProject\Project“文件夹下创建的工程文件夹目录：

- Doc：工程说明文档
- Project：工程文件
- rtthread/3.0.3
  - bsp：存放板级支持包
  - include：头文件
  - include/libc：头文件
  - libcpu/arm/conrtex-m3：处理器内核相关接口文件（STM32F103使用cortex-m3内核，属于ARM内核）
  - libcpu/arm/conrtex-m4：处理器内核相关接口文件（STM32F207使用cortex-m3内核，属于ARM内核）
  - libcpu/arm/conrtex-m7：处理器内核相关接口文件（STM32F407使用cortex-m3内核，属于ARM内核）
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


