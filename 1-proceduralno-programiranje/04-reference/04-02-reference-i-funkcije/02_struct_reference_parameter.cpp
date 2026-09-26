#include <iostream>

using std::cout;

struct ElevatorState
{
    int mCurrentFloor;
    bool mDoorOpen;
};

// Mijenja stanje postojećeg objekta pomoću reference kao parametra
void update_state(ElevatorState& refState, int newFloor, bool doorOpen)
{
    refState.mCurrentFloor = newFloor;
    refState.mDoorOpen = doorOpen;
}

int main()
{
    ElevatorState objState{2, false};

    cout << "Pocetni kat: " << objState.mCurrentFloor << '\n';
    cout << "Vrata otvorena: " << (objState.mDoorOpen ? "da" : "ne") << '\n';

    update_state(objState, 5, true);

    cout << "\nNakon poziva update_state():\n";
    cout << "Kat: " << objState.mCurrentFloor << '\n';
    cout << "Vrata otvorena: " << (objState.mDoorOpen ? "da" : "ne") << '\n';

    return 0;
}
/* ============================================================
Pocetni kat: 2
Vrata otvorena: ne

Nakon poziva update_state():
Kat: 5
Vrata otvorena: da
*/