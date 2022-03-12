# 容器库概览
## 类型
*vector*：可变大小数组。支持快速随机访问。连续内存，只在尾部插入或删除元素快

*deque*：双端队列。支持快速随机访问。连续内存，只在头或尾部插入或删除元素快

*list*：双向链表。支持双向 顺序访问。在任何位置插入或删除元素速度快

*forward_list*:单向链表，只支持单向顺序访问，在任何位置插入或删除元素速度快

*array*:固定大小数组。支持随机访问，不支持删除插入元素

*string*：专门保存char的vector容器。


# 容器库概览
| 类型别名 | description ｜
| ------ | ------ |
| iterator | 此容器的迭代器类型 |
| const_iterator | 可以读取元素，不能修改元素的迭代器类型 |
| size_type | 无符号整数类型，可以保存容器的最大大小 |
| different_type | 带符号整数类型，足够保存两个迭代器之间的距离 |
| value_type | 元素类型 |
| reference | 元素的左值类型，含义是 value_type& |
| const_reference | 元素的const左值类型，含义是 const value_type& |


### 构造函数
1. C c
2. C c(c2)
3. C c1 = c2 :c1和c2容器类型相同，元素类型相同，对array而言，两者大小相同
4. C c(b,e):
   c初始化为迭代器b和e指定范围中的元素拷贝（范围：[b,e)）
   容器类型不要求相同，元素类型只要能相互转化即可
5. C c{a,b,c...}
6. C c = {a,b,c...}
7.C seq(n)
8. C seq(n,t) 

### 交换
1. a.swap(b)：交换c1和c2的元素，c1和c2的类型必须相同
2. swap(1,b)

### 替换
1. seq.assign(b,e):将seq中的元素替换为迭代器b，e所表示范围内的元素。（迭代器b，e不能指向seq中的元素）
2. seq.assign(il):将seq中的元素替换为列表il的元素
3. seq(n,t):将seq中的元素替换为n个t

* 注意点：
*赋值*
0. 赋值的核心是右侧元素对左侧的替换！  
1. 赋值操作会导致指向容器内部的迭代器，指针，引用失效。
2. 赋值运算符要求左右对象具有相同类型。将右对象的元素*拷贝*到左对象
3. assign允许赋值的两方元素不同但相融（例如：char*和string）

*swap*
0. swap的核心是右侧和左侧容器内部的数据结构的交换！
1. swap操作不会导致容器内部的迭代器，指针，引用失效。
例子：
```c++
vector<string> svec1(10);
vector<string> svec2(24);
```
大部分容器指向容器的迭代器，引用和指针在swap操作之后都不会失效。仍然指向swap操作之前所指向的那些元素。
例如：iter1之前指向svec1[3]，swap之后指向svec2[3]。
swap操作在常数时间内完成。

对string调用swap会导致迭代器，引用和指针失效。

对array调用swap会交换两个对象中的元素。swap操作操作时间依赖元素个数。
例如：iter1之前指向array[3],swap之后仍指向array[3].


### 大小
1. c.size()
2. c.max_size()
3. c.empty()

### 添加/删除元素
| Operation | Description |
| ------ | ---------- |
| c.insert(args) | 将args拷贝进c |
| c.emplace(inits) | 使用inits构造c中的一个元素 |
| c.erase(args) | 删除args指定的元素 |
| c.clear() | 删除c所有元素，返回void |

### 获取迭代器
| Operation | Description |
| ------ | ---------- |
| c.begin(), c.end() | 返回c的首元素，尾元素之后的迭代器 |
| c.cbegin(), c.cend() | 返回const_iterator |

### 反向容器的额外成员
| Operation | Description |
| ------ | ---------- |
| reverse_iterator | 按逆序寻址元素的迭代器 |
| const_reverse_iterator | 不能修改元素的逆序迭代器 |
| c.rbend(), c.rend() | c尾元素的迭代器，c首元素之前的迭代器 |
| c.crbegin(), c.crend() | c尾元素的const迭代器，c首元素之前的const迭代器 |
* 对反向迭代器的操作，是对正向迭代器的颠倒操作

### 关系运算符
==, !=, >, >=, <, <=
1. 关系运算符是逐个比较
2. 比较结果依赖于第一个不相同元素的比较结果。如果所有元素都相等，则比较两对象的元素个数。
3. 对于自己的定义的类。要重载==和<才能用关系运算符。

# 迭代器
## 迭代器范围
【begin， end）：左闭合区间

# ARRAY
## ARRAY初始化
1. 定义：要指定元素类型和个数
2. 例子：
   array<int, 10> ia1;
   array<int, 10> ia2 = {42}; // 除首元素外，其余元素执行默认初始化

