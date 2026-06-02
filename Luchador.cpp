#include "Luchador.hpp"
#include <iostream>
#include <cstdlib>

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
            std::cout << "#"; // Remaining HP
        }
        else
        {
            std::cout << "-"; // Lost HP
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

void Luchador::print() const
{
    std::cout << "--- " << name << " ---\n";
    std::cout << "Level: " << level << " | Attack Power: " << attackPoints << "\n";
    std::cout << "HP: " << HP << " / " << maxHP << "\n";
    printHPBar();
    std::cout << "\n";
}