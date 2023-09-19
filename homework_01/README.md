# Homework 01-230919

## 📜 Demands

- 实现`std::array`的大部分功能，包括
    - For-each遍历
    - **提高**：进一步了解设计模式**Iterator**
- 基于附件*array.starter.zip*，实现课件中的`Sufe::Array`模板类功能，用给定的*main.cpp*通过测试
    - 不同初始化方式
    - 调用Size()，[]，At()，<< 输出到屏幕
    - for-each遍历
    - 调用Sort()，对数组自身排序

## 📝 Efforts

### Makefile

压缩包中给到的makefile在vscode中进行编译遇到的问题是:

- 不能主动创建build文件夹,会报错如下:

    ```
    process_begin: CreateProcess(NULL, mkdir build, ...) failed.
    make (e=2): 系统找不到指定的文件。
    make: *** [Makefile:24: build] Error 2
    ```

- 在人工创建build文件后,能正常生成*main.o*和*runme.exe*文件,但是vscode仍然报错生成失败,无法进入到调试界面.

**解决方案:**

最后经过一番搜索和尝试之后,发现可以在每个命令前添加`cmd /C`,强制指定使用cmd而不是默认的powershell来跑编译.现在确实不会再有报错了,不过这么干的后果大概是makefile不能跨平台了(毕竟Linux和macos并没有cmd).
