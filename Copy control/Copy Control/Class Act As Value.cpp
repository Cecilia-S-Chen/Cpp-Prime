#include <iostream>
using namespace std;

/*
 * 行为像值的类
 * 1、要素：
 *      * 定义拷贝构造函数，对指针成员所指的内容进行拷贝，而不是对指针成员本身进行拷贝
 *      * 定义一个析构函数，来释放指针成员
 *      * 定义拷贝赋值运算符：
 *          ** 具有构造函数作用：创建一个新变量存储右侧对象指针所指向的资源
 *          ** 具有析构函数作用：首先销毁本对象（左侧对象）指针所指向的旧的资源
 *          ** 拷贝赋值运算符作用，通过新变量，将右侧对象指针所指的值赋值给左侧对象指针所指的值
 *        按照以上步骤操作拷贝复制运算符，保证在赋值给自身时，不会出现从已经释放的内存中拷贝数据赋值给当前对象！
 */

class HasPtr {
public:
    /* 在构造拷贝函数中，将原有对象指针成员所指的对象赋值给当前指针成员所指的对象。
     * 使得新对象和老对象的指针成员指向两份资源
     *
     * 1、因为在构造函数中为string分配了动态内存；
     * 2、在delete中删除这份动态内存
     * 3、在拷贝赋值运算符的定义时，定义对指针成员，拷贝它所指向的对象，不拷贝指针成员本身
     *      因为在默认的合成拷贝赋值运算符是对指针进行进行拷贝，导致多个对象的指针成员指向同一份内存，在析构时会产生内存重复释放的情况
     *
     */
    HasPtr(const string &s = string()) : ps(new string(s)), i(0) {};
    HasPtr(const HasPtr& rhs) : ps(new string(*rhs.ps)), i(rhs.i) {};
    HasPtr& operator=(const HasPtr& rhs);
    ~HasPtr() {delete ps};

private:
    string *ps;
    int i;
};

// 正确的拷贝赋值运算符定义
HasPtr& HasPtr::operator=(const HasPtr &rhs) {
    new_ps = new string(*rhs.ps); // 创建临时变量，是为了自拷贝时的安全性！！
    delete ps;
    ps = new_ps;
    i = rhs.i;
}

/*
 * 错误的拷贝赋值运算符定义,关键点：
 *      没有考虑自拷贝。在自拷贝情况下，delete ps会释放左侧指针所指的内容，导致邮册1指针所指的内容无效
 *      然后将右侧无效的内容再赋值给左侧
 *
 * HasPtr& HasPtr::operator=(const HasPtr& rhs) {
 *  delete ps;
 *  ps = rhs.ps;
 *  i = rhs.i;
 * }
 */