#include <iostream>

using std::cout;

// Demonstrira referencu na const int vezanu uz const varijablu
void demonstrate_const_reference()
{
    const int lockedFloor{5};
    const int& refLockedFloor{lockedFloor};
    // Ograničenje pri vezivanju obične reference uz const varijablu:
    // int& refFloor{lockedFloor}; // Obična referenca ne može se vezati uz
                                   // const varijablu

    cout << "lockedFloor:    " << lockedFloor << '\n';
    cout << "refLockedFloor: " << refLockedFloor << '\n';

    // lockedFloor = 7;    // Nije dopušteno mijenjati vrijednost const varijable
    // refLockedFloor = 7; // Nije dopušteno mijenjati vrijednost const varijable
                           // pomoću reference
    
    cout << "------------------------------\n";
}

// Demonstrira referencu na const int vezanu uz običnu varijablu
void demonstrate_const_reference_to_variable()
{
    int floor{5};
    const int& refFloor{floor};

    cout << "Pocetna vrijednost floor: " << floor << '\n';
    cout << "Vrijednost refFloor:      " << refFloor << '\n';

    floor = 7;

    cout << "Nakon promjene floor:     " << floor << '\n';
    cout << "Vrijednost refFloor:      " << refFloor << '\n';

    // refFloor = 9; // Nije dopušteno mijenjati vrijednost pomoću reference
}

int main()
{
    demonstrate_const_reference();
    demonstrate_const_reference_to_variable();

    return 0;
}
/* ============================================================
lockedFloor:    5
refLockedFloor: 5
------------------------------
Pocetna vrijednost floor: 5
Vrijednost refFloor:      5
Nakon promjene floor:     7
Vrijednost refFloor:      7
*/