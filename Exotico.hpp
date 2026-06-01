#pragma once
#include "Luchador.hpp"
 
class Exotico : public Luchador {
private:
    float love; 
 
public:
    Exotico();
    Exotico(std::string name, int life, int attackPoints, int level, float love);
 
    float getLove() const;
    void setLove(float love);
 
    void receiveAttack(int damage) override;
    void attack(Luchador& target) override;
    void print() const override;
};