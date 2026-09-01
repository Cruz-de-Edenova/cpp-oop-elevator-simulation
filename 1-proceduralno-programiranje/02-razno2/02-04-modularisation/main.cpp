#include "elevator.h"

int main()
{
    int startFloor{2};
    int destinationFloor{7};

    int floorCount{calculate_floor_count(startFloor, destinationFloor)};
    int travelTime{calculate_travel_time(floorCount)};

    print_route(startFloor, destinationFloor, floorCount);
    print_travel_time(travelTime);

    return 0;
}

/* ============================================================
Pocetni kat: 2
Odredisni kat: 7
Broj prijedenih katova: 5
Vrijeme voznje: 10 s

*/