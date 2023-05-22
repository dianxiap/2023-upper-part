#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
using namespace std;

// 定义基类 area_cl
class area_cl {
protected:
    double height;
    double width;

public:
    area_cl(double h, double w) : height(h), width(w) {}

    virtual double area() = 0;
};

// 定义派生类 rectangle
class rectangle : public area_cl {
public:
    rectangle(double h, double w) : area_cl(h, w) {}

    double area() {
        return height * width;
    }
};

// 定义派生类 isosceles
class isosceles : public area_cl {
public:
    isosceles(double h, double w) : area_cl(h, w) {}

    double area() {
        return 0.5 * height * width;
    }
};

int main() {
    area_cl* shape1 = new rectangle(10.0, 5.0);
    area_cl* shape2 = new isosceles(4.0, 6.0);

    cout << "Rectangle area: " << shape1->area() << endl;
    cout << "Isosceles triangle area: " << shape2->area() << endl;

    delete shape1;
    delete shape2;

    return 0;
}
