// Poglavlje 1.1 struct
#include <iostream>

/*
ElevatorState grupira podatke koji zajedno opisuju trenutno stanje jednog lifta. 
Umjesto tri nepovezane varijable sada imamo jedan složeni tip podatka.
*/
struct ElevatorState
{
    int currentFloor_;  // Trenutni kat
    bool doorsOpen_;    // Stanje vrata
    bool moving_;       // Informacija je li se kreće lift 
};

int main()
{
    // Stvaramo jednu varijablu tipa ElevatorState
    ElevatorState objElevator{1, false, false};

    // Članovima structa pristupamo pomoću operatora .
    std::cout << "Pocetni kat: " << objElevator.currentFloor_ << '\n';
    std::cout << "Vrata otvorena: " << objElevator.doorsOpen_ << '\n';
    std::cout << "Lift se krece: " << objElevator.moving_ << '\n';

    std::cout << '\n';

    // Mijenjamo pojedine članove iste složene varijable
    objElevator.currentFloor_ = 3;
    objElevator.doorsOpen_ = true;
    objElevator.moving_ = false;

    std::cout << "Novo stanje lifta\n";
    std::cout << "Kat: " << objElevator.currentFloor_ << '\n';
    std::cout << "Vrata otvorena: " << objElevator.doorsOpen_ << '\n';
    std::cout << "Lift se krece: " << objElevator.moving_ << '\n';

    return 0;
}
/* ==================================================================================
Pocetni kat: 1
Vrata otvorena: 0
Lift se krece: 0

Novo stanje lifta
Kat: 3
Vrata otvorena: 1
Lift se krece: 0

*/