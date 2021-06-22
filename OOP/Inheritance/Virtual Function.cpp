#include <iostream>
using namespace std;
/*
 * 静态绑定：
 * 核心：在编译时就能确定函数
 * 动态绑定：
 * 核心：在运行时才能确定函数
 * 实现方式：通过 继承+虚函数
 * 虚函数：
 * 1、应用对象：类中的非静态函数 和 非构造函数
 * 2、访问控制与继承：
 *      派生类可以继承，并override基类全部的虚函数
 *      派生类只能调用public和protected虚函数，不能调用private虚函数
 */