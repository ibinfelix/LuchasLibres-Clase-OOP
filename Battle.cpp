#include "Luchador.hpp"
#include "Tecnico.hpp"
#include "Rudo.hpp"
#include "Exotico.hpp"
#include "Ataque.hpp"
#include "Equipo.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <stdexcept>
#include <thread>
#include <chrono>
#include <vector>
#include <fstream>
#ifdef _WIN32
#include <windows.h>
#endif

void imprimirDivisor() {
    std::cout << "========================================\n";
}

int obtenerEntradaValida(int minimo, int maximo) {
    int entrada;
    while (true) {
        try {
            if (!(std::cin >> entrada)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                throw std::invalid_argument("Invalid input. Please enter a number.");
            }
            if (entrada < minimo || entrada > maximo) {
                throw std::out_of_range("Input out of valid range!");
            }
            return entrada;
        } catch (const std::exception& e) {
            std::cout << "[ERROR] " << e.what() << " (Choose " << minimo << "-" << maximo << "): ";
        }
    }
}

int seleccionarLuchador(Equipo& equipo) {
    equipo.imprimirEstadoEquipo();
    std::cout << "Select a wrestler (1-" << equipo.getNumLuchadores() << "): ";
    
    int seleccion = obtenerEntradaValida(1, equipo.getNumLuchadores());
    int indice = seleccion - 1;
    
    try {
        Luchador* luchador = equipo.getLuchador(indice);
        if (luchador->getHP() <= 0) {
            std::cout << "[ERROR] " << luchador->getName() << " is defeated! Choose another.\n\n";
            return seleccionarLuchador(equipo);
        }
        
        if (!equipo.cambiarLuchador(indice)) {
            throw std::runtime_error("Failed to change wrestler!");
        }
        std::cout << "\n" << luchador->getName() << " enters the ring!\n\n";
        return indice;
    } catch (const std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
        return seleccionarLuchador(equipo);
    }
}

int seleccionarAtaque(Luchador* luchador) {
    std::cout << "\n" << luchador->getName() << " can use:\n";
    
    int ataqueDisponible = 0;
    for (int i = 0; i < luchador->getNumAtaques(); ++i) {
        try {
            Ataque* ataque = luchador->getAtaque(i);
            std::cout << "[" << (i + 1) << "] ";
            ataque->print();
            if (ataque->getPPActual() > 0) {
                ataqueDisponible++;
            } else {
                std::cout << " [NO PP!]";
            }
            std::cout << "\n";
        } catch (const std::exception& e) {
            std::cout << "[ERROR] " << e.what() << "\n";
        }
    }
    
    if (ataqueDisponible == 0) {
        std::cout << "[WARNING] No attacks available with PP! Opponent attacks instead.\n";
        return -1;
    }
    
    std::cout << "Choose an attack (1-" << luchador->getNumAtaques() << "): ";
    int seleccion = obtenerEntradaValida(1, luchador->getNumAtaques());
    
    try {
        Ataque* ataque = luchador->getAtaque(seleccion - 1);
        if (ataque->getPPActual() <= 0) {
            std::cout << "[ERROR] That attack has no PP left! Choose another.\n";
            return seleccionarAtaque(luchador);
        }
        return seleccion - 1;
    } catch (const std::exception& e) {
        std::cout << "[ERROR] " << e.what() << "\n";
        return seleccionarAtaque(luchador);
    }
}

void combateEquipos(Equipo& equipoJugador, Equipo& equipoPc) {
    imprimirDivisor();
    std::cout << "    LUCHA LIBRE TEAM BATTLE!\n";
    imprimirDivisor();
    
    std::cout << "\n[ROUND START]\n";
    std::cout << equipoJugador.getNombre() << " VS " << equipoPc.getNombre() << "\n";
    
    int ronda = 1;
    
    try {
        std::cout << "\n--- Choose your first wrestler ---\n";
        seleccionarLuchador(equipoJugador);
        
        std::cout << "--- PC selects a wrestler ---\n";
        int pcSeleccion = rand() % equipoPc.getNumLuchadores();
        equipoPc.cambiarLuchador(pcSeleccion);
        std::cout << equipoPc.getLuchadorActivo()->getName() << " enters the ring!\n\n";
        
        while (equipoJugador.hayLuchadoresVivos() && equipoPc.hayLuchadoresVivos()) {
            std::cout << "\n" << "=== ROUND " << ronda << " ===\n";
            std::cout << equipoJugador.getNombre() << ": " 
                      << equipoJugador.contarLuchadoresVivos() << " alive\n";
            std::cout << equipoPc.getNombre() << ": " 
                      << equipoPc.contarLuchadoresVivos() << " alive\n\n";
            
            Luchador* jugadorActual = equipoJugador.getLuchadorActivo();
            Luchador* pcActual = equipoPc.getLuchadorActivo();
            
            if (!jugadorActual->tienePP() && !pcActual->tienePP()) {
                std::cout << "\n[BOTH SIDES OUT OF PP] No attacks remaining. The battle ends in a draw.\n";
                break;
            }
            
            std::cout << "[" << jugadorActual->getName() << "] ";
            jugadorActual->printHPBar();
            std::cout << "\n[" << pcActual->getName() << "] ";
            pcActual->printHPBar();
            std::cout << "\n\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(700));
            std::cout << "--- " << jugadorActual->getName() << "'s Turn ---\n";
            int ataqueJugador = seleccionarAtaque(jugadorActual);

            if (ataqueJugador == -1) {
                std::cout << "[NOTICE] No PP available for " << jugadorActual->getName() << ". Skipping player's attack.\n";
            } else {
                try {
                    jugadorActual->atacarCon(
                        jugadorActual->getAtaque(ataqueJugador), 
                        *pcActual
                    );
                } catch (const std::exception& e) {
                    std::cout << "[ERROR] Attack failed: " << e.what() << "\n";
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(900));

            if (pcActual->getHP() <= 0) {
                std::cout << "\n" << pcActual->getName() << " is defeated!\n";
                std::cout << equipoPc.getNombre() << " must send a new wrestler!\n\n";
                
                int nuevoPc = -1;
                for (int i = 0; i < equipoPc.getNumLuchadores(); ++i) {
                    if (equipoPc.getLuchador(i)->getHP() > 0) {
                        nuevoPc = i;
                        break;
                    }
                }
                
                if (nuevoPc != -1) {
                    equipoPc.cambiarLuchador(nuevoPc);
                    std::cout << equipoPc.getLuchadorActivo()->getName() << " enters the ring!\n\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(900));
                } else {
                    break;
                }
            } else {
                std::cout << "\n--- " << pcActual->getName() << "'s Turn ---\n";
                std::vector<int> disponibles;
                for (int i = 0; i < pcActual->getNumAtaques(); ++i) {
                    Ataque* a = pcActual->getAtaque(i);
                    if (a && a->getPPActual() > 0) disponibles.push_back(i);
                }

                if (disponibles.empty()) {
                    std::cout << "[NOTICE] " << pcActual->getName() << " has no attacks with PP. Skipping.\n";
                } else {
                    int idx = disponibles[rand() % disponibles.size()];
                    try {
                        pcActual->atacarCon(pcActual->getAtaque(idx), *jugadorActual);
                    } catch (const std::exception& e) {
                        std::cout << "[ERROR] PC attack failed: " << e.what() << "\n";
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(900));
                if (jugadorActual->getHP() <= 0) {
                    std::cout << "\n" << jugadorActual->getName() << " is defeated!\n";
                    std::this_thread::sleep_for(std::chrono::milliseconds(800));
                    if (equipoJugador.contarLuchadoresVivos() > 0) {
                        std::cout << equipoJugador.getNombre() << " must send a new wrestler!\n\n";
                        seleccionarLuchador(equipoJugador);
                    } else {
                        break;
                    }
                }
            }
            
            ronda++;
        }
        
        imprimirDivisor();
        std::cout << "         BATTLE ENDED!\n";
        imprimirDivisor();
        
        if (equipoJugador.hayLuchadoresVivos()) {
            std::cout << "\n[VICTORY] " << equipoJugador.getNombre() << " wins the battle!\n";
        } else {
            std::cout << "\n[DEFEAT] " << equipoPc.getNombre() << " wins the battle!\n";
        }
        
    } catch (const std::exception& e) {
        std::cout << "[CRITICAL ERROR] " << e.what() << "\n";
        std::cout << "Battle terminated.\n";
    }
}

int main() {
    try {
        srand(static_cast<unsigned int>(time(0)));
    // On Windows, switch console to UTF-8 so braille glyphs render correctly
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);
#endif
        
        imprimirDivisor();
        std::cout << "  WELCOME TO LUCHA LIBRE TEAM BATTLE!\n";
        imprimirDivisor();

        try {
            std::ifstream artFile("Luchador.txt");
            if (artFile.is_open()) {
                std::string line;
                std::cout << "\n";
                while (std::getline(artFile, line)) {
                    std::cout << line << "\n";
                }
                std::cout << "\n";
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
        } catch (const std::exception& e) {
            std::cout << "[NOTICE] Could not read Luchador.txt: " << e.what() << "\n";
        }
        
        Equipo equipoJugador("Player Team");
        Equipo equipoPc("CPU Team");

        std::vector<Luchador*> pool;
        pool.push_back(new Tecnico("El Mascara Dorada", 150, 28, 6, 0.75f));
        pool.push_back(new Tecnico("El Payaso Plateado", 155, 26, 6, 0.70f));
        pool.push_back(new Rudo("El Destructor", 180, 22, 5, 16));
        pool.push_back(new Rudo("Blue Demon", 200, 20, 5, 18));
        pool.push_back(new Exotico("El Santo", 140, 30, 7, 0.50f));
        pool.push_back(new Exotico("Pimpinela Escarlata", 145, 32, 7, 0.55f));

        std::cout << "\nBuild your team! Choose 3 wrestlers from the pool below:\n";
        for (int i = 0; i < static_cast<int>(pool.size()); ++i) {
            std::cout << "[" << (i+1) << "] ";
            pool[i]->print();
            std::cout << "\n";
        }

        int picksNeeded = 3;
        std::vector<bool> chosen(pool.size(), false);
        while (picksNeeded > 0) {
            std::cout << "Select wrestler number to add to your team (1-" << pool.size() << "): ";
            int sel = obtenerEntradaValida(1, static_cast<int>(pool.size())) - 1;
            if (chosen[sel]) {
                std::cout << "You already picked that wrestler. Choose another.\n";
                continue;
            }
            equipoJugador.agregarLuchador(pool[sel]);
            chosen[sel] = true;
            std::cout << pool[sel]->getName() << " added to your team.\n";
            picksNeeded--;
        }

        for (int i = 0; i < static_cast<int>(pool.size()); ++i) {
            if (!chosen[i]) {
                equipoPc.agregarLuchador(pool[i]);
            }
        }
        
        std::cout << "\n[INITIALIZING ATTACKS]\n";
        
        Ataque* ataque1 = new Ataque("Patada Giratoria", 20, 85, 15);
        Ataque* ataque2 = new Ataque("Golpe Preciso", 15, 100, 20);
        Ataque* ataque3 = new Ataque("Llave de Lucha", 25, 75, 10);
        
        Ataque* ataque4 = new Ataque("Golpe Brutal", 30, 80, 12);
        Ataque* ataque5 = new Ataque("Embestida", 22, 90, 15);
        Ataque* ataque6 = new Ataque("Movimiento Mistico", 28, 80, 12);
        Ataque* ataque7 = new Ataque("Danza de Fuego", 26, 85, 14);

        for (Luchador* luch : pool) {
            if (dynamic_cast<Tecnico*>(luch)) {
                luch->agregarAtaque(new Ataque(*ataque1));
                luch->agregarAtaque(new Ataque(*ataque2));
                luch->agregarAtaque(new Ataque(*ataque3));
            } else if (dynamic_cast<Rudo*>(luch)) {
                luch->agregarAtaque(new Ataque(*ataque4));
                luch->agregarAtaque(new Ataque(*ataque5));
                luch->agregarAtaque(new Ataque(*ataque2));
            } else if (dynamic_cast<Exotico*>(luch)) {
                luch->agregarAtaque(new Ataque(*ataque6));
                luch->agregarAtaque(new Ataque(*ataque7));
                luch->agregarAtaque(new Ataque(*ataque1));
            }
        }
        
        std::cout << "Attacks loaded!\n\n";

        combateEquipos(equipoJugador, equipoPc);
        
        for (Luchador* p : pool) {
            delete p;
        }
        delete ataque1; delete ataque2; delete ataque3;
        delete ataque4; delete ataque5; delete ataque6; delete ataque7;
        
        std::cout << "\nThank you for playing!\n";
        
    } catch (const std::exception& e) {
        std::cout << "[FATAL ERROR] " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}