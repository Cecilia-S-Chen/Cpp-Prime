#include <iostream>
#include <memory>
using namespace std;

/*
 * Shared Ptr和New结合使用
 * 1、原因：为初始化的智能指针默认初始化是空指针
 * 2、方法：
 *  （1）用New初始化智能指针
 *  （2）用make_shared生成智能指针
 * 3、使用new初始化智能指针
 *  接收指针参数（new产生的普通指针）的智能指针构造函数是explicit，所以不能隐式转化，必须使用直接初始化
 * 4、tips：
 *  智能指针和new产生的普通指针不能相互转化（因为接收指针参数的智能指针构造函数是explicit）
 *  需要智能指针时，在赋值，入参和返回时都要显示将普通指针绑定到智能指针上
 *  需要普通指针时，可以把智能指针绑定到普通指针上
 */
void SharedPtrAndNewTest()
{
    // shared_ptr<int> p1 = new int(1024); //错误，接收指针参数的智能指针构造函数是explicit，不能隐式转化
    shared_ptr<int> p2(new int(1024)); //正确，explicit 构造函数，采用直接初始化
}


/*
 * 不要混合使用普通指针和智能指针
 *
 *
    * 定义和改变shared_ptr的其他方法
        shared_ptr<T1>p(q) p管理内置指针q所指向的对象，内置指针q必须指向new分配的内存，且能够转化成T类型
        shared_ptr<T1>p(u) p从unique_ptr u那里接管了对象的所有权
        shared_ptr<T1>p(q,d) p接管了内置指针q所指向的对象的所有权，q必须能转化为T*类型。p将使用可调用对象d来代替delete
        shared_ptr<T1> p(p2,d) p是shared_ptr p2的拷贝，唯一的区别就是p将用可调用的对象来代替delete
        p.reset() 若p是唯一指向其对象的shared_ptr，reset会释放此对象
        p.reset(q) 若传递了可选的参数内置指针q，会令p指向q，否则将p制成空
        p.reset(q,d) 若传递了可选的参数内置指针q，会令p指向q，否则将p制成空，若还传递了参数d，将会调用d而不是delete来释放q
 *
 */

void process(shared_ptr<int> ptr) //入参为值传递，ptr的引用计数+1
{
    //使用ptr
} //离开作用域，ptr的引用计数-1

void SharedPtrAndNewTest2()
{
    int* x(new int(1024)); // x是指向动态内存的普通指针
    /*
     * 为了避免值传递，ptr引用计数+1，将临时shared_ptr传递给process，当调用所在的表达式结束时，这个临时对象就被销毁了。
     * 因为临时shared_ptr没有被引用过，所以计数变为0，所以shared_ptr所指向的内存（也是x所指向的内存）被释放，从而x变为一个空悬指针
     * 为了避免使用空悬指针，造成为定义的后果，我们认为：
     *      当shared_ptr绑定到一个普通指针上时，将内存管理责任交给了shared_ptr。
     *      所以不应该再使用内置指针来访问shared_ptr所指向的内存了，因为我们不知道该对象何时会被销毁！！！
     *
     */
    process(shared_ptr<int>(x));
    int j = *x; //为定义的：解析一个空悬指针，结果是为定义的！！
}

/*
 * 不要使用get初始化另一个智能指针，或为智能指针赋值
 *  1、get函数定义：返回一个内置指针，指向智能指针管理的对象
 *  2、get函数应用场景：需要向 不能使用智能指针 的代码传递一个内置指针
 *  3、tips：get返回的内置指针，不能delete
 *          只能将普通指针绑定在get返回的指针上，将另一个智能指针绑定在get返回的指针上是错误的！！（编译器不会报错）
 *          因为相互独立的shared_ptr指向同一块内存时，各自的引用计数相互独立，可能一个计数为0，把内存释放了，而另一个智能指针还在使用这个内存，从而变为空悬指针！
 *          而当第二个智能指针释放这个内存时，会造成内存的二次delete
 *  4、核心：get只是返回了指针，指向智能指针所管理的对象，实际对对象的控制权还属于智能指针！！！
 *          一般的拷贝，都是把对对象的控制权移交出去了
 *
 */
void GetTest()
{
    shared_ptr<int> p(new int(42)); // p的引用计数为1
    int *q = p.get(); // 正确：q为普通指针
    {
        // 易错点：两个独立的shared_ptr（p和临时shared_ptr）指向相同的内存
        shared_ptr<int>(q);
    } // 程序块结束，临时shared_ptr 所指向的内存被释放
    int foo = *p; // 未定义：p所指向的内存已经被释放！！！
}