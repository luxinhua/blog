---
title: cmake build summary 
date: 2021/6/8
categories: cmake 
---

cmake 

---
### 最小例子
---
~~~bash
cmake_minimum_required(VERSION 3.10)
project(CalculateSqrt VERSION 1.0) # 设定工程名和版本号
add_executable(CalculateSqrt main.c)
~~~

---
### 指定头文件路径
---
~~~bash
# 指定项目编译的时候需要include的文件路径，PROJECT_BINARY_DIR变量为编译发生的目录，也就是make执行的目录，PROJECT_SOURCE_DIR为工程所在的目录
# target_include_directories官方文档：https://cmake.org/cmake/help/v3.3/command/target_include_directories.html
target_include_directories(CalculateSqrt PUBLIC "${PROJECT_BINARY_DIR}")
~~~

---
### 编译系统的配置导入到头文件中
---
~~~bash
自动生成CalculateSqrtConfig.h文件，直接include， 可以用作开关定义
set(TestA 1) 或者  option(TestA "Test A" 1)
configure_file(CalculateSqrtConfig.h.in CalculateSqrtConfig.h)
CalculateSqrtConfig.h.in 文件中： 
#define testA  @TestA@
~~~

---
### 添加子目录进入编译系统
---
~~~bash
add_subdirectory(MathFunctions) 
~~~

---
### 添加链接库
---
~~~bash
# 该指令的作用为将目标文件与库文件进行链接 
# target_link_libraries官方文档:https://cmake.org/cmake/help/latest/command/target_link_libraries.html 
target_link_libraries(CalculateSqrt PUBLIC MathFunctions) 
~~~

---
### 源码生成库
---
~~~bash
# 使用特定的源码为项目增加lib 
add_library(MathFunctions mysqrt.cpp) 
~~~
---
### 安装测试
---
添加在CMakeList.txt
就是决定执行make install 的时候，拷贝哪些文件到lib/bin/include
~~~bash
install(TARGETS MathFunctions DESTINATION lib) 
install(FILES MathFunctions.h DESTINATION include) 
~~~