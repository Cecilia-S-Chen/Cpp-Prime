#include <iostream>
using namespace std;
/*
 * 静态绑定：
 * 核心：在编译时就能确定函数
 * 动态绑定：
 * 核心：在运行时才能确定函数，父类的指针指向子类的对象
 * 实现方式：通过 继承+虚函数
 * tips：1、只能将父类的指针或引用绑定到存储子类对象的内存上
 *      2、不能将子类的指针或引用绑定到存储父类对象的内存上
 *      3、即使一个基类的指针或引用绑定到一个派生类对象上，也不能执行从基类到派生类的转化，因为：
 *          （1）因为转化过程在编译时就完成了，这个时候还不知道其动态类型是派生类，所以编译器会认为这是基类像派生类的转化
 *          （2）换言之，编译器只能通过静态类型检查来判断转化是否正确
 *          （3）如果要实现派生类向基类转化：
 *              使用dynamic_cast:在运行时检查类型转化的正确性
 *              使用static_cast：强制覆盖编译器的检查工作
 *
 *      Bulk_quote bulk；
 *      Quote *itemP = &bulk； // 正确：动态绑定
 *      Bulk_quote *bulkP = itemP; // 错误：不能将静态类型为基类的指针转化成派生类
 *
 * 虚函数：
 * 1、应用对象：类中的非静态函数 和 非构造函数
 * 2、访问控制与继承：
 *      派生类可以继承，并override基类全部的虚函数
 *      派生类只能调用public和protected虚函数，不能调用private虚函数
 */

class Quote {
public:
    friend class Pal;
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

/*
 * 友元与继承：
 * 1、核心：友元关系不能继承。
 *  （1）基类的友元访问派生类时没有友元特权，派生类的友元访问基类时没有友元特权
 *  （2）友元的派生类不继承友元访问其他类私有部分的能力！
 * 2、tips：每个类控制自己的成员访问权限
 */
class Pal {
public:
    int f(Quote q) {return q.price;} //正确：基类友元访问基类private成员
    int f1(Bulk_quote bulkQuote) {return bulkQuote.min_qty;} //错误：Pal不是Bulk_quote的友元，不能访问其私有成员
    /*
     * 正确：Pal时Quote友元，可以访问Bulk_quote中Quote的私有部分
     *      对派生类和友元，派生类访问列表不起作用，类中的访问符号确定了对派生类和友元的可见性（每个类负责控制自己成员的访问权限）
     */
    int f2(Bulk_quote bulkQuote) {return bulkQuote.price;}
};

int main() {
    Bulk_quote bulkQuote;
    Quote *item = &bulkQuote;
/*
 *
 * 静态类型：
 * 1、定义：静态类型在 编译时 就已知，它是 变量声明是的类型 或 表达式的生成类型
 * 动态类型：
 * 1、定义：动态类型在 运行时 才已知，它是变量或表达式表示的 内存中的对象类型
 *
 * 例子：
 * item的静态类型根据声明来看是Quote，
 * 但是动态类型，根据内存中的对象来看是Bulk_Quote，Quote类型的指针指向了放着Bulk_Quote类型的对象）
 *
 * PS：表达式不是指针或引用，动态和类型和静态类型必须一致！
 * 动态绑定的核心：
 * ->只有指针和引用调用虚函数才能实现动态绑定
 * ->指针或引用的静态类型和动态类型不一致是支持c++多态性的核心根本
 *
 *
 * 类型转化：
 * 1、从派生类向基类的类型转化只对指针或引用类型有用
 * 2、基类想派生类不存在 隐式类型 转化
 * 3、和任何其他成员一样，派生类向基类的类型转化也可能会由于访问权限而不可行
 */
    int n = 1;
    item->net_price(n);
}
