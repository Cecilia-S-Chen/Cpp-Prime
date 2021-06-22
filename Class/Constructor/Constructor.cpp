#include <iostream>
#include <string>
using namespace std;
/*
 * 构造函数：
 * 1、目的：初始化类对象的成员变量
 * 2、表达式：
 *  （1）构造函数与类名相同
 *  （2）构造函数没有返回类型
 *  （3）构造函数可以overload
 *  （4）构造函数不能被声明成const！！！因为只有对象被构造完，才能获得const属性
 * 3、默认构造函数：
 *      （1）没有overload构造函数时，系统自动生成合成的默认构造函数，使用合成的默认构造函数初始化对象
 *      （2）一旦程序员定义了构造函数，合成的默认构造函数将不存在！！
 *          为了避免不能隐式初始化，所以程序员应该重新定义一个默认构造函数
 * 4、默认构造函数重要性：
 *  因为默认构造函数是在 不显示初始化对象时，对对象隐式初始化，为了避免对象的错误初始化，我们必须了解默认构造函数
 */
class Sale_item {
    Sale_item() = default; // 默认构造函数
    /*
     * 构造函数初始化列表：
     *  1、定义：为新创建对象的部分或全部数据成员赋值
     *  2、作用：不使用构造函数初始化列表，数据成员会被先默认初始化(调用默认构造函数初始化)，当构造函数体内对该成员赋值时，再覆盖之前的默认初始化。（区别构造函数体内赋值与列表初始化！）
     *          使用构造函数初始化列表，数据成员直接由列表传入的值初始化，未被初始化的才会采用默认初始化。数据成员只初始化一次！
     *
     *  3、tips：
     *      （1）为部分数据成员赋值，其他的成员默认初始化
     *  4、必须列表初始化的情况
     *       (1) 如果成员是 const 或者 引用 的话，必须通过初始值列表将其初始化
     *      （2） 如果类 没有默认构造函数 的话，成员变量不会默认初始化，必须通过列表初始化！
     *  5、构造函数初始化顺序：
     *      1、成员变量初始化顺序，和类中的定义顺序一致，和初始化列表中的顺序不一定一致！！！
     *          在成员A初始化成员B时，初始化顺序极其重要！
     *      2、最好使用入参初始化成员变量，尽量避免使用成员变量初始化其他成员变量
     *          如果成员变量A依据成员变量B初始化，则A定义在B的后面，否则会出现 用未初始化的B定义A的情况！
     *   6、构造函数默认实参：
     *      1、默认实参：在函数定义时给入参赋的值为默认实参，在调用该函数时，可以省略该入参，相当于调用默认实参
     *      2、如果构造函数给所有入参都赋值，则该构造函数等同于默认构造函数 -> 默认构造函数是不要要用户提供入参的构造函数！！！
     *
     */
    Sale_item(string &s) : bookNo(s);
    Sale_item(string &s, int n, double p) : bookNo(s), units_sold(n), revenue(p*n) {};


    /*
     * 4、构造函数初始化：
     *  （1）使用列表初始化
     *  （2）使用"="初始化
     *  （3）使用"{}"初始化！
     */
    int bookNo = 0;
    int units_sold = 0;
    vector<string> soldBookList {""}; //用列表初始化vector
};


class ConstRef {
public:
    ConstRef(int ii);

private:
    int i;
    const int ci;
    int &ri;
};

ConstRef::ConstRef(int ii)
{/*
 * 因为定义了构造函数，默认构造函数失效，成员变量不能通过默认构造函数赋初值
 */
    i = ii; // 正确
    ci = ii; // 错误：不能给const赋值，必须要通过列表初始化
    ri = ii; // 错误：ri作为引用没有绑定对象，所以不能赋值
}


/*
 * Nodefault 定义了构造函数，没有默认构造函数
 * struct A 中含有类成员a_member,因为合成默认构造函数没有办法给a_member赋值（Nodefault的构造函数需要入参），A无法实例化成对象
 * struct B 中含有类成员b_member,B有默认构造函数，但是默认构造函数无法给b_member赋值，B无法实例化成对象
 */
class NoDefault {
public:
    NoDefault(const string);
};
struct A {
    NoDefault a_member;
};
struct B {
    B () = default;
    NoDefault b_member;
};

/*
 * 合成默认构造函数：
 * 1、系统提供的默认构造函数
 * 2、用于默认初始化成员变量
 * 3、内置成员变量不能默认初始化
 */
class Foo {
public:
    int a;
    double b;
    // constructor
    Foo(int a1,double b1) : a(a1), b(b1) {

    }

    // copy constructor

    Foo other = f2;

    Foo(const Foo &other) : a(other.a), b(other.b) {

    }

    // assignment
    Foo& operator= (const Foo &other) {
        this->a = other.a;
        this->b = other.b;
        return *this;
    }

};


int main ()
{
    /*
     * Foo f1（f1）：使用自定义的构造函数初始化对象
     * Foo f1；使用默认构造函数初始化对象
     * Foo f1（）：定义一个没有入参，返回类型是Foo的函数f1
     */
    Foo f1; // 使用默认构造函数创造对象

    Foo f2 = f1;
    Foo f2 = Foo(f1);
    Foo f2(f1); // 使用一般构造函数创造对象


    Foo f3;


    f3 = f2;
    f3.operator=(f2);



}



