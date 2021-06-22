#include <iostream>
using namespace  std;

/*
 * 行为像指针的类：
 *  1、核心：对指针成员进行拷贝时，拷贝的是指针成员本身，而不是指针成员所指的对象
 *  2、资源管理方式
 *          （1）使用shared_ptr来管理类中的资源（间接管理）
 *          （2）使用引用计数管理资源（直接管理）
 *
 *
 *  引用计数工作方式：
 *  1、该类的构造函数需要做以下事情：
 *      （1）初始化对象
 *      （2）创建引用计数：记录多少对象正在和当前对象共享资源
 *                      当刚创建对象时，将引用计数初始化为1，当引用计数为0时，销毁该对象资源
 *  2、该类的拷贝构造函数做以下事情：
 *      （1）拷贝给定对象的数据成员
 *      （2）拷贝计数器并递增一位
 *  3、该类析构函数做以下事情：
 *      （1）递减计数器
 *      （2）当计数器递减为0时，释放指针成员所指的内存
 *  4、该类的赋值运算符做以下事情：
 *      （1）递增右侧运算对象的计数器
 *      （2）递减左侧运算对象的计数器
 *      （3）如果左侧运算对象的计数器递减为0，拷贝运算符必须销毁状态
 *
 *  在哪里存放计数器：
 *      1、核心：计数器必须属于类，被对象共享，这样才能计算出当前有多少对象在共享成员指针所指向的资源
 *      2、存放计数器位置：
 *          （1）保存在类的动态内存中，当拷贝构造函数或者拷贝赋值运算符时，拷贝计数器的指针本身，使得不同对象指向相同的计数器
 *          （2）
 *
 */

class HasPtr {
public:
    HasPtr(const string& s = string()) : ps(new string(s)), i(0), count(new size_t(1)) {}
    HasPtr(const HasPtr& rhs);
    HasPtr& operator=(const HasPtr&);
    ~HasPtr();

private:
    string* ps;
    int i;
    size_t* count;
};

// 引用计数器递增一位，表示多一个对象共享ps所指的资源
HasPtr::HasPtr(const HasPtr &rhs): ps(rhs.ps), i(rhs.i), count(rhs.count) {
    *count ++;
}

// 引用计数器递减一位，表示少一个对象共享ps所值的资源
HasPtr::~HasPtr() {
    if(-- *count == 0) {// --在前表示先减再比较
        delete ps;
        delete count;
    }
}

HasPtr& HasPtr::operator=(const HasPtr& rhs) {
    ++ *rhs.count; // 递增右侧对象的引用计数
    if (-- *count == 0) {
        /*
         * 递减左侧对象的引用计数：
         *  如果没有其他用户，释放本对象指针所指的内存
         *  如果还有其他用户，不用管本对象所指的内存，等到其他用户不用的时候，由其他用户释放
         */
        delete ps;
        delete count;
    }

    ps = rhs.ps; // 让本对象的指针成员，指向右侧对象指针成员所指的内存
    i = rhs.i;
    count = rhs.count;
}

