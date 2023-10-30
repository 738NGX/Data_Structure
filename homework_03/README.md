# Homework 03

## 📜Demands

1. 给你一个 (中缀)算术表达式，按优先级添加括号
    `std::string ConvertToPostfix(const std::string &infix);`
    输入表达式`31+23-45*54/(9-6)^4`
    加括号` ((31+23)-((45*54)/((9-6)^4)))`
    只考虑运算符**+一x÷^()**
    提示:
    参考`std::string ConvertToPostfix(const std::string &infix);`
    需要用一个`stack<string>`用来生成结果

2. 计算添加了括号的中缀表达式(直接计算，不能转化为后缀)
    `float Evaluate(const std::string &infixBracket);`

## 📝Efforts

### 辅助函数

为了辅助实现目标函数功能,声明了以下函数:

```c++
/*判断c是否为一个运算符号*/
bool IsOperator(char c);

/*判断运算符号c的运算优先级*/
int Precedence(char c);

/*判断c1与c2两个运算符的优先性,c1低于c2,或c1等于c2但右结合时,返回false;反之返回true*/
bool ComparePrecedence(char c1,char c2);

/*将字符串转换为浮点数*/
float str2f(const std::string& str);

/*将浮点数转换为字符串*/
std::string f2str(float n);

/*给出一个只有一个运算符号的中缀表达式,计算其结果*/
float CalculateString(const std::string &infix);
```

函数实现如下:

```c++
bool IsOperator(char c)
{
    string operators="+-*/^()";
    return operators.find(c)!=string::npos;
}

int Precedence(char c)
{
    std::map<char,int> precedence={
        {'^',4},{'*',3},{'/',3},{'+',2},
        {'-',2},{'(',0},{')',0},
    };
    return IsOperator(c) ? precedence[c] : 0;
}

bool ComparePrecedence(char c1,char c2)
{
    if(Precedence(c1)==Precedence(c2))
        return c1!='^';
    return Precedence(c1)>Precedence(c2);
}

float str2f(const string& str)
{
    std::istringstream iss(str);
    float num;
    iss>>num;
    return num;    
}

string f2str(float n)
{
    std::stringstream strStream;  
	strStream<<n; 
	return strStream.str();  
}

float CalculateString(const string &infix)
{
    string left_s,right_s;
    char op;
    bool inputing_right=false;
    
    for(auto ch:infix)
    {
        if(IsOperator(ch))
        {
            op=ch;
            inputing_right=true;
            continue;
        }
        if(!inputing_right) left_s.push_back(ch);
        else right_s.push_back(ch);
    }
    if(!inputing_right) return str2f(left_s);
    float left=str2f(left_s),right=str2f(right_s);
    switch(op)
    {
        case '+': return left+right;
        case '-': return left-right;
        case '*': return left*right;
        case '/': return left/right;
        case '^': return pow(left,right);
        default : return 0;
    }
}
```

### 中缀表达式转换后缀表达式

为了实现中缀表达式加括号,必须先得知运算顺序,于是先将其转换为后缀表达式

```c++
string ConvertToPostfix(const string &infix)
{
    string postfix;
    stack<char> stk;
    stk.push('#');

    for(auto ch:infix)
    {
        if(!IsOperator(ch))
        {
            postfix.append(1,ch);
            continue;
        }
        if(ch=='(')
        {
            stk.push(ch);
            continue;
        }
        if(ch==')')
        {
            while(stk.top()!='(')
            {
                postfix.append(1,stk.top());
                stk.pop();
            }
            stk.pop();
            continue;
        }
        while(stk.top()!='(' && ComparePrecedence(stk.top(),ch))
        {
            postfix.append(1,stk.top());
            stk.pop();
        }
        postfix.append(" ");
        stk.push(ch);
    }

    while(stk.top()!='#')
    {
        postfix.append(1,stk.top());
        postfix.append(" ");
        stk.pop();
    }

    return postfix;
}
```

### 中缀表达式添加括号

空格作为数字入栈的标志;运算符作为加括号,出栈合并再入栈的标志;

```c++
string AddBrackets(const string &infix)
{
    string postfix=ConvertToPostfix(infix);
    string num;
    stack<string> stk;

    for(auto ch:postfix)
    {
        if(ch==' ')
        {
            if(num.size()) stk.push(num);
            num.clear();
            continue;
        }
        if(!IsOperator(ch))
        {
            num.push_back(ch);
            continue;
        }
        if(num.size()==0)
        {
            num=stk.top();
            stk.pop();
        }
        string tmp="("+stk.top()+ch+num+")";
        stk.pop();
        num.clear();
        stk.push(tmp);
    }
    return stk.top();
}
```

### 计算添加了括号的中缀表达式

右括号作为出栈的标志,合并直到左括号的所有内容;

```c++
float Evaluate(const string &infixBracket)
{
    stack<char> stk;
    stk.push('#');
    for(auto ch:infixBracket)
    {
        if(ch==')')
        {
            string tmp_fix;
            while(stk.top()!='(')
            {
                tmp_fix.push_back(stk.top());
                stk.pop();
            }
            stk.pop();
            std::reverse(tmp_fix.begin(),tmp_fix.end());
            string tmp_res=f2str(CalculateString(tmp_fix));
            for(auto c:tmp_res) stk.push(c);
        }
        else stk.push(ch);
    }
    string res;
    while(stk.top()!='#')
    {
        res.push_back(stk.top());
        stk.pop();
    }
    std::reverse(res.begin(),res.end());

    return str2f(res);
}
```

## 🖨️Test Results

测试代码:

```c++
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
```
运行结果:

```
input : 3+4*2/(1-5)^2^3
output: 3 4 2* 1 5- 2 3^ ^ / +
----------
input : 31+23-45*54/(9-6)^4
output: 31 23+ 45 54* 9 6- 4^ / -
----------
input : 3+4*2/(1-5)^2^3
output: (3+((4*2)/((1-5)^(2^3))))
----------
input : 31+23-45*54/(9-6)^4
output: ((31+23)-((45*54)/((9-6)^4)))
----------
input : (3+((4*2)/((1-5)^(2^3))))
output: 3
----------
input : ((31+23)-((45*54)/((9-6)^4)))
output: 24
----------
```

