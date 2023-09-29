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

### 复制构造&赋值重载

- 两种操作的实现方式类似,可以互相套用;
- 参数的私有成员不能直接在复制操作中访问,需要通过函数间接访问;

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



