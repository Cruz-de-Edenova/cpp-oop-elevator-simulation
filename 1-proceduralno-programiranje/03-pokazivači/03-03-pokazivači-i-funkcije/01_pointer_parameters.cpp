#include <iostream>

using std::cout;

/* ============================================================
                         POMOĆNE FUNKCIJE
   ============================================================ */

// Mijenja samo vrijednost parametra (varijabla pozivatelja ostaje nepromijenjena)
void change_copy(int value)
{
    value = 20;
    cout << "Vrijednost unutar funkcije: " << value << '\n';
}
// ————————————————————————————————————————————————————————————

// Mijenja vrijednost varijable pozivatelja preko pokazivača
void change_original(int* ptrValue)
{
    if (ptrValue == nullptr)
    {
        return;
    }

    *ptrValue = 20;
}
// ————————————————————————————————————————————————————————————

// Vraća pokazivač na veću od dvije vrijednosti
int* find_larger(int* ptrFirst, int* ptrSecond)
{
    if (*ptrFirst > *ptrSecond)
    {
        return ptrFirst;
    }

    return ptrSecond;
}

/* ============================================================
                  DEMONSTRACIJSKE FUNKCIJE
   ============================================================ */

// Uspoređuje promijenjenu kopiju s varijablom pozivatelja
void demonstrate_value_parameter()
{
    int value{10};

    cout << "Vrijednost prije poziva: " << value << '\n';
    change_copy(value);
    cout << "Vrijednost nakon poziva: " << value << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira promjenu vrijednosti varijable pozivatelja preko pokazivača
void demonstrate_pointer_parameter()
{
    int value{10};

    cout << "Vrijednost prije poziva: " << value << '\n';
    change_original(&value);
    cout << "Vrijednost nakon poziva: " << value << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira pokazivač kao povratnu vrijednost funkcije
void demonstrate_pointer_return()
{
    int firstValue{12};
    int secondValue{27};

    int* ptrLarger{find_larger(&firstValue, &secondValue)};

    cout << "Veca vrijednost je: " << *ptrLarger << '\n';
}

/* ============================================================
                         MAIN
   ============================================================ */

int main()
{
    demonstrate_value_parameter();
    demonstrate_pointer_parameter();
    demonstrate_pointer_return();

    return 0;
}
/* ============================================================
Vrijednost prije poziva: 10
Vrijednost unutar funkcije: 20
Vrijednost nakon poziva: 10
------------------------------
Vrijednost prije poziva: 10
Vrijednost nakon poziva: 20
------------------------------
Veca vrijednost je: 27
*/