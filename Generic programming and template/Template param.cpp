#include <iostream>
using namespace std;

/*
 * 模版参数
 *
 * 一、模版参数作用域：
 *  * 模版参数作用域在声明之后到声明或定义结束之前。可以隐藏外层作用域中相同的名字。
 *  * 但是模版内不能重命名模版参数名，因为模版本质是简单替换，如果重命名模版参数名，替换时可能会出现错误。
 *
 * 二、声明与定义
 *  * 模版参数名字在声明和定义中不必相同，只要数量和种类（类型模版参数或非类型模版参数）相同即可。
 *
 * 三、模版的类型成员
 * 为了区别模版的类型成员和static成员。在模版类型成员前加typename
 */

template<typename T>
typename T::value_type top(const T& c) // 通过typename表示value_type是T的类型成员,而不是static成员
{
    if (!c.empty()) {return c.back();}
    else {return typename T::value_type();}
}

/*
 * 默认模版实参
 *  从右往左，不能间隔
 */
template <typename T, typename F = less<T>>  // 默认模版实参是可调用对象
int compare(const T &v1, const T &v2, F f = F()) // 默认实参是 默认模版实参的实例化
{
    if (f(v1, v2)) {return -1;}
    if (f(v2, v1)) {return 1;}
}

/*
 * 成员模版
 *  一、定义：类的成员函数是模版函数，模版函数不能是虚函数。
 *  二、分类：
 *      1、普通（非模版）类的成员模版
 *      2、类模版的成员模版：模版类和模版函数的模版参数是独立的。在类外定义模版成员函数，必须同时为类模版和成员模版提供参数列表。
 *                       类模版的参数列表在前，成员函数模版的参数列表在后
 *  三、实例化：
 *      实例化模版类的模版成员函数，类和成员函数的模版参数都要提供。类的模版参数要显示提供，成员函数的模版参数可以推导。
 */
template <typename T> class Blob {
public:
    template <typename It> Blob(It b, It e);

private:
    shared_ptr<vector<T>> data;
};

template <typename T>
template <typename It>
    Blob<T>::Blob(It b, It e) : data(make_shared<vector<T>>(b, e)) {}


/*
 * 控制实例化：
 *  问题：模版在使用时才会实例化，可能导致在多个文件中存在相同的实例。
 *  解决办法：显示实例化
 *      （1）在文件A.cpp中进行 模版实例化定义：template declaration；
 *      （2）在其他文件中进行 模版实例化声明（表示在其他文件中已经实例化定义了，只能使用，不能重复定义）：extern template declaration；
 *  tips：
 *      （1）declaration是模版类或函数的声明，所有模版形参已经替换成模版实参。
 *      （2）模版实例化定义只能有一个，但extern声明可以有多个。
 *      （3）模版实例化后，不知道哪个文件会使用这个实例，所以，需要实例化所有成员！
 *      （4）区别普通实例化和显示实例化：
 *          普通实例化：用不到的成员不会被实例化，不用考虑模版实参是否适用
 *          显示实例化：所有成员都要实例化
 *
 */