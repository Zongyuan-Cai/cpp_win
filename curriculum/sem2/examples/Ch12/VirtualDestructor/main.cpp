// Virtual destructor demonstration.
// Fig. 12.4~12.6: Demonstrating the importance of virtual destructors.

#include <iostream>
using std::cout;
using std::endl;

class Base {
public:
    Base() {
        cout << "Base" << endl;
        p1 = new int(1);
    }
    virtual ~Base() {
        cout << "~Base" << endl;
        delete p1;
    }
private:
    int *p1;
};

class Derive : public Base {
public:
    Derive() {
        cout << "Derive" << endl;
        p2 = new int(2);
    }
    virtual ~Derive() {
        cout << "~Derive" << endl;
        delete p2;
    }
private:
    int *p2;
};

int main() {
    Base *pDerive = new Derive;
    delete pDerive;
    return 0;
}
