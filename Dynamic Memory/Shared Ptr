#include<iostream>
#include<memory>
using namespace std;
/*
# shared_ptr类
        * shared_ptr定义： shared_ptr<string> p1;

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
            make_shared是构造智能指针，指向类型为T的对象，传入参数列表必须符合类型T的某个构造函数的入参列表

        * share_ptr的拷贝和赋值
            1. 核心：当进行拷贝和赋值时，shared_ptr会记录有多少个shared_ptr指向自己创建的这个对象。

            2. 方法：引用计数（每个shared_ptr独有）

            （1）当拷贝一个shared_ptr，该shared_ptr的的计数器就会增加

            （2）当给shared_ptr赋予新值或是shared_ptr被销毁，计数器就会递减

            （3）一旦shared_ptr所指向的对象的计数器变为0时，就会自动释放自己所管理的对象
*/


/*
     * shared_ptr自动销毁管理的对象
            方式：利用shared_ptr的析构函数销毁
            工作原理：每次调用析构函数都会递减shared_ptr指向对象的引用计数。如果计数为0，析构函数就会销毁shared_ptr所指向的对象，并释放其所占用的内存
                    特殊情况：当计数为0时，仍然保留这个对象。当shared_ptr存放在一个容器中，随后重排容器，从而不再需要某些元素。应该使用erase删除不再需要的shared_ptr元素
            举例：
                1、给r赋值，令它指向另一个地址，r原来创建的对象的计数器变为0.释放原来创建的对象
                2、q被赋值给r，q指向的对象的计数器递增
*/

void sharedPtrTest()
{
    auto q = make_shared<int>(555);
    auto r = make_shared<int>(42);
    r = q;
}


//  * shared_ptr可以自动释放关联内存
class Foo {
public:
    Foo(int i) : mem_i(i) {}

private:
    int mem_i;
};

shared_ptr<Foo> factory (int arg)
{
    return make_shared<Foo>(arg);
}

shared_ptr<Foo> use_factory(int arg)
{
    shared_ptr<Foo> p = factory(arg);
    /*
     * 当我们返回p时，引用计数进行了递增操作，所以离开作用域时，销毁p会让引用计数递减，p所指的内存不会被释放掉
     *
     */
    return p;
}

