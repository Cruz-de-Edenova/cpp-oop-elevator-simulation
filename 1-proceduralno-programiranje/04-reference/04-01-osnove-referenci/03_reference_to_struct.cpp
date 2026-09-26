#include <iostream>

using std::cout;

struct ElevatorState
{
    int mCurrentFloor;
    bool mDoorOpen;
};

// Demonstracija reference na objekt korisnički definiranog tipa
int main()
{
    ElevatorState objState{2, false};
    ElevatorState& refState{objState};

    cout << "Pocetni kat: " << objState.mCurrentFloor << '\n';
    cout << "Vrata otvorena: " << (objState.mDoorOpen ? "da" : "ne") << '\n';

    refState.mCurrentFloor = 5;
    refState.mDoorOpen = true;

    cout << "\nNakon promjene preko reference:\n";
    cout << "Kat: " << objState.mCurrentFloor << '\n';
    cout << "Vrata otvorena: " << (objState.mDoorOpen ? "da" : "ne") << '\n';

    cout << "\nAdresa objState:       " << &objState << '\n';
    cout << "Adresa preko refState: " << &refState << '\n';

    return 0;
}
/* ============================================================
Pocetni kat: 2
Vrata otvorena: ne

Nakon promjene preko reference:
Kat: 5
Vrata otvorena: da

Adresa objState:       0x9b6fff9d0
Adresa preko refState: 0x9b6fff9d0
*/