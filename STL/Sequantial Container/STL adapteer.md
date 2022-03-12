# 容器适配器
##适配器介绍
1. 顺序容器适配器：
* stack
* queue
* priority_queue

2. 适配器目的：将一种容器类型转化成另一种类型

3. 适配器操作

| 命令 | 解释 |
| --- | --- |
|size_type|保存当前类型最大对象个数|
|value_type|元素类型|
|container_type|实现适配器的底层容器类型|
|A a|默认构造函数创建空适配器|
|A a(b)|利用拷贝构造函数，创建拷贝b的适配器对象|
|==, !=, <, <=, >, >=|适配器支持所有关系运算符，返回底层容器比较结果|
|a.empty()|判空|
|a.size()|a中元素个数|
|swap(a,b) a.swap(b)|a与b的底层容器类型必须相同|

##定义适配器
`stack<int> stk1 ` 默认构造函数

`stack<int> stk2(deq)` 拷贝构造函数
 
`stack<string, vector<string>> str_stk (optional入参为可选项目)` 包含两个入参的构造函数，第二个入参重载默认容器类型

1. 构造stack：除了array和forward_list容器以外，任何容器都可以构造stack，不支持与size有关的操作
2. 构造queue：除stack要求外，还不能构造在vector上
3. priority_queue:除stack要求外，不能构造在list上
                    priority_queue要求随机访问。
