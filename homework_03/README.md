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