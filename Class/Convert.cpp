#include <iostream>
#include <string>
using namespace std;

class ImplicitCoversion{
public:
    ImplicitCoversion(int i) : i_member(i) {} // 隐式转化
    explicit ImplicitCoversion(string s) : s_member(s) {} // 必须显示转化
    operator string() const {
        return s_member;
    }
    string s_member;
    int i_member = 0;
};

void print(ImplicitCoversion a) {

}




int main()
{
    /*
     * 类类型转化：
     * 1、构造函数将其他类型转化成构造函数所在类类型
     *  构造函数可以将 入参类型 转化成 构造函数所在类类型的对象（该对象为临时量）。例如：ImplicitCoversion i(s);
     * 2、operator return_type () const;
     *      将所在类类型转化成return_type;
     * 3、只允许一步转化
     *  例如：print(666)是错误的，因为涉及两步转化
     *      第一步：666转化成int
     *      第二步：int隐式转化成ImplicitCoversion
     * 4、explict：
     * （1）如果构造函数前有explicit，则必须显示转化，例如：从string 显示的 转化成ImplicitCoversion，print(ImplicitCoversion(s));
     *      如果没有explicit，则可以隐式转化，例如：从int 隐式的 转化成ImplicitCoversion，print(num);
     * （2）explict使用在类内的构造函数声明处，如果在类外定义构造函数，定义不应该再出现 explicit！！
     * （3）explict构造函数只能用于直接初始化：
     *      ImplicitConversion(null_book); // 正确，用explict声明，只能通过直接初始化
     *      ImplicitConversion i = null_book; // 错误，使用拷贝初始化（=），属于隐式转化
     * （4）explict可以用于强制转化：
     *      string s;
     *      print(ImplicitCoversion(s)); // 正确，显示转化
     *      print（static_cast<ImplicitConversion>(s)）; // 正确，强制转化（等同于显示转化）
     *      print(s); // 错误，隐式转化
     * （5）explict只对一个实参的构造函数有效，多个实参的构造函数不能用隐式转化！！！
     *
     */
    string s = "666";
    int num = 666;
    ImplicitCoversion i(s);

    print(ImplicitCoversion(s)); // 显示转化

    print(num); // 隐式转化

    string s2 = i; // operator转化

}


