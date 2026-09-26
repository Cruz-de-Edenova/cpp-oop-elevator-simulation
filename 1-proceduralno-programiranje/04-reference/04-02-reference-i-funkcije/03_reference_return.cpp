#include <iostream>

using std::cout;

// Vraća referencu na varijablu koja sadrži veći broj kata
int& select_higher_floor(int& refFirstFloor, int& refSecondFloor)
{
    if (refFirstFloor > refSecondFloor)
    {
        return refFirstFloor;
    }

    return refSecondFloor;
}

int main()
{
    int firstFloor{2};
    int secondFloor{7};

    int& refSelectedFloor{select_higher_floor(firstFloor, secondFloor)};

    cout << "Prvi kat: " << firstFloor << '\n';
    cout << "Drugi kat: " << secondFloor << '\n';
    cout << "Odabrani kat: " << refSelectedFloor << '\n';

    refSelectedFloor = 10;

    cout << "\nNakon promjene pomocu vracene reference:\n";
    cout << "Prvi kat: " << firstFloor << '\n';
    cout << "Drugi kat: " << secondFloor << '\n';

    return 0;
}
/* ============================================================
Prvi kat: 2
Drugi kat: 7
Odabrani kat: 7

Nakon promjene pomocu vracene reference:
Prvi kat: 2
Drugi kat: 10
*/