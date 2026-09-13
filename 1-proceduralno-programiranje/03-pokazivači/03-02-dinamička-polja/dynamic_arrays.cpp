#include <iostream>

using std::cin;
using std::cout;

/* ============================================================
                         FUNKCIJE
   ============================================================ */

// Demonstrira stvaranje, korištenje i oslobađanje dinamičkog polja
void demonstrate_dynamic_array()
{
    constexpr int elementCount{5};

    int* ptrValues{new int[elementCount]{}};

    for (int index{0}; index < elementCount; ++index)
    {
        ptrValues[index] = index + 1;
    }

    cout << "Elementi dinamickog polja:\n";

    for (int index{0}; index < elementCount; ++index)
    {
        cout << ptrValues[index] << '\n';
    }

    cout << "Velicina pokazivacke varijable: " << sizeof(ptrValues) << '\n';

    delete[] ptrValues;
    ptrValues = nullptr;

    cout << "Pokazivac je nullptr: "
         << (ptrValues == nullptr ? "da" : "ne") << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira dinamički alocirano polje čija se veličina određuje tijekom
// izvođenja programa
void demonstrate_runtime_array_size()
{
    int floorCount{};

    cout << "Unesi broj katova zgrade: ";
    cin >> floorCount;

    if (floorCount <= 0)
    {
        cout << "Broj katova mora biti veci od nule.\n";
        return;
    }

    bool* ptrFloorSelections{new bool[floorCount]{}};
    bool isInitialFloorSelected{ptrFloorSelections[0]};

    cout << "Pocetni kat "
     << (isInitialFloorSelected ? "je odabran" : "nije odabran") << '\n';

    ptrFloorSelections[0] = true;
    isInitialFloorSelected = ptrFloorSelections[0];
    
    cout << "Pocetni kat je sada "
     << (isInitialFloorSelected ? "odabran" : "nije odabran") << '\n';

    delete[] ptrFloorSelections;
    ptrFloorSelections = nullptr;
}

/* ============================================================
                         MAIN
   ============================================================ */

int main()
{
    demonstrate_dynamic_array();
    demonstrate_runtime_array_size();

    return 0;
}
/* ============================================================
Elementi dinamickog polja:
1
2
3
4
5
Velicina pokazivacke varijable: 8
Pokazivac je nullptr: da
------------------------------
Unesi broj katova zgrade: 3
Pocetni kat nije odabran
Pocetni kat je sada odabran
*/