#include <iostream>

using std::cout;

/* ============================================================
                    PROTOTIPOVI FUNKCIJA
   ============================================================ */

// Deklarira funkciju sa defaultnim argumentom
int calculate_travel_time(int floorCount, int secondsPerFloor = 2);

// Deklarira funkciju koja ispisuje kat
void print_floor(int floor);

// Deklarira demonstracijske funkcije
void demonstrate_parameters_and_arguments();
void demonstrate_default_argument();
void demonstrate_default_argument_scope();

/* ============================================================
                         MAIN()
   ============================================================ */

int main()
{
    demonstrate_parameters_and_arguments();
    demonstrate_default_argument();
    demonstrate_default_argument_scope();

    return 0;
}

/* ============================================================
Kat: 3
Vrijeme voznje: 10 s
------------------------------
1. izracun vremena: 10 s
2. izracun vremena: 15 s
------------------------------
Vanjski opseg: 10 s
Unutarnji opseg: 15 s
Ponovno vanjski opseg: 10 s

*/

/* ============================================================
                    DEFINICIJE FUNKCIJA
   ============================================================ */

// Izračunava vrijeme vožnje lifta prema broju katova i vremenu po katu
int calculate_travel_time(int floorCount, int secondsPerFloor)
{
    return floorCount * secondsPerFloor;
}
// ————————————————————————————————————————————————————————————

// Ispisuje kat proslijeđen kao parametar
void print_floor(int floor)
{
    cout << "Kat: " << floor << '\n';
}
// ————————————————————————————————————————————————————————————

// Demonstrira parametre, argumente i poziv funkcije
void demonstrate_parameters_and_arguments()
{
    int currentFloor{3};
    int floorCount{5};
    int secondsPerFloor{2};

    // 'currentFloor' je argument, a 'floor' je parametar funkcije 'print_floor()'
    print_floor(currentFloor);

    /* U varijablu 'travelTime' je pohranjena povratna vrijednost poziva funkcije
    calculate_travel_time() */
    int travelTime{calculate_travel_time(floorCount, secondsPerFloor)};

    cout << "Vrijeme voznje: " << travelTime << " s\n";
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira korištenje defaultnog argumenta
void demonstrate_default_argument()
{
    int floorCount{5};

    // Izostavljen je drugi argument, pa se koristi defaultni argument
    int defaultTravelTime{calculate_travel_time(floorCount)};

    // Ovdje se ne koristi defaultni argument
    int customTravelTime{calculate_travel_time(floorCount, 3)};

    cout << "1. izracun vremena: " << defaultTravelTime << " s\n";
    cout << "2. izracun vremena: " << customTravelTime << " s\n";
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira različite defaultne argumente u različitim opsezima
void demonstrate_default_argument_scope()
{
    int floorCount{5};
    int outerTravelTime{calculate_travel_time(floorCount)};

    cout << "Vanjski opseg: " << outerTravelTime << " s\n";

    {
        // U ovom opsegu drugi parametar ima defaultni argument
        int calculate_travel_time(int floorCount, int secondsPerFloor = 3);

        int innerTravelTime{calculate_travel_time(floorCount)};
        cout << "Unutarnji opseg: " << innerTravelTime << " s\n";
    }

    int outerTravelTimeAgain{calculate_travel_time(floorCount)};
    cout << "Ponovno vanjski opseg: " << outerTravelTimeAgain << " s\n";
}