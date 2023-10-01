# Homework 02-实现Sufe::IntVector

动态数组的封装

## 📜Demands

- 在`Sufe::IntVector`里实现Insert/Delete算法
    - `void Insert(int idx, int val);`
    - `void Delete(int idx);`
    - `void Pushback(int val);`
- 分别测试插入5万+数据元素的时间（AutoTimer）
    - 一直插入为第一个元素: `Insert(0, val)`
    - 一直插入为最后一个元素：`Pushback(val)`

## 📝Efforts

### launch.json

在*homework01*的**🪲Problems**章节有提到如下问题:

> vscode&C++ extension环境下,可以正常生成(和直接在命令行中运行make命令一样),但是无法通过vscode进入到调试界面;

经过仔细研究发现,这个问题可能与*launch.json*这个文件有关,于是对其进行了修改,最终结果如下:

```json
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "MakeBuild(win)",
            "type": "cppdbg",
            "request": "launch",
            "program": "${workspaceRoot}/build/runme.exe",
            "args": [],
            "stopAtEntry": false,
            "cwd": "${workspaceFolder}",
            "environment": [], 
            "externalConsole": false,
            "MIMode": "gdb",
            "miDebuggerPath": "gdb.exe",
            "preLaunchTask": "Makefile"
        }
    ]
}
```

修改的地方如下:

- 鉴于对*Makefile*的修改已经失去了对MacOS/Linux的适配(详见*homework01*相关部分),因此直接删除了对应的launch配置;
- `"stopAtEntry"`修改为`false`,这样每次进入调试时不会在第一句暂停;
- `"externalConsole"`修改为`false`,这样调试会在vscode的内部终端而不是Windows的外部控制台进行(外部控制台在调试结束后会自动关闭,不打断点不方便看结果);

