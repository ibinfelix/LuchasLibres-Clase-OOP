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
    virtual ~Luchador() = default;

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
    void printHealthBar() const { printHPBar(); } // Alias for consistency
    virtual void receiveAttack(int damage);
    virtual void attack(Luchador& target);
    virtual void print() const;
    
    // Aliases for naming consistency with derived classes
    int getHealth() const { return HP; }
    int getLife() const { return maxHP; }
    void setHealth(int health) { setHP(health); }
    
    // Pure virtual method for polymorphism
    virtual void revive() = 0;
    
    // Operator overloading: compare fighters by attack power
    bool operator>(const Luchador& other) const {
        return this->attackPoints > other.attackPoints;
    }
};

#endif