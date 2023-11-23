#pragma once
#include <map>
#include <vector>
#include <string>

namespace Sufe
{
  struct Node
  {
    int key;     // binarytree node key or huffman symbol frequency
    char symbol; // huffman symbol
    Node *left;
    Node *right;
    Node(int val) : key(val), symbol(0), left(nullptr), right(nullptr) {}
  };

  class BinaryTree
  {
  public:
    // Build a binary tree based on preorder and inorder array
    BinaryTree(const std::vector<int> &preorder, const std::vector<int> &inorder);
    // TODO: implement this constructor to build huffman tree
    BinaryTree(const std::vector<char> &symbols, const std::vector<int> &freq);

    // Release tree memory recursively
    ~BinaryTree() { Reset(); }

    // Copy a tree structure, not pointer.
    BinaryTree(const BinaryTree &other);
    // Implement assigment overloading, the same as copy constructor
    BinaryTree &operator=(const BinaryTree &rhs);

    // TODO: implement Encode and Decode for huffman tree
    std::string Encode(std::string txt);
    std::string Decode(std::string binary);

    // implement iterative version of traversals.
    void LevelOrder();
    void PreOrder_Iterative();
    void InOrder_Iterative();
    void PostOrder_Iterative();

    void Reset();

  private:
    void Release(Node *root);
    Node *Clone(const Node *root);
    Node *BuildTree_Iterative(
        const std::vector<int> &preorder,
        const std::vector<int> &inorder);
    Node *BuildTree(
        const std::vector<int> &preorder, int pre,
        const std::vector<int> &inorder, int lh, int rh);

    // TODO: internal recursive method, used for encoding
    void FindCodes(Node *root, std::string path, std::map<char, std::string> &output);

    Node *m_root;
  };
}