#include <iostream>
#include <string>
using namespace std;

/*
 * 基类：
 * 1、某个类作为基类时，必须已经定义，而不仅仅是声明 -> 因此一个类不能派生自身！！！
 * 2、继承具有传递性，每个派生类都将继承其直接基类和间接基类可以继承的全部成员
 *
 */

class Quote {
public:
    Quote() = default;
    Quote(const string &book, double sales_price) : book(book), price(sales_price) {}
    string isbin() const {return bookNo;}
    virtual double net_price(size_t n) const {return n * price;}
    virtual ~Quote();
private:
    string book;
protected:
    double price = 0.0;
};


/*
 * 抽象基类：
 * 1、目的：我们希望提供一些统一的成员变量和成员函数接口。由派生类实现不同类对应的不同策略（成员函数的body实现不同）。
 *          这时我们需要定义抽象基类
 * 2、方法：抽象基类是一种抽象的总策略，没有具体实现。所以抽象基类不能被实例化！!
 *          我们通过纯虚函数函数，阻止抽象基类实例化
 * 3、定义：含有（或直接继承，没有override）纯虚函数的类称为抽象基类。只要有一个纯虚函数，该类就不能实例化
 *
 *
 */

class Disc_quote : public Quote {
public:
    Disc_quote() = default;
    Disc_quote(string book, double price, size_t qty, double disc) : Quote(book, price), quantity(qty), disc(disc) {}
    double net_price(size_t) const = 0; // 纯虚函数

private:
    size_t  quantity = 0;
    double disc = 0.0;
};
