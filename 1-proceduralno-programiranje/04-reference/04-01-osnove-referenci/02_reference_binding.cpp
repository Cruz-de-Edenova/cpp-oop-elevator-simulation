#include <iostream>

using std::cout;

// Demonstracija vezivanja reference uz jedan objekt
int main()
{
    int firstValue{10};
    int secondValue{20};
    int& refValue{firstValue};

    cout << "Prije dodjele:\n";
    cout << "firstValue:  " << firstValue << '\n';
    cout << "secondValue: " << secondValue << '\n';
    cout << "refValue:    " << refValue << '\n';

    refValue = secondValue;

    cout << "\nNakon refValue = secondValue:\n";
    cout << "firstValue:  " << firstValue << '\n';
    cout << "secondValue: " << secondValue << '\n';
    cout << "refValue:    " << refValue << '\n';

    cout << "\nAdresa firstValue:     " << &firstValue << '\n';
    cout << "Adresa preko refValue: " << &refValue << '\n';
    cout << "Adresa secondValue:    " << &secondValue << '\n';

    return 0;
}
/* ============================================================
Prije dodjele:
firstValue:  10
secondValue: 20
refValue:    10

Nakon refValue = secondValue:
firstValue:  20
secondValue: 20
refValue:    20

Adresa firstValue:     0x675efffc64
Adresa preko refValue: 0x675efffc64
Adresa secondValue:    0x675efffc60
*/