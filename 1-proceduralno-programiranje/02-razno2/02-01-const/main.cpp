#include <iostream>

using std::cout;
using std::cin;

/* ============================================================
                         FUNKCIJE
   ============================================================ */

// Vraća vrijeme vožnje i može sudjelovati u compile-time izračunu
constexpr int calculate_travel_time(int floorCount, int secondsPerFloor)
{
    return floorCount * secondsPerFloor;
}
// ————————————————————————————————————————————————————————————

// Ispisuje kat, a const sprječava promjenu lokalne kopije parametra
void print_floor(const int floor)
{
    cout << "Kat: " << floor << '\n';
    // floor = 5;   // Pogreška: lokalna kopija je const
}
// ————————————————————————————————————————————————————————————

// Demonstrira const varijablu čija vrijednost ne mora biti compile-time konstanta
void demonstrate_const_variable()
{
    int currentFloor{3};
    const int startingFloor{currentFloor};

    cout << "Trenutni kat: " << currentFloor << '\n';
    cout << "Pocetni kat: " << startingFloor << '\n';

    currentFloor = 4;
    // startingFloor = 4;   // Pogreška: startingFloor je const

    cout << "Novi trenutni kat: " << currentFloor << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira constexpr vrijednosti poznate tijekom kompajliranja
void demonstrate_constexpr_variable()
{
    constexpr int floorCount{10};
    constexpr int secondsPerFloor{2};
    constexpr int fullTravelTime{floorCount * secondsPerFloor};

    cout << "Broj prijedenih katova: " << floorCount << '\n';
    cout << "Sekundi po katu: " << secondsPerFloor << '\n';
    cout << "Ukupno vrijeme voznje: " << fullTravelTime << " s\n";
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Pokazuje da const na parametru po vrijednosti štiti samo lokalnu kopiju
void demonstrate_const_parameter()
{
    int currentFloor{4};

    print_floor(currentFloor);
    currentFloor = 6;

    cout << "Trenutni kat: " << currentFloor << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira compile-time i runtime poziv iste constexpr funkcije
void demonstrate_constexpr_function()
{
    constexpr int floorCount{5};
    constexpr int secondsPerFloor{2};
    constexpr int compileTimeResult{
        calculate_travel_time(floorCount, secondsPerFloor)};

    int runtimeFloorCount{0};
    cout << "Unesite broj prijedenih katova: ";
    cin >> runtimeFloorCount;
    
    int runtimeResult{
        calculate_travel_time(runtimeFloorCount, secondsPerFloor)};

    cout << "Rezultat za vrijeme kompajliranja: " << compileTimeResult << " s\n";
    cout << "Rezultat tijekom izvodenja programa: " << runtimeResult << " s\n";
}

/* ============================================================
                         MAIN
   ============================================================ */
   
int main()
{
    demonstrate_const_variable();
    demonstrate_constexpr_variable();
    demonstrate_const_parameter();
    demonstrate_constexpr_function();

    return 0;
}
/* ============================================================
Trenutni kat: 3
Pocetni kat: 3
Novi trenutni kat: 4
------------------------------
Broj prijedenih katova: 10
Sekundi po katu: 2
Ukupno vrijeme voznje: 20 s
------------------------------
Kat: 4
Trenutni kat: 6
------------------------------
Unesite broj prijedenih katova: 7
Rezultat za vrijeme kompajliranja: 10 s
Rezultat tijekom izvodenja programa: 14 s

*/