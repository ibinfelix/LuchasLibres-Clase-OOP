#ifndef LUCHADOR_HPP
#define LUCHADOR_HPP

#include <string>
#include <vector>

class Ataque;

class Luchador {
private:
    std::string name;
    int maxHP;           
    int HP;         
    int attackPoints;   
    int level;
    std::vector<Ataque*> ataques;

public:
    Luchador();
    Luchador(std::string name, int maxHP, int attackPoints, int level);
    virtual ~Luchador();

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

    void agregarAtaque(Ataque* ataque);
    int getNumAtaques() const;
    Ataque* getAtaque(int index) const;
    void imprimirAtaques() const;
    bool tienePP() const;

    int HPPercentage() const;
    void printHPBar() const;
    void printHealthBar() const { printHPBar(); }
    virtual void receiveAttack(int damage);
    virtual void atacarCon(Ataque* ataque, Luchador& target);
    virtual void attack(Luchador& target);
    virtual void print() const;
    
    int getHealth() const { return HP; }
    int getLife() const { return maxHP; }
    void setHealth(int health) { setHP(health); }
    
    virtual void revive() = 0;
    
    bool operator>(const Luchador& other) const {
        return this->attackPoints > other.attackPoints;
    }
};

#endif