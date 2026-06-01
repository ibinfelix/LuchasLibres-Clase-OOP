#ifndef LUCHADOR_HPP
#define LUCHADOR_HPP

#include <string>

class Luchador {
private:
    std::string name;
    int life;           
    int health;         
    int attackPoints;   
    int level;          

public:
    // Constructors
    Luchador();
    Luchador(std::string name, int life, int attackPoints, int level);

    // Getters
    std::string getName() const;
    int getLife() const;
    int getHealth() const;
    int getAttackPoints() const;
    int getLevel() const;

    // Setters
    void setName(std::string name);
    void setLife(int life);
    void setHealth(int health);
    void setAttackPoints(int attackPoints);
    void setLevel(int level);

    // Methods
    int healthPercentage() const;
    void printHealthBar() const;
    virtual void receiveAttack(int damage);
    virtual void attack(Luchador& target);
    virtual void print() const;
};

#endif