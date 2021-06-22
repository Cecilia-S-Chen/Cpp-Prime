#include <iostream>
#include <string>
using namespace std;

class Quote {
public:
    Quote() = default;
    Quote(const string &book, double sales_price) : book(book), price(sales_price) {}
    string isbin() const {return bookNo;}
    virtual double net_price(size_t n) const {return n * price;}
    virtual ~Quote();
private:
    string book;
protected:
    double price = 0.0;
};

