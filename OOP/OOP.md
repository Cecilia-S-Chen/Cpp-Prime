#OOP
##定义
* object—oriented programming 面向对象编程
##核心
* 数据抽象
* 继承
* 动态绑定

###继承
* 定义：不同类之间的层次关系
* 基类：层次关系的根部。基类的函数有以下几种
        1、一般函数：定义所有类共有的成员
        2、虚函数：基类希望派生类重写的函数
        3、纯虚函数：基类强制派生类一定要重写的函数
  
```c++
class Quote {
public:
    std::string isbin() const;
    virtual double price(std::size_t n) const;
};
```

* 派生类：层次关系的叶子
    要重写的虚函数一定要在子类中声明；
    声明要重写的虚函数一定要在对应的cpp文件中重写，否则会生成错误的虚表；
    
```c++
class Bulk_quote : public Quote { 
    /*
     * 使用类派生列表说明派生子类的父类
     * 并且基类前 可以有 访问说明符
     */
    double price(std::size_t n) const override;
};
```

* 防止继承
1. 在类后加final，表示该类不能被继承
2. 在虚函数后加final，表示该虚函数不能被override

```c++
class NoDerived final {}; // 表示NoDerived不能被继承
class Base {};
class Last final : public Base {}; // 表示Last不能被继承
```


###动态绑定
1、定义：父类指针即能指向父类，也能指向子类，在运行时确定所使用的函数版本，称为动态绑定/运行时绑定

