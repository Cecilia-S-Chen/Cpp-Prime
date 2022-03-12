# 顺序容器
## 添加元素
|Operation|Description|
|--------|----------|
|c.push_back(t)||
|c.emplace_back(args)|在尾部创建值为args的元素|
|c.push_front(t)||
|c.emplace_front(args)|在头部创建值为args的元素|
|c.insert(p,t)||
|c.emplace(p,args)||
|c.insert(p,b,e)|将迭代器b,e范围内的元素插入p指向的元素*之前*。b,e不能指向c中的元素。返回新添加的第一个元素的迭代器。如b,e范围为空，则返回p。|
|c.insert(p,il)|插入花括号初始化列表il|

* 注意点：
1. forward_list有专属的insert和emplace
2. forward_list不支持push_back和emplace_back
3. vector和string不支持push_front和emplace_front
4. 向顺序容器插入元素会导致所有指向容器的迭代器，引用和指针失效。
    因为可能引起部分元素的后移。或者所有元素搬迁到新内存中。
5. 所有添加元素的操作都是将外部元素*拷贝*到容器中。
6. 因为insert插入元素的位置可以是end()的位置,所以要将元素插入所指位置之前。
7. 只有insert操作返回迭代器。其他大部分操作返回void。
```c++
list<string> lst;
auto iter = lst.begin();
while(cin>> word) {
    iter = lst.insert(iter, word);
} // 等价于循环执行push_front 
```
7. emplace系列是创造新元素，而不是拷贝元素。

## 访问元素
1. 获取首元素
```c++
auto begin = *c.begin();
auto begin = c.front();
```
2. 获取尾元素
```c++
auto end = *c.end();
auto end = c.back(); // forward_list容器没有back()元素
```

3. c[n], 如n越界，则函数的的行为未定义
    c.at(n):若n越界，则会报错out of range。at只适用于string、vector、deque、array
* 在访问元素前，要确保容器非空

## 删除元素
|Operation|Description|
|------|-------|
|c.pop_back()||
|c.pop_front()||
|c.erase(p)||
|c.erase(b,e)|删除范围：[b,e)|
|c.clear()||
* 注意点
1. forward_list不支持push_back();
2. vector,string 不支持push_front();
3. 除了首位允许删除的元素外。删除其他的元素，都会导致之后的迭代器失效。
4. 除了erase返回*删除后元素之后位置*的迭代器！！！其他操作返回void

## 改变容器的大小
* resize：用于扩大或缩小容器。
    * 扩大容器：采用提供的对象或默认初始化来填充容器多余的元素
    * 缩小容器：舍弃超过范围的元素。导致被舍弃元素的迭代器失效。
```c++
list<int> ilist(10, 42); // size为10
list.resize(15); // size为15，5个新元素为默认值0
list.resize(25, -1); // size为25，10个新元素为-1
list.resize(5); // 从lst末尾删除20个元素
```