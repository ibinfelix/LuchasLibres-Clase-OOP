#pragma once
#include "Luchador.hpp"
#include <vector>
#include <stdexcept>

class Equipo {
private:
    std::vector<Luchador*> luchadores;
    std::string nombreEquipo;
    int indexActivo;

public:
    Equipo(std::string nombre);
    ~Equipo();

    void agregarLuchador(Luchador* luchador);
    Luchador* getLuchadorActivo() const;
    Luchador* getLuchador(int index) const;
    int getNumLuchadores() const;
    std::string getNombre() const;
    
    bool cambiarLuchador(int index);
    bool hayLuchadoresVivos() const;
    int contarLuchadoresVivos() const;
    
    void imprimirEquipo() const;
    void imprimirEstadoEquipo() const;
};
