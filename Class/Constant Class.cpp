#include <iostream>
using namespace std;

/*
 * constexpr函数的参数和返回值必须是字面值类型
 *
 * 字面值常量类：
 * 1、要求：
 *  （1）所有数据成员必须是字面值类型
 *  （2）如果有构造函数，则必须有一个constexpr构造函数
 *  （3）如果数据成员含有类内初始值，则初始值必须是一条常量表达式，或者是用该成员对应类的constexpr表达式初始化
 */

class Debug {
public:
    /*
     * constexpr构造函数有两种形式：
     * 1、= default
     * 2、= delete
     * 3、即符合构造函数的要求（没有返回语句），又符合constexpr的要求（只有返回语句），所以constexpr的构造函数是空的
     * 4、constexpr构造函数必须初始化所有数据成员
     */
    constexpr Debug(bool b = true) : hw(b), io(b), other(b) {}
    constexpr Debug(bool h, bool i , bool o) : hw(h), io(i), other(o) {}
    constexpr bool any() {return hw || io || other;}

    void set_hw(bool b) {hw = b;}
    void set_io(bool b) {io = b;}
    void set_other(bool b) {other = b;}
private:
    bool hw; // hardware
    bool io; // input and output
    bool other; // 其他错误
};

int main() {
    // 实例化 字面值常量类 时要在类名前加 constexpr
    constexpr Debug io_sub(false, true, false); //调试的io
    constexpr Debug prod(false); //不调试
}

