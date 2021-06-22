#include <iostream>
using namespace std;

/*
 * 虚析构函数：
 * 1、由来：继承关系导致应该定义虚析构函数
 * 2、原因：如果析构函数为非虚函数，delete一个指向派生类对象的基类指针，将会产生为定义的行为！！
 * 3、tips：三五法则中，如果需要析构函数，通常也需要拷贝构造函数和拷贝赋值运算符。
 *          此处的基类为例外，基类总是需要析构函数（且定义为body为空的虚析构函数），此时不需要拷贝构造函数和拷贝赋值运算符
 *
 * 虚析构函数阻止合成移动操作：
 * 1、一个类定义或者合成了析构函数，则编译器不会为这个类合成移动操作
 */

class Quote {
public:
    virtual ~Quote() = default;
};

class Bulk_quote : public Quote {
public:
    ~Bulk_quote() {}
};

int main() {
    Quote* itemP = new Quote;
    delete itemP; // 调用Quote的析构函数
    Quote* itemP = new Bulk_quote;
    delete itemP; // 调用Buil_Quote的析构函数
}