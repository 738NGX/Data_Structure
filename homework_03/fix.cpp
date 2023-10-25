#include "fix.h"

#include <iostream>
#include <stack>
#include <map>

using std::string;
using std::stack;

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
            //postfix.append(" ");
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