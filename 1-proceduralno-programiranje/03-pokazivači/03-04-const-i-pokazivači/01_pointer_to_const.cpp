#include <iostream>

using std::cout;

/* ============================================================
                  DEMONSTRACIJSKE FUNKCIJE
   ============================================================ */

// Pokazuje da se vrijednost ne može mijenjati preko pokazivača na const int
void demonstrate_pointer_to_const()
{
    int value{10};
    const int* ptrValue{&value};

    cout << "Vrijednost: " << *ptrValue << '\n';

    // *ptrValue = 20;  // Pogreška: podatak se ne može mijenjati preko ptrValue

    value = 20;

    cout << "Nova vrijednost: " << *ptrValue << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Pokazuje da se pokazivač na const int može preusmjeriti na drugu varijablu
void demonstrate_pointer_reassignment()
{
    int firstValue{10};
    int secondValue{20};

    const int* ptrValue{&firstValue};

    cout << "Prva vrijednost: " << *ptrValue << '\n';

    ptrValue = &secondValue;

    cout << "Druga vrijednost: " << *ptrValue << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Pokazuje pokazivač na varijablu tipa const int
void demonstrate_const_variable()
{
    const int value{30};
    const int* ptrValue{&value};

    cout << "Const vrijednost: " << *ptrValue << '\n';

    // value = 40;      // Pogreška: const varijablu nije moguće mijenjati
    // *ptrValue = 40;  // Pogreška: vrijednost nije moguće mijenjati preko ptrValue

    int const* ptrAlternative{&value};  // Identično: const int*

    cout << "Alternativni zapis: " << *ptrAlternative << '\n';
}

/* ============================================================
                               MAIN
   ============================================================ */

int main()
{
    demonstrate_pointer_to_const();
    demonstrate_pointer_reassignment();
    demonstrate_const_variable();

    return 0;
}
/* ============================================================
Vrijednost: 10
Nova vrijednost: 20
------------------------------
Prva vrijednost: 10
Druga vrijednost: 20
------------------------------
Const vrijednost: 30
Alternativni zapis: 30
*/