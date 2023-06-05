#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
using namespace std;

class Merchandise {
public:
    Merchandise();
    ~Merchandise();
    friend istream& operator>>(istream& in, Merchandise& s);  //输入一件商品的信息
    friend ostream& operator<<(ostream& out, Merchandise& s);//输出一件商品的信息
private:
    int no;   //编号
    char* name;     //商品名
    double price;     //价格
};

Merchandise::Merchandise() {
    name = new char[20];
}

Merchandise::~Merchandise() {
    delete[] name;
}

istream& operator>>(istream& in, Merchandise& s) {
    //输入一件商品的信息
    cout << "请输入商品编号：";
    in >> s.no;
    cout << "请输入商品名称：";
    in >> s.name;
    cout << "请输入商品价格：";
    in >> s.price;
    return in;
}

ostream& operator<<(ostream& out, Merchandise& s) {
    //输出一件商品的信息
    out << "商品编号：" << s.no << endl;
    out << "商品名称：" << s.name << endl;
    out << "商品价格：" << s.price << endl;
    return out;
}

int main() {
    Merchandise mer;
    cin >> mer;
    cout << mer;
    return 0;
}