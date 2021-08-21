#include_next <iostream>
#include <memory>
using namespace  std;

/*
 * 右值引用和成员函数：
 * 1、定义：成员函数可以定义两个版本（拷贝版本和移动版本）。
 *          拷贝版本接受指向const的左值引用，移动版本接受指向非const的右值引用
 * 2、使用：
 *  拷贝版本入参：const T&，拷贝不需要对入参进行改变，所以入参为const
 *  移动版本：T&&，入参为右值引用，不能是const
 */


