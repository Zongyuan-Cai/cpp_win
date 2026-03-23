#include <iostream>
#include <string>
using namespace std;

class Coin
{
private:
    int value;

public:
    Coin(int v) : value(v)
    {
        cout << "Coin " << value << " is created." << endl;
    }
    ~Coin()
    {
        cout << "Coin " << value << " is destroyed." << endl;
    }
    int getValue() const { return value; }
};

class Esper
{
private:
    string name;
    Coin projectile;

public:
    Esper(string n = "Misaka Mikoto", int coinValue = 100) : name(n), projectile(coinValue)
    {
        cout << "Esper " << name << " is ready." << endl;
    }
    ~Esper()
    {
        cout << "Esper " << name << " has left." << endl;
    }
    void fire()
    {
        cout << "Fire!Railgun !" << endl;
    }
};

int main()
{
    Esper esper;
    esper.fire();
    return 0;
}