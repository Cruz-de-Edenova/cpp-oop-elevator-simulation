#include <iostream>

using std::cout;

// Vraća referencu na const int s većim brojem kata
const int& select_higher_floor(const int& refFirstFloor, const int& refSecondFloor)
{
    // refFirstFloor = 10; // Referenca na const int ne dopušta promjenu vrijednosti
    if (refFirstFloor > refSecondFloor)
    {
        return refFirstFloor;
    }

    return refSecondFloor;
}

// Demonstrira korištenje vraćene reference na const int
int main()
{
    int firstFloor{2};
    int secondFloor{7};

    const int& refSelectedFloor{select_higher_floor(firstFloor, secondFloor)};

    cout << "Prvi kat: " << firstFloor << '\n';
    cout << "Drugi kat: " << secondFloor << '\n';
    cout << "Odabrani kat: " << refSelectedFloor << '\n';

    // Referenca na const int ne dopušta promjenu vrijednosti:
    // refSelectedFloor = 10; 

    secondFloor = 10;

    cout << "\nNakon promjene varijable secondFloor:\n";
    cout << "Drugi kat: " << secondFloor << '\n';
    cout << "Odabrani kat: " << refSelectedFloor << '\n';

    return 0;
}
/* ============================================================
Prvi kat: 2
Drugi kat: 7
Odabrani kat: 7

Nakon promjene varijable secondFloor:
Drugi kat: 10
Odabrani kat: 10
*/