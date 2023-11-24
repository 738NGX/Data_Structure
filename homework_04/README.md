# Homework 04-Huffman树

在计算机信息处理中，霍夫曼编码使用变长编码表对源符号（如文件中的一个字母）进行编码，其中变长编码表是通过一种评估来源符号出现概率的方法得到的，出现概率高的字母使用较短的编码，反之出现概率低的则使用较长的编码，这便使编码之后的字符串的平均长度、期望值降低，从而达到无损压缩数据的目的。

例如，在英文中，e的出现概率最高，而z的出现概率则最低。当利用霍夫曼编码对一篇英文文章进行压缩时，e极有可能用一个比特来表示，而z则可能花去25个比特（不是26）。用普通的表示方法时，每个英文字母均占用一个字节，即8个比特。二者相比，e使用了一般编码的1/8的长度，z则使用了3倍多。倘若我们能实现对于英文中各个字母出现概率的较准确的估算，就可以大幅度提高无损压缩的比例。

霍夫曼树又称最优二叉树，是一种带权路径长度最短的二叉树。所谓树的带权路径长度，就是树中所有的叶结点的权值乘上其到根结点的路径长度（若根结点为0层，叶结点到根结点的路径长度为叶结点的层数）。树的路径长度是从树根到每一结点的路径长度之和，记为$WPL=(W_1*L_1+W_2*L_2+W_3*L_3+...+W_n*L_n)$，N个权值$W_i$（i=1,2,...n）构成一棵有N个叶结点的二叉树，相应的叶结点的路径长度为$L_i$（i=1,2,...n）。可以证明霍夫曼树的WPL是最小的。

## 📜Demands

用最小堆实现基于BinaryTree的Huffman树

- 测试:对二进制文本解码
- 要求:输入一组字符以及相应的使用频率,生成BinaryTree表示的Huffman tree,并能对二进制编码解码
- 提示:在BinaryTree的自定义构造函数里，根据每个字符及其频率可以创建各自Node，然后使用最小堆，根据贪婪法取出频率最小的两个Node,合并成新的Node后插入最小堆,继续这样过程,直到只剩下一个Node作为root节点

## 📝Efforts

### 对Node重载的额外构造函数

因为源文件中只有`Node(int val) : key(val), symbol(0), left(nullptr), right(nullptr) {}`一种构造函数,实际上并不能满足后面程序实现的需求,于是重载了几种额外的构造函数如下:

```c++
Node(int val,char ch): key(val),symbol(ch),left(nullptr),right(nullptr) {}
Node(int val,Node* l,Node* r): key(val),symbol(0),left(l),right(r) {}
Node(int val,char ch,Node* l,Node* r): key(val),symbol(ch),left(l),right(r) {}
```

### 霍夫曼树构造函数

#### 需求

Build huffman tree by a list of symbols and their frequencies.

#### 贪婪法

1. 创建空最小堆,检查字母表和频率表大小是否一致;
2. 遍历字母表和频率表,两两创建节点并压入堆中;
3. 当堆大小大于1时循环执行:
    1. 连续出堆两次,按先后分别记为左右两个节点备用.
    2. 创建一个新节点,val记为左右两个节点的val总和,左右节点分别为刚刚出堆的两个节点.
    3. 新节点入堆
4. 取出堆中的唯一剩下节点,即为根节点.

#### 实现

```c++
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
```

### FindCodes

#### 需求

Find all symbols and their codes in huffman tree.Caller calls FindCodes(m_root, "", output), then results are stored in output map.The idea is to iterate all leaves, where you save symbol and its path (code).Implement is by recursion (see similar excercise: print all path from root to leaves).

#### 递归

- 空节点-直接返回;
- 含字符节点-将当前路径加入到map中后返回;
- 递归-左右子节点各递归一次;

#### 实现

```c++
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
```

### 编码与解码

#### Encode

通过FindCodes创建map,随后遍历源字符串,在map中查询结果并导出到结果字符串.

#### Decode

创建一个指向根节点的指针.遍历编码字符串,遇到字符为0指针指向左子节点,为1指向右子节点;如果指针指向的节点有字符则输出到结果字符串,同时将指针重新指回根节点.

#### 实现

```c++
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
```

## 🖨️Test Results

测试代码见`main.cpp`

运行结果:

```
Huffman message has length of 204
The original text is: the quick brown fox jumps over a lazy dog
```

