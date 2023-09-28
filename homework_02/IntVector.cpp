#include <cassert>
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
  }

  IntVector &IntVector::operator=(const IntVector &rhs)
  {
    // TODO: 按课件实现赋值运算符重载
    return *this;
  }

  void IntVector::Insert(int idx, int val)
  {
    // TODO: 按算法思路实现Insert
  }

  void IntVector::Delete(int idx)
  {
    // TODO: 按算法思路实现Delete
  }

  void IntVector::Resize(int sz, int val)
  {
    // TODO: 按课件实现Resize
  }

  void IntVector::Reserve(int cap)
  {
    // TODO: 按课件实现Reserve
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
