#include <iostream>
#include <string>
using namespace std;

/*
 * 委托构造函数：
 *      1、定义：使用它所属类的其他构造函数执行它自己的初始化过程
 *              一个构造函数A通过 初始值列表 里的构造函数B，完成对象初始化
 *      2、tips：
 *     （1）委托构造函数具有传递性！e.g.A委托给B，B委托给C，C为A和B执行对象初始化
 *     （2）执行顺序为栈结构：
 *          入栈：A->B->C的signature
 *          出栈：先执行C的函数body，其次是B的Body，最后是A的Body
 */
class Sales_data {
public:
    Sales_data(int cnt, double price, string num) : units_sold(cnt), revenue(cnt*price), bookNo(num) {}
    Sales_data() : Sales_data(0,0,"") {}
    Sales_data(string s) : Sales_data(0,0,s) {}
    Sales_data(istream input) : Sales_data() {cout << input << endl;}
private:
    int units_sold;
    double revenue;
    string bookNo;
};
