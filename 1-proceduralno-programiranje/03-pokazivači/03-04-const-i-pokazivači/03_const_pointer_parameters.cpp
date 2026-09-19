#include <iostream>

using std::cout;

struct ElevatorState
{
    int mCurrentFloor;
    bool mDoorOpen;
};

/* ============================================================
                       POMOĆNE FUNKCIJE
   ============================================================ */

// Ispisuje stanje bez mogućnosti promjene strukture preko pokazivača
void print_state(const ElevatorState* ptrState)
{
    if (ptrState == nullptr)
    {
        return;
    }

    cout << "Kat: " << ptrState->mCurrentFloor << '\n';
    cout << "Vrata otvorena: " << (ptrState->mDoorOpen ? "da" : "ne") << '\n';

    // ptrState->mCurrentFloor = 5;  // Pogreška: promjena nije dopuštena
}
// ————————————————————————————————————————————————————————————

// Mijenja stanje strukture preko pokazivača
void change_floor(ElevatorState* ptrState, int newFloor)
{
    if (ptrState == nullptr)
    {
        return;
    }

    ptrState->mCurrentFloor = newFloor;
}

/* ============================================================
                  DEMONSTRACIJSKE FUNKCIJE
   ============================================================ */

// Demonstrira poziv funkcije koja prima pokazivač na const strukturu
void demonstrate_read_only_parameter()
{
    ElevatorState objState{2, false};

    print_state(&objState);

    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira poziv funkcije koja preko pokazivača može mijenjati strukturu
void demonstrate_modifiable_parameter()
{
    ElevatorState objState{2, false};

    cout << "Kat prije promjene: " << objState.mCurrentFloor << '\n';

    change_floor(&objState, 5);

    cout << "Kat nakon promjene: " << objState.mCurrentFloor << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira da se adresa const strukture može proslijediti funkciji za čitanje
void demonstrate_const_structure()
{
    const ElevatorState objState{7, true};

    print_state(&objState);

    // change_floor(&objState, 3);  // Pogreška: funkcija može mijenjati strukturu
}

/* ============================================================
                               MAIN
   ============================================================ */

int main()
{
    demonstrate_read_only_parameter();
    demonstrate_modifiable_parameter();
    demonstrate_const_structure();

    return 0;
}
/* ============================================================
Kat: 2
Vrata otvorena: ne
------------------------------
Kat prije promjene: 2
Kat nakon promjene: 5
------------------------------
Kat: 7
Vrata otvorena: da
*/