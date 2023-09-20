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
    };
}