#include "fix.h"

#include <iostream>
#include <stack>
#include <algorithm>
#include <sstream>
#include <cmath>

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