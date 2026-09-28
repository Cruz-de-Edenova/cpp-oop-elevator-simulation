#include <iostream>

using std::cout;

struct ElevatorState
{
    int mCurrentFloor;
    bool mDoorOpen;
};

// Mijenja stanje postojećeg objekta pomoću reference
void set_floor(ElevatorState& refState, int newFloor)
{
    refState.mCurrentFloor = newFloor;
}

// Pokušava promijeniti stanje objekta pomoću pokazivača
bool try_set_floor(ElevatorState* ptrState, int newFloor)
{
    if (ptrState == nullptr)
    {
        return false;
    }

    ptrState->mCurrentFloor = newFloor;
    return true;
}

// Demonstrira referencu kao parametar kada objekt mora postojati
void demonstrate_reference_parameter()
{
    ElevatorState objState{2, false};

    set_floor(objState, 5);

    cout << "Nakon set_floor():\n";
    cout << "Kat: " << objState.mCurrentFloor << '\n';

    cout << "------------------------------\n";
}

// Demonstrira pokazivač kao parametar kada je dopušten nullptr
void demonstrate_pointer_parameter()
{
    ElevatorState objState{2, false};
    ElevatorState* ptrState{&objState};

    bool success{try_set_floor(ptrState, 5)};

    cout << "Poziv s adresom objekta:\n";
    cout << "Uspjeh: " << (success ? "da" : "ne") << '\n';
    cout << "Kat: " << objState.mCurrentFloor << '\n';

    ptrState = nullptr;
    success = try_set_floor(ptrState, 7);

    cout << "\nPoziv s nullptr:\n";
    cout << "Uspjeh: " << (success ? "da" : "ne") << '\n';
    cout << "Kat: " << objState.mCurrentFloor << '\n';
}

int main()
{
    demonstrate_reference_parameter();
    demonstrate_pointer_parameter();

    return 0;
}

/* ============================================================
Nakon set_floor():
Kat: 5
------------------------------
Poziv s adresom objekta:
Uspjeh: da
Kat: 5

Poziv s nullptr:
Uspjeh: ne
Kat: 5
*/
