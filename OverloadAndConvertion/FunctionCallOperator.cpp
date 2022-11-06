#include <iostream>
#include <functional>
using namespace std;

/* 函数对象：
 * 1.定义：类定义了调用运算符，该类的对象为函数对象。因为该对象的行为像函数一样
 * lambda
 * 1. lambda是函数对象。因为编译器会把lambda表达式翻译从未命名类的未命名对象。
 * 2. lambda捕获参数：等同于定义了调用运算符的类，可以定义一些成员函数，作用于调用运算符中。
 * 3. lambda表达式翻译成的未命名的类，不含默认构造函数，默认析构函数，赋值运算符。
 *      是否包含默认拷贝构造函数，移动构造函数，取决于捕获数据成员的类型。
 *
 */
class SizeCompare {
public:
    SizeCompare(size_t n) : sz(n) {}
    bool operator()(const string &s) const
    {
        return s.size() >= sz;
    }

private:
    size_t sz;
};

int main2()
{
    size_t sz;
    // SizeConpare类等同于lambda函数 wordCompare
    auto wordCompare = [sz](const string &s) {
        return s.size() >= sz;
    };
}

/*
 * 标准库定义的函数对象
 * 标准库定义了表示算数运算符，关系运算模板符，逻辑运算符的类。每个类分别定义了一个执行命名操作的调用运算符。
 * 算数：
 *  plus<Type>,minus<Type>,multiplies<Type>,divides<Type>,modulus<Type>,negate<Type>
 * 关系：
 *  equal_to<Type>,not_equal_to<Type>,greater<Type>,greater_equal<Type>,less<Type>,less_equal<Type>
 * 逻辑：
 *  logical_and<Type>,logical_or<Type>,logical_not<Type>
 */


/*
 * 可调用对象与function
 *  1. 可调用对象范围：
 *      函数，函数指针，lambda表达式，bind创建的函数，重载函数调用运算符的类
 *  2. 对象的类型
 *  3.调用形式：
 *      由返回值类型和入参类型决定
 */
// 一定要区别类型与调用形式。例如add的类型是int(*)(int,int); mod的类型是int(int,int).
int add(int i, int j) {
    return i + j;
}
auto mod = [](int i, int j) {
    return i % j;
};
struct divide {
    int operator()(int denominator, int divisor) {
        return denominator / divisor;
    }
};

/*
 * 目的：设计计算器，将不同类型，但调用类型相同的操作放在同一个map中。
 * 难点：通常map中定义的是类型。现在要定义调用形式！
 * 解决方法：map中的类型用function类型代替！
 *
 * function
 * 1. 定义：function是模版类型。用来存储可调用对象，对象的调用形式为T。使用时，必须为function定义调用形式。
*/

function<int(int,int)> f1 = add;
function<int(int,int)> f2 = divide();
function<int(int,int)> f3 = [](int i, int j) { return i % j; };
// calculator包含类型不同，但是调用形式相同的成员
//map<string, function<int,(int,int)>> calculator = {
//        {"+", add},
//        {"-", minus<int>},
//        {"/", divide()},
//        {"*", [](int i, int j) { return i % j; }},
//        {"%", mod}
//};


