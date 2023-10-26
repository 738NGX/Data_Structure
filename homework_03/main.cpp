#include <iostream>
#include "fix.h"

using namespace std;

template<class T>
void TestCase(const string &str,T (*func)(const string&))
{
    cout<<"input : "<<str<<endl;
    cout<<"output: "<<(*func)(str)<<endl;
    cout<<"----------"<<endl;
}

int main()
{
    TestCase("3+4*2/(1-5)^2^3",ConvertToPostfix);
    TestCase("31+23-45*54/(9-6)^4",ConvertToPostfix);
    
    TestCase("3+4*2/(1-5)^2^3",AddBrackets);
    TestCase("31+23-45*54/(9-6)^4",AddBrackets);
    
    TestCase("(3+((4*2)/((1-5)^(2^3))))",Evaluate);
    TestCase("((31+23)-((45*54)/((9-6)^4)))",Evaluate);
    
    return 0;
}