#include <iostream>
#include "binarytree.h"

using namespace std;

int main()
{
    vector<char> symbols{'a', 'b', 'c', 'd', 'e', 'f',
                         'g', 'h', 'i', 'j', 'k', 'l',
                         'm', 'n', 'o', 'p', 'q', 'r',
                         's', 't', 'u', 'v', 'w', 'x',
                         'y', 'z', ' '};

    vector<int> freq{81, 15, 28, 42, 127, 22,
                     20, 61, 70, 2, 8, 40,
                     24, 67, 75, 19, 1, 60,
                     63, 90, 28, 10, 23, 2,
                     20, 1, 99};

    Sufe::BinaryTree huffman(symbols,freq);
    string message=huffman.Encode("the quick brown fox jumps over a lazy dog");
    cout<<"Huffman message has length of "<<message.size()<<endl;
    cout<<"The original text is: "<<huffman.Decode(message)<<endl;

    return 0;
}
