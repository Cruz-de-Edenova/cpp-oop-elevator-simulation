#include <iostream>
#include <vector>

using std::cout;
using std::vector;

/* ============================================================
                         FUNKCIJE
   ============================================================ */

// Demonstrira prolazak kroz polje fiksne veličine pomoću range-based for petlje
void demonstrate_range_based_for()
{
    int selectedFloors[]{2, 5, 1, 4};

    cout << "Odabrani katovi:\n";

    for (int floor : selectedFloors)
    {
        cout << floor << '\n';
    }

    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira osnovnu uporabu ključne riječi 'auto'
void demonstrate_auto()
{
    auto currentFloor{3};

    cout << "Trenutni kat: " << currentFloor << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira vektor kao spremnik čija se veličina može mijenjati
void demonstrate_vector()
{
    vector<int> objSelectedFloors{2, 5, 1, 4};

    objSelectedFloors.push_back(6);

    cout << "Ukupan broj odabranih katova: " << objSelectedFloors.size() << '\n';
    cout << "Odabrani katovi:\n";

    for (auto floor : objSelectedFloors)
    {
        cout << floor << '\n';
    }
}

/* ============================================================
                         MAIN
   ============================================================ */

int main()
{
    demonstrate_range_based_for();
    demonstrate_auto();
    demonstrate_vector();

    return 0;
}
/* ============================================================
Odabrani katovi:
2
5
1
4
------------------------------
Trenutni kat: 3
------------------------------
Ukupan broj odabranih katova: 5
Odabrani katovi:
2
5
1
4
6
*/