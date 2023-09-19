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
    };

  public:
    // 缺省构造函数
    Array() : m_data{0} {}
    // TODO: 1) 实现初始化列表的构造函数
    Array(std::initializer_list<_TYPE> list);

    int Size() const { return _SIZE; }

    // TODO: 2) 实现排序功能
    void Sort();

    // TODO: 3) 实现begin()和end()
    Iterator begin();
    Iterator end();

    // TODO: 4) 实现At()和[]运算符重载
    _TYPE &At(int idx);
    _TYPE &operator[](int idx);
    const _TYPE &operator[](int index) const;

    friend std::ostream &operator<<(std::ostream &out, const Array &arr)
    {
      // TODO: 5) 实现<<运算符重载
      return out;
    }

  private:
    _TYPE m_data[_SIZE];
  };
}