#include <iostream>
#include <string>
#include <vector>
#include <set>
using namespace std;
class Message;

class Folder {
public:
    Folder(const Folder &);
    Folder& operator=(Folder &);
    void addMsg(Message *);
    void remMsg(Message *);
private:
    set<Message*> messages_set;

};

class Message {
public:
    Message(const Message &);
    Message& operator=(const Message &);
    ~Message();

    void save(Folder &);
    void remove(Folder &);

private:
    string contents;
    set<Folder*> folders_set;
    void add_to_Folder(const Message &);
    void remove_from_folder();

};

// 拷贝构造函数：当创建message副本时，历遍每个包含message的folder，都添加message的副本
Message::Message(const Message &m)
        : contents(m.contents), folders_set(m.folders_set)
{
    add_to_Folder(m);
}

void Message::save(Folder &f)  {
    folders_set.insert(&f);
    f.addMsg(this);
}

void Message::remove(Folder &f) {
    folders_set.erase(&f);
    f.remMsg(this);
}

// 历遍每个包含message的folder，都添加message的副本
void Message::add_to_Folder(const Message &m) {
    for(Folder* f : m.folders_set) {
        f->addMsg(this);
    }
}

// 历遍每个包含message的folder，都删除该message
void Message::remove_from_folder()
{
    for(Folder* f : this->folders_set) {
        f->remMsg(this);
    }
}

/* 拷贝赋值运算符
 * 因为涉及Folder和Message两大类，拷贝赋值运算符的操作：
 * 1、将左侧Message所在的Folder中删除左侧Message
 * 2、将右侧Message赋值给左侧Message
 * 3、将右侧Message所在的文件夹都添加上左侧Message
 */
Message& Message::operator=(const Message &m) {
    remove_from_folder();
    contents = m.contents;
    folders_set = m.folders_set;
    add_to_Folder(m);
}

/* 析构函数作用：
 * （1）当析构Message时，历遍每个包含message的folder，都删除该message
 * （2）自动调用，系统构造的string析构函数，析构contents
 * （3）自动调用set的析构函数，析构set
 */
Message::~Message() {
    remove_from_folder();
}
