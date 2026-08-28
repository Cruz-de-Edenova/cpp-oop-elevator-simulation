// Poglavlje 1.2 Alias deklaracije pomoću typedef i using

#include <array>
#include <iostream>

/* ============================================================
                         FUNKCIJE
   ============================================================ */

// Pokazuje stariji način definiranja aliasa pomoću typedef
void demonstrate_typedef()
{
    typedef unsigned int FloorNumber;

    FloorNumber currentFloor{1};
    FloorNumber targetFloor{5};

    std::cout << "'typedef' primjer\n";
    std::cout << "Trenutni kat: " << currentFloor << '\n';
    std::cout << "Odabrani kat: " << targetFloor << '\n';
}
// ————————————————————————————————————————————————————————————

// Pokazuje moderniji C++ način definiranja aliasa pomoću using
void demonstrate_using()
{
    using FloorNumber = unsigned int;

    FloorNumber currentFloor{2};
    FloorNumber targetFloor{7};

    std::cout << "\n'using' primjer\n";
    std::cout << "Trenutni kat: " << currentFloor << '\n';
    std::cout << "Odabrani kat: " << targetFloor << '\n';
}
// ————————————————————————————————————————————————————————————

// Pokazuje da alias ne stvara novi tip nego da je samo drugo ime postojećeg tipa
void demonstrate_same_type()
{
    using FloorNumber = unsigned int;

    FloorNumber currentFloor{3};
    unsigned int nextFloor{4};

    currentFloor = nextFloor;

    std::cout << "\nAlias i izvorni tip\n";
    std::cout << "Novi trenutni kat: " << currentFloor << '\n';
}
// ————————————————————————————————————————————————————————————

// Pokazuje kako alias pojednostavljuje dugu deklaraciju koja se ponavlja
void demonstrate_simplified_declaration()
{
    /* Bez aliasa svaki objekt mora ponavljati cijeli naziv složenog tipa.
    Ovdje std::array samo služi kao primjer nešto dulje deklaracije. */
    std::array<std::array<int, 3>, 4> objMatrix0{};

    /* Alias složenom tipu daje kratko i smisleno ime. Nakon toga se isti tip može 
    koristiti bez ponavljanja cijele deklaracije. */
    using Matrix4x3 = std::array<std::array<int, 3>, 4>;

    Matrix4x3 objMatrix1{};
    Matrix4x3 objMatrix2{};

    objMatrix0[0][0] = 2;
    objMatrix1[0][0] = 5;
    objMatrix2[0][0] = 8;

    std::cout << "\nPojednostavljenje deklaracije\n";
    std::cout << "objMatrix0[0][0] = " << objMatrix0[0][0] << '\n';
    std::cout << "objMatrix1[0][0] = " << objMatrix1[0][0] << '\n';
    std::cout << "objMatrix2[0][0] = " << objMatrix2[0][0] << '\n';
}

/* ============================================================
                           MAIN
   ============================================================ */

int main()
{
    demonstrate_typedef();
    demonstrate_using();
    demonstrate_same_type();
    demonstrate_simplified_declaration();

    return 0;
}
/* ============================================================
'typedef' primjer
Trenutni kat: 1
Odabrani kat: 5

'using' primjer
Trenutni kat: 2
Odabrani kat: 7

Alias i izvorni tip
Novi trenutni kat: 4

Pojednostavljenje deklaracije
objMatrix0[0][0] = 2
objMatrix1[0][0] = 5
objMatrix2[0][0] = 8

*/