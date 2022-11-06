#include <iostream>
using namespace std;

/*
 * 派生类中删除的copy control与基类的关系
 * 1、如果基类中的默认构造函数，拷贝构造函数，拷贝赋值运算符和析构函数是被删除的，或者不可访问的，派生类中的对应成员也将是被删除的
 *      因为编译器不能使用基类成员来对基类部分进行构造、赋值和销毁操作
 * 2、基类中有一个不可访问或删除的析构函数，派生类中的合成构造函数、拷贝构造函数也将是被删除的
 *      因为编译器无法销毁派生类对象的基类部分
 * 3、编译器不会合成删除的移动操作。当基类中的对应移动操作是删除或不可访问的，派生类中的该函数将是被删除的，因为派生类对象的基类部分不可移动
 *    如果基类的析构函数是删除或不可访问的，则派生类的移动构造函数也将是被删除的
 */

class B {
public:
    B() {};
    B(const B&) = delete;
};

class D : public B {};

int main1() {
    D d;// 正确：D的合成默认构造函数使用B的默认构造函数
    // D d2(d); // 错误：D的合成拷贝构造函数是被删除的
    // 错误：因为B已经定义了拷贝构造函数，所以B的合成的默认移动构造函数会被定义为删除，D的合成的默认移动构造函数也会被删除。因为父类是不可移动的
    // D d3(std::move(d));
}

//----------------------------------------------------------------------------------------------------------------------
/*
 * 派生类的拷贝控制成员
 * 1、构造函数和析构函数：
 *  派生类负责构造和析构派生类自己的成员，基类部分调用基类的构造函数和析构函数
 *  说明不用显示调用，操作系统会自动执行
 * 2、拷贝成员和移动成员：
 *  派生类负责拷贝和移动派生类和基类的成员。
 *  如果派生类希望基类调用自己的拷贝和移动成员，必须显示调用基类的拷贝/移动成员
 */

class Base {
public:
    Base& operator=(const Base &rhs);
private:
    int mem_b;
};

Base &Base::operator=(const Base &rhs) {
    return const_cast<Base&>(rhs);
}

class Derive : public Base {
public:
    /*
     * 如果Base类没有拷贝构造函数和移动构造函数 会怎样？
     *
     * 因为Base没有拷贝构造函数和移动构造函数，所以Derive会调用默认构造函数进行替代。默认构造函数给Base成员赋的是默认值。
     * 所以Derived调用拷贝构造函数后，Base的成员被赋了默认值，而Derive的成员拷贝了其他对象的Derive成员值。
     * 移动构造函数的结果也如此。
     */

    Derive(const Derive& d) : Base(d), //调用Base类拷贝构造函数，初始化Base类成员
                              mem_d(d.mem_d) //拷贝初始化Derived类成员
    {}

    Derive(Derive&& d) : Base(std::move(d)), mem_d(d.mem_d) {}
    Derive& operator=(const Derive&);
    ~Derive(); // 此时～B（）被自动执行，不需要显示调用
private:
    double mem_d;
};

Derive& Derive::operator=(const Derive& rhs)
{
    Base::operator=(rhs); // 调用基类拷贝赋值运算符为基类成员赋值
    // 自行定义Derive类的拷贝赋值运算符操作
}
