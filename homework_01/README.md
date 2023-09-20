# Homework 01-实现Sufe::Array



## 📜Demands

- 实现`std::array`的大部分功能，包括
    - For-each遍历
    - **提高**：进一步了解设计模式**Iterator**
- 基于附件*array.starter.zip*，实现课件中的`Sufe::Array`模板类功能，用给定的*main.cpp*通过测试
    - 不同初始化方式
    - 调用Size()，[]，At()，<< 输出到屏幕
    - for-each遍历
    - 调用Sort()，对数组自身排序

## 📝Efforts

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

### Iterator(迭代器)

- **迭代器模式**让用户在不知道内部实现的基础上,对容器内每个数据元素进行遍历
- 本质上还是指针

```c++
class Iterator
{
private:
    _TYPE *m_ptr;
public:
    Iterator(_TYPE *elem):m_ptr(elem){}
    _TYPE &operator*(){return *m_ptr;}
    void operator++(){++m_ptr;}
    bool operator!=(const Iterator &rhs){return m_ptr!=rhs.m_ptr;}
};

Iterator begin(){return Iterator(m_data);}
Iterator end(){return Iterator(m_data+_SIZE);}
```

### 初始化列表的构造函数

编译器对{,……}自动生成 `std::initializer_list`

```c++
Array(std::initializer_list<_TYPE> list):m_data{0}
{
    assert(list.size()<=_SIZE);
    std::copy(list.begin(),list.end(),m_data);
}
```

#### assert语句

```
void assert(int expression);
```

assert宏的原型定义在<assert.h>中，其作用是先计算表达式expression的值为假(即为0),那么它就先向stderr打印一条出错信息，然后通过条用abort来终止程序；

使用assert的缺点是，频繁的调用会极大的影响程序的性能，增加额外的开销。

在这个构造函数中,使用assert语句来防止初始化的列表容量大于之前初始设置的数组size.

### 排序

最开始的想法是直接开摆直接用`std::sort()`来完成排序,但是在生成时出现了报错,说明编译器并不支持这么干.于是最终还是决定尝试一下手写快速排序来进行实现.

#### 快速排序

快速排序，又称划分交换排序（partition-exchange sort）

**1.基本思想**

通过一趟排序将待排记录分隔成独立的两部分，其中一部分记录的关键字均比另一部分的关键字小，则可分别对这两部分记录继续进行排序，以达到整个序列有序。

**2. 实现逻辑**

快速排序使用分治法（Divide and conquer）策略来把一个序列（list）分为两个子序列（sub-lists）。

> ① 从数列中挑出一个元素，称为 “基准”（pivot），
> ② 重新排序数列，所有元素比基准值小的摆放在基准前面，所有元素比基准值大的摆在基准的后面（相同的数可以到任一边）。在这个分区退出之后，该基准就处于数列的中间位置。这个称为分区（partition）操作。
> ③ 递归地（recursive）把小于基准值元素的子数列和大于基准值元素的子数列排序。

递归到最底部时，数列的大小是零或一，也就是已经排序好了。这个算法一定会结束，因为在每次的迭代（iteration）中，它至少会把一个元素摆到它最后的位置去。

#### 实现

快速排序的实现方法有两种,一种是使用递归法,一种是使用迭代法.其优点和缺点分别记录在下表中:

|      | 递归法                                   | 迭代法                                |
| ---- | ---------------------------------------- | ------------------------------------- |
| 优点 | 代码量较少,可读性较高                    | 在同一栈帧中不断迭代,不会产生额外开销 |
| 缺点 | 函数调用和堆栈占用对时间和空间的开销较大 | 代码量更大,影响可读性                 |

在尝试两种方法之后,最终还是选择了迭代法.递归法遇到的具体问题会在**🪲Problems**章节进行详细阐述.

迭代法的实现如下:

```c++
// 作为Array类的私有成员以便辅助实现快速排序的结构体,记录一个数据范围的开始与结束
struct Range
{
    int start,end;
    Range(int s=0,int e=0){start=s,end=e;}
};

// 公有方法,实现排序功能
void Sort()
{
    Range r[_SIZE]; int p=0;
    // r[]模拟堆栈,p为数量,r[p++]为push,r[--p]为pop且取得元素
    r[p++]=Range(0,_SIZE-1);

    // 当所有排序完成后,在循环体检验p时恰好p=0,不再进入循环
    while(p)
    {
        Range range=r[--p];
        if(range.start>=range.end) continue;
        _TYPE pivot=m_data[range.end];  // 基准数统一使用末尾数
        int left=range.start,right=range.end-1;

        while(left<right)
        {
            while(m_data[left]<pivot && left<right) left++;
            while(m_data[right]>=pivot && left<right) right--;
            std::swap(m_data[left],m_data[right]);
        }
        if(m_data[left]>=m_data[range.end])
            std::swap(m_data[left],m_data[range.end]);
        else left++;

        r[p++]=Range(range.start,left-1);
        r[p++]=Range(left+1,range.end);
    }
}
```

### 运算符重载

```c++
// TODO: 4) 实现At()和[]运算符重载
_TYPE &At(int idx)
{
    assert(idx>=0 && idx<_SIZE);
    return m_data[idx];
}
_TYPE &operator[](int idx){return m_data[idx];}
const _TYPE &operator[](int index) const{return m_data[index];}

// TODO: 5) 实现<<运算符重载
friend std::ostream &operator<<(std::ostream &out, const Array &arr)
{
    for(size_t i=0;i<_SIZE;i++)
    {
    	out<<arr[i]<<" ";
    }
    return out;
}
```

## 🖨️Test Results

```
arr_x has size 4
arr_4 has size 4
arr_7 has size 7
initial elements of arr_7 are 8 4 6 5 7 9 3
sorted elements of arr_7 are 3 4 5 6 7 8 9
```

## 🪲Problems

### Makefile

关于makefile除了上述在**📝Efforts**章节中提到的强制以cmd运行可能会出现的兼容性问题,还存在有这些问题:

- vscode&C++ extension环境下,可以正常生成(和直接在命令行中运行make命令一样),但是无法通过vscode进入到调试界面;
- 可以通过Makefile Tools这个插件正常进入到调试,但是如果目录下没有build这个文件夹的话,会生成失败;
- Makefile Tools这个插件偶尔会出现生成的exe仍然是修改前的上一版代码的情况(没有彻底覆盖上一版)

### 快速排序

一开始采用的是递归法来实现快排,代码如下:

```c++
void quick_sort(int start,int end)
{
    if(start>=end) return;
    _TYPE pivot=m_data[end];
    int left=start,right=end-1;

    while(left<right)
    {
        while(m_data[left]<pivot && left<right) left++;
        while(m_data[right]>=pivot && left<right) right--;
        std::swap(m_data[left],m_data[right]);
    }
    if(m_data[left]>=m_data[end])
        std::swap(m_data[left],m_data[end]);
    else left++;

    quick_sort(start,left-1);
    quick_sort(left+1,end);
}

void Sort(){quick_sort(0,_SIZE-1);}
```

但是主要发现了两个问题:

- `_TYPE pivot=m_data[end];`这一句并没能成功赋值,在调试时发现`pivot`的值一直为0;
- 受上一条影响,排序后的结果为0 3 4 5 6 7 8,即9变成了0;

怀疑是存在潜在的数组越界问题,但是编译器并没有给出报错.于是在最后综合权衡下,还是选择了迭代法来进行实现.

## 📓Logs

- 2023.9.19 开工,TODO除了排序部分全部完成;
- 2023.9.20 TODO全部完成,程序测试完成,文档写作完成,作业上交完成;

