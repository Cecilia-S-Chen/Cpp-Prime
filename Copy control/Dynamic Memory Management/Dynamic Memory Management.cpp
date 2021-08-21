#include <iostream>
#include <memory>
#include <utility>
using namespace std;

/*
 * 1、前提：类需要可变大小的内存空间
 * 2、方式：
 *  （1）使用标准容器库保存数据
 *  （2）自己进行内存分配，通过拷贝控制成员来管理分配内存
 *  3、举例子：以标准库中的vector为例:
 *  （1）元素存储在连续的内存空间中
 *  （2）预分配足够内存
 *  （3）添加每个元素前检查是否有足够内存
 *  （4）若有，则构造新对象；若没有，则分配新空间，销毁旧空间，新空间通常是旧空间的两倍
 */

class StrVec {
public:
    StrVec() : element(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(const StrVec& strVec);
    StrVec& operator=(const StrVec&);
    size_t size() {return first_free-element;}
    size_t capacity() {return cap-element;}
    string* begin() {return element;}
    string* end() {return first_free;}
    void push_back(string);
    ~StrVec();

    static allocator<string> alloc; // 声明std中的类allocator，来构造新对象
    static pair<string*, string*> alloc_n_copy(string* first, string* last);
    void free();
    void chk_n_alloc();
    void reallocate();



private:
    string* element;
    string* first_free;
    string* cap;

};

void StrVec::chk_n_alloc()
{
    if (first_free == cap) {
        reallocate();
    }
}

pair<string*, string*> StrVec::alloc_n_copy(string *first, string *last)
{
    /*
     * alloc_n_copy:
     * 1、用尾指针-首指针来计算需要多少空间，并且allocate指向分配空间的首位置
     * 2、return返回指针pair
     *      第一个指向首元素，第二个将first到last范围内的元素拷贝到data所指向的未初始化的空间后，返回 指向构造后最后一个元素之后位置的指针
     */
    auto data = alloc.allocate(last - first);
    return {data, uninitialized_copy(first, last, data)};
}

void StrVec::push_back(string s)
{
    chk_n_alloc();
    /*
     * allocator的construct函数
     * 1、参数1：指针，所指向的位置是分配的未构造的内存空间
     * 2、参数2：该参数提供构造对象的构造函数，此处参数2是string，调用string的构造函数来构造对象
     */
    alloc.construct(first_free++, s);
}

void StrVec::free()
{
    // 不能传递给deallocator空指针
    if (element) {
        for (auto p = first_free; p != element;) {
            alloc.destroy(--p); //销毁指针所指向的对象
        }
        alloc.deallocate(element, cap - element); //销毁从element指针所指的位置开始，（cap-element）为分配内存的总大小
    }
}

StrVec::StrVec(const StrVec& strVec)
{
    pair<string*, string*> copy = alloc_n_copy(strVec.element,strVec.cap);
    element = copy.first;
    first_free = cap = copy.second;
}

StrVec::~StrVec()
{
    free();
}

StrVec& StrVec::operator=(const StrVec &rhs)
{
    auto copy = alloc_n_copy(rhs.element, rhs.cap);
    free(); //释放this之前分配的内存，如果不释放（且新分配的内存无法完全覆盖老内存），则this中可能残留之前分配内存中的内容
    element = copy.first;
    first_free = cap = copy.second;
    return *this;
}

/*
 * 移动构造函数和std：：move
 * 1、移动构造函数：
 *  （1）定义：将资源从给定对象移动到正在创建的对象中，而不是拷贝
 *  （2）核心：！！！！！！！！！
 *          拷贝构造函数，开辟一份新内存，将旧内存中的内容拷贝到新内存中。实际上，存储资源的内存变化了
 *          移动构造函数，将旧内存的控制权从原有对象转移到新对象上。实际上，存储资源的内存没有变化，控制内存的对象变化了
 *  （3）操作方法：移动构造函数是拷贝指向资源的指针，而不是拷贝资源
 * 2、move：
 *  （1）使用目的：表示调用移动构造函数，而非拷贝构造函数
 *  （2）tip：使用时直接调用std：：move，而非提供using声明，再使用move;
 *          move在utility头文件中
 *
 */

void StrVec::reallocate()
{
    //1、确定新内存大小（一般为旧内存的两倍）
    auto newcapacity = size() ? 2 * size() : 1;
    //2、分配新内存
    auto newdata = alloc.allocate(newcapacity);
    //3、将数据从旧内存移动到新内存
    auto dest = newdata; //指向新数组的第一位
    auto elem = element;// 指向旧数组的第一位
    for (size_t i; i < size(); i++) {
        alloc.construct(dest++, std::move(*elem++)); //适用move函数调用移动构造函数，而非拷贝构造函数
    }
    //4、移动完资源，马上释放旧内存，避免内存泄漏
    free();
    //5、更新指针
    element = newdata;
    first_free = dest;
    cap = newdata + newcapacity;
}