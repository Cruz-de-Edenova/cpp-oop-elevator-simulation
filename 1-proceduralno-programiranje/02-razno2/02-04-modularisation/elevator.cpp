#include <iostream>
#include "elevator.h"

using std::cout;

// Izračunava broj prijeđenih katova između početnog i odredišnog kata
int calculate_floor_count(int startFloor, int destinationFloor)
{
    int floorDifference{destinationFloor - startFloor};

    if (floorDifference < 0)
    {
        return -floorDifference;
    }

    return floorDifference;
}
// ————————————————————————————————————————————————————————————

// Izračunava vrijeme vožnje prema broju katova i vremenu po katu
int calculate_travel_time(int floorCount, int secondsPerFloor)
{
    return floorCount * secondsPerFloor;
}
// ————————————————————————————————————————————————————————————

// Ispisuje podatke o početnom i odredišnom katu
void print_route(int startFloor, int destinationFloor, int floorCount)
{
    cout << "Pocetni kat: " << startFloor << '\n';
    cout << "Odredisni kat: " << destinationFloor << '\n';
    cout << "Broj prijedenih katova: " << floorCount << '\n';
}
// ————————————————————————————————————————————————————————————

// Ispisuje ukupno vrijeme vožnje
void print_travel_time(int travelTime)
{
    cout << "Vrijeme voznje: " << travelTime << " s\n";
}