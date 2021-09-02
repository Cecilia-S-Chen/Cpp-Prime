#include <iostream>
#include <vector>
#include <memory>
using namespace std;

/*
 * 普通内存：分配的资源和对象的生命周期一致
 * 动态内存：分配的资源和对象生命周期不一致
 * 对象（shared_ptr）,资源（shared_ptr所指向的对象）
 *
 * 举例：定义一个Blob类，拷贝Blob对象时，原Blob对象和拷贝Blob对象共享相同的底层资源（底层资源储存在动态内存中）
 */

class StrBlob {
public:
    /*
     * size_t和size_type:
     * 1、size_type：
     *  （1）定义由string类类型和vector类类型定义的类型，用以保存任意string对象或vector对象的长度。
     *  （2）size_t和size_type区别：size_t是全局定义的类型；size_type是STL类中定义的类型属性
     *                            size_t定义在<csrdef>;size_type定义在<string>或<vector>
     *                            vector使用size_type作为下标类型，数组使用size_t作为下表类型
     *  （3）size_t和size_type相同点：标准库类型size_type和size_t定义为unsigned int类型.不同的机器环境unsigned int长度不同
     */
    typedef vector<string>::size_type size_type;
    StrBlob();
    // initializer_list类似vector，接受花括号list，但是只能用于初始化，不具有vector其他的功能
    StrBlob(initializer_list<string>);
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}
    // 添加和删除元素
    void push_back(const string& t) {data->push_back(t);}
    void pop_back();
    // 元素访问
    string& front();
    string& back();

private:
    shared_ptr<vector<string>> data;
    // 如果data[i]不合理，抛出一个异常
    void check(size_type, const string&) const;
};


StrBlob::StrBlob() : data(make_shared<vector<string>>()) {}
StrBlob::StrBlob(initializer_list<string> i1) : data(make_shared<vector<string>>(i1)) {}

// string参数，用来承载抛出异常的内容
void StrBlob::check(size_type i, const string& msg) const
{
    if (i >= data->size()) {
        throw out_of_range(msg);
    }
}

string& StrBlob::front()
{
    // 检查如果i=0时，报错，说明vector是空的
    check(0, "front on empty StrBlob");
    return data->front();
}

string& StrBlob::back() 
{
    check(0, "back on empty StrBlob");
    return data->back();
}

void StrBlob::pop_back() 
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}

/*
 * StrBlob的拷贝、赋值和销毁
 * 因为StrBlob创建了shared_ptr，所以在拷贝、赋值和销毁时，实际上变更的是shared_ptr的计数器，当计数为0时，才会销毁shared_ptr所指向的指针
 */
