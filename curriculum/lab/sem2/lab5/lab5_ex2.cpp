#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

class Shape {
public:
    virtual ~Shape() {}
    virtual double getArea() const = 0;
    virtual void print() const = 0;
    virtual int getDimension() const = 0;
};

class TwoDimensionalShape : public Shape {
public:
    ~TwoDimensionalShape() {}

    int getDimension() const {
        return 2;
    }
};

class ThreeDimensionalShape : public Shape {
public:
    ~ThreeDimensionalShape() {}
    virtual double getVolume() const = 0;

    int getDimension() const {
        return 3;
    }
};

class Circle : public TwoDimensionalShape {
public:
    Circle(double radius) {
        this->radius = radius;
    }

    ~Circle() {}

    double getArea() const {
        return 3.14159265358979323846 * radius * radius;
    }

    void print() const {
        cout << "Circle with radius " << radius;
    }

private:
    double radius;
};

class Square : public TwoDimensionalShape {
public:
    Square(double side) {
        this->side = side;
    }

    ~Square() {}

    double getArea() const {
        return side * side;
    }

    void print() const {
        cout << "Square with side " << side;
    }

private:
    double side;
};

class Triangle : public TwoDimensionalShape {
public:
    Triangle(double side1, double side2, double side3)
    {
        this->side1 = side1;
        this->side2 = side2;
        this->side3 = side3;
    }

    ~Triangle() {}

    double getArea() const {
        double s = (side1 + side2 + side3) / 2.0;
        return sqrt(s * (s - side1) * (s - side2) * (s - side3));
    }

    void print() const {
        cout << "Triangle with sides " << side1 << ", " << side2 << ", " << side3;
    }

private:
    double side1;
    double side2;
    double side3;
};

class Sphere : public ThreeDimensionalShape {
public:
    Sphere(double radius) {
        this->radius = radius;
    }

    ~Sphere() {}

    double getArea() const {
        return 4.0 * 3.14159265358979323846 * radius * radius;
    }

    double getVolume() const {
        return (4.0 / 3.0) * 3.14159265358979323846 * radius * radius * radius;
    }

    void print() const {
        cout << "Sphere with radius " << radius;
    }

private:
    double radius;
};

class Cube : public ThreeDimensionalShape {
public:
    Cube(double side) {
        this->side = side;
    }

    ~Cube() {}

    double getArea() const {
        return 6.0 * side * side;
    }

    double getVolume() const {
        return side * side * side;
    }

    void print() const {
        cout << "Cube with side " << side;
    }

private:
    double side;
};

int main() {
    vector<Shape*> shapes;
    shapes.push_back(new Circle(5.0));
    shapes.push_back(new Square(4.0));
    shapes.push_back(new Triangle(3.0, 4.0, 5.0));
    shapes.push_back(new Sphere(3.0));
    shapes.push_back(new Cube(2.0));

    cout << fixed << setprecision(2);

    for (Shape* shape : shapes) {
        shape->print();
        cout << '\n';
        if (shape->getDimension() == 2) {
            cout << "Area: " << shape->getArea() << "\n\n";
        } else {
            ThreeDimensionalShape* threeDimensional = (ThreeDimensionalShape*)shape;
            cout << "Surface area: " << threeDimensional->getArea() << '\n';
            cout << "Volume: " << threeDimensional->getVolume() << "\n\n";
        }
    }

    for (Shape* shape : shapes) {
        delete shape;
    }

    return 0;
}