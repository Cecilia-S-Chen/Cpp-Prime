#include <iostream>
using namespace std;

class Base {
public:
    Base() {cout <<"default base constructor is called" << endl;}
    Base(int j) : pri_base_mem(j) {cout << "base constructor1 is called" << endl;}
    Base(int i, int j) : pub_base_mem(i), pri_base_mem(j) {cout << "base constructor2 is called" << endl;}
    int pub_base_mem;
private:
    int pri_base_mem;
};

class Derived : public Base {
public:
    Derived() {cout <<"default derived constructor is called" << endl;}
    Derived(int i, int j, int k) :Base(i, j), pri_derived_mem(k) {cout << "derived constructor is called" << endl;}

private:
    int pri_derived_mem;
};

int main() {
    Derived(1,2,3);
}

