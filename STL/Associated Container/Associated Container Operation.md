# 关联容器操作
## 添加元素
|insert操作|说明|
|-----|-----|
|c.insert(v)|返回map，包含迭代器，指向具有指定关键字的元素，以及一个指示插入是否成功的bool值|
|c.emplace(args)|与insert相同，不同点是用args构造一个元素|
|c.insert(b,e)|b,e表示迭代器范围|
|c.insert(il)|il表示初始化列表|
|c.insert(p,v)|在指定位置插入元素，返回迭代器，指向具有给定关键字的元素|
|c.emplace(p,args)||

## 删除元素
|erase操作||
|------|-----|
|c.erase(k)|从c中删除每个关键字为k的元素，返回一个size_type的值，指出删除元素的数量|
|c.erase(p)|p为迭代器，返回指向p之后的元素|
|c.erase(b,e)|删除迭代器[b,e)范围内的元素，返回e|

## 访问元素

### map的下标操作
1. 定义：通过下标运算符，或者对应的at函数查找关键字关联的值
2. 注意点： 
   1. set没有值，不能用下标查找
   2. multimap一个关键字可能对应多个值，不能用下标查找
   3. 如果下标没找到对应的值，会在map中创建一个对应的pair
   4. 因为下标查找可能会创造新元素，所有只能对非const的map使用
   
|查找操作||
|------|------|
|c.find(k)|查找第一个关键字为k对应的值，若k不在容器中，返回尾后迭代器|
|c.count(k)|返回关键字为k的元素数量|
|c.lower_bound(k)|返回迭代器，指向第一个关键字不小于k的元素|
|c.upper_bound(k)|返回迭代器，指向第一个关键字不大于k的元素|
|c.equal_range(k)|返回迭代器，表示关键字大于k的元素范围.若k不存在，则返回迭代器都为c.end()|

lower_bound，upper_bound
  1. 只适用于有序容器
  2. 如果存在指定元素，lower_bound返回元素的迭代器，如果不存在该元素，返回第一个大于该元素的迭代器。
  3. upper_bound返回第一个大于该元素的迭代器，如果没有，则返回尾后元素
  4. equal_range返回pair的first与lower_bound返回结果相同。second与upper_bound返回结果相同


    

