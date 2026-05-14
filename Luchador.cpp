#include "Luchador.hpp"
#include <iostream>
#include <cstdlib> // For rand()

// Default Constructor
Luchador::Luchador() : name("Luchador Anonimo"), life(100), health(100), attackPoints(10), level(1) {}

// Parameterized Constructor
Luchador::Luchador(std::string name, int life, int attackPoints, int level) {
    this->name = name;
    this->life = life;
    this->health = life; // health is initialized to max life
    this->attackPoints = attackPoints;
    this->level = level;
}

// --- Getters ---
std::string Luchador::getName() const { return name; }
int Luchador::getLife() const { return life; }
int Luchador::getHealth() const { return health; }
int Luchador::getAttackPoints() const { return attackPoints; }
int Luchador::getLevel() const { return level; }

// --- Setters ---
void Luchador::setName(std::string name) { this->name = name; }
void Luchador::setLife(int life) { this->life = life; }
void Luchador::setAttackPoints(int attackPoints) { this->attackPoints = attackPoints; }
void Luchador::setLevel(int level) { this->level = level; }
void Luchador::setHealth(int health) { 
    this->health = health; 
    if (this->health < 0) this->health = 0;
    if (this->health > this->life) this->health = this->life;
}

// --- Required Methods ---

// 3. Method that calculates the health percentage
int Luchador::healthPercentage() const {
    if (life <= 0) return 0; // Prevent division by zero
    return (health * 100) / life;
}

// 4. Method that prints the 20-character health bar
void Luchador::printHealthBar() const {
    int percentage = healthPercentage();
    int solidBars = percentage / 5; // 100% / 5 = 20 characters
    
    std::cout << "[";
    for (int i = 0; i < 20; ++i) {
        if (i < solidBars) {
            std::cout << "#"; // Remaining health
        } else {
            std::cout << "-"; // Lost health
        }
    }
    std::cout << "] " << percentage << "%";
}

// 5. Method to receive attack
void Luchador::receiveAttack(int damage) {
    health -= damage;
    if (health < 0) {
        health = 0;
    }
    std::cout << name << " receives " << damage << " points of damage!\n";
}

// 6. Method to attack a target
void Luchador::attack(Luchador& target) {
    std::cout << name << " attacks " << target.getName() << "!\n";
    
    int damage = 0;
    int halfAttack = attackPoints / 2;
    if (halfAttack < 1) halfAttack = 1; // Failsafe to prevent modulo by zero

    if (target.getLevel() > this->level) {
        // Target is higher level: Damage is random between 1 and half of attack points
        damage = (rand() % halfAttack) + 1;
    } else {
        // Target is lower or equal level: Damage is random between half and total attack points
        int range = attackPoints - halfAttack + 1;
        damage = (rand() % range) + halfAttack;
    }

    // Substract health points from the target
    target.receiveAttack(damage);
}

// 7. Method to print unit stats
void Luchador::print() const {
    std::cout << "--- " << name << " ---\n";
    std::cout << "Level: " << level << " | Attack Power: " << attackPoints << "\n";
    std::cout << "HP: " << health << " / " << life << "\n";
    printHealthBar();
    std::cout << "\n";
}