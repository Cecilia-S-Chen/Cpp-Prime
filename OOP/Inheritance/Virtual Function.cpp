#include <iostream>
using namespace std;

/*
 * 静态绑定：
 * 核心：在编译时就能确定函数
 * 动态绑定：
 * 核心：在运行时才能确定函数
 * 实现方式：通过 继承+虚函数
 * 虚函数：
 * 1、应用对象：类中的非静态函数 和 非构造函数
 * 2、访问控制与继承：
 *      派生类可以继承，并override基类全部的虚函数
 *      派生类只能调用public和protected虚函数，不能调用private虚函数
 */


/*
 * 虚函数
 * 1、override：
 * 区分派生类中的两种函数
 * 1、希望重写父类的成员函数：加override，如果子类没有重写则会报错
 * 2、希望写一个和父类成员函数重名，但是实际不同的子类成员函数：不加override
 *
 * 2、final：
 * 不希望派生类重写当前这个虚函数
 *
 * 3、虚函数与默认实参：
 * 定义：如果虚函数使用了默认实参，则实参值由静态类型决定
 * 解释：如果使用基类的指针或引用调用派生类对象，当调用带有默认参数的成员函数时，
 *      调用的成员函数是派生类对应的成员函数，传入的默认参数是基类定义的默认参数
 * tips：如果虚函数使用默认实参，则基类和派生类中定义的默认实参最好一致！！！
 *
 * 纯虚函数：
 * 1、定义：纯虚函数没有函数体，在类内的声明语句后加 =0；
 * 2、tips：纯虚函数可以定义函数体，但是函数体必须定义在类外！！
 *
 */


class Quote {
public:
    virtual double net_price(size_t n) const {return n * price;}
private:
    string book;
protected:
    double price = 0.0;
};


class Bulk_quote : public Quote {
public:
    double net_price(size_t n) const override;

private:
    size_t min_qty = 0;
    double discount= 0.0;

};

int main() {
    Bulk_quote bulkQuote;
    Quote *item = &bulkQuote;
    /*
     * 4、回避虚函数机制：
     *  定义：希望虚函数调用不要进行动态绑定，使用特定版本虚函数，该调用将在编译时完成解析，而不是运行时
     *  方法：在调用成员函数前加上作用域符
     *  例子：通过加 Quote：： 明确调用父类的net_price，不论item指向父类还是子类对象
     */
    item->Quote::net_price()
}

