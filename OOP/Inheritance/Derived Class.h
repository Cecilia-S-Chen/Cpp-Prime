#include <iostream>
#include <string>
#include "OOP/Inheritance/Base Class.h"
using namespace std;

/*
 * 派生类：
 * 1、格式：class 派生类名 ： 访问说明符 基类名
 *  （1）：类派生列表指明从哪个基类继承而来
 *  （2）访问说明符 表示控制派生类从基类继承而来的成员是否对派生类可见
 *          public:基类中public\protected\private的对派生类可见性分别是public\private\protected
 *          protected:基类中public\protected\private的对派生类可见性分别是protected\private\private
 *          private:基类中public\protected\private的对派生类可见性分别是private\private\private
 *
 *          如果访问说明符不是public，用户不能实例化派生类！
 *  2、继承：
 *  （1）派生类可以在override的函数前加virtual，不加也可以，因为从基类继承的虚函数在派生类中国也默认为虚函数
 *  （2）从基类继承的虚函数要加上override，编译器会帮助你检查在派生类中是否确实重写
 */

class Bulk_quote : public Quote {
public:
    /*
     * 派生类的成员调用
     * 核心：通过 成员所属类 的接口 调用相应的成员
     *
     * （1）构造函数
     * 1、每个类只能控制它自己成员的初始化过程
     * 2、如果派生类构造函数没有指明调用基类哪个构造函数，则会调用基类的默认构造函数初始化基类成员变量
     * 3、初始化顺序：先初始化基类变量，再初始化派生类变量
     *
     * （2）普通函数调用：
     * 通过继承的基类接口调用基类成员
     *
     */
    Bulk_quote() = default;
    Bulk_quote(const string& book, double price, size_t qty, double discount) :
        Quote(book, price), min_qty(qty), discount(discount) {}
    double net_price(size_t n) const override;

private:
    size_t min_qty = 0;
    double discount= 0.0;
};



/*
 * 静态成员：
 *  1、基类中的静态成员是唯一的，被基类和所有的派生类共享
 *  2、基类遵循访问控制规则：public\protected\private
 */
