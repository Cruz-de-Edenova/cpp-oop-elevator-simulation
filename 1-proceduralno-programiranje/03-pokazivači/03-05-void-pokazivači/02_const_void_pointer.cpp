#include <iostream>

using std::cout;

/* ============================================================
                  DEMONSTRACIJSKE FUNKCIJE
   ============================================================ */

// Demonstrira da se vrijednost ne može mijenjati preko pokazivača na const void
void demonstrate_const_void_pointer()
{
    int value{30};
    const void* ptrData{&value};

    const int* ptrValue{static_cast<const int*>(ptrData)};

    cout << "Vrijednost: " << *ptrValue << '\n';

    // *ptrValue = 40;  // Pogreška: vrijednost se ne može mijenjati
    // int* ptrOther{static_cast<int*>(ptrData)};  // Pogreška: uklanja const

    value = 40;

    cout << "Nova vrijednost: " << *ptrValue << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira da se const pokazivač na void ne može preusmjeriti
void demonstrate_const_pointer()
{
    int firstValue{50};
    void* const ptrData{&firstValue};

    int* ptrValue{static_cast<int*>(ptrData)};

    *ptrValue = 70;

    cout << "Vrijednost: " << *ptrValue << '\n';

    // int secondValue{60};
    // ptrData = &secondValue;  // Pogreška: const pokazivač se ne može preusmjeriti
}

/* ============================================================
                               MAIN
   ============================================================ */

int main()
{
    demonstrate_const_void_pointer();
    demonstrate_const_pointer();

    return 0;
}
/* ============================================================
Vrijednost: 30
Nova vrijednost: 40
------------------------------
Vrijednost: 70
*/