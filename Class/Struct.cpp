
#include <iostream>
#include <string>
using namespace std;
#define LOG(x) cout<<x<<endl;
//#define struct class 如果这个语句生效，那么所有的struct都会变成class。

/*      struct
 struct存在的意义是因为C++为何和C有向后兼容性。因为C只有struct。所以C++在创造class的同时，也保留了struct。
struct从技术上来讲 struct和class只是默认可见度不同而已。
<<<<<<< HEAD
struct默认的是public， class默认的是private
=======
1、struct默认的是public， class默认的是private
2、class定义的派生类是私有继承，struct定义的派生类是公有继承，和父类类型无关
 栗子：class Base {}
    struct D1 : Base {} // 默认公有继承
    class D2 : Base {} // 默认私有继承
>>>>>>> cpp prime notes


如何区分使用struct和class？
其实不用区分，但是为了增加代码的可读性，我们可以采用这样的规定

struct只用来存放一堆数据。 比如 坐标， 人的基本信息，或者简单的处理一下信息。例如加减坐标，打印输出等。
class可以拥有丰富的功能。 比如 闹钟，闹钟有很多的功能，报时，铃声等function。
不使用struct来继承。
*/
struct StructPlayer{

    int X, Y;
    int speed;

    void Move(int a, int b){
        X += a;
        Y += b;
    }
};

struct Vec
{
    float x,y;
    void Add(const Vec& other)//表示传进一个reference
    {
        x+=other.x;
        y+=other.y;
    }
};

void struct_test()
{
    StructPlayer player2;
    cout<<"x before inside move:"<<player2.X<<"y before inside moeve:"<<player2.Y<<endl; //属性没给定时，有默认值
    player2.Move(-100, -99);
    cout<<"x after struct move:"<<player2.X<<"y after struct move:"<<player2.Y<<endl;
}



struct Sales_data{
    /*
     * 等价于伪代码 string isbin（const Sale_data *const this） {this->BookNo}
     */
    string isbin() const {return BookNo;}
    Sales_data& combine(const Sales_data&);
    double avg_price() const;
    string BookNo;
    unsigned unit_sold = 0;
    double revenue = 0.0;
};