#include <iostream>

using std::cout;

struct CalculationResult
{
    int mSum;
    int mDifference;
};

/* ============================================================
                      POMOĆNE FUNKCIJE
   ============================================================ */

// Vraća dva rezultata preko pokazivača kao izlaznih parametara
void calculate(
    int firstValue,      // Prva ulazna vrijednost
    int secondValue,     // Druga ulazna vrijednost
    int* ptrSum,         // Adresa varijable za rezultat zbrajanja
    int* ptrDifference)  // Adresa varijable za rezultat oduzimanja
{
    *ptrSum = firstValue + secondValue;
    *ptrDifference = firstValue - secondValue;
}
// ————————————————————————————————————————————————————————————

// Vraća ista dva rezultata pomoću jedne strukture
CalculationResult calculate_result(int firstValue, int secondValue)
{
    CalculationResult objResult{
        firstValue + secondValue,  // mSum
        firstValue - secondValue   // mDifference
    };

    return objResult;
}

/* ============================================================
                   DEMONSTRACIJSKE FUNKCIJE
   ============================================================ */

// Demonstrira dobivanje više rezultata preko pokazivača
void demonstrate_output_parameters()
{
    int sum{};
    int difference{};

    calculate(10, 4, &sum, &difference);

    cout << "Zbroj: " << sum << '\n';
    cout << "Razlika: " << difference << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira dobivanje istih rezultata vraćanjem strukture
void demonstrate_struct_result()
{
    CalculationResult objResult{calculate_result(10, 4)};

    cout << "Zbroj: " << objResult.mSum << '\n';
    cout << "Razlika: " << objResult.mDifference << '\n';
}

/* ============================================================
                         MAIN
   ============================================================ */

int main()
{
    demonstrate_output_parameters();
    demonstrate_struct_result();

    return 0;
}
/* ============================================================
Zbroj: 14
Razlika: 6
------------------------------
Zbroj: 14
Razlika: 6
*/