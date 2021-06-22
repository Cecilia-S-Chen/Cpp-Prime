#include <iostream>
#include <string>
using namespace std;
/*
 * 拷贝构造函数：
 * 定义：构造函数 第一个入参 是自身类类型 的引用，且额外参数都有默认值
 *      s使用 "=" 初始化对象，将右侧的 对象 拷贝到 正在创建的左侧同类型对象中
 * 作用：合成拷贝构造函数 将被拷贝对象的每个 非static成员 拷贝给正在创建的对象 的对应成员
 *          不同成员函数依据类型进行拷贝。
 *          * 内置类型直接拷贝
 *          * 非内置类型调用自己的拷贝构造函数进行拷贝
 *          * 数组 助益拷贝数组元素
 * 特点：
 *  1、拷贝函数常被隐式使用，不能定义为 explicit（例如隐式类型转化）
 *  2、没有定义拷贝构造函数（即使定义了其他类型构造函数），编译器会默认定义 合成拷贝构造函数
 *
 *  应用场景：
 *  1、"=" 初始化
 *  2、将对象作为实参 传递给 非引用类型的 形参（将实参对象拷贝给形参）
 *  3、一个返回类型为 非引用类型的函数 返回一个对象（将函数内的对象 拷贝给 返回值）
 *  4、用花括号初始化 数组 或者 聚合类
 *
 *  PS；只要涉及 将原有对象 拷贝给 同类型新建对象，就是拷贝初始化
 */

class Sale_Data {
public:
    Sale_Data() = default;
    Sale_Data(cont Sale_Data &);

private:
    string bookNo;
    int units_sold;
    double revenue;
};

Sale_Data::Sale_Data(const Sale_Data &orig ) :
    bookNo(orig.bookNo), units_sold(orig.units_sold), revenue(orig.revenue)
    {}

 /* 区别 直接初始化 和 拷贝初始化
 * 1、直接初始化：调用对应的构造函数进行初始化
 * 2、拷贝初始化：使用"="初始化对象
 *
 */

 string name(10, "C"); // 直接初始化
 string name2(name); //直接初始化
 string nameCopy = name; //拷贝初始化
 string = string(10, "A"); //拷贝初始化
