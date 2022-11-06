#include <iostream>
using namespace std;

/*
 * 泛型编程核心：
 *  不依赖具体类型，普适性的模版
 *
 * 函数模版：
 *      1、模版形参和模版实参：函数模版定义时，定义的是模版形参。函数模版实例化时，将模版实参绑定到模版形参上。
 *      2、模版实例化：在调用模版时，会根据提供的实参，实例化出一个特定版本的函数，称为模版实例
 *      3、模版类型参数和非模版类型参数：
 *          模版类型参数前使用关键字：class或typename
 *          非模版类型参数前使用特定类型名，且一定是常量，或者指向静态生命周期对象的指针或引用。
 *
 * 模版编译：
 *  1、模版函数在使用时才实例化模版实例。所以需要将模版定义在头文件中
 *  2、模版函数在编译的链接阶段才使用。所以模版函数的错误通常出现在链接阶段
 */
template<typename T> // 模版类型参数
int compare(const T &v1, const T &v2)
{
    if (v1 < v2) return -1;
    if (v1 > v2) return 1;
    return 0;
}

template<unsigned N, unsigned M> // 非类型模版参数
int compare(const char (&p1)[N], const char (&p2)[M])
{
    return strcmp(p1, p2); // strcmp:p1>p2返回正数，p1<p2返回负数，=返回0
}

int main ()
{
    cout << compare(1, 0) << endl;
    cout << compare('a', 'b') << endl;
    cout << compare("mom", "hi") << endl;
}

