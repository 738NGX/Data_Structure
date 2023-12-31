#include <cassert>
#include <algorithm>
#include "IntVector.h"

using namespace std;

namespace Sufe
{
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

    void IntVector::Insert(int idx, int val)
    {
        // TODO: 按算法思路实现Insert
        assert(idx<=m_size);
        
        // 重新分配内存空间
        if(m_size==m_capacity) Reserve(m_capacity*2);
        m_size++;

        // 传统的迭代方式,额外的时间开销
        //for(int i=m_size-1;i>idx;i--)
        //{
        //    m_data[i]=m_data[i-1];
        //}

        // 如果[m_data+idx,m_data+m_size-1)与复制目标范围重叠,行为未定义(cppreference.com)
        //std::copy(m_data+idx,m_data+m_size-1,m_data+idx+1);
        
        // 范围的重叠在形式上是允许的，但是会导致结果的顺序不可预测(cppreference.com)
        //std::copy_n(m_data+idx,m_size-idx-1,m_data+idx+1);
        
        // 移动重叠的范围时,std::move 在移动到左侧(目标范围的起始在源范围外)时适合，而std::move_backward在移动到右侧(目标范围的结尾在源范围外)时适合。
        std::move_backward(m_data+idx,m_data+m_size-1,m_data+m_size);

        m_data[idx]=val;
    }

    void IntVector::Delete(int idx)
    {
        // TODO: 按算法思路实现Delete
        assert(idx<=m_size);
        
        std::move(m_data+idx+1,m_data+m_size,m_data+idx);

        // 重新分配内存空间
        if(m_size<=m_capacity/4&&m_capacity>16) Reserve(m_capacity/2);
        m_size--;
    }

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

    int &IntVector::At(int idx)
    {
        assert(idx >= 0 && idx < m_size);
        return m_data[idx];
    }

    void IntVector::Reset()
    {
        if (m_data)
        {
            delete[] m_data;
            m_data = nullptr;
            m_capacity = m_size = 0;
        }
    }

    std::ostream &operator<<(std::ostream &out, const IntVector &arr)
    {
        for (int i = 0; i < arr.Size(); i++)
        {
            out << arr[i] << " ";
        }
        return out;
    }
}
