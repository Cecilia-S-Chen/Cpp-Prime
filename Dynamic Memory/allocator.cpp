#include <iostream>
#include <memory>
#include <vector>
using namespace std;

/*
 * allocator类：
 * 1、allocator来由：
 *  （1）希望将内存分配和对象构造分开，首先分配内存，在需要时才进行对象构造
 *  （2）new将内存分配和对象构造组合在一起
 *      delete将内存释放和对象析构组合在一起，无法满足上述要求
 * 2、**内存与对象构造分离**的 原因：
 *  （1）new分配了n个对象的内存，并且构造了n个对象。实际上我们可能并不需要这么多对象
 *  （2）每个对象都被赋值两次：一次是默认初始化时，一次是赋值时
 *  （3）因为new是调用默认构造函数进行初始化对象，没有默认构造函数的类不能动态分配数组
 *
 * 3、allocator定义：
 * (1)allocator是模版，指明对象的类型，使allocator根据对象类型来确定分配内存大小和对齐位置
 *
 * 4、allocator类的相关算法
 *  （1）allocator<T> a:定义了allocator的对象a，a可以为类型T的对象分配内存
 *  （2）a.allocate(n) :分配内存，用来保存n个类型为T的对象。返回指向这块内存的指针p
 *  （3）a.deallocate(p,n) :释放从T*指针p中开始的内存，这块内存保存了n个类型为T的对象
 *      p必须是一个先前由allocate返回的头指针
 *      且n必须是p创建时所要求的大小
 *  （4）a.construct(p,args) 函数用来构造对象。
 *      p指向**原始内存**，所以一般使用p++，表示先构造对象，后将指针向后移动，保证p始终执行原始内存！！！！
 *      args传递给类型为T的构造函数，用来构造类型为T的对象。因此args一定要与类型T的某个构造函数的入参（类型，个数）匹配！！！
 *  （5）a.destroy(p) 函数用来析构对象。对p所指向的对象执行析构函数
 *
 *
 * 5、allocator伴随算法：
 *  (1)功能：在**未初始化内存**中创建对象
 *  (2)定义位置：memory
 * （3）算法定义：这些函数在 给定目的位置 创建元素，而不是由系统分配内存给它们
 *      T* unintialized_copy(b,e,b2) :从迭代器b，e指向的 输入范围中（通过首位指针确定拷贝范围） 拷贝元素到迭代器b2指定的**未构造**的原始内存中，b2指向的内存必须足够大！
 *      能容纳元素的拷贝.
 *      T* uninitialized_copy_n(b,n,b2):从迭代器b指向的元素开始，拷贝n个元素（通过首指针和元素个数，确定拷贝范围）到b2开始的内存中
 *      void unintialized_fill(b,e,t): 在迭代器b和e指定的原始内存范围中创建对象，对象的值均为**t的拷贝**
 *      void unintialized_fill_n(b,n,t):从迭代器b指向的内存开始创建n个对象，对象的值均为t的拷贝
 *
 */

int main()
{
    //----------------------------allocator类算法-----------------------------------------------------------
    int n = 50;
    allocator<string> alloc;
    auto const q = alloc.allocate(n); //根据对象类型为string，分配n个string的内存，返回指向首元素的指针
    auto p = q;
    alloc.construct(p++); // *p为空字符串，先构造对象，后移动指针！
    alloc.construct(p++, 10, 'c'); //*p为cccccccccc
    alloc.construct(p++, "hi"); // *p为ccccccccccchi

    while (q != p) {
        alloc.destroy(--p); // p指向的是尾元素的后一位，需要用--p，先将p指向尾元素，再执行析构函数！
    }

    //----------------------------allocator类伴随算法--------------------------------------------------------
    vector<int> vi = {1, 2, 3, 4, 5};
    auto p = alloc.allocate(vi.size() * 2);
    auto q = uninitialized_copy(vi.begin(), vi.end(), p); //函数返回指向最后一个元素之后的指针
    uninitialized_fill_n(q, vi.size(), 42); //将返回的指针q传递给fill函数



}

