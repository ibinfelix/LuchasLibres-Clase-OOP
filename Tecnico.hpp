#pragma once
#include "Luchador.hpp"
 
class Tecnico : public Luchador {
    private:
        float accuracy; 
    
    public:
        Tecnico();
        Tecnico(std::string name, int life, int attackPoints, int level, float accuracy);
    
        float getAccuracy() const;
        void setAccuracy(float accuracy);
    
        void receiveAttack(int damage) override;
        void attack(Luchador& target) override;
        void print() const override;
        void revive() override;
};