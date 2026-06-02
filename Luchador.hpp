#ifndef LUCHADOR_HPP
#define LUCHADOR_HPP

#include <string>

class Luchador {
private:
    std::string name;
    int maxHP;           
    int HP;         
    int attackPoints;   
    int level;         

public:
    Luchador();
    Luchador(std::string name, int maxHP, int attackPoints, int level);

    std::string getName() const;
    int getmaxHP() const;
    int getHP() const;
    int getAttackPoints() const;
    int getLevel() const;

    void setName(std::string name);
    void setmaxHP(int maxHP);
    void setHP(int HP);
    void setAttackPoints(int attackPoints);
    void setLevel(int level);

    int HPPercentage() const;
    void printHPBar() const;
    void receiveAttack(int damage);
    void attack(Luchador& target);
    void print() const;
};

#endif