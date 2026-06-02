#include "Tecnico.hpp"
#include <iostream>
#include <cstdlib>
 
Tecnico::Tecnico() : Luchador(), accuracy(0.5f) {}
 
Tecnico::Tecnico(std::string name, int life, int attackPoints, int level, float accuracy)
    : Luchador(name, life, attackPoints, level), accuracy(accuracy) {
    if (this->accuracy < 0.0f) this->accuracy = 0.0f;
    if (this->accuracy > 1.0f) this->accuracy = 1.0f;
}
 
float Tecnico::getAccuracy() const { return accuracy; }
void Tecnico::setAccuracy(float accuracy) { this->accuracy = accuracy; }
 
void Tecnico::receiveAttack(int damage) {
    int roll = rand() % 100;
    int dodgeThreshold = static_cast<int>(accuracy * 100);
 
    if (roll < dodgeThreshold) {
        std::cout << getName() << " reads the move perfectly and DODGES the attack!\n";
        return;
    }
 
    setHealth(getHealth() - damage);
    std::cout << getName() << " receives " << damage << " damage!\n";
}
 
void Tecnico::attack(Luchador& target) {
    std::cout << getName() << " strikes at " << target.getName() << " with precision!\n";
 
    int halfAttack = getAttackPoints() / 2;
    if (halfAttack < 1) halfAttack = 1;
 
    int damage = 0;
    if (target.getLevel() > getLevel()) {
        damage = (rand() % halfAttack) + 1;
    } else {
        int range = getAttackPoints() - halfAttack + 1;
        damage = (rand() % range) + halfAttack;
    }
 
    int roll = rand() % 100;
    int critThreshold = static_cast<int>(accuracy * 100);
    if (roll < critThreshold) {
        damage *= 2;
        std::cout << "[CRITICAL HIT!] " << getName() << "'s move lands perfectly! Damage doubled!\n";
    }
 
    target.receiveAttack(damage);
}
 
void Tecnico::print() const {
    std::cout << "--- [TECNICO] " << getName() << " ---\n";
    std::cout << "Level: " << getLevel() << " | Attack: " << getAttackPoints()
              << " | Accuracy: " << static_cast<int>(accuracy * 100) << "%\n";
    std::cout << "HP: " << getHealth() << " / " << getLife() << "\n";
    printHealthBar();
    std::cout << "\n";
}

void Tecnico::revive() {
    setHealth(getLife());
    std::cout << "[REVIVAL] " << getName() << " has been revived and returned to full health!\n";
}