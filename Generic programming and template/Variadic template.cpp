#include <iostream>
using namespace std;

/*
 * 可变参数模版
 *  1、定义：可变参数模版是 接受可变数目参数的模版函数或模版类。可变数目的参数被称为参数包，在*参数名左边*添加...，表示有零个或多个参数。
 *  2、参数包分类：
 *      模版参数包：表示零个或多个模版参数
 *      函数参数包：表示零个或多个函数参数
 *      * 如果一个参数的类型是模版参数包，那么这个参数也是函数参数包，因为函数参数和其类型是一一对应的
 *  3、tips：
 *      * 编译器会从函数实参推断模版参数的类型。对于可变参数模版，编译器还会推断包中参数的数目。如果没有提供对应实参，参数包会实例化为"空包"。
 *      * 因为可变参数的个数是不确定的，所有可变参数函数通常是递归的。除了定义递归函数外，还要定义递归出口函数，否则递归函数会无限递归。
 */

// Args表示一个模版参数包，rest表示函数参数包
template<typename T, typename... Args>
void foo(const T &t, const Args& ...rest) {
    cout << sizeof...(Args) << endl; // 获取类型参数的数目
    cout << sizeof...(rest) << endl; // 获取函数参数的数目
}

// 递归出口函数
template<typename T>
ostream &print(ostream& os, const T& t)
{
    return os << t;
}
// 递归函数
template <typename T, typename... Args>
ostream  &print(ostream& os, const T& t, const Args&... rest)
{
    os << t << ", ";
    return print(os, rest...); // 包扩展操作。每次都会用函数参数包中的第一个参数匹配它，其余的匹配rest
}

/*
 * 包扩展：
 *  1、操作：扩展一个包就是将它分解成构成元素，对每个元素应用模版，获得扩展后的列表。通过在*参数右边*添加...触发扩展操作
 *  2、tips：
 *      参数包定义：...在左边
 *      参数包扩展：...在右边
 */
template<typename T>
void debug_rep(T t)
{
    // 实现
}

template<typename... Args>
ostream &errorMsg(ostream &os, const Args&... rest)
{
    return print(os, debug_rep(rest)...); // 对每个元素都应用debug_rep
}

/*
 * 模版特例化
 *  1、定义：特例化版本就是模版的独立定义，在其中，一个或递归模版参数被指定为特定类型。
 *  2、应用：函数模版特例化
 *      （1）为每个模版参数都提供实参
 *      （2）template<>表示这是模版特例化
 *      类模版特例化：
 *      （1）不必为所有模版参数提供实参
 *      （2）可以只特例化特定成员，而不特例化整个类模版
 *  3、tips；
 *      （1）特例化时，原模版必须声明在作用域中
 *      （2）为了避免模版和特例化声明顺序错误导致的错误。应该把模版的声明放在前面，之后是模版特例化。
 *
 */
template<typename T>
int compare(const T&, const T&);

// 模版特例化
template<>
int compare(const char* const& p1, const char* const& p2) // T为 const char*
{
    return strcmp(p1, p2);
}

//类部分特例化
//template <class T>
//struct remove_reference<T> {
//        typedef T type;
//};
//template<class T>
//struct remove_reference<T&> {
//    typedef T type;
//};
//template<class T>
//struct remove_reference<T&&> {
//    typedef T type;
//};