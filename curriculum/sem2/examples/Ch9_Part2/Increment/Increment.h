// Fig. 9.16-3: Increment.h
// Definition of class Increment.

#ifndef INCREMENT_H
#define INCREMENT_H

class Increment
{
public:
    Increment( int c = 0, int i = 1 ); // default constructor

    void addIncrement()
    {
        count += increment;
    }

    void print() const; // prints count and increment
private:
    int count;
    const int increment; // const data member
    int &refCount; // reference data member
};

#endif
