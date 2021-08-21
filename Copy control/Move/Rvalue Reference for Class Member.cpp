#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

/*
 * 右值引用和成员函数：
 * 1、定义：成员函数可以定义两个版本（拷贝版本和移动版本）。
 *          拷贝版本接受指向const的左值引用，移动版本接受指向非const的右值引用
 * 2、使用：
 *  拷贝版本入参：const T&，左值引用不能对被引用元素进行改变（因为其他对象可能还用用该元素），所以入参为const
 *  移动版本：T&&，入参为右值引用（其他对象不再用该入参，所以将该入参据为己有），可以改变该入参，所以入参不为const
 */


class StrVec {
public:
    StrVec() = default;
    StrVec(StrVec &&) noexcept; // 移动构造函数：&&表示是移动构造函数，传入的第一个参数是右值引用
    StrVec operator=(StrVec &&) noexcept; // 移动赋值运算符
    ~StrVec() = default;

    void check_n_alloc();
    void reallocate();
    void push_back(const string&); //左值引用
    void push_back(string&&); //右值引用
    size_t size() { return (first_free - elements);}
    void free();

private:
    static allocator<string> alloc;
    string* elements;
    string* first_free;
    string* cap;
};

void StrVec::check_n_alloc()
{
    if (first_free == cap) {
        reallocate();
    }
}

void StrVec::reallocate()
{
    auto newcapacity = size() ? size()*2 : 1;
    auto first = alloc.allocate(newcapacity);
    auto last = uninitialized_copy(begin(), end(), first);
    free();
    elements = first;
    first_free = last;
    cap = first + newcapacity;
}

void StrVec::push_back(const string &s)
{
    check_n_alloc();
    alloc.construct(first_free++, s);
}

/*
 * 将入参右值引用传递给s！！！
 * 变量s是左值！！！！
 * 用std：：move把s转化成右值引用！！！
 */
void StrVec::push_back(string &&s)
{
    check_n_alloc();
    /*
     * 右值引用类型成员变量：
     * 1、传参是右值引用
     * 2、调用construct时，使用std：：move（），表示调用的是移动构造函数。
     */
    alloc.construct(first_free++, std::move(s));
}

void StrVec::free() {
    if(elements) {
        for (auto p = first_free; p != elements;) {
            alloc.destroy(--p);
        }
        alloc.deallocate(elements, cap - elements);
    }
}


//---------------------------------------------------------------------------------------------------------------------
/*
 * 右值和左值引用成员函数：
 * 1、栗子：
 *  s1+s2 = "wow"；
 *  s1+s2 表示运算符结果，得到一个右值！ 将一个右值放在等式的左边对其进行赋值
 *  为了强制左侧运算对象是一个左值，采用方法：在参数列表后放置引用限定符
 *
 * 2、引用限定符
 *  （1）定义：&和&&，代表this可以指向一个左值或右值
 *  （2）使用方法：引用限定符只能用于（非static）成员函数，且必须同时出现在函数的声明和定义中（类似noexcept）
 *              函数可以同时使用 const 和引用限定符
 *
 * 3、重载和引用函数
 * (1)定义：可以用引用限定符区分重载版本（类似const）
 *（2）与const的区别：
 *      const：signature相同的成员函数，通过const来区分，一个加const，一个不加
 *      引用限定符：signature相同的成员函数，必须都加引用限定符号，或者都不加！！！！通过引用限定符来区分，一个左值引用&，一个右值引用&&
 */

class Foo {
public:
    Foo &operator=(const Foo&) &; // 参数列表后的引用限定符表示 只能向可修改的左值赋值（等号左边必须是左值）
    Foo someMem() const &; //const在前，引用限定符在后

    Foo sorted() &&;
    Foo sorted() const &;

private:
    vector<int> data;
};

// this所指向的对象是右值，没有其他用户使用该对象，可以对该对象的成员改变
Foo Foo::sorted() &&
{
    sort(data.begin(), data.end());
    return *this;
}

// this所指向的对象是const的左值，不能对该对象的成员改变，在排序前对对象进行拷贝
Foo Foo::sorted() const &
{
    Foo copy_foo(*this);
    sort(data.begin(),data.end());
    return copy_foo;
}
