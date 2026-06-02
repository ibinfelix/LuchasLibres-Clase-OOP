#include "Luchador.hpp"
#include "Tecnico.hpp"
#include "Rudo.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>

int main() {
    srand(static_cast<unsigned int>(time(0)));

    std::cout << "========================================\n";
    std::cout << "  WELCOME TO THE LUCHA LIBRE SIMULATOR! \n";
    std::cout << "========================================\n\n";

    Tecnico tecnico("El Mascarado Sagrado", 120, 24, 5, 0.7f); 
    Rudo rudo("El Demonio Obscuro", 150, 18, 4, 15);     

    std::cout << "The contenders step into the ring:\n\n";
    tecnico.print();
    std::cout << "\n                  VS\n\n";
    rudo.print();
    std::cout << "========================================\n\n";

    std::cout << "[SYSTEM]: Testing setters... El Demonio gets angry and levels up!\n";
    rudo.setLevel(6);
    std::cout << rudo.getName() << " is now level " << rudo.getLevel() << "!\n\n";
    
    std::cout << "[SYSTEM]: Demonstrating operator overloading (>):\n";
    if (tecnico > rudo) {
        std::cout << tecnico.getName() << " has more attack power than " << rudo.getName() << "!\n\n";
    } else {
        std::cout << rudo.getName() << " has more attack power than " << tecnico.getName() << "!\n\n";
    }

    int round = 1;
    
    // LOOP del combate
    while (tecnico.getHP() > 0 && rudo.getHP() > 0) {
        std::cout << "--- ROUND " << round << " ---\n";
        
        tecnico.attack(rudo);
        rudo.printHPBar();
        std::cout << "\n\n";

        if (rudo.getHP() <= 0) {
            break;
        }

        rudo.attack(tecnico);
        tecnico.printHPBar();
        std::cout << "\n\n";

        round++;
    }

    std::cout << "========================================\n";
    std::cout << "          THE MATCH IS OVER!            \n";
    std::cout << "========================================\n";

    if (tecnico.getHP() > 0) {
        std::cout << "\nWINNER: " << tecnico.getName() << " maintains his honor!\n";
        std::cout << "[SYSTEM]: Attempting revival of defeated opponent...\n";
        rudo.revive();
    } else {
        std::cout << "\nWINNER: " << rudo.getName() << " takes the glory!\n";
        std::cout << "[SYSTEM]: Attempting revival of defeated opponent...\n";
        tecnico.revive();
    }

    return 0;
}