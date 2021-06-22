#include <iostream>
using namespace std;
/*
 control flow包括continue，break，return
 continue表示：跳过这个循环，直接进入下一个循环
 break：跳出这个loop
 return：返回main的结果，并跳出main function
 区别：continue和break必须用在loop中，而return可以用在任何地方
 */

void flow_control()
{
    for(int i=0;i<5;i++)
    {
        if(i%2==0)
            continue;//break；
        cout<<i<<endl;
    }
    cin.get();
}

