#include <iostream>
#include <vector>
using namespace std;

/*
 * 非动态内存：
 *  数组的长度是预先定义好的，在整个程序中固定不变。
 *
 * 动态内存：
 * 1、使用动态内存的意义：
 *  （1）编译时无法确定数据大小：但是在实际的编程中，往往会出现所需的内存空间大小取决于实际要处理的数据多少，而实际要处理的数据数量在编程时无法确定的情况。
 *  （2）避免内存浪费：如果总是定义一个尽可能大的数组，又会造成空间浪费。
 *
 *  2、动态内存定义：
 *  使得程序可以在运行期间，根据实际需要，要求操作系统临时分配一片内存空间用于存放数据。
 *  此种内存分配是在程序运行中进行的，而不是在编译时就确定的，因此称为“动态内存分配”。
 */


 /*  3、动态内存开辟：
 *  （1）T1 *p = new T1;
 *       通过 new 运算符来实现动态内存分配。会动态分配出一片大小为 sizeof(T1) 字节的内存空间，并且将该内存空间的起始地址赋值给 p
 *  （2）T1 *p =new T1[N];
 *       用来动态分配一个任意大小的数组。
 *       T1 是任意类型名，p 是类型为 T1* 的指针，N 代表“元素个数”。
 *       这样的语句动态分配出 N × sizeof(T1) 个字节的内存空间，这片空间的起始地址被赋值给 p。
  * （3）动态内存初始化：
  *     * 内置类型和组合类型没有默认初始化，动态分配对象的值是未定义的
  *     * 类类型使用默认构造函数进行初始化。、
  *     i. 默认初始化。
  *     ii. 对内置类型使用直接初始化
  *     iii. 使用构造函数初始化
  *     iv. 使用初始化列表初始化
  *     v. 值初始化
  *  （4）auto使用：当括号中只有单一类型时，才能使用auto
 */
void NewTest()
{
    string* ps = new string; //类类型使用默认构造函数初始化，初始化为空string
    string* ps1 = new string(); // 值初始化 为空string
    int *pi1 = new int; // 内置类型没有默认初始化，pi指向未初始化的int
    int *pi2 = new int(1024); //直接初始化
    string *pi3 = new string(10,'9'); //使用构造函数初始化
    vector<int>* pv = new vector<int>{0,1,2,3,4,5}; //使用初始化列表

    int a = 10;
    auto p1 = new auto(a); //正确：使用auto时，括号只有单一类型

    /*
     *  动态分配const对象
     *  1、定义：const int* pci = new const int(1024);
     *  2、tips：用new分配const对象是一定要对对象初始化
     *          new返回的是指向const的指针（底层const）
     *
     *  内存耗尽：
     *  1、普通new：内存耗尽时，new表达式会抛出bad_alloc
     *  2、定位new：允许向new传递额外的参数，如果传递nothrow，意图告知它不能抛出异常
     */
    int *p2 = new(nothrow) int; //如果内存耗尽，分配动态对象失败，new返回一个空指针
}




