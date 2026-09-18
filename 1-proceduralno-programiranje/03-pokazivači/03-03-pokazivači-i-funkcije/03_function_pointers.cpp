#include <iostream>

using std::cout;

/* ============================================================
                         POMOĆNE FUNKCIJE
   ============================================================ */

// Zbraja dvije cjelobrojne vrijednosti
int add(int firstValue, int secondValue)
{
    return firstValue + secondValue;
}
// ————————————————————————————————————————————————————————————

// Oduzima drugu cjelobrojnu vrijednost od prve
int subtract(int firstValue, int secondValue)
{
    return firstValue - secondValue;
}
// ————————————————————————————————————————————————————————————

// Poziva funkciju primljenu preko pokazivačkog parametra
int calculate(int firstValue, int secondValue, int (*ptrOperation)(int, int))
{
    return ptrOperation(firstValue, secondValue);
}

/* ============================================================
                    DEMONSTRACIJSKE FUNKCIJE
   ============================================================ */

// Demonstrira osnovno korištenje pokazivača na funkciju
void demonstrate_function_pointer()
{
    int (*ptrOperation)(int, int){add};

    cout << "Zbrajanje: " << ptrOperation(8, 3) << '\n';

    ptrOperation = subtract;

    cout << "Oduzimanje: " << ptrOperation(8, 3) << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira pokazivač na funkciju kao parametar druge funkcije
void demonstrate_function_pointer_parameter()
{
    int additionResult{calculate(10, 4, add)};
    int subtractionResult{calculate(10, 4, subtract)};

    cout << "Rezultat zbrajanja: " << additionResult << '\n';
    cout << "Rezultat oduzimanja: " << subtractionResult << '\n';
}

/* ============================================================
                         MAIN
   ============================================================ */

int main()
{
    demonstrate_function_pointer();
    demonstrate_function_pointer_parameter();

    return 0;
}
/* ============================================================
Zbrajanje: 11
Oduzimanje: 5
------------------------------
Rezultat zbrajanja: 14
Rezultat oduzimanja: 6
*/