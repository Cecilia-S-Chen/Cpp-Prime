#include <iostream>
using namespace std;

void loop()
{
    //for loop
    /*
     for(par1;par2;par3)
     par1是变量声明，代表迭代器设置；
     par2是针对迭代器的condition判断，只要判断为真，就继续执行for loop；
     par3表示在下一个loop开始前执行这个操作

     表达方式1:
    for(int i=0;i<5;i++)
    {
        cout << i << endl;
    }

     */

    /*
     表达方式2
     par1只执行一次，提出，放在前面
     par2可以用变量，function等替换
     par3在每次loop结束后执行，可以放在loop最后
     */
    bool condition = true;
    int i = 0;
    for (;condition;){
        cout << i << endl;
        if (i >= 5) condition = false;
        i++;
    }
    //--------------------------------------------------------------------
    while(i<5)
    {
        cout << i << endl;
        i++;
    }

    //--------------------------------------------------------------------
    do
    {
        cout << i << endl;
        i++;
    }while(i<5);
    /*
     while loop与do while的区别：
     while loop是先判断条件再执行body；do while是先执行body再判断条件。
     所以do while至少会执行一次body
     */


}
