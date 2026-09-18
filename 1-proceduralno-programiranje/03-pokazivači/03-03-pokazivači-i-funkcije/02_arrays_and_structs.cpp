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

// Ispisuje elemente polja i prima broj elemenata zasebno
void print_values(int values[], int elementCount)
{
    for (int index{0}; index < elementCount; ++index)
    {
        cout << values[index] << '\n';
    }
}
// ————————————————————————————————————————————————————————————

// Mijenja prvi element polja preko pokazivača
void set_first_value(int* ptrValues, int newValue)
{
    ptrValues[0] = newValue;
}
// ————————————————————————————————————————————————————————————

// Mijenja samo lokalnu kopiju strukture
void change_floor_copy(ElevatorState objState, int newFloor)
{
    objState.mCurrentFloor = newFloor;
    cout << "Kat unutar funkcije: " << objState.mCurrentFloor << '\n';
}
// ————————————————————————————————————————————————————————————

// Mijenja strukturu pozivatelja preko pokazivača
void change_floor(ElevatorState* ptrState, int newFloor)
{
    ptrState->mCurrentFloor = newFloor;
}
// ————————————————————————————————————————————————————————————

// Stvara početno stanje lifta i vraća strukturu po vrijednosti
ElevatorState create_initial_state()
{
    ElevatorState objState{0, false};
    return objState;
}

/* ============================================================
                   DEMONSTRACIJSKE FUNKCIJE
   ============================================================ */

// Demonstrira prosljeđivanje polja funkciji
void demonstrate_array_parameter()
{
    constexpr int elementCount{4};
    int values[elementCount]{2, 4, 6, 8};

    cout << "Elementi polja prije promjene:\n";
    print_values(values, elementCount);

    set_first_value(values, 10);

    cout << "Prvi element nakon promjene: " << values[0] << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira prosljeđivanje strukture po vrijednosti
void demonstrate_struct_by_value()
{
    ElevatorState objState{2, false};

    cout << "Kat prije poziva: " << objState.mCurrentFloor << '\n';
    change_floor_copy(objState, 5);
    cout << "Kat nakon poziva: " << objState.mCurrentFloor << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira prosljeđivanje pokazivača na strukturu
void demonstrate_struct_by_pointer()
{
    ElevatorState objState{2, false};

    cout << "Kat prije poziva: " << objState.mCurrentFloor << '\n';
    change_floor(&objState, 5);
    cout << "Kat nakon poziva: " << objState.mCurrentFloor << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira strukturu kao povratnu vrijednost funkcije
void demonstrate_struct_return()
{
    ElevatorState objState{create_initial_state()};

    cout << "Pocetni kat: " << objState.mCurrentFloor << '\n';
    cout << "Vrata otvorena: " << (objState.mDoorOpen ? "da" : "ne") << '\n';
}

/* ============================================================
                         MAIN
   ============================================================ */

int main()
{
    demonstrate_array_parameter();
    demonstrate_struct_by_value();
    demonstrate_struct_by_pointer();
    demonstrate_struct_return();

    return 0;
}
/* ============================================================
Elementi polja prije promjene:
2
4
6
8
Prvi element nakon promjene: 10
------------------------------
Kat prije poziva: 2
Kat unutar funkcije: 5
Kat nakon poziva: 2
------------------------------
Kat prije poziva: 2
Kat nakon poziva: 5
------------------------------
Pocetni kat: 0
Vrata otvorena: ne
*/