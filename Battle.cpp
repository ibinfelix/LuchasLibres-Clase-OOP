#include "Luchador.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>

int main() {
    // Seed the random number generator so damage is different every run
    srand(static_cast<unsigned int>(time(0)));

    std::cout << "========================================\n";
    std::cout << "  WELCOME TO THE LUCHA LIBRE SIMULATOR! \n";
    std::cout << "========================================\n\n";

    // Create two units using the parameterized constructor
    Luchador tecnico("El Mascarado Sagrado", 120, 24, 5); // Tecnico (Good guy)
    Luchador rudo("El Demonio Obscuro", 150, 18, 4);      // Rudo (Bad guy)

    std::cout << "The contenders step into the ring:\n\n";
    tecnico.print();
    std::cout << "\n                  VS\n\n";
    rudo.print();
    std::cout << "========================================\n\n";

    // Testing a Setter to prove functionality
    std::cout << "[SYSTEM]: Testing setters... El Demonio gets angry and levels up!\n";
    rudo.setLevel(6);
    std::cout << rudo.getName() << " is now level " << rudo.getLevel() << "!\n\n";

    int round = 1;
    
    // Combat Loop: Ends when someone loses all health points
    while (tecnico.getHealth() > 0 && rudo.getHealth() > 0) {
        std::cout << "--- ROUND " << round << " ---\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        
        // Tecnico attacks Rudo
        tecnico.attack(rudo);
        rudo.printHealthBar();
        std::cout << "\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        // Check if Rudo was defeated before letting him counter-attack
        if (rudo.getHealth() <= 0) {
            break;
        }

        // Rudo attacks Tecnico
        rudo.attack(tecnico);
        tecnico.printHealthBar();
        std::cout << "\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(3000));

        round++;
    }

    std::cout << "========================================\n";
    std::cout << "          THE MATCH IS OVER!            \n";
    std::cout << "========================================\n";

    if (tecnico.getHealth() > 0) {
        std::cout << "\nWINNER: " << tecnico.getName() << " maintains his honor!\n";
    } else {
        std::cout << "\nWINNER: " << rudo.getName() << " takes the glory!\n";
    }

    return 0;
}