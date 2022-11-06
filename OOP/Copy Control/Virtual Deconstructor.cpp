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
 * 2、五个控制成员：
 *  析构函数：如果没有定义，编译器就会自动合成
 *  拷贝构造函数/拷贝赋值运算符：没有定义时，且没有定义移动构造函数/移动赋值运算符/析构函数时，系统就会自动生成！！
 *  移动构造函数/移动赋值运算符：没有定义时，且没有定义拷贝构造函数/拷贝赋值运算符/析构函数时，系统就会自动生成！！
 */

class Quote1 {
public:
    virtual ~Quote1() = default;
};

class Bulk_quote1 : public Quote1 {
public:
    ~Bulk_quote1() {}
};

int main2() {
    Quote1* itemP1 = new Quote1;
    delete itemP1; // 调用Quote的析构函数
    Quote1* itemP2 = new Bulk_quote1;
    delete itemP2; // 调用Buil_Quote的析构函数
}