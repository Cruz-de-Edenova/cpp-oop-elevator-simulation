#include <iostream>

using std::cout;

// Mijenja samo lokalnu kopiju proslijeđene vrijednosti
void change_floor_copy(int floor)
{
    floor = 5;
    cout << "Vrijednost parametra floor: " << floor << '\n';
}
// ————————————————————————————————————————————————————————————

// Mijenja izvornu varijablu pomoću referentnog parametra
void change_floor(int& refFloor)
{
    refFloor = 5;
    cout << "Vrijednost parametra refFloor: " << refFloor << '\n';
}
// ————————————————————————————————————————————————————————————

// Demonstrira prosljeđivanje argumenta po vrijednosti
void demonstrate_value_parameter()
{
    int currentFloor{2};

    cout << "Prije poziva: " << currentFloor << '\n';
    change_floor_copy(currentFloor);
    cout << "Nakon poziva: " << currentFloor << '\n';

    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira prosljeđivanje argumenta pomoću reference
void demonstrate_reference_parameter()
{
    int currentFloor{2};

    cout << "Prije poziva: " << currentFloor << '\n';
    change_floor(currentFloor);
    cout << "Nakon poziva: " << currentFloor << '\n';
}
// ————————————————————————————————————————————————————————————

int main()
{
    demonstrate_value_parameter();
    demonstrate_reference_parameter();
    return 0;
}
/* ============================================================
Prije poziva: 2
Vrijednost parametra floor: 5
Nakon poziva: 2
------------------------------
Prije poziva: 2
Vrijednost parametra refFloor: 5
Nakon poziva: 5
*/
