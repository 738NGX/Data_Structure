# Homework 02-实现Sufe::IntVector

动态数组的封装

## 📜Demands

- 在`Sufe::IntVector`里实现Insert/Delete算法
    - `void Insert(int idx, int val);`
    - `void Delete(int idx);`
    - `void Pushback(int val);`
- 分别测试插入5万+数据元素的时间（AutoTimer）
    - 一直插入为第一个元素: `Insert(0, val)`
    - 一直插入为最后一个元素：`Pushback(val)`