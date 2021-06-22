#include <iostream>
using namespace std;

/*
 * 三个确定类型的关键字：typedef、auto、decltype
 * 目的：采用类型别名
 *  （1）为了不让用户了解具体用什么类型实现，隐藏内部实现
 *  （2）为了方便记忆类型
 * typedef：
 * 1、作用：用于确定类型别名，给A类型取一个符合特定程序含义的别名
 * 2、同义字：using
 *      using new_name = old_name; //using使用格式
 * auto：
 * 1、作用：通过初始值判断变量的类型
 * 2、特性：
 *      （1）一般情况下，auto保留底层const，舍弃顶层const。因为赋值相当于copy，将对象copy一份后改动，不影响原来const的对象（顶层const没有保留）。
 *      取对象的地址后，根据地址改动仍是原const对象（底层const保留）
 *      （2）特殊情况，auto保留引用的顶层const。因为对对象引用后，改动时处理的是原const的对象（顶层const保留）
 * decltype：
 * 1、作用：编译器分析表达式，得到返回类型，却不执行得到表达式的具体结果
 * 2、特性：
 *      （1）decltype(array)返回的类型是array，不是指向array首元素的指针！
 */
int intArray[10] = {0,1,2,3,4,5,6,7,8,9};
typedef double wages; //wages是double的同义词
typedef char* pstring; //pstring是指向char的指针的同义词
typedef int intArr[10]; //intArray是包含10个整数的数组的别名
using intArr1 = int [10];
wages hour, weak;
pstring cptr = 0;

auto i = 0, *p = &i; //共用一个auto的变量的初始基本数据类型必须一致，p必须是指向整数的指针

const int ci = 0, &cj = ci;
decltype(ci) di = 3.14; //di是const int类型
decltype(cj) dj = di; //dj是const int&绑定在di上
decltype(intArray) *pArray; //decltype返回的是包含十个整数的数组，*表示指向包含十个整数数组的指针
/*
 *
 */
int main() {
    cout << di << endl;
}



