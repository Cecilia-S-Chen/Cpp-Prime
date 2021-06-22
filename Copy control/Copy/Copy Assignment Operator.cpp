#include <iostream>
using namespace std;

/*
 * 重载运算符：
 * 1、定义：operator+"要重载的运算符号"，e.g. 重载赋值运算符是 operator=
 * 2、tips：
 *  （1）重载运算符本质是函数，有入参（为运算对象）和返回值
 *  （2）入参：重载运算符为成员函数时，左侧运算对象为this，右侧运算对象为入参
 *  （3）返回值：赋值运算符返回值为左侧运算对象的引用
 *
 */

/*
 * 拷贝赋值运算符：
 * 1、合成拷贝赋值运算符：
 *  （1）来源：如果类没有定义拷贝赋值运算符，编译器会生成 合成拷贝赋值运算符
 *  （2）作用：
 *      *禁止该类型对象的赋值
 *      *将右侧运算对象的非static成员赋予左侧的运算对象的相应成员
 *
 */

class Sales_data {
public:
    Sales_data() : bookNo(" "), units_sold(0), revenue(0) {}
    Sales_data(string bookNo_i, int units_sold_i, double revenue_i) : bookNo(bookNo_i),
        units_sold(units_sold_i), revenue(revenue_i) {}

    string bookNo;
    int units_sold;
    double revenue;

    Sales_data& operator=(Sales_data &other)
    {
        bookNo = other.bookNo;
        units_sold = other.units_sold;
        revenue = other.revenue;
        return *this;
    }

};


int main() {
    Sales_data book1;
    Sales_data book2("book2", 1, 10);
    book1 = book2;
    cout << book1.bookNo << endl;
    cout << book1.units_sold << endl;
    cout << book1.revenue << endl;
}