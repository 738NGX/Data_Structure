#pragma once
#include <vector>
#include "binarytree.h"

namespace Sufe
{
  class Heap
  {
  public:
    // add NULL element at index 0.
    Heap() { m_data.push_back(NULL); }

    // to extract the root which is the minimum element
    Node *ExtractMin();

    // Inserts a new key: pointer to node of BinaryTree
    void InsertKey(Node *nd);

    bool IsEmpty() { return m_data.size() <= 1; }
    // Actual size without counting element at index 0
    int Size() { return m_data.size() - 1; }

  private:
    // A recursive method to heapify a subtree with root at given index
    // This method assumes that the subtrees are already heapified
    void MinHeapify(int i);

    int Parent(int i) { return i / 2; }
    // to get index of left child of node at index i
    int Left(int i) { return 2 * i; }
    // to get index of right child of node at index i
    int Right(int i) { return (2 * i + 1); }

    std::vector<Node *> m_data;
  };
}