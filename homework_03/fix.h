#pragma once
#include <iostream>
#include <map>
#include <sstream>

bool IsOperator(char c);

int Precedence(char c);

/*判断c1与c2两个运算符的优先性,c1低于c2,或c1等于c2但右结合时,返回false;反之返回true*/
bool ComparePrecedence(char c1,char c2);

/*将字符串转换为浮点数*/
float str2f(const std::string& str);

/*将浮点数转换为字符串*/
std::string f2str(float n);

float CalculateString(const std::string &infix);

std::string ConvertToPostfix(const std::string &infix);

std::string AddBrackets(const std::string &infix);

float Evaluate(const std::string &infixBracket);