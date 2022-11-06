#include <iostream>
using namespace std;

/*
 * 继承中的类作用域：
 * 核心：继承关系中，派生类的作用域在基类中，如果名字在派生类中无法解析，编译器将继续在外侧基类作用域中寻找该名字
 */

class Quote {
public:
    int get_mem1(int i) {return mem;}
    int get_mem2(int i) {return 0;}
    int get_mem2(int i, double d) {return i+d;}
protected:
    size_t quantity;
    double discount;
    int mem;
};

class Disc_quote : public Quote {
public:
    using Quote::get_mem2;
    pair<size_t, double> discount_policy() const {
        return {quantity, discount};
    }
    int get_mem1() {return mem;} // 返回Disc_quote中的mem；
    int get_mem2() {return Quote::mem;} // 通过指定作用域，调用基类中的成员mem

protected:
    /*
     * 名字冲突与隐藏：
     *  0、为什么要有名字隐藏？
     *      为了避免使用者误调用基类的同名函数
     *  1、含义：派生类重新定义直接或间接基类中的名字，此时定义在内层作用域的名字将**隐藏**定义在外层作用域的名字
     *  2、规避方法：如果不希望基类中的成员被派生类中的同名成员隐藏，可以通过作用域，指定调用基类中的成员
     *              实现原理是让编译器从基类中开始查找该名字，从而绕开派生类中对该成员的重新定义
     */
    int mem; // 隐藏基类中的mem；
};

int main2() {
    /*
     * 名字查找：
     * （1）核心：只根据名字查找，不care形参列表
     * （2）tips：用户能使用对象的哪些成员函数，由对象的静态类型决定（这是由函数调用的步骤决定的：先名字查找，后通过虚表确定）
     * （3）栗子：当静态类型和动态类型不一致时：动态类型有，则用户不能使用成员A
     */
    Disc_quote discQuote;
    Quote* quote = &discQuote;
    discQuote.discount_policy(); // 正确；discQuote的静态类型是Disc_quote
    // quote->discount_policy(); // 错误：quote的静态类型是Quote，静态类型不包含discount_policy

    /*
     * override与overload:
     * 核心：override是运行期确定 overload是编译器确定的
     * 1、定义
     * （1）overload:在同一个作用域中会出现overload(函数名字相同，形参列表不同，表示两个不同的函数)
     * （2）override：
     *      1、定义：在不同的作用域中会出现override（函数名字相同，形参列表无所谓)内层作用域的函数会覆盖外层作用域的函数,
     *      2、核心：因为编译器从内层开始名字查找，一旦找到了就不会再向外层查！！！即使外层有符合条件的函数，只要内层找到的同名函数不符合调用要求，编译器就会调用报错
     *      3、tips：只对虚函数进行override（要求函数名+形参列表必须相同），因为会写入虚表中动态调用
     *              对非虚函数进行override，会导致被override的基类函数被覆盖，永远调用不到！！
     * 2、核心：override和overload的出现是因为编译器名字查找的原理（只根据名字查找，不care形参列表）
     * 3、覆盖（override）重载（overload）函数
     *  （1）成员函数无论是否是虚函数，都可以重载
     *  （2）派生类希望重载后的多个实例对它都是可见的，需要override所有重载实例，或者所有重载实例都不override。如果只覆盖其中几个，剩下的重载实例会被名字隐藏！！
     *  （3）为解决override所有重载实例过于繁琐，可以用**using声明语句**， using+名字 可以把该函数的**所有重载实例**添加到派生类作用域中，
     *      然后只要重载特定实例即可
     *  （4）要求；基类函数的每个重载实例，派生类中都必须是可访问的
     */
    discQuote.get_mem1(); // 正确，通过名字隐藏，调用Disc_Quote的成员get_mem1();
    // discQuote.get_mem1(1); // 错误，名字隐藏，子类看不到基类的get_mem1(int i);
    discQuote.Quote::get_mem1(1); // 正确：通过作用域运算符，覆盖名字隐藏，使派生类可以获取到基类的同名函数！
    discQuote.get_mem2(); // 正确：discQuote使用派生类override的get_mem2()
    discQuote.get_mem2(0,1.1); // 正确：通过using声明，将Quote中重载的get_mem2实例添加到派生类的作用域中！避免了名字隐藏！
}
/*
 * 函数调用步骤：
 * （1）定义：先名字查找到成员，在根据是否是虚函数确定调用哪个版本
 *          因为每个类都有自己的虚函数表，只有确定了静态类型，才能确定使用哪个vptr和哪个vtable
 * （2）举例子：以p->mem()为栗子：
 * 1、确定P的静态类型
 * 2、在p的静态类型中查找mem，如果找不到，则一次在基类中不断查找，直到继承链的顶端。如果直到顶端也找不带，则编译器报错
 * 3、找到mem，进行类型检查，确定调用是否合法
 * 4、假如调用合法！！！才根据是否是虚函数，产生不同可执行代码：
 *  （1）如果mem是虚函数，且通过指针或引用调用，则根据**动态类型**，在虚表中确定要运行哪个版本的虚函数
 *      tips：虚表中的虚函数一定是 函数名字+入参完全相同（返回类型可以不同），不相同则不能写入虚表！！
 *  （2）如果mem不是虚函数，或者通过对象调用，则根据**静态类型**进行常规函数调用
 *
 */