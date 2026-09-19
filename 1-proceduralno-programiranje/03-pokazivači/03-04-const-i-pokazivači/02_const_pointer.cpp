#include <iostream>

using std::cout;

/* ============================================================
                  DEMONSTRACIJSKE FUNKCIJE
   ============================================================ */

// Pokazuje da const pokazivač ne može promijeniti adresu koju sadrži
void demonstrate_const_pointer()
{
    int value{10};
    int* const ptrValue{&value};

    cout << "Vrijednost: " << *ptrValue << '\n';

    *ptrValue = 20;

    cout << "Nova vrijednost: " << *ptrValue << '\n';

    // ptrValue = nullptr;  // Pogreška: const pokazivač se ne može preusmjeriti

    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Pokazuje da const pokazivač mora biti inicijaliziran
void demonstrate_required_initialization()
{
    int value{30};

    // int* const ptrValue;  // Pogreška: const pokazivač mora biti inicijaliziran

    int* const ptrValue{&value};

    cout << "Vrijednost: " << *ptrValue << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Pokazuje const pokazivač na const int
void demonstrate_const_pointer_to_const()
{
    int value{40};
    const int* const ptrValue{&value};

    cout << "Vrijednost: " << *ptrValue << '\n';

    // *ptrValue = 50;     // Pogreška: vrijednost se ne može mijenjati
    // ptrValue = nullptr; // Pogreška: pokazivač se ne može preusmjeriti

    value = 50;

    cout << "Nova vrijednost: " << *ptrValue << '\n';
}

/* ============================================================
                               MAIN
   ============================================================ */

int main()
{
    demonstrate_const_pointer();
    demonstrate_required_initialization();
    demonstrate_const_pointer_to_const();

    return 0;
}
/* ============================================================
Vrijednost: 10
Nova vrijednost: 20
------------------------------
Vrijednost: 30
------------------------------
Vrijednost: 40
Nova vrijednost: 50
*/