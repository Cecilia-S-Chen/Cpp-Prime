#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
using namespace std;

/*
 * 标准库定义的泛型算法：
 * * 泛型算法只对迭代器操作，并考虑容器类型。所以无法改变容器的大小（例如删除、添加元素）。
 * 1. 只读算法：算法不改变"输入范围"的元素
 * 2. 写容器元素的算法：算法改变"输入范围"的元素
 *      * 算法不保证"输入范围"的安全性。为解决此问题，引入"插入迭代器"。
 */
int main1 () {
    // 只读算法
    vector<int> vec_i = {1, 2, 3};
    int sum = accumulate(vec_i.cbegin(), vec_i.cend(), 0); // 只读，iterator 为const
    cout << sum << endl;

    //写操作
    fill_n(vec_i.begin(), vec_i.size(), 0); // 写操作，iterator为非const
    /*
     * 为了保证写操作的"输入范围"是安全的，使用"插入迭代器"
     * back_inserter：接受指向容器的引用，返回该容器绑定的插入迭代器
     */
    vector<int> vec_empty;
    fill_n(back_inserter(vec_empty), 10, 0); // 调用push_back在空vector中插入10个元素
    cout << vec_empty.size() <<endl;

    //拷贝操作
    replace_copy(vec_i.cbegin(), vec_i.cend(), back_inserter(vec_empty), 0, 42); // 将vec_i中的01替换成42，并将替换后的vector，拷贝到vec_empty之后
}

/*
 * 5类迭代器
 * 1. 输入迭代器：只读，不写；单遍扫描，只能递增
 * 2. 输出迭代器：只写，不读；单遍扫描，只能递增
 * 3. 前向迭代器：可读写；多遍扫描，只能递增
 * 4. 双向迭代器：可读写；多遍扫描，可递增递减
 * 5. 随机访问迭代器：可读写，多遍扫描，
 *
 *
 * 算法形参模型
 * alg(beg, end, other args);
 * alg(beg, end, dest, other args); // 目标空间要足够容纳写入数据
 * // 输入2的范围要大于输入1的范围
 * alg(beg, end, beg2, other args);
 * alg(beg, end, beg2, end2, other args);
 *
 *
 * 算法命名规范
 * 1、算法使用重载形式传递谓词：重载区别默认运算法和谓词
 *  unique(beg, end);
 *  unique(beg, end, comp);
 * 2、_if版本算法：_if区别输入参数和谓词
 * find(beg, end, val);
 * find_if(beg, end, pred);
 * 3、_copy区别是否拷贝元素的版本：_copy表示拷贝元素
 *
 */

