#include "Equipo.hpp"
#include <iostream>

Equipo::Equipo(std::string nombre) 
    : nombreEquipo(nombre), indexActivo(-1) {}

Equipo::~Equipo() {
    luchadores.clear();
}

void Equipo::agregarLuchador(Luchador* luchador) {
    if (luchador == nullptr) {
        throw std::invalid_argument("Cannot add null wrestler to team!");
    }
    luchadores.push_back(luchador);
    if (indexActivo == -1) {
        indexActivo = 0;
    }
}

Luchador* Equipo::getLuchadorActivo() const {
    if (indexActivo < 0 || indexActivo >= static_cast<int>(luchadores.size())) {
        throw std::out_of_range("No active wrestler available!");
    }
    return luchadores[indexActivo];
}

Luchador* Equipo::getLuchador(int index) const {
    if (index < 0 || index >= static_cast<int>(luchadores.size())) {
        throw std::out_of_range("Wrestler index out of range!");
    }
    return luchadores[index];
}

int Equipo::getNumLuchadores() const {
    return luchadores.size();
}

std::string Equipo::getNombre() const {
    return nombreEquipo;
}

bool Equipo::cambiarLuchador(int index) {
    if (index < 0 || index >= static_cast<int>(luchadores.size())) {
        return false;
    }
    
    Luchador* nuevo = luchadores[index];
    if (nuevo->getHP() <= 0) {
        std::cout << "That wrestler is defeated!\n";
        return false;
    }
    
    indexActivo = index;
    return true;
}

bool Equipo::hayLuchadoresVivos() const {
    for (const auto& luchador : luchadores) {
        if (luchador->getHP() > 0) {
            return true;
        }
    }
    return false;
}

int Equipo::contarLuchadoresVivos() const {
    int count = 0;
    for (const auto& luchador : luchadores) {
        if (luchador->getHP() > 0) {
            count++;
        }
    }
    return count;
}

void Equipo::imprimirEquipo() const {
    std::cout << "\n========== " << nombreEquipo << " ==========\n";
    for (int i = 0; i < static_cast<int>(luchadores.size()); ++i) {
        std::cout << "[" << (i + 1) << "] ";
        luchadores[i]->print();
    }
    std::cout << "====================================\n\n";
}

void Equipo::imprimirEstadoEquipo() const {
    std::cout << "\n--- " << nombreEquipo << " Status ---\n";
    for (int i = 0; i < static_cast<int>(luchadores.size()); ++i) {
        std::cout << "[" << (i + 1) << "] " << luchadores[i]->getName() 
                  << " - HP: " << luchadores[i]->getHP() << "/" 
                  << luchadores[i]->getmaxHP();
        if (luchadores[i]->getHP() <= 0) {
            std::cout << " [DEFEATED]";
        }
        if (i == indexActivo) {
            std::cout << " <-- ACTIVE";
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}
