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
            r[p++]=Range(0,_SIZE-1);

            while(p)
            {
                Range range=r[--p];
                if(range.start>=range.end) continue;
                _TYPE mid=m_data[range.end];
                int left=range.start,right=range.end-1;

                while(left<right)
                {
                    while(m_data[left]<mid && left<right) left++;
                    while(m_data[right]>=mid && left<right) right--;
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
        
        struct Range
        {
            int start,end;
            Range(int s=0,int e=0){start=s,end=e;}
        };
    };
}