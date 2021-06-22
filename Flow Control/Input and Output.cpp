/*
* #表示preprocess statement
*include表示加载head file
*iostream表示input output stream。cout表示程序的输出接口，cin表示输入接口
 */
#include <iostream>

void variable();//先声明函数，之后在main中才可以调用该函数
void LogTest();

int main()
{
    //std::cout<<"Hello World!"<<std::endl;
    /*
    * <<有两个作用：1.是向左位移两位；2.是流运算符。
     对于流运算符，<<表示数据流入方向。
     例如：cout<<"Hello World!"表示“Hello World”通过cout输出。cin>>num表示把输入放入num
    *endl类似于/n
     */
    LogTest();


    std::cin.get();//表示等待直到press enter

}

