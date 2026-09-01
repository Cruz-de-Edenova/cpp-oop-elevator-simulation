#ifndef ELEVATOR_H
#define ELEVATOR_H

// Izračunava broj prijeđenih katova između početnog i odredišnog kata
int calculate_floor_count(int startFloor, int destinationFloor);

// Izračunava vrijeme vožnje prema broju katova i vremenu po katu
int calculate_travel_time(int floorCount, int secondsPerFloor = 2);

// Ispisuje podatke o početnom i odredišnom katu
void print_route(int startFloor, int destinationFloor, int floorCount);

// Ispisuje ukupno vrijeme vožnje
void print_travel_time(int travelTime);

#endif