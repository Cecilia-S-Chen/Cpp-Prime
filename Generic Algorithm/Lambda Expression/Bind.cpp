#include <iostream>
#include <vector>
#include <functional>
using namespace std;
using namespace placeholders;

/*
 * 参数绑定：
 *  1. 目的：应用于以下场景：
 *      受参数个数限制，只能提供捕获列表传递多余的参数。
 *      此表达式要在多处使用，或者表达式比较复杂，不适合用lambda
 *  2. bind函数核心：两个调用对象参数列表的映射
 *      (1)可以修改参数个数
 *      (2)重排序参数
 *      例如：修改元素个数同时重排序参数
 *          auto g = bind(f, a, b, _2, c, _1);
 *          g(_1, _2)映射为f(a,b,_2,c,_1)
 *  3. 定义：auto newCallable = bind(oldCallable , arg_list);
 *      arg_list:_n表示新的调用对象中第n个参数，_n在arg_list中的位置，表示传入原来的可调用对象参数的位置。这样就把新对象的参数和旧对象的参数对应起来了。
 *  4. bind定义在std::placeholders命名空间中
 *  5. 绑定引用参数：
 *      当arg_lst中要传入参数的引用时，必须使用ref或cref。ref返回一个对象，包含给定的引用，同时此对象是可以拷贝的。
 */

bool isShorter(string s1, string s2)
{
    return s1.size() < s2.size();
}

int main4()
{
    vector<string> words = {"coke", "chips", "watermelon", "steak"};
    sort(words.begin(), words.end(), isShorter); // string从短到长排序
    sort(words.begin(), words.end(), bind(isShorter, _2, _1)); // string从长到短排序
}