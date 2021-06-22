#include <iostream>
#include <vector>
using namespace std;

class Screen {
public:
    typedef string :: size_type pos;
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
    Screen& rollBack();

private:
    pos cursor = 0; // 光标的位置
    pos height = 0, width = 0; // 表示屏幕的高，宽
    string contents;
};

/*
 * inline：
 * 1、定义：
 *      对于规模较小的函数，在 定义前 加上inline，表示将该函数定义复制在该函数的各个调用点处。
 * 2、tips：
 *  （1）定义 在类内部的函数 自动内联
 *  （2）声明 在类内部的函数 不是内联！！除非在类外部定义该函数前，加上 inline
 *  （3）在函数的 定义前 加上inline，函数为内联函数
 */

inline Screen& Screen::set(pos r, pos col, char ch)
{
    contents[r * width + col] = ch;
    return *this;
}
inline Screen& Screen::move(int a, int b)
{
    height += a;
    width += b;
    return *this;
}

inline  Screen& Screen::display()
{
    cout << "unconst Screen" << contents << endl;
    return *this;
}

