#include "Luchador.hpp"
#include "Ataque.hpp"
#include <iostream>
#include <cstdlib>
#include <fstream>

Luchador::Luchador() : name("Luchador Anonimo"), maxHP(100), HP(100), attackPoints(10), level(1) {}

Luchador::Luchador(std::string name, int maxHP, int attackPoints, int level)
{
    this->name = name;
    this->maxHP = maxHP;
    this->HP = maxHP;
    this->attackPoints = attackPoints;
    this->level = level;
}

std::string Luchador::getName() const { return name; }
int Luchador::getmaxHP() const { return maxHP; }
int Luchador::getHP() const { return HP; }
int Luchador::getAttackPoints() const { return attackPoints; }
int Luchador::getLevel() const { return level; }

void Luchador::setName(std::string name)
{
    std::cout << "The luchador's name is now: " << name << "!" << std::endl;
    this->name = name;
}
void Luchador::setmaxHP(int maxHP) { this->maxHP = maxHP; }
void Luchador::setAttackPoints(int attackPoints) { this->attackPoints = attackPoints; }
void Luchador::setLevel(int level) { this->level = level; }
void Luchador::setHP(int HP)
{
    this->HP = HP;
    if (this->HP < 0)
        this->HP = 0;
    if (this->HP > this->maxHP)
        this->HP = this->maxHP;
}

int Luchador::HPPercentage() const
{
    if (maxHP <= 0)
        return 0;
    return (HP * 100) / maxHP;
}

void Luchador::printHPBar() const
{
    int percentage = HPPercentage();
    int solidBars = percentage / 5;

    std::cout << "[";
    for (int i = 0; i < 20; ++i)
    {
        if (i < solidBars)
        {
            std::cout << "#";
        }
        else
        {
            std::cout << "-";
        }
    }
    std::cout << "] " << percentage << "%";
}

void Luchador::receiveAttack(int damage)
{
    HP -= damage;
    if (HP < 0)
    {
        HP = 0;
    }
    std::cout << name << " receives " << damage << " points of damage!\n";
    // Print punch ASCII art when an attack lands
    try {
        std::ifstream artFile("Punch.txt");
        if (artFile.is_open()) {
            std::string line;
            while (std::getline(artFile, line)) {
                std::cout << line << "\n";
            }
        }
    } catch (...) {
        // silently ignore if file can't be read
    }
}

void Luchador::attack(Luchador &target)
{
    std::cout << name << " attacks " << target.getName() << "!\n";

    int damage = 0;
    int halfAttack = attackPoints / 2;
    if (halfAttack < 1)
        halfAttack = 1;

    if (target.getLevel() > this->level)
    {
        damage = (rand() % halfAttack) + 1;
    }
    else
    {
        int range = attackPoints - halfAttack + 1;
        damage = (rand() % range) + halfAttack;
    }

    target.receiveAttack(damage);
}

void Luchador::agregarAtaque(Ataque* ataque) {
    if (ataque == nullptr) {
        throw std::invalid_argument("Cannot add null attack!");
    }
    ataques.push_back(ataque);
}

int Luchador::getNumAtaques() const {
    return ataques.size();
}

Ataque* Luchador::getAtaque(int index) const {
    if (index < 0 || index >= static_cast<int>(ataques.size())) {
        throw std::out_of_range("Attack index out of range!");
    }
    return ataques[index];
}

void Luchador::imprimirAtaques() const {
    std::cout << "\n--- " << name << "'s Attacks ---\n";
    for (int i = 0; i < static_cast<int>(ataques.size()); ++i) {
        std::cout << "[" << (i + 1) << "] ";
        if (ataques[i] != nullptr) {
            ataques[i]->print();
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

void Luchador::atacarCon(Ataque* ataque, Luchador& target) {
    if (ataque == nullptr) {
        throw std::invalid_argument("Attack cannot be null!");
    }
    
    if (!ataque->usarAtaque()) {
        std::cout << name << " tried to use " << ataque->getNombre() << " but has no PP left!\n";
        return;
    }
    
    std::cout << name << " uses " << ataque->getNombre() << " on " << target.getName() << "!\n";
    
    int damage = ataque->getPoder();
    
    int variance = damage / 4;
    if (variance < 1) variance = 1;
    damage = damage - variance + (rand() % (variance * 2 + 1));
    
    int roll = rand() % 100;
    if (roll >= ataque->getPrecision()) {
        std::cout << "[MISS!] The attack didn't connect!\n";
        return;
    }
    
    target.receiveAttack(damage);
}

bool Luchador::tienePP() const {
    for (const Ataque* a : ataques) {
        if (a != nullptr && a->getPPActual() > 0) return true;
    }
    return false;
}

void Luchador::print() const
{
    std::cout << "--- " << name << " ---\n";
    std::cout << "Level: " << level << " | Attack Power: " << attackPoints << "\n";
    std::cout << "HP: " << HP << " / " << maxHP << "\n";
    printHPBar();
    std::cout << "\n";
}

Luchador::~Luchador() {
    for (Ataque* a : ataques) {
        delete a;
    }
    ataques.clear();
}