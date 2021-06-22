#include <iostream>
using namespace std;

/*
 * Swap函数：
 * 1、定义：用以交还两个元素。当没有认为规定时，操作系统会默认合成Swap函数
 * 2、Swap函数功能：
 *  （1）元素的值交换；
 *  （2）元素的指针交换；
 * 3、Swap函数的核心：创建中间变量，帮助元素交换
 * 4、tips；
 *      (1)swap函数于控制拷贝成员不同，不是必须的，可以定义成友元，被多个类共享
 *      (2)swap函数中调用的swap函数，会优先调用被交换的对象自己的swap函数，如果被交换对象没有swap函数，会调用标准库std::swap函数
 */


class HasPtr {
public:
    friend void swap(HasPtr&, HasPtr&); // 将swap
    HasPtr(const HasPtr& rhs) : ps(new string(*rhs.ps)), i(rhs.i) {}
    HasPtr& operator=(HasPtr);

private:
    string* ps;
    int i;
};

void swap(HasPtr& lhs, HasPtr& rhs) {
    /*
     *
     */
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
}

/*
 * Swap函数在拷贝赋值运算符中的作用：
 * 1、步骤：右侧对象的副本与左侧对象进行交换
 *          当离开拷贝赋值运算符函数作用域时，右侧对象副本调用析构函数（等于原来的左侧对象调用了析构函数，如果引用计数为0，则销毁左侧对象）。
 *          新的左侧对象（等于原来的右侧对象的副本）return;
 * 2、优点：
 *  （1）自动处理了自赋值的情况，且天然安全
 *          因为入参为右侧对象的拷贝副本，所以即使右侧对象和左侧对象是同一个对象（自赋值），在入参时已经创建了一个对象副本。避免多个指针指向同一个内存
 *  （2）实现对 左侧对象进行引用计数 自动递减 和 右侧对象进行引用计数 自动递增
 *
 */

HasPtr& HasPtr::operator=(HasPtr rhs) { // 实现构造函数作用
    swap(*this, rhs); // rhs指向左侧对象曾经指向的内存
    return *this;
} // 实现析构函数作用

