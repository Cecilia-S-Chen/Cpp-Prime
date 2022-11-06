#include <iostream>
using namespace std;

/*
 * 输入和输出运算符

1. 输出运算符应尽量减少格式化操作
    * 输出运算符应该主要负责打印对象内容，而非控制格式
2. 输入和输出运算符必须是非成员函数
    * IO运算符通常需要读写类的非公有数据成员，所以IO运算符一般被声明为友元
3. 输入运算符返回istream的引用（输入流的引用）；输出运算符返回ostream的引用（输出流的引用）
4. 输入运算符需要处理失败的情况，输出运算符通常不需要处理.
    * 因为我们通常要使用输入的数据
 */

class Sales_data {
public:
    Sales_data() : bookNo(" "), units_sold(0), revenue(0) {}
    Sales_data(string bookNo_i, int units_sold_i, double revenue_i) : bookNo(bookNo_i),
                                                                      units_sold(units_sold_i), revenue(revenue_i) {}
    Sales_data &operator+=(const Sales_data &rhs);
    string bookNo;
    int units_sold;
    double revenue;
};

// 重载输出运算符
ostream &operator<<(ostream &os, const Sales_data &item)
{
//    os << item.isbn() << " " << item.uints_sold << " " << item.revenue << " " << item.avg_price;
    return os;
}

// 重载输入运算符
istream &operator>>(istream &is, Sales_data &item)
{
    double price;
    is >> item.bookNo >> item.units_sold >> price;
    if (is) // 获取所有输入后要检查有效性再使用
        item.revenue = item.units_sold * price;
    else
        item = Sales_data(); // 输入的失败处理
    return is;
}

/*
 * 算数运算符 & 关系运算符 & 赋值运算符
 * 1. 算数运算符和关系运算符通常为非成员函数。
 *      类如果定义了算数运算符，通常也会定义复合赋值运算符。且类通常用复合赋值运算符来实现算数运算符
 *      类的算数运算符通常为非成员函数，复合赋值运算符通常为成员函数
 * 2. 如果存在唯一一种逻辑可靠的<定义，应该考虑为这个类定义<运算符.且<的结果必须和==的结果一致。
 * 3. 赋值运算符必须是成员函数
 */

// 复合赋值运算符
Sales_data &Sales_data::operator+=(const Sales_data &rhs)
{
    units_sold += rhs.units_sold;
    revenue += rhs.revenue;
    return *this;
}

// 算数运算符
Sales_data operator+(const Sales_data &lhs, const Sales_data &rhs)
{
    Sales_data sum = lhs;
    sum += rhs; // 调用sum的成员函数+=
    return sum;
}


/*
 * 下标运算符
 * 1. 下标运算符必须是成员函数
 * 2. 要同时定义下标函数的常量和非常量版本。确保作用于常量对象时，返回的仍是常量对象。
 */
class StrVec {
public:
    string& operator[](size_t n)
    {
        return elements[n];
    }
    const string& operator[](size_t n) const
    {
        return elements[n];
    }

private:
    string *elements; // 执行地址首元素的指针
};

/*
 * 递增和递减运算符
 * 1. 递增和递减运算符通常被定义为成员函数
 * 2. 递增和递减运算符应该同时定义前置和后置版本
 *  为了和内置版本保存一致，前置版本返回对象引用
 *  为了和内置版本保存一致，后置版本返回对象的原值，而非引用
 * 3. 因为普通的重载无法区分这两种情况，所以后置版本接受一个额外的int形参（但不适用）。
 *  手动调用后置版本，需要给定一个int入参
 *  如果被动调用后置版本，编译器会为这个形参提供值0实参
 */
class StrBolbPtr {
public:
    // 前置递增和递减运算符
    StrBolbPtr& operator++();
    StrBolbPtr& operator--();
    // 后置递增和递减运算符
    StrBolbPtr operator++(int);
    StrBolbPtr operator--(int);

    // 成员访问运算符
    string& operator*() const;
    string* operator->() const;

private:
    int curr;
};

StrBolbPtr& StrBolbPtr::operator++()
{
//    check(curr, "increment past end od StrBolbPtr"); // 如果curr已经指向了容器的尾后位置，则无法递增它
    ++curr;
    return *this;
}

StrBolbPtr& StrBolbPtr::operator--()
{
    --curr;
//    check(curr, "decrement past begin of StrBolbPtr"); // 如果curr是0，则不能递减
    return *this;
}

StrBolbPtr StrBolbPtr::operator++(int)
{
    StrBolbPtr ret = *this; // 不需要检查有效性，因为返回的是未递增的版本
    ++*this; //调用前置版本，进行递增。并在前置版本里检查有效性
    return ret; // 直接返回原对象
}

StrBolbPtr StrBolbPtr::operator--(int)
{
    StrBolbPtr ret = *this; // 不需要检查有效性，因为返回的是未递增的版本
    --*this; //调用前置版本，进行递减。并在前置版本里检查有效性
    return ret; // 直接返回原对象
}

/*
 * 成员访问运算符
 * 1. 箭头运算符必须是成员函数
 * 2. 解引用运算符通常是成员函数
 */
string& StrBolbPtr::operator*() const
{
//    auto p = check(curr, "dereference past end");
//    return (*p)[curr];
}

string* StrBolbPtr::operator->() const
{
    return &(this->operator*());
}
