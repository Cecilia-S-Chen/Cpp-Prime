#include <iostream>
#include <utility>

/*
 * 右值引用：
 * 1、左值和右值的定义：
 *  （1）左值：表达式的左侧，表示对象的身份，可以取地址！！
 *  （2）右值：表达式的右侧，表示对象的值，是一个临时值，不能取地址！！
 *
 * 2、生成左值或右值：
 *  （1）左值：返回左值引用函数，赋值、下标、解引用、前置递增\递减运算符
 *  （2）右值：返回非引用类型的函数、算数、关系、位、后置递增\递减运算符、字面值常量
 *
 * 3、左值引用和右值引用：
 *  （1）左值引用：普通引用，用&表示
 *  （2）右值引用：绑定在将要销毁的对象上，用&&表示
 *  （3）const左值引用：因为const左值引用要绑定在不变的对象上，右值没有地址不能修改，所以绑定在右值上！！！！
 *  （4）std::move:可以将左值转化成右值，实现右值引用绑定在左值上 的目的
 *
 * 4、左值引用和右值引用的区别：
 *  （1）左值引用：左值引用的对象持久
 *  （2）右值引用：右值引用的对象是字面值常量、临时创建的对象。因为右值引用的对象的以下两个特点，所以右值引用的代码可以接管所引用对象的资源
 *              临时创建的对象：（1）将要被销毁（2）该对象没有其他用户
 *
 * 5、变量的左值属性
 *   （1）核心：被声明出来的左、右值引用都是左值。
                变量可以看成只有运算对象，没有运算符的表达式。变量表达式都是左值！！因为变量是持久的，直到离开作用域才会被销毁
 *   （2）tips：1、不能将 右值引用 绑定到 *右值引用类型的变量* 上
                2、右值引用既可以是左值，也可以是右值，如果有名称则为左值，否则是右值！！！！！
                3、作为函数返回值的 && 是右值（在等式右边），直接声明出来的 && 是左值（在等式左边）。
                例如：
                std::move() 返回右值引用，从定义上说，右值引用是变量，变量是左值；
                int &&ref = std::move(a)，此时右值引用ref要绑定在右值上，std::move(a)是右值；
 *
 *  6、右值引用的显示转化：
 *  （1）定义：使用std：：move将左值转化成右值，使得右值引用可以绑定在该值上
 *  （2）tips：move是告知编译器，对一个左值希望像右值一样处理它。
 *            调用move后，意味着对移后的原对象只能销毁、或赋予它新值。但不能使用移后的原对象的值
 *
 */

void rvalue_reference_test()
{
    int i = 42; // i是左值
    int &r = i; // 正确：r是左值引用，绑定在左值上
//    int &&r = i; // 错误：rr是右值引用，绑定在左值上错的
//    int &r2 = i * 42; // 错误：算数运算符返回的是右值，左值引用不能绑定在右值上
    const int &r3 = i * 42; // 正确：const左值引用后可以绑定在右值上
    int &&rr2 = i * 42; // 正确：将右值引用rr2绑定在右值上

    int &&rr1 = 42; // 正确：字面值常量是右值
//    int &&rr2 = rr1; // 错误：因为rr1是右值引用类型的变量，变量是左值，所以右值引用不能绑定到左值上！

    int &&rr3 = std::move(rr1); // 使用std::move，而非move是避免潜在的名字冲突
}
