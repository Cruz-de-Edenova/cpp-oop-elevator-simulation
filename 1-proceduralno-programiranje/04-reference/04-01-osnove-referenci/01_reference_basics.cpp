#include <iostream>

using std::cout;

// Demonstracija osnovnog korištenja reference
int main()
{
    int currentFloor{3};
    int& refCurrentFloor{currentFloor};
    int& refSelectedFloor{currentFloor};

    cout << "currentFloor:      " << currentFloor << '\n';
    cout << "refCurrentFloor:   " << refCurrentFloor << '\n';
    cout << "refSelectedFloor:  " << refSelectedFloor << '\n';

    refCurrentFloor = 5;

    cout << "\nNakon promjene preko refCurrentFloor:\n";
    cout << "currentFloor:      " << currentFloor << '\n';
    cout << "refCurrentFloor:   " << refCurrentFloor << '\n';
    cout << "refSelectedFloor:  " << refSelectedFloor << '\n';

    refSelectedFloor = 7;

    cout << "\nNakon promjene preko refSelectedFloor:\n";
    cout << "currentFloor:      " << currentFloor << '\n';
    cout << "refCurrentFloor:   " << refCurrentFloor << '\n';
    cout << "refSelectedFloor:  " << refSelectedFloor << '\n';

    cout << "\nAdresa currentFloor:     " << &currentFloor << '\n';
    cout << "Adresa refCurrentFloor:  " << &refCurrentFloor << '\n';
    cout << "Adresa refSelectedFloor: " << &refSelectedFloor << '\n';

    return 0;
}
/* ============================================================
currentFloor:      3
refCurrentFloor:   3
refSelectedFloor:  3

Nakon promjene preko refCurrentFloor:
currentFloor:      5
refCurrentFloor:   5
refSelectedFloor:  5

Nakon promjene preko refSelectedFloor:
currentFloor:      7
refCurrentFloor:   7
refSelectedFloor:  7

Adresa currentFloor:     0xf2bdbffe1c
Adresa refCurrentFloor:  0xf2bdbffe1c
Adresa refSelectedFloor: 0xf2bdbffe1c
*/