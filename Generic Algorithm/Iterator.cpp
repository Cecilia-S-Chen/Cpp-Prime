#include <iostream>
#include <list>
#include <numeric>
#include <vector>
using namespace std;

/*
 * 插入迭代器：
 * 1. 作用：通过对插入迭代器赋值，该迭代器调用*容器操作*给指定位置插入元素
 * 2. 分类：
 *      back_inserter:插入元素后，返回指向尾后的迭代器
 *      front_inserter:插入元素后，返回指向首元素的迭代器
 *      inserter:插入元素后，返回的迭代器指向给定元素
 */

int main5()
{
    list<int> lst = {1,2,3,4};
    list<int> lst2, lst3;
    copy(lst.begin(), lst.end(), front_inserter(lst2));
    for (int i : lst2) {
        cout << i << ",";
    } // 输出4，3，2，1

    copy(lst.begin(), lst.end(), inserter(lst3, lst3.begin()));
    for (int j : lst3) {
        cout << j << ";";
    } // 输出1；2；3；4
}



/*
 * 流迭代器
 * 1.定义：istream_iterator读取输入流；ostream_iterator向输出流写数据。当istream_iterator不绑定流时，迭代器为空，表示尾后迭代器
 */

int main6()
{
    vector<int> vec_i;
    istream_iterator<int> int_iter(cin);
    istream_iterator<int> int_eof; // 尾后迭代器
    while(int_iter != int_eof) {
        vec_i.push_back(*int_iter++);
    }
    cout << accumulate(int_iter, int_eof, 0) << endl;
}

/*
 * 反向迭代器：
 * 1. 反向迭代器：从尾元素向首元素反向移动的迭代器
 * 2. tips:
 *  (1)反向迭代器需要递减运算符：forward_list和流迭代器不支持递减运算符
 *  (2)将逆序迭代器转化成普通迭代器，使用base()成员函数
 *  (3)普通迭代器和反向迭代器都是*左闭合区间*！！！！
 */
int main7()
{
    string line = "first, middle, last";
    auto rcomma = find(line.crbegin(), line.crend(), ',');
    cout << string(rcomma.base(), line.cend()) << endl;
}