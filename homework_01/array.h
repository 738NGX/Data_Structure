#include <iostream>
#include <cassert>

namespace Sufe
{
    template <class _TYPE, int _SIZE>
    class Array
    {
    public:
        // TODO: 实现Iterator类
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

    public:
        // 缺省构造函数
        Array() : m_data{0} {}
        // TODO: 1) 实现初始化列表的构造函数
        Array(std::initializer_list<_TYPE> list):m_data{0}
        {
            assert(list.size()<=_SIZE);
            std::copy(list.begin(),list.end(),m_data);
        }

        int Size() const { return _SIZE; }

        // TODO: 2) 实现排序功能
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

        // TODO: 3) 实现begin()和end()
        Iterator begin(){return Iterator(m_data);}
        Iterator end(){return Iterator(m_data+_SIZE);}

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

    private:
        _TYPE m_data[_SIZE];
        
        // 作为Array类的私有成员以便辅助实现快速排序的结构体,记录一个数据范围的开始与结束
        struct Range
        {
            int start,end;
            Range(int s=0,int e=0){start=s,end=e;}
        };
    };
}