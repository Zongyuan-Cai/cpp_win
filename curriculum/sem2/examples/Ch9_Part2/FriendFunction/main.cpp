// Fig. 9.22: main.cpp
// Friends can access private members of a class.

#include <iostream>
using std::cout;
using std::endl;

class Count
{
    friend void setX( Count &, int ); // friend declaration
public:
    // constructor
    Count()
        : x( 0 )
    {
        // empty body
    }

    void print() const
    {
        cout << x << endl;
    }
private:
    int x;
};

// function setX can modify private data of Count
// because setX is declared as a friend of Count
void setX( Count &c, int val )
{
    c.x = val; // friend function can modify Count's private member
}

int main()
{
    Count counter;

    cout << "counter.x after instantiation: ";
    counter.print();

    setX( counter, 8 ); // invoke friend function
    cout << "counter.x after call to setX friend function: ";
    counter.print();

    return 0;
}
