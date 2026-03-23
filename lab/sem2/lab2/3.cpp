#include <iostream>
#include <string>
using namespace std;

class Operator
{
private:
    string name;
    double atk;

public:
    Operator(string n = "", double a = 0.0) : name(n), atk(a) {}
    double getAtk() const { return atk; }
    string getName() const { return name; }
};

class TacticalBuilding
{
private:
    const int buildingID;
    Operator stationedOp;
    double buffMultiplier;

public:
    TacticalBuilding(string name, double atk, int id, double buff) : buildingID(id), stationedOp(name, atk), buffMultiplier(buff) {}

    double calculateTotalDamage() const
    {
        return stationedOp.getAtk() * buffMultiplier;
    }

    void printInfo() const
    {
        cout << "Building ID: " << buildingID << endl;
        cout << "Stationed Operator: " << stationedOp.getName() << endl;
        cout << "Buff Multiplier: " << buffMultiplier << endl;
        cout << "Total Damage: " << calculateTotalDamage() << endl;
    }
};

int main()
{
    TacticalBuilding tb1("Liskarm", 450.0, 101, 1.5);
    tb1.printInfo();
    TacticalBuilding tb2("Mudrock", 880.0, 102, 1.2);
    tb2.printInfo();
    return 0;
}