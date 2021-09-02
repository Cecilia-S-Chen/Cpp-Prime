#include <iostream>
#include <memory>
using namespace std;

/*
 * Shared Ptr和New结合使用
 * 1、原因：为初始化的智能指针默认初始化是空指针
 * 2、方法：
 *  （1）用New初始化智能指针
 *  （2）用make_shared生成智能指针
 * 3、使用new初始化智能指针
 *  接收指针参数（new产生的普通指针）的智能指针构造函数是explicit，所以不能隐式转化，必须使用直接初始化
 * 4、tips：
 *  智能指针和new产生的普通指针不能相互转化（因为接收指针参数的智能指针构造函数是explicit）
 *  所以在赋值，入参和返回时都要显示将普通指针绑定到智能指针上
 */
void SharedPtrAndNewTest()
{
    // shared_ptr<int> p1 = new int(1024); //错误，接收指针参数的智能指针构造函数是explicit，不能隐式转化
    shared_ptr<int> p2(new int(1024)); //正确，explicit 构造函数，采用直接初始化
}

/*
 * 不要混合使用普通指针和智能指针
 */
