#ifndef LUCHADOR_HPP
#define LUCHADOR_HPP

#include <string>

class Luchador {
private:
    std::string name;
    int life;           // Maximum life points
    int health;         // Current life points
    int attackPoints;   // Maximum attack points
    int level;          // Character level

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

    // Required Assignment Methods
    int healthPercentage() const;
    void printHealthBar() const;
    void receiveAttack(int damage);
    void attack(Luchador& target);
    void print() const;
};

#endif