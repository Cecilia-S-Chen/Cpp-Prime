###shared_ptr类
* shared_ptr定义：
  ```c++
  shared_ptr<string> p1;
  ```

* shared_ptr和unique_ptr都支持的操作：
    1. ```shared_ptr<T> unique_ptr<t>```:空智能指针，指向类型为T的对象
       
    2. p:智能指针p作为一个条件判断，如果指向一个对象，则为true
    3. *p:解引用p，获得它指向的对象
    4. p.get():返回p中保存的**指针**，在使用前必须确保指针所指的对象没有被释放
    5. ```swap(p,q) 和 q.swap(p)```:交换p和q中的指针
    
* shared_ptr独有的操作：
    1. ```make_shared<T>(args)``` 返回一个shared_ptr,指向动态分配的类型为T的对象。使用args初始化对象
    2. ```shared_ptr<T>p(q)```p是shared_ptr的拷贝，此操作会递增q中的计数器。q中的指针必须能转化成T*
    3. p = q:p和q都是shared_ptr,所保存的指针必须能相互转化。此操作会递减p的引用计数，递增q的引用计数。如果p的引用计数为0，会将p所指的内存释放
    4. p.use_count():返回与p 共享对象 的智能指针数量（自身也算一个）。
    5. p.unique():p.use_count()为1（说明只有自己指向该对象），返回true，否则返回false
    
* make_shared函数
    1. 使用方法：
    ```c++
    shared_ptr<string> p3 = make_shared<string>(10,'9');
    auto p4 = make_shared<vector<string>>(); // 传参列表为空，表示默认初始化
    ```
  make_shared是构造智能指针，指向类型为T的对象，传入参数列表必须符合类型T的某个初始化列表

