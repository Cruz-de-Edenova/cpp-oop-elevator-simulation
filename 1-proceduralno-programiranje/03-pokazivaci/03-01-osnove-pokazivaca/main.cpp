#include <iostream>

using std::cout;

struct FloorSensorData
{
    int mFloor;
    bool mIsActive;
};

/* ============================================================
                         FUNKCIJE
   ============================================================ */

// Demonstrira vezu varijable, njezine adrese i pokazivača
void demonstrate_address_and_pointer()
{
    int currentFloor{3};
    int* ptrCurrentFloor{&currentFloor};

    cout << "Trenutni kat: " << currentFloor << '\n';
    cout << "Adresa varijable: " << &currentFloor << '\n';
    cout << "Vrijednost pokazivaca: " << ptrCurrentFloor << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira pristup varijabli operatorom dereferenciranja
void demonstrate_dereference()
{
    int currentFloor{4};
    int* ptrCurrentFloor{&currentFloor};

    cout << "Izravni pristup: " << currentFloor << '\n';
    cout << "Pristup preko pokazivaca: " << *ptrCurrentFloor << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira promjenu postojeće varijable preko pokazivača
void demonstrate_modify_through_pointer()
{
    int currentFloor{2};
    int* ptrCurrentFloor{&currentFloor};

    cout << "Prije promjene: " << currentFloor << '\n';

    *ptrCurrentFloor = 5;

    cout << "Nakon promjene: " << currentFloor << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira sigurno početno stanje pokazivača pomoću nullptr
void demonstrate_null_pointer()
{
    int* ptrCurrentFloor{nullptr};

    if (ptrCurrentFloor == nullptr)
    {
        cout << "Vrijednost pokazivaca: " << ptrCurrentFloor << '\n';
    }

    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira stvaranje i oslobađanje jednog dinamičkog objekta
void demonstrate_dynamic_allocation()
{
    int* ptrTargetFloor{new int{7}};

    cout << "Odredisni kat: " << *ptrTargetFloor << '\n';

    *ptrTargetFloor = 9;
    cout << "Promijenjeni odredisni kat: " << *ptrTargetFloor << '\n';

    delete ptrTargetFloor;
    ptrTargetFloor = nullptr;

    cout << "Vrijednost pokazivaca: " << ptrTargetFloor << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira pokazivač na jednostavan korisnički definirani tip
void demonstrate_user_defined_type()
{
    FloorSensorData objSensorData{4, true};
    FloorSensorData* ptrSensorData{&objSensorData};

    cout << "Ocitani kat: " << ptrSensorData->mFloor << '\n';
    cout << "Stanje senzora: "
         << (ptrSensorData->mIsActive ? "aktivan" : "neaktivan") << '\n';

    ptrSensorData->mFloor = 6;
    cout << "Novi ocitani kat: " << objSensorData.mFloor << '\n';
}

/* ============================================================
                         MAIN
   ============================================================ */
   
int main()
{
    demonstrate_address_and_pointer();
    demonstrate_dereference();
    demonstrate_modify_through_pointer();
    demonstrate_null_pointer();
    demonstrate_dynamic_allocation();
    demonstrate_user_defined_type();

    return 0;
}
/* ============================================================
Trenutni kat: 3
Adresa varijable: 0x44981ff844
Vrijednost pokazivaca: 0x44981ff844
------------------------------
Izravni pristup: 4
Pristup preko pokazivaca: 4
------------------------------
Prije promjene: 2
Nakon promjene: 5
------------------------------
Vrijednost pokazivaca: 0
------------------------------
Odredisni kat: 7
Promijenjeni odredisni kat: 9
Vrijednost pokazivaca: 0
------------------------------
Ocitani kat: 4
Stanje senzora: aktivan
Novi ocitani kat: 6
*/