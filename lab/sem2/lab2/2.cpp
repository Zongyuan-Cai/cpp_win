#include <iostream>
using namespace std;

class HornetSilkNeedle
{
private:
    int currentSilk;
    const int maxSilk;

public:
    HornetSilkNeedle(int max = 100, int initialSilk = 0) : currentSilk(initialSilk), maxSilk(max) {}

    void gatherSilk(int amount)
    {
        if (currentSilk + amount <= maxSilk)
        {
            currentSilk += amount;
        }
        else
        {
            currentSilk = maxSilk;
        }
    }

    void heal()
    {
        if (currentSilk >= 30)
        {
            currentSilk -= 30;
            cout << "Healed!" << endl;
        }
        else
        {
            cout << "Not enough silk!" << endl;
        }
    }

    void displayStatus() const
    {
        cout << "Silk: " << currentSilk << "/" << maxSilk << endl;
    }
};

int main()
{
    cout << "Normal Hornet action" << endl;
    HornetSilkNeedle hornet(100, 50);
    hornet.displayStatus();
    hornet.heal();
    hornet.displayStatus();
    cout << endl;
    cout << "Const Hornet action" << endl;
    const HornetSilkNeedle constHornet(150);
    constHornet.displayStatus();
    // constHornet.heal();
    return 0;
}