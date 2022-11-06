#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
 * 模版类：
 *  1、核心：模版类是不考虑类的类型的蓝图
 *  2、tips：
 *      （1）模版类无法推断类型，一定要提供类型实参，如果有默认实参，就提供空<>
 *      （2）模版类内的成员函数被隐式声明为内联函数
 *      （3）类模版的成员函数只有在用到时才实例化，如果类的成员函数不使用，即使模版类型不适合该成员函数，也不会报错（因为不会实例化）
 */
template <typename T>
class Blob {
public:
    typedef T value_type;
    typedef typename vector<T>::size_type  size_type; // 类的模版类型形参提供给vector模版作为实参
    Blob();
    Blob(initializer_list<T> il);
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}
    void push_back(const T &t) {data->push_back(t);}
    void push_back(T &&t) {data->push_back(move(t));}
    void pop_back();

    T& back();
    T& operator[](size_type i);
    /*
     * 模版类的static成员函数：
     *  1、每个模版实例共享static成员。因为模版的本质是替换和重写。提供不同模版实参，得到不同的模版实例。只有相同模版实例才能共享static成员
     *  2、static成员只有使用时才会实例化，如果不使用static成员，不用考虑static成员中的模版参数是否合适（因为不会实例化）
     */
    static size_t count() {return ctr;}

private:
    shared_ptr<vector<T>> data;
    void check(size_type i, const string& msg) const;
    static size_t ctr;
};

/*
 * 1、在模版类外声明的成员函数一定要加上和类一样的(数量和类型)的模版形参列表
 * 2、类名后加上模版实参，实参与形参相同
 * 3、通过类名声明，可以加入类的作用域，等同于在类内操作。
 */
template <typename T>
Blob<T>::Blob() : data(make_shared<vector<T>>()) {}

template<typename T>
Blob<T>::Blob(initializer_list<T> il) : data(make_shared<vector<T>>(il)) {}

template<typename T>
void Blob<T>::check(size_type i, const string &msg) const
{
    if (i >= data->size()) {
        throw out_of_range(msg);
    }
}

template<typename T>
T& Blob<T>::back()
{
    check(0, "back on empty Blob");
    return data->back();
}

template<typename T>
T& Blob<T>::operator[](size_type i)
{
    check(i, "subscript out of range");
    return (*data)[i];
}

template<typename T>
void Blob<T>::pop_back()
{
    check(0, "pop_back on empty Blob");
    data->pop_back();
}

// 模版类型别名
typedef Blob<string> StrBlob;
template<typename T> using twin = pair<T, T>;

int main()
{
    Blob<string> articles = {"a", "an", "the"}; // 拷贝构造函数初始化
}


/*
 * 类模版和友元
 * 1、类模版和非模版友元：友元可以访问类的所有模版实例
 * 2、非模版类和模版友元：类可以开放访问权限给部分友元模版实例，或全部友元模版实例
 * 3、类模版和模版友元：
 *      * 类模版开放相同类型的模版实例给友元的模版实例
 *      * 类模版可以开放所有实例给部分与自身类型不同的友元模版实例
 *      * 类模版可以开放所有的模版实例给给所有的友元模版实例
 */

// 非模版类和模版友元
template<typename T> class Pal1;
class Normal {
    friend class Pal1<Normal>;
    template<typename T> friend class Pal2;
};

// 模版类和模版友元
template<typename T1> class PartPal1;
template<typename Foo> class PartPal2;
template<typename T1> class C;
template<typename T1> bool operator==(const C<T1>&, const C<T1>&);

template<typename T1> class Foo
{
    friend class PartPal1<T1>; // 开放与友元相同类型的模版实例给PartPal1；
    friend class PartPal2<Foo>; // 开放所有模版实例 给部分与自身模版类型不同 的友元模版实例；
    template<typename T2> friend class AllPal; // 开放所有模版实例 给所有友元模版实例，不需要在类前声明该友元
    friend bool operator==<T1>(const C<T1>&, const C<T1>&); // 友元函数
    friend T1; // 将模版参数声明为友元
};
