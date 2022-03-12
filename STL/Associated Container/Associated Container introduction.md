# 关联容器
|类型|Description|
|------|------|
|map|map.h|
|set|set.h|
|multimap|map.h|
|multiset|set.h|
|unorder_map|unorder_map.h|
|unorder_set|unorder_set.h|

* 关联容器的区分标准：
1. map或set
2. 是否允许关键字重复（nulti）
3. 是否有序

|关联容器成员别名||
|-------|------|
|key_type|表示map的key值类型，表示set的元素类型（key_type和value_type一致）。key_type一定是const|
|mapped_type|表示map的value类型|
|value_type|表示map的元素类型，为pair<key_type, mapped_type>, 表示set的元素类型|
```c++
set<string>::value_type v1; // v1是string
map<string, int>::value_type v2; // v3是pair<string, int>
```

### 关键字类型要求
1. 关键字类型必须定义比较方法，且比较方法应该是*严格弱序*
2. 比较方法可以是系统定义，也可以是自定义
```c++
bool compareIsbn(const Sale_data &lhs, const Sale_data &rhs)
{
    return lhs.isbn() < rhs.isbn();
}

// 当set元素是结构体时，必须同时定义该元素的比较类型
multiset<Sales_data, decltype(compareIsbn)*> bookstore(compareIsbn);
```
## Pair
*定义*：
1. Pair定义了一对元素
2. 定义在头文件utility中
3. 数据成员是 public的，通过first，second分别访问第一个和第二个数据成员

|pair操作|描述|
|------|------|
|pair<T1, T2>p;|对数据成员进行值初始化|
|pair<T1, T2>p(v1,v2)|firsr和second数据成员分别用v1和v2进行初始化|
|pair<T1, T2>p = {v1, v2}|对pair进行隐式初始化|
|make_pair(v1, v2)|返回用v1和v2初始化的pair，成员数据的类型从v1，v2推断出来|
|p1 == p2 和 p1 != p2|==说明first和second成员分别相等|
