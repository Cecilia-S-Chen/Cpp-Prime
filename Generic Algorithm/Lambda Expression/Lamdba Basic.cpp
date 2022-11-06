  
/*lambda表达式：
1、目的：用来定义匿名函数

2、声明Lambda表达式
Lambda表达式完整的声明格式如下：

[capture list] (params list) mutable exception-> return type { function body }
各项具体含义如下

capture list：捕获lambda所在函数的局部非static变量
params list：形参列表
mutable指示符：用来说用是否可以修改捕获的变量
exception：异常设定
return type：返回类型
function body：函数体
此外，我们还可以省略其中的某些成分来声明“不完整”的Lambda表达式，常见的有以下几种：

序号	格式
1	[capture list] (params list) -> return type {function body}
2	[capture list] (params list) {function body}
3	[capture list] {function body}
其中：

格式1声明了const类型的表达式，这种类型的表达式不能修改捕获列表中的值。
格式2省略了返回值类型，但编译器可以根据以下规则推断出Lambda表达式的返回类型： 
    （1）：如果function body中存在return语句，则该Lambda表达式的返回类型由return语句的返回类型确定； 
    （2）：如果function body中没有return语句，则返回值为void类型。
格式3中省略了参数列表，类似普通函数中的无参函数。

*/

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool cmp(int a, int b)
{
    return  a < b;
}

int main2 ()
{
    vector<int> myvec{ 3, 2, 5, 7, 3, 2 };
    vector<int> lbvec(myvec);

    sort(myvec.begin(), myvec.end(), cmp); // 旧式做法
    cout << "predicate function:" << endl;
    for (int it : myvec)
        cout << it << ' ';
    cout << endl;

    sort(lbvec.begin(), lbvec.end(), [](int a, int b) -> bool { return a < b; });   // Lambda表达式
    cout << "lambda expression:" << endl;
    for (int it : lbvec)
        cout << it << ' ';
        
        
    /*
    修改捕获变量
    使用mutable关键字,说明表达式体内的代码可以修改值捕获的变量
    */
    int a = 123;
    auto f = [a]()mutable { cout << ++a; }; // 不会报错
    cout << a << endl; // 输出：123
    f(); // 输出：124
}
