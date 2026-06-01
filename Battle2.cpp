#include "Luchador.hpp"
#include "Tecnico.hpp"
#include "Rudo.hpp"
#include "Exotico.hpp"
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <thread>
#include <chrono>
 
void printDivider() {
    std::cout << "========================================\n";
}
 
void runFight(Luchador& a, Luchador& b) {
    printDivider();
    std::cout << "           FIGHT!\n";
    printDivider();
    a.print();
    std::cout << "              VS\n\n";
    b.print();
    printDivider();
    std::cout << "\n";
 
    int round = 1;
    while (a.getHealth() > 0 && b.getHealth() > 0) {
        std::cout << "--- ROUND " << round << " ---\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
 
        a.attack(b);
        b.printHealthBar();
        std::cout << "\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
 
        if (b.getHealth() <= 0) break;
 
        b.attack(a);
        a.printHealthBar();
        std::cout << "\n\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(1500));
 
        round++;
    }
 
    printDivider();
    if (a.getHealth() > 0)
        std::cout << "  WINNER: " << a.getName() << "!\n";
    else
        std::cout << "  WINNER: " << b.getName() << "!\n";
    printDivider();
    std::cout << "\n";
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
}
 
int main() {
    srand(static_cast<unsigned int>(time(0)));
 
    printDivider();
    std::cout << "  LUCHA LIBRE SIMULATOR 2 - BATTLE TIME!\n";
    printDivider();
    std::cout << "\n=== MEET THE FIGHTERS ===\n\n";
 
    Tecnico tecnico("Mistico", 110, 20, 4, 0.70f);
    Rudo    rudo("El hijo del perro Aguayo", 150, 18, 4, 16);
    Exotico exotico("Dulce Gardenia", 120, 17, 3, 0.85f);
 
    tecnico.print();
    rudo.print();
    exotico.print();
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
 
    // Match 1: Tecnico vs Rudo
    std::cout << "\n>>> MATCH 1: Tecnico vs Rudo <<<\n\n";
    Tecnico t1("Mistico", 110, 20, 4, 0.70f);
    Rudo    r1("El hijo del perro Aguayo", 150, 18, 4, 16);
    runFight(t1, r1);
 
    // Match 2: Rudo vs Exotico
    std::cout << "\n>>> MATCH 2: Rudo vs Exotico <<<\n\n";
    Rudo    r2("El hijo del perro Aguayo", 150, 18, 4, 16);
    Exotico e1("Dulce Gardenia", 120, 17, 3, 0.85f);
    runFight(r2, e1);
 
    // Match 3: Tecnico vs Exotico
    std::cout << "\n>>> MATCH 3: Tecnico vs Exotico <<<\n\n";
    Tecnico t2("Mistico", 110, 20, 4, 0.70f);
    Exotico e2("Dulce Gardenia", 120, 17, 3, 0.85f);
    runFight(t2, e2);
 
    printDivider();
    std::cout << "  THAT'S ALL FOLKS! LUCHA LIBRE IS OVER!\n";
    printDivider();
 
    return 0;
}