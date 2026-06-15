// Virtual function demonstration with Animal/Bird hierarchy.
// Demonstrating dynamic binding (polymorphism) via virtual functions.

#include <iostream>
using std::cout;
using std::endl;

class Animal {
public:
    virtual void move() const {
        cout << "Animal moves" << endl;
    }
};

class Bird : public Animal {
public:
    virtual void move() const {  // override
        cout << "Bird flies" << endl;
    }
};

class Fish : public Animal {
public:
    virtual void move() const {  // override
        cout << "Fish swims" << endl;
    }
};

int main() {
    Animal animal;
    Bird bird;
    Fish fish;

    // Static binding — called by object name and (.) operator
    cout << "Static binding (by object name):" << endl;
    animal.move();
    bird.move();
    fish.move();

    // Dynamic binding — called by base-class pointer
    cout << "\nDynamic binding (by base-class pointer):" << endl;
    Animal *ptr;

    ptr = &bird;
    ptr->move();   // calls Bird::move()

    ptr = &fish;
    ptr->move();   // calls Fish::move()

    ptr = &animal;
    ptr->move();   // calls Animal::move()

    // Dynamic binding — called by base-class reference
    cout << "\nDynamic binding (by base-class reference):" << endl;
    Animal &refBird = bird;
    Animal &refFish = fish;

    refBird.move();   // calls Bird::move()
    refFish.move();   // calls Fish::move()

    return 0;
}
