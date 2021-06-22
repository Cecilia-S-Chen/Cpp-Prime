#include <istream>
using namespace std;

class Player
{/*
 * 友元；
 *  1、目的：允许其他类或者函数访问该类的 非公有 成员，将其他类或者函数定义为该类的友元。
 *          例如某些函数即是类的接口，但又在类外，当这些函数需要获取类的私有成员时，需要将函数变成该类的友元。
 *  2、实现方法：friend 关键字,加在 友元类或函数 在该类中的 友元声明 或 定义 前
 *          友元包含：
 *          （1）普通函数
 *          （2）其他类：例如类B作为类A友元后，类B的成员函数可以访问类A的private成员变量。
 *          （3）其他类的成员函数：一定要标明该函数属于的类！例如类B的函数funcB作为类A的友元。friend return type classB：：funcB（）；
 *                  eg.类A的成员函数funcA作为类B的友元
 *                  1、定义类A，在类A中声明funcA，但不能定义funcA！！（因为funcA作为类B的接口要调用类B的成员，此时类B还不存在！）
 *                  2、定义类B，在类B中对funcA进行友元声明
 *                  3、定义funcA，此时funcA才能获取类B的成员！
 *  3、tips：
 *      (1)友元一般集中定义在类的开头或结尾。不受访问说明符的约束
 *      (2)友元声明不能代替函数声明或者定义。如果需要调用友元函数。则友元函数必须在类外 声明或者定义
 *      (3)为确保类的对象能调用友元函数。一般把友元函数声明和类放在 同一个头文件中。
 *     （4）友元不具有传递性。即A类的友元B可以访问A的private成员变脸。B的友元C不能访问A的private成员变量！
<<<<<<< HEAD
=======
 *     （5）友元关系不能继承，基类的友元访问派生类时不具有友元特权；派生类友元访问基类时同理
>>>>>>> cpp prime notes
 *  4、友元的声明和作用域
 *              友元可以在类中进行 定义 或 友元声明，但友元的声明一定在类的外部
 *              区别：友元声明：friend +声明
 *                  友元的声明：与普通类和函数的声明相同
 *                  友元声明不可代替普通的声明！！！
 */

    friend Player add(const Player&, const Player&); // 声明只需定义变量的类型，不需要定义变量的名字
    friend istream &read(istream&, Player&);
    friend  ostream &print(ostream& output, Player& p) {
        output << p.itemNum << endl;
    }

public:
    int x,y;
    int speed;

    void Move(int a,int b)
    {
        x+=a;
        y+=b;
    }

    void Count () const
    {
        itemNum++;
    }

    void speak(ostream ouput, Player& p); // 虽然友元print在类中定义，但是print必须在类外声明之后才可以使用

private:
    mutable int itemNum;

};

void Player::speak(ostream ouput, Player& p) {
    print(ouput, p);
}

Player add(const Player&, const Player&);
istream &read(istream&, Player&);
ostream &print(ostream&, Player&);

