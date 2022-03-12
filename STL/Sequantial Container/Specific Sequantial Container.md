# Forward_list
* 核心：forward_list是单向链表。
  所以只能对指定元素之后的元素操作（因为单向链表可以快速查找后继节点）。
  因此没有front()相关操作。
* 定义 *首前* 迭代器，位于首元素之前。

### forward_list 特有操作
|Operation|Description|
|---------|-----------|
|lst.before_begin()|返回指向首元素之前的迭代器|
|lst.cbefore_begin()||
|lst.insert_after(p,t)|在p之后插入对象t，返回最后一个插入元素的迭代器|
|lst.insert_after(p,n,t)|在p之后插入n个t|
|lst.insert_after(p,b,e)|b,e是表示范围的一对迭代器，不能指向lst内|
|lst.insert_after(p,il)|在p后插入初始列表il|
|emplace_after(p,args)|使用args在p后创建一个元素，返回指向该元素的迭代器|
|lst.erase_after(p)|删除p之后的元素|
|lst.erase_after(b,e)|删除元素范围[b,e),返回指向被删元素的下一个（e元素）的迭代器|


# Vector
|容器大小管理|Description|
|------|------|
|c.shrink_to_fit()|适用于vector、string、deque.将capacity减少为与size()相同大小|
|c.capacity()|适用于vector和string。该容器对象在不重新分配内存的情况下，最多保存多少元素|
|c.reserve(n)|适用于vector和string。将capacity扩大为n|
* 比较resize和reserve
  * resize根据参数，会扩大或缩小容器内存
  * reserve根据参数n，会扩大capacity。如果n小于capacity，则capacity不变。
reserve只会扩大内存，不会缩小内存。
    
# String
|Operation|Description|
|-------|-------|
|string s(cp, n)|拷贝cp前n个元素，n不应该超出cp的长度|
|string s(s2,pos2)|从pos2开始拷贝s2|
|string s(s2, pos2, len2)|从pos2开始拷贝s2，长度为len2。如果长度超过范围，则只会拷贝到s2的空字符串为止。|
|s.substr(pos,n)|返回一个从pos开始，长度为n的子字符串|
|s.insert(s_pos, num, 元素)|在指定s中的位置前，插入num个元素|
|s.insert(s_pos, pos2)|将从pos2开始的字符串，插入s_pos前|
|s.append(s1)|在s的尾部增加字符串，返回s引用|
|s.erase(s_pos,num)|从s_pos开始，删除num个字符，返回s引用|
|s.replace(pos1, len1, s1)|replace等同与erase+insert，在pos1的位置后删除len1个元素，再插入s1字符串。返回s的引用|
|s.assign(args)|将s中的字符替换为args中的字符，返回指向s的引用|

* 的insert参数接受下标和迭代器。如果入参是迭代器，就返回迭代器。如果入参是下标，返回值也是下标。
* 没有特殊指令下，拷贝遇到空字符串停止。


### 查找
|Operation|Description|
|------|------|
|s.find(args)|查找s中args第一次出现的位置|
|s.rfind(args)|查找s中args最后一次出现的位置|
|s.find_first_of(args)|在s中查找args中*任何一个字符*第一次出现的位置|
|s.find_last_of(args)|在s中查找args中*任何一个字符*最后一次出现的位置|
|s.find_first_not_of|在s中查找第一个不在args中的字符位置|
|s.find_last_not_of|在s中查找最后一个不在args中的字符位置|

* arga必须是以下形式

|args|含义|
|-------|------|
|c,pos||  
|s2,pos||
|cp,pos||
|cp,pos,n||

* 如果找到了返回对应下标 string::size_type,如果没找到返回string::npos


### 比较
compare函数根据比较的结果：大于、等于还是小于。返回0，正数或负数

|Param|Description|
|-------|------|
|s2|比较s和s2|
|pos1,n1,s2|将s从pos1开始的n1个字符和s2比较|
|pos1,n1,s2,pos2,n2|将s中从pos1开始的n1个字符与s2中从pos2开始的n2个字符进行比较|
|cp|cp是以空字符结尾的字符数组|
|pos1,n1,cp|将s从pos1开始的n1个字符与cp字符数组进行比较|
|pos1,n1,cp,n2|将s从pos1开始的n1个字符与cp的n2个字符进行比较|


### 数值转化
|Operation|Description|
|-------|------|
|to_string(val)||
|stoi(s,p,b)|i为int|
|stol(s,p,b)|l为long|
|stoul(s,p,b)|ul为unsigned long|
|stoll(s,p,b)|ll为long long|
|stoull(s,p,b)|unsigned long long|
|stof(s,p)|float|
|stod(s,p)|double|
|stold(s,p)|long double|
* p用来表示保存s中第一个非数值字符的下标。默认值为0，表示不保存
* b表示转换所用的基数。默认为10
