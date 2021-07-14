#include <iostream>

void conditions_branches()
{
    /*
     if (var > 5)
        if (var > 10)
            var = 100;
        else
            var = 8;
     else
        0;

     */

    // if else的简短写法
    int var = 8;
    int res1 = var > 5? 10000: 0;  // if var>5, result = 1000  else result = 0
    std::cout<<res1<<std::endl;
    int res2 = var > 5 ? var >10? 100 : 8 : 0;//
    std::cout<<res2<<std::endl;

    const char* ptr = "ba";
    /*这是一个非常典型的用于判定当前信息是否是None的方法
     当ptr指向某个变量或者地址的时候，ptr的bool值就是一个true。
     当ptr等于nullptr(或者0), 那么ptr的bool值就是false
     */
    if (ptr)  //如果ptr有所指，则执行，
        std::cout << "this is not None, this is "<< *ptr << ", the next one is "<< *(ptr+1) << std::endl;
    else if (*ptr == 'c')
        std::cout << "hello this word" << std::endl; //这一行永远不会执行，因为if条件中包含了if else的条件
    else
        std::cout << "this is a None" << std::endl;


}


