#include <iostream>
#include <string>
using namespace std;

class Weapon
{
private:
    string weaponName;
    const int maxAmmo;

public:
    Weapon(string name = "", int ammo = 0) : weaponName(name), maxAmmo(ammo)
    {
        cout << "Weapon " << weaponName << " loaded." << endl;
    }
    ~Weapon()
    {
        cout << "Weapon " << weaponName << " dropped." << endl;
    }
    string getWeaponInfo() const
    {
        return weaponName;
    }
};

class Leon
{
private:
    const string codeName;
    Weapon primary;
    Weapon secondary;

public:
    Leon(string name, string p_name, int p_max, string s_name, int s_max) : codeName(name), primary(Weapon(p_name, p_max)), secondary(Weapon(s_name, s_max))
    {
        cout << "Agent " << codeName << " deployed." << endl;
    }
    ~Leon()
    {
        cout << "Agent " << codeName << " extracted." << endl;
    }
};

int main()
{
    Leon agent("Kenny", "SilverGjost", 1, "Shotgun", 2);
    cout << "Mission Ongoing" << endl;
    return 0;
}