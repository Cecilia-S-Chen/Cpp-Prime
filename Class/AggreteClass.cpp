#include <iostream>
#include <string>
using namespace std;

/*
 * 聚合类：
 * 1、定义：
 * （1）用户可以直接访问其成员
 * （2）用初始值列表初始化聚合类
 * 2、特点：
 * （1）所有成员都是public的
 * （2）没有定义任何的构造函数
 * （3）没有类内初始值
 * （4）没有基类，也没有virtual函数
 *
 * 3、缺点：
 * （1）所有成员都是public，内部实现暴露
 * （2）将初始化对象的任务交给使用者，而非类的设计者（因为没有类内初始值）
 * （3）添加或者删除一个成员后，所有初始化语句都需要更新
 */

struct Data {
    // struct默认成员是public的
    int val;
    string s;
};

int main () {
    // 聚合类初始化方式一
    Data val0;
    val0.val = 1;
    val0.s = "Allen";

    // 聚合类初始化方式二：利用初始值列表初始化
    Data val1 = {0, "Cecilia"};

    /*
     * tips:
     * （1）如果初始值列表个数小于成员个数，靠后的成员被值初始化（默认初始化）！
     * （2）初始值列表的顺序必须和声明顺序一致！
     */



}