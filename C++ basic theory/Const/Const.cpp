#include <iostream>
using namespace std;

/*
 * fun1与fun2的区别：入参是否是引用
 * fun1与fun3的区别：引用入参是否是const（引用的const为底层const）
 * fun1与fun4的区别：入参是否是const引用
 * fun2与fun3的区别：入参是否是引用
 * fun2与fun4没有区别：const是为保护原来的值不被改变，值传递将原来的值复制一份，对复制进行改变，不影响原来，所以const可以去掉
 *                  （即顶层const在overload时，不作为区别依据）
 * fun3与fun4区别：入参是否是引用
 *
 *
 * fun1与fun3的区别：
 * （1）安全性：fun1保证其他人不会对引用入参进行修改，从而改变原来的num1和num2
 * （2）fun1可以使用字面值常量作为入参，例如：Compare（4，10）
 *      涉及特殊处理：常量引用可以绑定字面值常量。将字面值常量复制到另一块内存A中，将引用绑定到内存A上
 *  (3)fun3必须保证实际入参类型和函数定义的入参类型完全相同！！！（引用的要求）
 *     fun1允许实际入参类型和函数定义的入参类型能类型转化即可(引用的特殊处理),例如对fun4而言：
 *      double ref1 = 3.1415;
 *      double ref2 = 314.15;
 *      Compare(ref1, ref2);
 *      特殊处理同上：将ref1和ref2复制到两块int的内存中（此处从double转化成int),将num1和num2绑定到这两块内存中
 *      ！！！！！这种特殊处理是为了把fun1和fun4的功能拉齐，
 *              如果这种特殊处理不存在，fun4可以传入不同类型的入参，而fun1不行，但是有的场景必须用引用传入（例如入参占内存特别大，不能用值传递）
 *              此时就会出现问题！！！！！
 *
 */

bool Compare(const int& num1, const int& num2) // fun1
{
    return num1 < num2;
}
bool Compare(const int num1, const int num2) // fun2
{
    return num1 < num2;
}
bool Compare(int& num1, int& num2) // fun3
{
    return num1 < num2;
}
bool Compare2(int num1, int num2) // fun4
{
    return num1 < num2;
}


int main1() {
    const double pi = 3.14;
    double d = 2.123;
    double d2 = 3.123;
    int i = 3;
    /*
     * 指针分为两个部分：指向的地址（地址），被指的东西（地址里存的东西）
     * 12.const * ptr_name 表示被指的东西不能变，指向的地址可以变
     * *12.const ptr_name 表示指向的地址不能变，被指的东西可以变
     */
    const double *ptr = &pi;
    ptr = &d;

    double *const piptr = &d;
    *piptr = d2;

    const int ci = 1;
    auto e =  &ci;
    const int *ptr_e = &ci;

    /*
     * 顶层const和底层const
     * tips：
     *      1、可以用 常量 or 非常量 初始化 常量；不能用 常量 初始化 非常量
     *          eg. int &i = 42 //不正确，因为42是常量，i是非常量引用
     *              const int &i = 42 // 正确，特殊情况，字面值常量可以初始化常量引用
     *      2、函数重载的区别不能是顶层const的有无。
     *          eg. Record lookup(Phone*)
     *              Record lookup(Phone* const)
     *                 区别在于指针是否是const，有无顶层const，不能作为函数overload的依据
     *      3、函数重载的依据可以是底层const的有无。
     *          eg. Record lookup(Phone*)
     *              Record lookup(const Phone*)
     *                 区别在于指针指向的对象是否是const，有无底层const，作为函数overload的依据
     */
}

