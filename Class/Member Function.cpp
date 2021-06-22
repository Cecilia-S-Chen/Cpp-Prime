#include <iostream>
using namespace std;

/*
 * this：
 * 1、定义：指向调用当前成员函数的对象
 *
 * 2、this定义的目的：
 *  因为对象存储在data memory中，成员函数存储在code memory中，所有对象共用同一块内存中的同一个成员函数。
 *  如何区分是哪个对象调用该成员函数？需要this指明对象

 *
 * const成员函数
 * 1、定义：返回 对象的常量引用，即return type前加const！！
 *
 * 2、const成员函数的原因：
 *  this是指向 非常量对象 的 常量指针。
 *  问题：所以this不能指向常量对象，导致常量对象不能调用非常量成员函数！！！！
 *  为了解决这个问题，将非常量成员函数 加上const 变成常量成员函数。本质是将this指针变成 指向常量对象的常量指针！！！
 *
 * 3、const与函数重载：
 * （1）、成员函数有无const，可以作为重载的标志
 * （2）、入参是否是const引用传递或者const指针传递，可以作为函数重载的标志
 * （3）、return type是否是const，可以作为函数重载的标志
 *
 * 4、const成员函数特征：
 *      const成员函数通过 指向常量的this指针 调用常量成员变量，所以只能读取成员变量，不能修改
 *      const成员函数的，返回*this：返回的是常量引用！！
 *
 * 5、const成员函数调用：
 * 常量对象调用常量成员函数
 * 非常量对象调用 非常量 和 常量 成员函数
 *
 */
class MemberFunction {
public:
    MemberFunction(int ii, double dd) : i(ii), d(dd) {}
    void notConstFunc(int inputi, double inputd);
    const MemberFunction& constFunc(int inputi, double inputd) const;

private:
    int i;
    double d;

};

void MemberFunction::notConstFunc(int inputi, double inputd) {
    i = inputi;
    d = inputd + i;
    cout << "notConstFunc" << " d = " << d << endl;
}

const MemberFunction& MemberFunction::constFunc(int inputi, double inputd) const {
    inputi = i;
    inputd = d;
    cout << "ConstFunc" << " input d = " << inputd << endl;
    return *this;
}

int main () {
    MemberFunction memberFunction(1,3.14);
    memberFunction.constFunc(1,3.14);
    memberFunction.notConstFunc(1,3.14);
}

