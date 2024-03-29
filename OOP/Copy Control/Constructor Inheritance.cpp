#include <iostream>
using namespace std;

/*
 * 继承的构造函数：
 * 1、派生类可以"继承" 直接基类的构造函数
 * 2、派生类不能继承基类的 拷贝/移动构造函数，如果派生类没有定义拷贝和移动构造函数，编译器会为其自动合成
 * 3、继承方式：使用using声明语句
 * 4、基类构造函数含有默认实参时，派生类将继承到多个构造函数，每个构造函数分别省略掉一个有默认实参的形参。
 *      换言之，对于有默认实参的构造函数，如果该默认实参的位置有入参，则入参会覆盖默认实参
 * 5、基类含有几个构造函数，大多数情况，派生类会继承所有的构造函数
 *
 * using作用：
 * 1、令某个名字在当前作用域可见
 * 2、令编译器产生代码。将派生类中基类的成员传递给基类构造函数。派生类自己的成员，使用默认初始化
 * 3、构造函数的using声明不会改变构造函数的访问级别。不论派生类对基类的using声明在哪，基类构造函数的访问级别任何在基类中声明的一致。
 * 4、using语句不能指定explicit或constexpr
 *    如果基类是explicit（只能显示初始化，不能用=隐式初始化），或者constexpr（字面值常量类），则派生类继承的构造函数也有此属性
 */

class Base {
private:
    int mem_b;
};

class Derive : public Base {
public:
    /*
     * using语句等同于
     * Derive(int rhs_b, int rhs_d) : Base(rhs_b) {}
     */
    using Base::Base; //继承了Base的构造函数
private:
    int mem_d;
};

