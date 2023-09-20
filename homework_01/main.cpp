#include <iostream>
#include "array.h"

using namespace std;
using Sufe::Array;

int main()
{
    Sufe::Array<int, 4> arr_x;
    cout << "arr_x has size " << arr_x.Size() << endl;

    // TODO: Enable following tests one by one
    Sufe::Array<int, 4> arr_4 = {3, 2, 1}; // 初始化元素个数 <= 4
    Sufe::Array<int, 7> arr_7 = {8, 4, 6, 5, 7, 9, 3};
    for (int i = 0; i < 4; i++)
    {
        arr_x.At(i) = 3 - i;
    }

    cout << "arr_4 has size " << arr_4.Size() << endl;;
    cout << "arr_7 has size " << arr_7.Size() << endl;

    cout << "initial elements of arr_7 are ";
    for (auto num : arr_7)
    {
        cout << num << " ";
    }
    cout << endl;

    // Call Sort and operator<<() overloading
    arr_7.Sort();
    cout << "sorted elements of arr_7 are " << arr_7 << endl;

    return 0;
}
