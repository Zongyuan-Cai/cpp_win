#include <iostream>
#include<iomanip>
using namespace std;

class Rectangle {
private:
    double length;
    double width;

public:
    Rectangle(double len = 1.0, double wid = 1.0) : length(len), width(wid) {}

    double getLength() const { return length; }
    double getWidth() const { return width; }

    bool setLength(double len) {
        if (len > 0.0 && len < 20.0) {
            length = len;
            return true;
        }
        return false;
    }

    bool setWidth(double wid) {
        if (wid > 0.0 && wid < 20.0) {
            width = wid;
            return true;
        }
        return false;
    }

    double perimeter() const {
        return 2 * (length + width);
    }

    double area() const {
        return length * width;
    }
};

int main() {
    cout << fixed << setprecision(1);
    Rectangle rect;

    cout << "length = " << rect.getLength() << ", width = " << rect.getWidth()
         << ", perimeter = " << rect.perimeter() << ", area = " << rect.area() << endl;

    rect.setLength(5.0);
    rect.setWidth(4.0);
    cout << "length = " << rect.getLength() << ", width = " << rect.getWidth()
         << ", perimeter = " << rect.perimeter() << ", area = " << rect.area() << endl;

    rect.setLength(1.0);
    rect.setWidth(1.0);
    cout << "length = " << rect.getLength() << ", width = " << rect.getWidth()
         << ", perimeter = " << rect.perimeter() << ", area = " << rect.area() << endl;

    return 0;
}
