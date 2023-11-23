#include <iostream>
#include "heap.h"

namespace Sufe
{
  // to extract the root which is the minimum element
  Node *Heap::ExtractMin()
  {
    // data[0] is a place holder.
    if (m_data.size() <= 1)
    {
      return nullptr;
    }

    // Store the minimum value, and remove it from heap
    Node *root = m_data[1];
    m_data[1] = m_data.back();
    m_data.pop_back();

    if (m_data.size() > 2)
    {
      MinHeapify(1);
    }

    return root;
  }

  // Inserts a new key 'k'
  void Heap::InsertKey(Node *nd)
  {
    // First insert the new key at the end
    m_data.push_back(nd);
    int i = (int)m_data.size() - 1;

    // Fix the min heap property if it is violated
    while (i > 1 && m_data[Parent(i)]->key > m_data[i]->key)
    {
      std::swap(m_data[i], m_data[Parent(i)]);
      i = Parent(i);
    }
  }

  void Heap::MinHeapify(int i)
  {
    int l = Left(i);
    int r = Right(i);
    int min = i;
    if (l < (int)m_data.size() && m_data[l]->key < m_data[min]->key)
    {
      min = l;
    }
    if (r < (int)m_data.size() && m_data[r]->key < m_data[min]->key)
    {
      min = r;
    }

    if (min != i)
    {
      std::swap(m_data[i], m_data[min]);
      MinHeapify(min);
    }
  }
}