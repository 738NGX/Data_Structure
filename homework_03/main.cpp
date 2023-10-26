#include <iostream>
#include "fix.h"

using namespace std;

int main()
{
    //cout<<ConvertToPostfix("3+4*2/(1-5)^2^3")<<endl;
    //cout<<ConvertToPostfix("31+23-45*54/(9-6)^4")<<endl;
    cout<<AddBrackets("31+23-45*54/(9-6)^4")<<endl;
    cout<<AddBrackets("3+4*2/(1-5)^2^3")<<endl;
    cout<<Evaluate("((31+23)-((45*54)/((9-6)^4)))")<<endl;
    cout<<Evaluate("(3+((4*2)/((1-5)^(2^3))))")<<endl;
    return 0;
}