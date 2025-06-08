#include <iostream>
#include <cstring>

// struct Attack{
// char *specialAtk;
// };

class Character{
protected:
char *name;
double attack_damage;
double hp, mana;

public:
Character(char *charname, double _atk, double _hp, double _mana) : name(new char[std::strlen(name) + 1]), attack_damage(_atk), hp(_hp), mana(_mana) {}

virtual void attack(Character &) = 0;


};

class Tank : public Character{
double specImmunity;
double attack_damage;
public:

};

int main() {

    return 0;
}