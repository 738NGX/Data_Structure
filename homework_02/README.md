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

### Reserve

- 调整实际内存空间(m_capacity)
- Reserve相当于预处理一次**满**情形
- **陷阱**:不要在循环里调用Reserve

#### 预备工作

构造函数正确设置capacity和size:

```c++
IntVector::IntVector(int sz) : m_size(0), m_capacity(16)
{
    if (sz > 0)
    {
        m_size = sz;
        m_capacity = std::max(m_size, 16);
    }
    m_data = new int[m_capacity]{0};
}

IntVector::IntVector(std::initializer_list<int> list)
{
    m_size = list.size();
    m_capacity = std::max(m_size, 16);
    m_data = new int[m_capacity]{0};
    std::copy(list.begin(), list.end(), m_data);
}
```

内部Reset()，释放动态内存:

```c++
void IntVector::Reset()
{
    if (m_data)
    {
        delete[] m_data;
        m_data = nullptr;
        m_capacity = m_size = 0;
    }
}
```

#### 最终实现

最终的实现方式与课件给出的方式稍有不同,具体表现在使用`std::copy`取代了for循环迭代来实现内存拷贝.具体造成的差异会在后文的**时间复杂度与性能测试**章节中进行阐释.

```c++
void IntVector::Reserve(int cap)
{
    // TODO: 按课件实现Reserve
    if(cap>m_capacity)
    {
        int* data= new (nothrow) int [cap];
        if(data)
        {
            std::copy(m_data,m_data+m_size-1,data);

            delete[] m_data;
            m_data=data;
            m_capacity=cap;
        }
    }
}
```

### 复制和赋值

- 两种操作的实现方式类似,可以互相借鉴
- 需要注意参数(右值)的私有成员不能直接访问进行拷贝,必须通过外部接口(公有函数/索引)进行访问

```c++
IntVector::IntVector(const IntVector &other)
    : m_data(nullptr), m_size(0), m_capacity(0)
{
    // TODO: 按课件实现复制构造函数
    m_size=other.Size();
    Reserve(other.Capacity());

    for(int i=0;i<m_size;i++)
    {
        m_data[i]=other[i];
    }
}

IntVector &IntVector::operator=(const IntVector &rhs)
{
    // TODO: 按课件实现赋值运算符重载
    if(this==&rhs) return *this;

    if(m_capacity<rhs.m_size) Reserve(rhs.m_capacity);

    m_size=rhs.Size();
    for(int i=0;i<m_size;i++)
    {
        m_data[i]=rhs[i];
    }
    return *this;
}
```

### Resize

- 调整数据元素的个数(m_size):`Resize(int sz, int val = 0); `
    - 如果`sz < m_size`,只保留前`sz`个数据元素;
    - 如果`sz > m_size`,扩张数据元素到`sz`个,新元素按`val`初始化;
    - 如果`sz > m_capacity`,需要处理**满**的情形;
- 注意,[],At(),Insert,Delete里的下标是按`size`,而不是`capacity`来计算;
- 把vector对象预设值数据元素为n个，通过`Resize(n);`

```c++
void IntVector::Resize(int sz, int val)
{
    // TODO: 按课件实现Resize
    if(sz<=m_size)
    {
        m_size=sz;
    }
    else
    {
        // 重新分配内存空间
        int cp=m_capacity;
        while(sz>=cp) cp*=2;
        Reserve(cp);

        std::fill(m_data+m_size,m_data+sz-1,val);
        m_size=sz;
    }
}
```

### 插入和删除

#### 插入算法

- 情形1：size < capacity
    - 把插入位置后的数据元素往后移动一个位置后再插入
- 情形2：size = capacity
    - 新分配2倍的内存空间
    - 把原数组复制到新数组头部
    - 释放原数组内存
    - 回到情形1

```c++
void IntVector::Insert(int idx, int val)
{
    // TODO: 按算法思路实现Insert
    assert(idx<=m_size);

    // 重新分配内存空间
    if(m_size==m_capacity) Reserve(m_capacity*2);
    m_size++;

    std::move_backward(m_data+idx,m_data+m_size-1,m_data+m_size);

    m_data[idx]=val;
}
```

#### 删除算法

- 正常情形：把要删除元素后面的数据元素往前 移动一个位置,保持连续性
- 特殊情形：释放过多占用空间
    - 数组size少到capacity/4时候,新分配一半大小的新数组
    - 把原数组元素复制到新数组
    - 释放原数组
    - 按正常情形处理

```c++
void IntVector::Delete(int idx)
{
    // TODO: 按算法思路实现Delete
    assert(idx<=m_size);

    std::move(m_data+idx+1,m_data+m_size,m_data+idx);

    // 重新分配内存空间
    if(m_size<=m_capacity/4&&m_capacity>16) Reserve(m_capacity/2);
    m_size--;
}
```

#### std::copy与std::move

最一开始其实采用的是用`std::copy`函数来实现数据元素位置的移动,但是后来在查阅cppreference.com时发现了如下的叙述:

(以下引用自cppreference.com原文)

> ##### std::copy, std::copy_if
>
> 复制范围 `[`first`, `last`)` 中的元素到从 d_first 开始的另一范围（复制目标范围）。
>
> 1) 按从 first 到 last 的顺序复制 `[`first`, `last`)` 中的所有元素。如果 d_first 在 `[`first`, `last`)` 中，那么行为未定义。此时可以用`std::copy_backward`代替。
>
> 2) 复制元素，但按照 policy 执行。此重载只有在
>
> | std::is_execution_policy_v\<std::decay_t<ExecutionPolicy>>   | (C++20 前) |
> | ------------------------------------------------------------ | ---------- |
> | std::is_execution_policy_v \<std::remove_cvref_t<ExecutionPolicy>> | (C++20 起) |
>
> ​	是 true 时才会参与重载决议。**如果 `[`first`, `last`)` 与复制目标范围重叠，那么行为未定义。**
>
> 3) 仅复制谓词 pred 对其返回 true 的元素。此复制算法是稳定的：保持被复制元素的相对顺序。**如果 `[`first`, `last`)` 与复制目标范围重叠，那么行为未定义。**
>
> 4) 同 (3)，但按照 policy 执行。此重载只有在
>
> | std::is_execution_policy_v\<std::decay_t<ExecutionPolicy>>   | (C++20 前) |
> | ------------------------------------------------------------ | ---------- |
> | std::is_execution_policy_v\<std::remove_cvref_t<ExecutionPolicy>> | (C++20 起) |
>
> ​	是 true 时才会参与重载决议。

这一条:

> **如果 `[`first`, `last`)` 与复制目标范围重叠，那么行为未定义。**

询问了ChatGPT之后,他给出的解释如下:

> 在C++的`std::copy`函数的官方文档中，确实明确指出，如果源范围和目标范围重叠，该函数的行为是未定义的（Undefined Behavior，简称UB）。未定义的行为意味着程序可能以任何方式运行：它可能按照您期望的方式运行，也可能产生错误，或者以其他任何方式运行。
>
> 值得注意的是，"未定义的行为"并不意味着"总是出错"或"总是产生非预期结果"。在某些实现或平台上，`std::copy`在源和目标范围重叠的情况下可能“恰好”工作，但这并不意味着它总是安全的，也不意味着在所有平台和编译器上都是如此。
>
> 当您的代码依赖于未定义的行为时，您无法保证它会在所有环境中一致和正确地工作。未定义的行为可能在不同的编译器，不同版本的编译器，或者甚至是不同的编译选项下产生不同的结果。此外，即使在您当前的环境中“看似正常”，未来的编译器更新或环境更改也可能导致问题。
>
> 要编写健壮和可维护的代码，您应该总是避免依赖未定义的行为，并使用为您的具体需求而设计的正确工具和函数。

进行了进一步的文档查询之后,发现`std::move`不仅能够实现相同的功能,并且可以有效处理重叠的区域,与此同时,文档还给出了如下的注释:

> 移动重叠的范围时， `std::move` 在移动到左侧（目标范围的起始在源范围外）时适合，而 `std::move_backward` 在移动到右侧（目标范围的结尾在源范围外）时适合。

因此最终确定的实现方式是插入操作使用`std::move_backward`,删除操作使用`std::move`来进行实现.

### 时间复杂度与性能分析

从课件上给出的作业测试示例来看,其消耗的时间如下:

```
Insert 50000 elements at tail
  Elapsed time: 0.002 seconds
Insert 50000 elements at head
  Elapsed time: 3.727 seconds 
Reserve and insert 50000 elements at head
  Elapsed time: 8.598 seconds
```

而我自己完成作业程序之后测试的消耗时间结果如下:

```
Insert 50000 elements at tail
  Elapsed time: 0.001 seconds
Insert 50000 elements at head
  Elapsed time: 0.066 seconds 
Reserve and insert 50000 elements at head
  Elapsed time: 1.649 seconds
```

首先考虑到可能两种算法主要区别就体现在使用标准库函数还是for循环迭代来进行拷贝/移动内存的操作,但经过文档的查询发现两种方式的时间复杂度均为**O(N)**,在实际表现上可能是编译器针对库函数有专门的优化,所以表现出了性能上的差距.

除此之外还注意到的一点就是计算机本身的性能也会对结果的运行速度产生影响.例如针对同一台笔记本(MagicBook14@i5-13500H),插电与不插电时在`Reserve and insert 50000 elements at head`这项测试时的性能差距达到了3秒多.所以计算机本身的性能差距对于运算结果的影响也是不可忽视的.

## 🖨️Test Results

```
Making foo[] grow:
size/capacity is 0 / 16
size/capacity becomes 17 / 32
size/capacity becomes 33 / 64
size/capacity becomes 65 / 128
size/capacity becomes 129 / 256
size/capacity becomes 257 / 512
size/capacity becomes 513 / 1024
size/capacity becomes 1025 / 2048
size/capacity becomes 2049 / 4096
size/capacity becomes 4097 / 8192
size/capacity becomes 8193 / 16384
size/capacity becomes 16385 / 32768
size/capacity becomes 32769 / 65536

Insert 50000 elements at tail
  Elapsed time: 0.001 seconds
Insert 50000 elements at head
  Elapsed time: 0.066 seconds 
Reserve and insert 50000 elements at head
  Elapsed time: 1.649 seconds
```

## 🪲Problems

时间复杂度这个环节有一个地方有点意思:

针对以下函数:

```c++
void IntVector::Insert(int idx, int val)
{
    // TODO: 按算法思路实现Insert
    assert(idx<=m_size);

    // 重新分配内存空间
    if(m_size==m_capacity) Reserve(m_capacity*2);
    m_size++;

    std::move_backward(m_data+idx,m_data+m_size-1,m_data+m_size);

    m_data[idx]=val;
}
```

如果将`m_size++;`这一句移动到`if(m_size==m_capacity) Reserve(m_capacity*2);`之前,程序执行的效率将会获得部分显著的提升,并且依然也能完成正常的插入操作.唯一的区别在于之前几列的测试输出结果可能会略微有点区别(以下测试平台为MagicBook14@i5-13500H,不插电):

**`m_size++`在`if`句后的测试结果:**

```
Making foo[] grow:
size/capacity is 0 / 16
size/capacity becomes 17 / 32
......
size/capacity becomes 32769 / 65536

Insert 50000 elements at tail
  Elapsed time: 0.001 seconds
Insert 50000 elements at head
  Elapsed time: 0.126 seconds 
Reserve and insert 50000 elements at head
  Elapsed time: 4.746 seconds 
```

**`m_size++`在`if`句前的测试结果:**

```
Making foo[] grow:
size/capacity is 0 / 16
size/capacity becomes 16 / 32
......
size/capacity becomes 32768 / 65536

Insert 50000 elements at tail
  Elapsed time: 0.004 seconds 
Insert 50000 elements at head
  Elapsed time: 0.204 seconds 
Reserve and insert 50000 elements at head
  Elapsed time: 0.154 seconds 
```

- 首先在前面几行:内存重新分配的环节向前移动了一步;
- `Insert 50000 elements at tail`(即pushback操作)测试的效率有退步;
- `Insert 50000 elements at head`的测试效率略有进步;
- `Reserve and insert 50000 elements at head`的测试效率大幅提升;

针对这里的性能差异,其造成的原因有待考证.
