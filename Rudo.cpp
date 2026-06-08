
#include "Rudo.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>
 
Rudo::Rudo() : Luchador(), strength(10) {}
 
Rudo::Rudo(std::string name, int life, int attackPoints, int level, int strength)
    : Luchador(name, life, attackPoints, level), strength(strength) {
    if (this->strength < 1)  this->strength = 1;
    if (this->strength > 20) this->strength = 20;
}
 
int Rudo::getStrength() const { return strength; }
void Rudo::setStrength(int s) {
    strength = s;
    if (strength < 1)  strength = 1;
    if (strength > 20) strength = 20;
}
 
void Rudo::receiveAttack(int damage) {
    int reduction = strength / 3;
    int actualDamage = damage - reduction;
    if (actualDamage < 1) actualDamage = 1;
 
    setHealth(getHealth() - actualDamage);
    std::cout << getName() << " takes the hit! Strength absorbs " << reduction
              << " damage. Receives " << actualDamage << " (from " << damage << ").\n";
    // Print punch ASCII art when an attack lands
    try {
        std::ifstream artFile("Punch.txt");
        if (artFile.is_open()) {
            std::string line;
            while (std::getline(artFile, line)) {
                std::cout << line << "\n";
            }
        }
    } catch (...) {}
}
 
void Rudo::attack(Luchador& target) {
    std::cout << getName() << " unleashes brute force on " << target.getName() << "!\n";
 
    int halfAttack = getAttackPoints() / 2;
    if (halfAttack < 1) halfAttack = 1;
 
    int damage = 0;
    if (target.getLevel() > getLevel()) {
        damage = (rand() % halfAttack) + 1;
    } else {
        int range = getAttackPoints() - halfAttack + 1;
        damage = (rand() % range) + halfAttack;
    }
 
    int bonus = strength / 2;
    damage += bonus;
    std::cout << "[STRENGTH BONUS] +" << bonus << " damage from raw power! (Strength: " << strength << ")\n";
 
    target.receiveAttack(damage);
}
 
void Rudo::print() const {
    std::cout << "--- [RUDO] " << getName() << " ---\n";
    std::cout << "Level: " << getLevel() << " | Attack: " << getAttackPoints()
              << " | Strength: " << strength << "/20\n";
    std::cout << "HP: " << getHealth() << " / " << getLife() << "\n";
    printHealthBar();
    std::cout << "\n";
}

void Rudo::revive() {
    setHealth(getLife());
    setStrength(strength + 2);
    std::cout << "[REVIVAL] " << getName() << " rises again with increased strength (+2)!\n";
}