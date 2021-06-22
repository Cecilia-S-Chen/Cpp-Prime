#include <iostream>
#include <vector>
using namespace std;

class Screen {
public:
    /*
     * tips：
     *  （1）定义类型别名为了向用户隐藏实现细节（用string类型存储数据）
     *  （2）类型别名必须 先定义后使用 ，这与成员变量可以先使用后定义有所不同
     */
    typedef string :: size_type pos; // 也可以用 using pos = string :: size_type 来定义类型的别名
    Screen (pos h, pos w, char c) {
        height = h;
        width = w;
        c = ' ';
    }
    Screen& set(char);
    Screen& set(pos, pos, char); // 声明，不需要写函数名，只要声明函数类型即可
    Screen& move(int a,int b);
    Screen& display();
    const Screen& display() const;

private:
    pos cursor = 0; // 光标的位置
    pos height = 0, width = 0; // 表示屏幕的高，宽
    string contents;
};

class Window_mgr{
public:
    // ScreenIndex表示窗口的编号类型
    using ScreenIndex = vector<Screen> :: size_type;
    // 向窗口添加一个Screen，返回它的编号
    ScreenIndex addScreen(const Screen&);

private:
    vector<Screen> screens{Screen(24, 80, ' ')};
};
/*
 * 函数的作用域有函数名前的类名规定,Window_mgr::addScreen
 * 返回类型的作用域由返回类型前的类名规定,Window_mgr::ScreenIndex
 * 作用域范围：
 *  (1)函数的作用域包含 从类名之后的这条语句的剩余部分都位于类的作用域中！！
 *  (2)返回类型的作用域只包含返回类型！
 */
Window_mgr::ScreenIndex Window_mgr::addScreen(const Screen &s)
{
    screens.push_back(s);
    return screens.size() - 1;
}

/*
 * 名字查找：
 *      1、在 该名字出现之前 的当前作用域查找定义
 *      2、如果找不到，向上的外层查到
 * 类的作用域：
 *      1、编译所有成员声明，所有声明中的内容（返回类型，传入参数），必须在声明前就定义好
 *      2、类全部可见后编译函数体（先编译成员声明，再编译成员函数），所以函数体中使用的成员变量可以在函数后边出现！！
 *      （如果是类外的函数，则函数体内的变量要在使用前就定义好！）
 * 定义在 类外部的成员 中使用的 对象 名字查找：
 *      1、在类中查找
 *      2、在 类外部的成员 定义之前 的 全局范围 查找
 */
typedef double Money;
int temp = 0;
class Account {
public:
    Money balance()
    {
        return bal;
    }

private:
    /*对 类作用域 而言：
     *  如果成员使用外层作用域的名字，且该名字代表一种类型在！！ 类中就不能重新定义该名字了！
     *  e.g.成员函数返回值类型A为类外定义过的名字，且类内又重新定义了
     *      成员函数return type A对应的是类外定义的名字
     *      成员函数body的中return用到的类A是类内对应的名字
     *      如果类内和类外对A的定义不同，则会产生二异性错误
     *   如果成员函数使用外层定义过的变量，类中可以重新定义该变量（但不推荐此写法！！！）
     *      要明确函数使用的是外层定义的变量还是类内重新定义的该变量，可以在变量前加上作用域！
     *
     *对 普通作用域而言：
     *  内层作用域可以重新定义外层作用域的名字，即使该名字在内层作用域中已经使用过了
     *
     */
    // typedef int Money; // 错误！因为之前在函数外已经定义了Money，balance 函数也会使用之前定义好的Money，此处再定义Money属于重复定义的错误，只是编译器没有相关报错
    Money bal; // balance中可以先使用了bal，之后才定义，这与类先编译声明，后编译函数体的规定有关

};

void changeTemp()
{
    int result = temp +1;
    cout << result << endl;
    int temp = 5; //
    cout << temp <<endl;
}

int main ()
{
    changeTemp();
}
