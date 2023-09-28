#pragma once
#include <iostream>

namespace Sufe
{
  class IntVector
  {
  public:
    IntVector(int sz = 0);
    IntVector(std::initializer_list<int> list);

    ~IntVector() { Reset(); }

    // TODO: 按课件实现复制构造函数和赋值运算符重载
    IntVector &operator=(const IntVector &);
    IntVector(const IntVector &);

    // TODO: 按算法思路实现Insert和Delete
    void Delete(int idx);
    void Insert(int idx, int val);
    void Pushback(int val) { Insert(m_size, val); }

    // TODO: 按课件实现Resize和Reserve
    void Resize(int sz, int val = 0);
    void Reserve(int cap);

    int Size() const { return m_size; }
    int Capacity() const { return m_capacity; }
    int &At(int idx);
    int &operator[](int idx) { return m_data[idx]; }
    const int &operator[](int idx) const { return m_data[idx]; }
    friend std::ostream &operator<<(std::ostream &out, const IntVector &arr);

  private:
    void Reset();

    int *m_data;
    int m_size;
    int m_capacity;
  };
}
