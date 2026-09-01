#include <iostream>

using std::cout;

/* ============================================================
                         STRUKTURE
   ============================================================ */

struct FloorRequest
{
    int mFloor;        // Kat
};

struct DoorRequest
{
    bool mOpen;        // Vrata lifta
};

/* ============================================================
                    PROTOTIPOVI FUNKCIJA
   ============================================================ */

// Deklarira preopterećenu funkciju za ispis vremena vožnje lifta
void print_travel_time(int seconds);

// Deklarira preopterećenu funkciju za ispis vremena vožnje lifta
void print_travel_time(double seconds);

// Deklarira preopterećenu funkciju za ispis zahtjeva za kat
void print_request(FloorRequest objRequest);

// Deklarira preopterećenu funkciju za ispis zahtjeva za vrata
void print_request(DoorRequest objRequest);

// Deklarira funkciju koja ispisuje broj katova
void print_floor_count(int floorCount);

// Deklarira preopterećenu funkciju za ispis odgode vrata
void print_door_delay(long seconds);

// Deklarira preopterećenu funkciju za ispis odgode vrata
void print_door_delay(double seconds);

// Deklarira demonstracijske funkcije
void demonstrate_basic_overloading();
void demonstrate_struct_overloading();
void demonstrate_standard_conversion();
void demonstrate_ambiguous_conversion();

/* ============================================================
                         MAIN
   ============================================================ */

int main()
{
    demonstrate_basic_overloading();
    demonstrate_struct_overloading();
    demonstrate_standard_conversion();
    demonstrate_ambiguous_conversion();

    return 0;
}

/* ============================================================
Procijenjeno vrijeme voznje: 10 s
Precizno vrijeme voznje: 10.5 s
------------------------------
Zahtjev za kat: 4
Zahtjev za vrata: otvori
------------------------------
Broj prijedenih katova: 5
------------------------------
Odgoda vrata u cijelim sekundama: 3 s
Precizna odgoda vrata: 3.2 s

*/

/* ============================================================
                    DEFINICIJE FUNKCIJA
   ============================================================ */

// Ispisuje vrijeme vožnje izraženo cijelim brojem sekundi
void print_travel_time(int seconds)
{
    cout << "Procijenjeno vrijeme voznje: " << seconds << " s\n";
}
// ————————————————————————————————————————————————————————————

// Ispisuje vrijeme vožnje izraženo decimalnim brojem sekundi
void print_travel_time(double seconds)
{
    cout << "Precizno vrijeme voznje: " << seconds << " s\n";
}
// ————————————————————————————————————————————————————————————

// Ispisuje zahtjev za vožnju na određeni kat
void print_request(FloorRequest objRequest)
{
    cout << "Zahtjev za kat: " << objRequest.mFloor << '\n';
}
// ————————————————————————————————————————————————————————————

// Ispisuje zahtjev za promjenu stanja vrata
void print_request(DoorRequest objRequest)
{
    if (objRequest.mOpen)
    {
        cout << "Zahtjev za vrata: otvori\n";
    }
    else
    {
        cout << "Zahtjev za vrata: zatvori\n";
    }
}
// ————————————————————————————————————————————————————————————

// Ispisuje broj katova nakon moguće cjelobrojne promocije u int
void print_floor_count(int floorCount)
{
    cout << "Broj prijedenih katova: " << floorCount << '\n';
}
// ————————————————————————————————————————————————————————————

// Ispisuje odgodu otvaranja/zatvaranja vrata kada je argument tipa 'long'
void print_door_delay(long seconds)
{
    cout << "Odgoda vrata u cijelim sekundama: " << seconds << " s\n";
}
// ————————————————————————————————————————————————————————————

// Ispisuje odgodu otvaranja/zatvaranja vrata kada je argument tipa 'double'
void print_door_delay(double seconds)
{
    cout << "Precizna odgoda vrata: " << seconds << " s\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira odabir preopterećenja prema tipu argumenta
void demonstrate_basic_overloading()
{
    int wholeSeconds{10};
    double preciseSeconds{10.5};

    print_travel_time(wholeSeconds);
    print_travel_time(preciseSeconds);

    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira preopterećenje funkcije pomoću različitih 'struct' tipova
void demonstrate_struct_overloading()
{
    FloorRequest objFloorRequest{4};
    DoorRequest objDoorRequest{true};

    print_request(objFloorRequest);
    print_request(objDoorRequest);

    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Pokazuje da promocija može ukloniti nepotrebno preopterećenje
void demonstrate_standard_conversion()
{
    short floorCount{5};

    // 'short' se standardnom cjelobrojnom promocijom pretvara u 'int'
    print_floor_count(floorCount);

    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Pokazuje dvosmislen poziv kada su dvije konverzije jednako dobre
void demonstrate_ambiguous_conversion()
{
    // 'int' se može pretvoriti i u 'long' i u 'double', pa je poziv dvosmislen:
    // print_door_delay(3);
    
    /* Ako se omogući gornja linija, kompajler prijavljuje ovu grešku:
    call of overloaded 'print_door_delay(int)' is ambiguous */

    // Ovdje nema dvosmislenosti
    long wholeDelay{3};
    double preciseDelay{3.2};

    print_door_delay(wholeDelay);
    print_door_delay(preciseDelay);
}