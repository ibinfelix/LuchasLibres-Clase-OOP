#pragma once
#include "Luchador.hpp"
 
class Rudo : public Luchador {
    private:
        int strength;
    
    public:
        Rudo();
        Rudo(std::string name, int life, int attackPoints, int level, int strength);
    
        int getStrength() const;
        void setStrength(int strength);
    
        void receiveAttack(int damage) override;
        void attack(Luchador& target) override;
        void print() const override;
        void revive() override;
};