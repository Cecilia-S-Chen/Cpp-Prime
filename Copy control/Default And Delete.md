#Default
* 使用：在声明或定义时使用
* 定义：使用=defulat来显示要求编译器生成合成版本
* default 与 合成默认构造函数的区别：
    * 在类内使用=default修饰成员声明时，合成函数将 隐式的声明为 **内联函数**
    * 在类外成员定义使用=default，成员是非内联函数
    * 合成默认构造函数是系统自发合成的，全部是内联函数
  
  
```c++
class Sales_data {
public:
    Sales_data() = default; // 内联函数
    Sales_data(const Sales_data&) = default; // 内联函数
    Sales_data& operator=(const Sales_data&); // 非内联函数
    ~Sales_data() = default; // 内联函数
};
Sales_data &operator=(const Sales_data&) = default;
```
> tips:只能对具有合成构造函数的成员使用default

#Delete
* 使用：在第一次声明时要写 =delete，避免声明后被其他成员误用！
* 使用目的：不希望该类使用拷贝构造函数或进行赋值操作
* delete作用：被delete定义的成员是被禁止使用的
* tips:析构函数不能是delete
* 合成成员被 **编译器** 定义成delete的情况：
  * 如果 类成员 的析构函数是删除的或者不可访问的（private），该类的合成析构函数被定义为delete
  * 如果 类成员 的拷贝构造函数 或析构函数 是删除或不可访问的，该类的合成构造函数也被编译器定义为delete
  * 如果 类成员 的拷贝赋值运算符 是删除或不可访问的，或者类有const 或 引用成员， 类的拷贝赋值运算符被定义为delete！！
    * 总结：如果类的数据成员不能构造，拷贝，赋值或销毁，该类的对应的成员函数会被定义为delete!
  

```c++
class Sales_data {
public:
    Sales_data() = default; 
    Sales_data(const Sales_data&) = delete; // 该类禁止使用拷贝构造
    Sales_data& operator=(const Sales_data&) = delete; // 禁止赋值
    ~Sales_data() = default; 
};
```

##Defualt与Delete区别
1. default可以在声明或者定义时使用，delete在**第一次声明**就要使用，避免被其他成员误用 
2. default只能用于有合成函数的成员，delete可以用于任何函数


#private拷贝控制
* 定义：阻止拷贝控制成员的另一种方式。（已经被delete取代了）
  * 将拷贝构造函数和赋值运算符定义在private中（阻止外部代码使用）
  * 只声明这些拷贝控制成员，不定义他们（阻止友元和成员函数使用）
  
```c++
class PrivateCopyControl {
    PrivateCopyControl (const PrivateCopyControl&);
    PrivateCopyControl& operator=(const PrivateCopyControl&);
public:
    PrivateCopyControl() = default;
    ~!PrivateCopyControl() = default;
};
```
