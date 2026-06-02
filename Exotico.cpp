#include "Exotico.hpp"
#include <iostream>
#include <cstdlib>
 
Exotico::Exotico() : Luchador(), love(0.5f) {}
 
Exotico::Exotico(std::string name, int life, int attackPoints, int level, float love)
    : Luchador(name, life, attackPoints, level), love(love) {
    if (this->love < 0.0f) this->love = 0.0f;
    if (this->love > 1.0f) this->love = 1.0f;
}
 
float Exotico::getLove() const { return love; }
void Exotico::setLove(float love) {
    this->love = love;
    if (this->love < 0.0f) this->love = 0.0f;
    if (this->love > 1.0f) this->love = 1.0f;
}
 
void Exotico::receiveAttack(int damage) {
    int roll = rand() % 100;
    int loveThreshold = static_cast<int>(love * 100);
 
    int actualDamage = damage;
    if (roll < loveThreshold) {
        actualDamage = damage / 2;
        if (actualDamage < 1) actualDamage = 1;
        std::cout << "[CROWD PROTECTION!] The audience's love shields " << getName()
                  << "! Only half damage received.\n";
    }
 
    setHealth(getHealth() - actualDamage);
    std::cout << getName() << " receives " << actualDamage << " damage!\n";
}
 
void Exotico::attack(Luchador& target) {
    std::cout << getName() << " dazzles the crowd and goes after " << target.getName() << "!\n";
 
    int halfAttack = getAttackPoints() / 2;
    if (halfAttack < 1) halfAttack = 1;
 
    int damage = 0;
    if (target.getLevel() > getLevel()) {
        damage = (rand() % halfAttack) + 1;
    } else {
        int range = getAttackPoints() - halfAttack + 1;
        damage = (rand() % range) + halfAttack;
    }
 
    if (love >= 0.8f) {
        damage += 8;
        std::cout << "[BLOWN KISS!] " << getName() << " distracts " << target.getName()
                  << " with charisma! +8 bonus damage!\n";
    }
 
    target.receiveAttack(damage);
}
 
void Exotico::print() const {
    std::cout << "--- [EXOTICO] " << getName() << " ---\n";
    std::cout << "Level: " << getLevel() << " | Attack: " << getAttackPoints()
              << " | Love: " << static_cast<int>(love * 100) << "%\n";
    std::cout << "HP: " << getHealth() << " / " << getLife() << "\n";
    printHealthBar();
    std::cout << "\n";
}

void Exotico::revive() {
    setHealth(getLife());
    setLove(love + 0.15f);
    std::cout << "[REVIVAL] " << getName() << " captivates the crowd and is reborn with enhanced love!\n";
}