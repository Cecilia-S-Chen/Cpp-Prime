#include <iostream>
#include <string>
#include <memory>
using namespace std;

/*
 * 移动与拷贝的区别：
 * 1、拷贝：别人家有，自己家弄一个和别人家一样的。优点是两份资源相互独立，互不影响
 * 2、移动：别人家不需要了，自己家正好需要，从别人家把资源拿过来。本质是资源传递
 *
 * 对象移动：
 * 1、引入对象移动的原因：
 *  （1）某些情况下，对象拷贝后，原内存就立刻被销毁，这时采用对象移动会大幅提升性能
 *   (2)IO类或unique_ptr类包含不能被共享的资源（例如指针或IO缓存），这种类型的对象不能拷贝，可以移动
 *  （3）如果需要拷贝的对象较大，进行不必要的拷贝代价非常高
 *
 * 2、适用范围：
 *  （1）标准库容器、string和share_ptr类既支持移动，也支持拷贝
 *  （2）IO类和unique_ptr只支持移动，不支持拷贝
 *
 */


/*
 * 移动构造函数和移动赋值运算符
 * 1、移动构造函数
 *  （1）定义：移动构造函数不分配新的内存。是将资源从原对象，移动到新对象中。
 *          所以移动后的原对象随时可以销毁（因为资源的控制权已经转移到新对象中）
 *  （2）tips：移动构造函数的第一个参数，是右值引用
 *
 *  2、移动赋值运算符
 *  (1)定义：将右值移动赋值给新对象
 * （2）noexcept：如果保证移动赋值运算符不会抛出异常，应该通过声明noexcept显示的告知标准库
 * （3）tips：保证自赋值。虽然移动赋值运算符是把（短暂的）右值赋值给新建对象，但是如果右值是move转化而来的。
 *          如果不保证自赋值，则有在使用右侧运算对象的资源前，就释放释放左侧运算对象的资源（两者是同一份资源）
 * （4）移后的原对象：仍然是有效的，可析构的状态（可析构说明没有其他用户使用它）
 *
 * 3、移动操作被定义为删除：
 *  （1）要求：显示的要求编译器生成=defualt（合成的）移动操作，且编译器不能移动所有成员，编译器会将移动操作定义为删除函数
 *  （2）原则：
 *      * 类有定义或合成拷贝操作，没有定义或合成移动操作，编译器将移动操作定义为删除
 *      * 类成员的移动操作被定义为删除或不可访问，类的移动操作被定义为删除
 *      * 类的析构函数被定义为删除或不可访问，类的移动操作被定义为删除
 *      * 类成员是const或是引用，则类的移动赋值运算符被定义为删除
 *
 *  4、移动操作和拷贝操作的区别：
 *      移动操作的对象是右值，拷贝操作的对象是左值/右值，所以拷贝操作可以替代移动操作
 *      在调用构造函数且没有指明调用那个构造函数时，一般入参为左值采用拷贝构造函数，入参为右值采用移动构造函数
 */

class StrVec {
public:
    StrVec() = default;
    StrVec(StrVec &&) noexcept; // 移动构造函数：&&表示是移动构造函数，传入的第一个参数是右值引用
    StrVec operator=(StrVec &&) noexcept; // 移动赋值运算符
    ~StrVec() = default;

    void free();

private:
    static allocator<string> alloc;
    string* elements;
    string* first_free;
    string* cap;
};

/*
 *  1、noexcept:
 *      （1）定义：通知标准库我们的构造函数不会抛出任何异常，避免标准库认为类对象随时会抛出异常，而做一些不必要的额外工作
 *      （2）使用方法：noexcept在参数列表的后边，在初始化列表之前.
 *                  必须要函数声明和定义的地方，都使用noexcept
 *      （3）tips：不抛出异常的移动构造函数，和移动赋值运算符，必须标记为noexcept
 *      （4）使用noexcept意义：
 *          因为移动操作抛出异常也是允许的，所以在某些情况下（例如vector的push_back），需要重新分配内存并拷贝到新内存中，
 *          如果使用了移动构造函数，在拷贝到新内存时发生错误，此时旧内存也已经被销毁。
 *          所以标准库默认采用拷贝构造函数，旧内存不变，如果在拷贝过程中出现问题，可以释放新内存，返回旧内存。
 *
 *          在这种情况下，我们仍希望使用移动构造函数，需要将移动构造函数标记为noexcept，表示该移动构造函数不会抛出异常，显示的告知标准库移动构造函数可以安全使用！！！
 */

 /*
  * tips：
 * 2、初始化列表：不表示新对象拷贝入参对象的资源。而表示新对象接管入参对象的资源！！！
 * 3、入参对象为右值，在资源被接管后，随时可以进行析构
 */
StrVec::StrVec(StrVec &&s) noexcept
    // 成员初始化器接管了入参s中的资源
    : elements(s.elements), first_free(s.first_free), cap(s.cap)
{
    /* 令s进入这样的状态----对其进行析构函数是安全的
     * 1、先将s的成员都置成空指针，然后再销毁移后的原对象
     * 2、利用destroy析构原对象
     * 3、利用deallocate释放原对象内存
     * PS：如果没有将成员都置为空指针，则在销毁移后的原对象时，就会释放刚刚移动的资源
     */
    s.elements = s.first_free = s.cap = nullptr;
}

StrVec StrVec::operator=(StrVec &&rhs) noexcept {
    // if校验，对自赋值不执行移动赋值运算符，保证自赋值正确性
    if (this != &rhs) {
        free(); //先释放新建对象中的内存，准备接管旧对象的资源
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        /*
         * 令rhs进入可析构的状态：
         * 因为新建对象已经接管了rhs的资源。所以将rhs的成员变量置为空指针，保证析构rhs是无害的
         */
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
}

void StrVec::free() {
    if(elements) {
        for (auto p = first_free; p != elements;) {
            alloc.destroy(--p);
        }
        alloc.deallocate(elements, cap - elements);
    }
}

//-----------------------------------------------------------------------------------------------------------------------------
/*
 * 合成的移动操作
 * 1、和合成的拷贝操作区别：
 *  （1）合成的拷贝操作：
 *      如果类没有定义自己的拷贝操作，编译器就会自动生成 合成的拷贝操作。
 *      如果一个类定义了移动操作，则该类 合成的拷贝构造操作 就会被定义为删除。所以定义了移动操作，就必须定义拷贝操作。
 *  （2）合成的移动操作：
 *      如果类没有定义任何自己版本的拷贝控制成员，且类的每个非static数据成员都可以移动。编译器才会合成移动操作！！！！
 *      如果一个类定义了拷贝控制成员（拷贝构造函数，拷贝赋值运算符，析构函数），那么编译器就不会自动生成 合成的移动操作。没有移动操作，类会用拷贝操作代替。
 *      （例如没有移动构造函数，std：：move会调用拷贝构造函数替代）
 *  总结：编译器以使用着的定义优先。如果使用者定义了构造函数（拷贝/移动），编译器就不生成其他的构造函数（拷贝/移动）
 *          即使用户定义了删除的构造函数（拷贝/移动），编译器也不会默认生成另一种构造函数（编译器认为你拷贝/移动构造函数都不想要）！！
 *
 *  (3)更新 三/五法则：
 *      五个拷贝控制成员（拷贝构造函数，拷贝赋值运算法，移动构造函数，移动赋值运算符，析构函数）为一个整体。定义了其中一个成员，就应该定义其他四个成员
 *      因为如果只定义其中个别成员，其他成员使用默认合成版本（可能会造成内存泄漏或内存的重复释放）
 *
*/

struct X {
    int i; // 内置类型可以移动
    string s;// string定义了自己的移动操作
};

Struct hasX {
    X mem; // X定义了自己的移动操作
};


struct  Y {
    Y(Y& y) = default;
};

struct hasY {
    /*
     * Y定义了拷贝构造函数，没有定义移动构造函数，则编译器会把移动构造函数定义为删除
     * hasY类有类成员mem，因为类Y的移动构造函数被定义为删除，所以hasY的移动构造函数也会被定义为删除
     */
    hasY() = default;
    // 显示的要求编译器合成移动构造函数，但是编译器无法移动成员mem，编译器会将移动构造函数定义为删除
    hasY(hasY &&) = default;
    Y mem;
};




int main()
{
    X x, x2 = std::move(x); // 使用合成的移动构造函数
    hasX hx, hx2 = std::move(hx);

    // hasY hy, hy2 = std::move(hy); // 移动构造函数被定义为删除，则move调用移动构造函数也是错误的！！
}