#include <iostream>

using std::cout;

// Demonstrira pristup istoj varijabli pomoću reference i pokazivača
void demonstrate_reference_and_pointer()
{
    int currentFloor{3};
    int& refCurrentFloor{currentFloor};
    int* ptrCurrentFloor{&currentFloor};

    cout << "Pocetna vrijednost:\n";
    cout << "currentFloor:       " << currentFloor << '\n';
    cout << "refCurrentFloor:    " << refCurrentFloor << '\n';
    cout << "*ptrCurrentFloor:   " << *ptrCurrentFloor << '\n';

    cout << "\nAdrese:\n";
    cout << "&currentFloor:      " << &currentFloor << '\n';
    cout << "&refCurrentFloor:   " << &refCurrentFloor << '\n';
    cout << "ptrCurrentFloor:    " << ptrCurrentFloor << '\n';

    refCurrentFloor = 5;

    cout << "\nNakon refCurrentFloor = 5:\n";
    cout << "currentFloor:       " << currentFloor << '\n';
    cout << "*ptrCurrentFloor:   " << *ptrCurrentFloor << '\n';

    *ptrCurrentFloor = 7;

    cout << "\nNakon *ptrCurrentFloor = 7:\n";
    cout << "currentFloor:       " << currentFloor << '\n';
    cout << "refCurrentFloor:    " << refCurrentFloor << '\n';
}

int main()
{
    demonstrate_reference_and_pointer();

    return 0;
}
/* ============================================================
Pocetna vrijednost:
currentFloor:       3
refCurrentFloor:    3
*ptrCurrentFloor:   3

Adrese:
&currentFloor:      0x9c85ffcbc
&refCurrentFloor:   0x9c85ffcbc
ptrCurrentFloor:    0x9c85ffcbc

Nakon refCurrentFloor = 5:
currentFloor:       5
*ptrCurrentFloor:   5

Nakon *ptrCurrentFloor = 7:
currentFloor:       7
refCurrentFloor:    7
*/
