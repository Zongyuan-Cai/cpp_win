#include <iostream>
using namespace std;
class Rectangle
{
private:
    double length;
    double width;

public:
    Rectangle(double l = 0, double w = 0) : length(l), width(w) {}
    ~Rectangle() {}
    void setLength(double l)
    {
        if (l >= 0)
            length = l;
        else
            cerr << "Length cannot be negative." << endl;
    }
    void setWidth(double w)
    {
        if (w >= 0)
            width = w;
        else
            cerr << "Width cannot be negative." << endl;
    }
    double getLength() const
    {
        return length;
    }
    double getWidth() const
    {
        return width;
    }
    double area() const
    {
        return length * width;
    }
    double perimeter() const
    {
        return 2 * (length + width);
    }
};
int main()
{
    Rectangle rect(5.0, 3.0);
    cout << "Length: " << rect.getLength() << endl;
    cout << "Width: " << rect.getWidth() << endl;
    cout << "Area: " << rect.area() << endl;
    cout << "Perimeter: " << rect.perimeter() << endl;

    rect.setLength(7.0);
    rect.setWidth(4.0);
    cout << "Updated Length: " << rect.getLength() << endl;
    cout << "Updated Width: " << rect.getWidth() << endl;
    cout << "Updated Area: " << rect.area() << endl;
    cout << "Updated Perimeter: " << rect.perimeter() << endl;

    return 0;
}