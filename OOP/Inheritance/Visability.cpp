#include <iostream>
using namespace std;

/*
 * 成员访问权限的由来：
 * 类有三种用户：
 * 1、普通用户：编写代码使用类的对象。代码只能访问类的公有成员；
 * 2、类的实现者：编写类的成员和友元，实现者可以通过类的成员和友元，访问类的公有部分和私有部分
 * 3、派生类：只能访问基类的public、protected部分，不能访问基类的私有部分
 *
 * 根据三种用户基类分为三个部分：
 * 1、公有部分：对外接口类成员
 * 2、protected部分：实现部分，供派生类访问
 * 3、私有部分：仅供基类成员和友元访问
 *
 * 成员访问权限：
 * 1、基类中该成员的访问说明符，影响派生类成员（及友元）访问直接基类成员
 *
 * 2、派生类的派生列表中的访问说明符，控制派生类用户（包括派生类对象，或派生类的派生类）对于基成员的访问权限：
 * public：派生类继承基类的成员并保持原来的访问权限
 * protected：基类中 public->protected, protected->private, private->private
 * private: 基类的的成员在派生类中全变成private
 */

class Base1 {
public:
    void pub_mem1();
protected:
    int prot_mem1();
private:
    char priv_mem1();
};

class Pub_Deriv1 : public Base1 {
    // 正确：派生类能访问protected成员
    int f() {return prot_mem1();}
    // 错误：派生类不能访问private成员
    char g() {return priv_mem1();}
};

class Priv_Deriv1 : private Base1 {
    // 正确：即使派生列表中的访问说明符是private，不影响派生类成员访问基类protected成员!!!!
    int f1() {return prot_mem1();}
};

int main() {
    Pub_Deriv1 pub;
    Priv_Deriv1 priv;
    pub.pub_mem1(); // 正确：pub_mem在派生类中是public的
    priv.pub_mem1(); // 错误：pub_mem在派生类中是private的
}

/* protected:
 * 1、定义：protected表示希望与派生类分享，不想被其他公共访问使用的成员
 * 2、tips：派生类成员或友元，只能通过派生类对象来访问基类protected成员，而不能直接访问基类对象中受保护的成员
 *          只能在派生类中访问基类protected成员，超出派生类范围就无法访问
 *          如果派生类成员或友元可以直接访问基类对象中的受保护成员，会导致protected失效，不是派生类的成员也有可能获取到基类的protected成员
 */

class Base2 {
protected:
    int prot_mem2; // protected成员
};

class Sneaky : public Base2 {
    friend void clobber (Sneaky&);
    friend void clobber (Base2&);
    int j;
};

// 正确：clobber能访问Sneaky对象的private和protected成员
void clobber(Sneaky& s) {
    s.j =s.prot_mem2 =0;
}

// 错误：clobber不能访问Base的protected成员
void clobber(Base2& b) {
    b.prot_mem2 = 0;
}

/*
 * 派生类向基类转化的可访问性
 * 1、定义：派生类向基类转化，就是令基类的指针或引用绑定在派生类上
 *  Base b;
 *  Derived d;
 *  Base *b1 = &d; // 令Base指针指向Derived对象
 *  Base &b2 = d; // 令Base引用绑定在Derived对象上
 * 栗子：D继承B
 * Con1、D public 继承B，用户 可以使用派生类对象转化成基类对象
 *  D protected 或 private 继承B，用户不能使用派生类对象转化成基类对象
 *  总结：类外 只能对public继承，进行派生类向基类转化
 * Con2、D public 或 protected 或 private 继承B， D的成员函数或者友元 可以使用D对象向B对象的转化
 *  总结：类内 在任何继承情况下，都可以使用派生类向基类转化
 * Con3、D public 或 protected 继承B，D的派生类成员和友元 可以使用D对象向B对象转化；
 *  D private 继承B，D的派生类成员和友元 不能使用D对象向B对象转化
 *  总结：派生类的派生类或者友元，在public和protected中使用派生类向基类转化
 */

class Base3 {
public:
    int pub_mem3;
protected:
    int prot_mem3;
private:
    int priv_mem3;
};

class Derived3 : private Base3 {
public:
    void BaseToDerived(Derived3& d) { //Con2，类内，私有继承可以转化
        Base3 &b = d;
    }
};

class Private_Derived3 : public Derived3 {
public:
    void BaseToDerived3(Derived3& d) { //Con3，类的派生类，私有继承不能转化
        Base3 &b = d;
    }
};

/*
 * 改变成员的可访问性：
 * 1、核心：使用using，using声明的成员的访问权限，由using之前的访问说明符来决定
 * 2、tips:using声明的直接/间接基类的成员，是可访问成员（非私有成员）！！
 * 3、方法：using 类名：：成员名字（例如函数名，变量名）
 */
class Base {
public:
    size_t size() const {return n;}

protected:
    size_t n;
};

class Derived : private Base {
    /*
     * Derived私有继承Base，size（）和n都为private成员
     * 但通过using对成员名字重新声明，根据using前的访问符，将size变为public；n变为protected
     */
public:
    using Base::size;
protected:
    using Base::n;
};