#include <iostream>
using namespace std;
#define LOG(x) cout<<x<<endl;

/*
reference的作用：
由于c++对于赋值的规定，即所有以等号连接的两个变量，或是将某个变量作为传参，传入function，均是copy这个变量！即a = b 实际上是先开辟一个新的内存空间，然后把b的内容copy到了新的内存空间上。
 可是很多时候我们并不想copy。 一方面是浪费内存，另一方面，我们本就想让其公用一个内存单元。从而做到内容共享，
一个改变，另一个也改变的目的。 着就是reference的作用。 举个例子，变量本身有一个大名，ref相当于变量的小名，无论叫大名还是小名，指的都是同一个变量。

reference的特性：
1. 影子效应： reference只会存在于source code中，当编译完成，reference就不会存在了。 reference本身并不占内存，也不能凭空创造，你只能去引用已经存在的变量。compile的时候， 编译器会把所有reference都替换成原来的变量。因此在compile之后，并不存在reference的痕迹。



reference的用法 “&”：
   1). 与变量一起： &var 得到的是var的地址，
   2). 与type一起： int& ref = var; 表示ref是var的reference，两个变量本质上是一个变量。ref只是var的一个影子而已。
   3). 做为传参：

       声明：
       void increament(int& val);
       使用：
       increament(a); (注意：在使用的时候可以直接用变量作为输入，变量前，不用&来标记)

注意：
1. reference一旦建立了，就不可以更改被引用的对象了，即ref一旦与a绑定，就不可以再与其他任何变量绑定了，影子没有选择的权利。
2. reference必须在创建之时就被赋值，并跟随一辈子。

但是上面两条不能的事情，pointer都可以，还是那句话，因为reference是假的变量，pointer是真的变量。




如何区分的使用reference和pointer

    1. 如果你想用 *引用的方式来传递参数* 而不是复制，那么就用reference。
    2. 而其他的所有和地址有关的事情，就都交给指针来完成吧。

reference只是一个语法糖，reference对于实际的编译没有任何影响，他就不会出现在编译之后的文件里。
而pointer是真实存在的。 因此pointer比reference更加的powerful。 所有用reference完成的，你都可以用pointer完成。
但是reference增强了可读性，并让编程的逻辑变得非常的简单。


*/

void Increment(int value)
{
    value++;
}

void IncrementWithAddress(int*address)
{
    (*address)++;//加括号是先将地址变成变量，再对变量进行操作
}

void IncrementWithRef(int& val)
{
    val++;
}

void Reference()
{
    int var=5;
    LOG("before the calling function ")
    LOG(var);
    Increment(var);
    LOG("after calling increament function")
    LOG(var);
    /*结果显示没什么卵用！！！！ 这是因为，这里我们并没有把a传递进去，只是把a的值传进去。 相当于把value复制为和a相同的值而已，然后去改变value，而没有改变a。
    由于我们没有对a的内存的值进行改动，那么自然a就还是原来的值， 有什么办法让a传递进去，直接对a进行修改， 而不是对a的copy进行修改？

    解决办法1：以地址为传参。  --> void increamentWithPassAddress(int* val)
    如果我们设置的函数，接受的参数就是地址，那么是不是就可以直接对地址进行操作了？ 这是不是就完成了上面没有完成的任务。这就和python里面obj参数的引用传递参数的作用是一样的了。

    解决办法2:用reference
    这个方法解决很多不必要的麻烦，在方法1中，address并不是a，你要时时刻刻留心着，他是pointer，用他的值的时候要加上*。但是在方法2中，val，他就是a，这样大大的增大了代码的可读性。
    */

    IncrementWithAddress(&var);
    LOG("after calling increament with address function");
    LOG(var)

    int& ref=var;
    IncrementWithRef(ref);
    LOG("after calling increament with reference function");
    LOG(var);

    ref=2; //ref与var指向同一个变量，所以改变ref等于改变var
    LOG(var);
}
