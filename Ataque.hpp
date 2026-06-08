#pragma once
#include <string>

class Ataque {
private:
    std::string nombre;
    int poder;
    int precision;
    int puntosResistencia;
    int ppActual;

public:
    Ataque();
    Ataque(std::string nombre, int poder, int precision, int pp);

    std::string getNombre() const;
    int getPoder() const;
    int getPrecision() const;
    int getPPActual() const;
    int getPPMax() const;

    void restaurarPP();
    bool usarAtaque();
    
    void print() const;
};
