#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
using namespace std;

class Merchandise {
public:
    Merchandise();
    ~Merchandise();
    friend istream& operator>>(istream& in, Merchandise& s);  //����һ����Ʒ����Ϣ
    friend ostream& operator<<(ostream& out, Merchandise& s);//���һ����Ʒ����Ϣ
private:
    int no;   //���
    char* name;     //��Ʒ��
    double price;     //�۸�
};

Merchandise::Merchandise() {
    name = new char[20];
}

Merchandise::~Merchandise() {
    delete[] name;
}

istream& operator>>(istream& in, Merchandise& s) {
    //����һ����Ʒ����Ϣ
    cout << "��������Ʒ��ţ�";
    in >> s.no;
    cout << "��������Ʒ���ƣ�";
    in >> s.name;
    cout << "��������Ʒ�۸�";
    in >> s.price;
    return in;
}

ostream& operator<<(ostream& out, Merchandise& s) {
    //���һ����Ʒ����Ϣ
    out << "��Ʒ��ţ�" << s.no << endl;
    out << "��Ʒ���ƣ�" << s.name << endl;
    out << "��Ʒ�۸�" << s.price << endl;
    return out;
}

int main() {
    Merchandise mer;
    cin >> mer;
    cout << mer;
    return 0;
}