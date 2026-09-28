#include <iostream>

using std::cout;

// Demonstrira razliku izmedju vezivanja reference i preusmjeravanja pokazivača
void demonstrate_binding_and_reassignment()
{
    int firstFloor{2};
    int secondFloor{7};

    int& refFloor{firstFloor};
    int* ptrFloor{&firstFloor};

    cout << "Pocetno stanje:\n";
    cout << "firstFloor:  " << firstFloor << '\n';
    cout << "secondFloor: " << secondFloor << '\n';
    cout << "refFloor:    " << refFloor << '\n';
    cout << "*ptrFloor:   " << *ptrFloor << '\n';

    ptrFloor = &secondFloor;

    cout << "\nNakon ptrFloor = &secondFloor:\n";
    cout << "*ptrFloor:   " << *ptrFloor << '\n';
    cout << "ptrFloor pokazuje na secondFloor: "
         << (ptrFloor == &secondFloor ? "da" : "ne") << '\n';

    refFloor = secondFloor;

    cout << "\nNakon refFloor = secondFloor:\n";
    cout << "firstFloor:  " << firstFloor << '\n';
    cout << "secondFloor: " << secondFloor << '\n';
    cout << "refFloor je i dalje vezan uz firstFloor: "
         << (&refFloor == &firstFloor ? "da" : "ne") << '\n';

    ptrFloor = nullptr;

    cout << "\nNakon ptrFloor = nullptr:\n";
    cout << "ptrFloor je nullptr: " << (ptrFloor == nullptr ? "da" : "ne") << '\n';
}

int main()
{
    demonstrate_binding_and_reassignment();

    return 0;
}

/* ============================================================
Pocetno stanje:
firstFloor:  2
secondFloor: 7
refFloor:    2
*ptrFloor:   2

Nakon ptrFloor = &secondFloor:
*ptrFloor:   7
ptrFloor pokazuje na secondFloor: da

Nakon refFloor = secondFloor:
firstFloor:  7
secondFloor: 7
refFloor je i dalje vezan uz firstFloor: da

Nakon ptrFloor = nullptr:
ptrFloor je nullptr: da
*/
