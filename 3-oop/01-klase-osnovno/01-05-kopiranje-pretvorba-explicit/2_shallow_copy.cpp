#include <iostream>

using std::cout;

/* ============================================================
                       klasa ShallowCopy
   ============================================================ */

class ShallowCopy
{
private:
    int* mPtrValue; // Pokazuje na dinamički alocirani int

public:
    // Alocira i inicijalizira dinamički podatak objekta
    ShallowCopy(int value);

    // Mijenja vrijednost dinamičkog podatka
    void set_value(int value);

    // Ispisuje adresu i vrijednost dinamičkog podatka
    void print_state();

    // Ručno oslobađa dinamički alocirani podatak
    void cleanup();
};
// ————————————————————————————————————————————————————————————

// Alocira i inicijalizira dinamički podatak objekta
ShallowCopy::ShallowCopy(int value)
    : mPtrValue{new int{value}}
{
}
// ————————————————————————————————————————————————————————————

// Mijenja vrijednost dinamičkog podatka
void ShallowCopy::set_value(int value)
{
    *mPtrValue = value;
}
// ————————————————————————————————————————————————————————————

// Ispisuje adresu i vrijednost dinamičkog podatka
void ShallowCopy::print_state()
{
    cout << "Adresa: " << mPtrValue << ", vrijednost: " << *mPtrValue << '\n';
}
// ————————————————————————————————————————————————————————————

// Ručno oslobađa dinamički alocirani podatak
void ShallowCopy::cleanup()
{
    delete mPtrValue;
    mPtrValue = nullptr;
}

/* ============================================================
                              main()
   ============================================================ */

// Demonstrira problem plitkog kopiranja pokazivača
int main()
{
    ShallowCopy objOriginal{10};
    ShallowCopy objCopy{objOriginal};

    cout << "Nakon kopiranja:\n";
    cout << "Original: ";
    objOriginal.print_state();
    cout << "Kopija:   ";
    objCopy.print_state();

    objCopy.set_value(20);

    cout << "Nakon promjene kroz kopiju:\n";
    cout << "Original: ";
    objOriginal.print_state();
    cout << "Kopija:   ";
    objCopy.print_state();

    // Oba objekta sadrže istu adresu pa memoriju oslobađamo samo jednom
    objOriginal.cleanup();

    // objCopy sada sadrži viseći pokazivač i više se ne koristi

    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Nakon kopiranja:
Original: Adresa: 0x1638f0af250, vrijednost: 10
Kopija:   Adresa: 0x1638f0af250, vrijednost: 10
Nakon promjene kroz kopiju:
Original: Adresa: 0x1638f0af250, vrijednost: 20
Kopija:   Adresa: 0x1638f0af250, vrijednost: 20
*/
