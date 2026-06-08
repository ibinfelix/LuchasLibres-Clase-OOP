#include "Ataque.hpp"
#include <iostream>

Ataque::Ataque() 
    : nombre("Golpe Basico"), poder(5), precision(100), puntosResistencia(20), ppActual(20) {}

Ataque::Ataque(std::string nombre, int poder, int precision, int pp)
    : nombre(nombre), poder(poder), precision(precision), puntosResistencia(pp), ppActual(pp) {
    if (this->poder < 1) this->poder = 1;
    if (this->precision < 0) this->precision = 0;
    if (this->precision > 100) this->precision = 100;
    if (this->puntosResistencia < 1) this->puntosResistencia = 1;
}

std::string Ataque::getNombre() const { return nombre; }
int Ataque::getPoder() const { return poder; }
int Ataque::getPrecision() const { return precision; }
int Ataque::getPPActual() const { return ppActual; }
int Ataque::getPPMax() const { return puntosResistencia; }

void Ataque::restaurarPP() {
    ppActual = puntosResistencia;
}

bool Ataque::usarAtaque() {
    if (ppActual > 0) {
        ppActual--;
        return true;
    }
    return false;
}

void Ataque::print() const {
    std::cout << nombre << " [Power: " << poder << " | Accuracy: " << precision 
              << "% | PP: " << ppActual << "/" << puntosResistencia << "]";
}
