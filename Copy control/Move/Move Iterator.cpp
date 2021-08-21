#include <iostream>
#include <memory>
using namespace std;


/*
 * 移动迭代器适配器
 * 1、核心：改变迭代器的 解引用运算符 的行为来适配此移动迭代器
 * 2、普通解引用运算符：返回一个元素的左值引用
 *    移动迭代器的解引用运算符：返回一个元素的右值引用
 * 3、方法：使用make_move_iterator 将普通迭代器转化成移动迭代器。
 */

class StrVec {
public:
    StrVec() = default;
    StrVec(StrVec &&) noexcept; // 移动构造函数：&&表示是移动构造函数，传入的第一个参数是右值引用
    StrVec operator=(StrVec &&) noexcept; // 移动赋值运算符
    void reallocate();
    ~StrVec() = default;

    size_t size() {return (first_free - elements);}
    void free();

private:
    static allocator<string> alloc;
    string* elements;
    string* first_free;
    string* cap;
};



void StrVec::reallocate()
{
    auto newcapacity = size() ? 2 * size() : 1;
    auto first = alloc.allocate(newcapacity);
    /*
     * 移动迭代器工作原理：
     * （1）unintialized_copy 对输入序列中的每个元素 **调用construct**，将元素拷贝到目的位置。拷贝元素时采用解引用运算符从输入序列中提取元素。
     * （2）普通的解引用运算符得到的是元素的左值引用。通过make_move_iterator,改变解引用运算符，得到元素的右值引用。
     * （3）使得调用 移动构造函数，构造新元素
     *
     * tips：必须要确定算法在将元素 的控制权转交到新对象后，旧对象不再使用该元素（因为旧对象已经失去对该元素的控制权）
     *      才能使用移动迭代器，将元素传递给算法
     */
    auto last = uninitialized_copy(make_move_iterator(begin()),
                                   make_move_iterator(end()), first); // allocate伴随函数 unintialized_copy
    free();
    elements = first;
    first_free = last;
    cap = elements + newcapacity;
}

void StrVec::free() {
    if(elements) {
        for (auto p = first_free; p != elements;) {
            alloc.destroy(--p);
        }
        alloc.deallocate(elements, cap - elements);
    }
}