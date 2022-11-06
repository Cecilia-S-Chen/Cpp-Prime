#include <iostream>
#include <string>
using namespace std;
/*
 * 三五法则：
 * 核心：用来管理动态内存！！！
 *
 * 1、需要析构函数的类也需要拷贝和赋值操作
 *      因为当类成员涉及开辟动态内存时，我们需要定义析构函数，释放动态内存。
 *      如果不定义拷贝构造函数和拷贝赋值函数，使用系统合成的对应函数，会造成重复释放相同的内存，这是错误的！！！
 *
 * 2、需要拷贝操作的类也需要赋值操作（不需要析构函数）
 * 3、需要赋值操作的类也需要拷贝操作（不需要析构函数）
 *      举个栗子🌰：
 *         如果一个类要为对象分配独一无二的序列号，如果需要用已知对象生成一个新对象，那么需要定义拷贝构造函数
 *         但是已知对象和新对象的序列号不能相同！！！所以需要自定义拷贝赋值运算符来避免将已知对象的序列号赋值给新对象！
 *
 */
class HasPtr {
public:
    HasPtr(const string& s = string()): ps(new string(s)), i(0) {}
    HasPtr(HasPtr& other) : ps(other.ps), i(other.i) {}
    ~HasPtr() {delete ps;};

    HasPtr f(HasPtr hp);

private:
    string *ps;
    int i;
};

HasPtr HasPtr::f(HasPtr hp) {
    HasPtr ret = hp;
    return ret; // ret.ps被销毁，导致hp.ps也被销毁
}



int main1() {
    HasPtr p1("Some Values");
    HasPtr p2("Ohter Values");
    p1.f(p2); //当f结束时，p2.ps指向的内存被释放
    HasPtr q(p2); //因为p2.ps被释放，指向无效内存。赋值给q，导致q.ps也指向无效内存



}