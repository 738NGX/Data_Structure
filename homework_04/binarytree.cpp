#include <iostream>
#include <queue>
#include <vector>
#include <stack>
#include <cassert>
#include "heap.h"
#include "binarytree.h"
using namespace std;

namespace Sufe
{
    BinaryTree::BinaryTree(const vector<int> &preorder, const vector<int> &inorder)
    {
        if(preorder.size()!=inorder.size())
        {
            cout<<"Invalid size"<<endl;
            return;
        }

        m_root=BuildTree_Iterative(preorder, inorder);
    }

    BinaryTree::BinaryTree(const std::vector<char> &symbols, const std::vector<int> &freq)
        : m_root(nullptr)
    {
        Heap minheap;
        if(symbols.size()!=freq.size())
        {
            cout<<"Invalid size"<<endl;
            return;
        }
        for(unsigned int i=0;i<symbols.size();i++)
        {
            minheap.InsertKey(new Node(freq[i],symbols[i]));
        }
        while(minheap.Size()>1)
        {
            Node *l=minheap.ExtractMin();
            Node *r=minheap.ExtractMin();
            Node *m=new Node(l->key+r->key,l,r);
            minheap.InsertKey(m);
        }
        m_root=minheap.ExtractMin();
    }

    BinaryTree::BinaryTree(const BinaryTree &other)
        : m_root(nullptr)
    {
        m_root=Clone(other.m_root);
    }

    BinaryTree &BinaryTree::operator=(const BinaryTree &rhs)
    {
        if(this == &rhs)
        {
            return *this;
        }

        Reset();
        m_root=Clone(rhs.m_root);

        return *this;
    }

    void BinaryTree::FindCodes(Node *root,string path,map<char,string> &output)
    {
        if(root==nullptr) return;
        if(root->symbol!=0)
        {
            output[root->symbol]=path;
            return;
        }
        FindCodes(root->left,path+"0",output);
        FindCodes(root->right,path+"1",output);
    }

    string BinaryTree::Encode(string txt)
    {
        string strbin;
        map<char,string> dict;
        FindCodes(m_root,"",dict);
        for(char ch:txt) strbin+=dict[ch];
        return strbin;
    }

    string BinaryTree::Decode(string binary)
    {
        string strtxt;
        Node* ptr=m_root;
        for(char ch:binary)
        {
            if(ch=='0') ptr=ptr->left;
            else if(ch=='1') ptr=ptr->right;
            if(ptr->symbol!=0)
            {
                strtxt.push_back(ptr->symbol);
                ptr=m_root;
            }
        }
        return strtxt;
    }

    void BinaryTree::LevelOrder()
    {
        queue<const Node *> treeQueue;

        if(m_root!=nullptr)
        {
            treeQueue.push(m_root);
        }

        int size=1;
        while (!treeQueue.empty())
        {
            const Node *node=treeQueue.front();
            treeQueue.pop();
            if(node)
            {
                cout<<node->key<<","<<node->symbol<<" ";
                treeQueue.push(node->left);
                treeQueue.push(node->right);
            }
            else
            {
                cout<<"$ ";
            }

            if(--size == 0)
            {
                cout<<endl;
                size=treeQueue.size();
            }
        }
    }

    void BinaryTree::PostOrder_Iterative()
    {
        if(m_root == nullptr)
        {
            return;
        }

        stack<const Node *> output;
        stack<const Node *> stk;
        stk.push(m_root);

        while (!stk.empty())
        {
            // Pop top element from stk;
            const Node *top=stk.top();
            stk.pop();

            // Push top element to output
            output.push(top);

            // push left and right node to stk;
            if(top->left!=nullptr)
            {
                stk.push(top->left);
            }

            if(top->right!=nullptr)
            {
                stk.push(top->right);
            }
        }

        // print result in output stack
        while (!output.empty())
        {
            cout<<output.top()->key<<" ";
            output.pop();
        }
        cout<<endl;
    }

    void BinaryTree::InOrder_Iterative()
    {
        stack<const Node *> stk;
        const Node *curr=m_root;

        while (!stk.empty() || curr)
        {
            while (curr)
            {
                stk.push(curr);
                curr=curr->left;
            }

            curr=stk.top();
            stk.pop();

            cout<<curr->key<<" ";
            curr=curr->right;
        }
        cout<<endl;
    }

    void BinaryTree::PreOrder_Iterative()
    {
        stack<const Node *> stk;
        if(m_root)
        {
            stk.push(m_root);
        }

        while (!stk.empty())
        {
            const Node *node=stk.top();
            stk.pop();

            cout<<node->key<<" ";

            if(node->right)
            {
                stk.push(node->right);
            }
            if(node->left)
            {
                stk.push(node->left);
            }
        }
        cout<<endl;
    }

    void BinaryTree::Reset()
    {
        Release(m_root);
        m_root=nullptr;
    }

    void BinaryTree::Release(Node *root)
    {
        if(root == nullptr)
        {
            return;
        }
        Release(root->left);
        Release(root->right);
        delete root;
    }

    Node *BinaryTree::Clone(const Node *root)
    {
        if(root == nullptr)
        {
            return nullptr;
        }
        Node *nd=new Node(root->key);
        nd->left=Clone(root->left);
        nd->right=Clone(root->right);

        return nd;
    }

    Node *BinaryTree::BuildTree(
        const vector<int> &preorder, int pre,
        const vector<int> &inorder, int lh, int rh)
    {
        if(lh > rh)
        {
            return nullptr;
        }
        int key=preorder.at(pre);
        Node *root=new Node(key);

        int index=lh;
        for (; index <= rh; index++)
        {
            if(inorder.at(index) == key)
            {
                break;
            }
        }
        assert(index <= rh);

        root->left=BuildTree(preorder, pre + 1, inorder, lh, index - 1);
        root->right=BuildTree(preorder, index - lh + pre + 1, inorder, index + 1, rh);
        return root;
    }

    Node *BinaryTree::BuildTree_Iterative(const vector<int> &preorder, const vector<int> &inorder)
    {
        assert(preorder.size() == inorder.size());
        // pre always points to inorder node, which is created next
        // in always points to leftmost child of right subtree, or stack top itself
        size_t pre=0, in=0;
        Node *root=new Node(preorder.at(pre++));

        stack<Node *> stk;
        stk.push(root);
        while (true)
        {
            if(inorder[in] == stk.top()->key)
            {
                Node *top=stk.top();
                stk.pop();
                in++;

                // all done
                if(in == inorder.size())
                {
                    break;
                }
                // the case that right child is empty
                if(!stk.empty() && inorder[in] == stk.top()->key)
                {
                    continue;
                }
                // set right child and push to stk.
                // Then process right subtree like a new one
                top->right=new Node(preorder.at(pre++));
                stk.push(top->right);
            }
            else
            {
                // Keep pushing left child to stk until leftmost child.
                Node *nd=new Node(preorder.at(pre++));
                stk.top()->left=nd;
                stk.push(nd);
            }
        }

        return root;
    }
}