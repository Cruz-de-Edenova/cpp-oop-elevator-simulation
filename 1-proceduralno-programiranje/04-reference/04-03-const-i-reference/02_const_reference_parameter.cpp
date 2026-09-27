#include <iostream>

using std::cout;

struct ElevatorState
{
    int mCurrentFloor;
    bool mDoorOpen;
};

// Ispisuje stanje bez mogućnosti promjene objekta pomoću reference
void print_state(const ElevatorState& refState)
{
    cout << "Kat: " << refState.mCurrentFloor << '\n';
    cout << "Vrata otvorena: " << (refState.mDoorOpen ? "da" : "ne") << '\n';

    // refState.mCurrentFloor = 5; // Nije dopušteno
}

// Demonstrira const referencu kao parametar funkcije
int main()
{
    ElevatorState objState{2, false};
    const ElevatorState objLockedState{7, true};

    cout << "Obican objekt:\n";
    print_state(objState);

    cout << "\nConst objekt:\n";
    print_state(objLockedState);

    return 0;
}
/* ============================================================
Obican objekt:
Kat: 2
Vrata otvorena: ne

Const objekt:
Kat: 7
Vrata otvorena: da
*/
