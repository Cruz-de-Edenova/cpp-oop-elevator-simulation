#include <iostream>

using std::cout;

/* ============================================================
                         klasa DeepCopy
   ============================================================ */

class DeepCopy
{
private:
    int* mPtrValue; // Pokazuje na vlastiti dinamički alocirani podatak

public:
    // Alocira i inicijalizira dinamički podatak objekta
    DeepCopy(int value);

    // Stvara neovisnu kopiju dinamičkog podatka izvornog objekta
    DeepCopy(const DeepCopy& refSource);

    // Mijenja vrijednost dinamičkog podatka
    void set_value(int value);

    // Ispisuje adresu i vrijednost dinamičkog podatka
    void print_state();

    // Ručno oslobađa dinamički alocirani podatak
    void cleanup();
};
// ————————————————————————————————————————————————————————————

// Alocira i inicijalizira dinamički podatak objekta
DeepCopy::DeepCopy(int value)
    : mPtrValue{new int{value}}
{
}
// ————————————————————————————————————————————————————————————

// Stvara neovisnu kopiju dinamičkog podatka izvornog objekta
DeepCopy::DeepCopy(const DeepCopy& refSource)
    : mPtrValue{new int{*(refSource.mPtrValue)}}
{
}
// ————————————————————————————————————————————————————————————

// Mijenja vrijednost dinamičkog podatka
void DeepCopy::set_value(int value)
{
    *mPtrValue = value;
}
// ————————————————————————————————————————————————————————————

// Ispisuje adresu i vrijednost dinamičkog podatka
void DeepCopy::print_state()
{
    cout << "Adresa: " << mPtrValue << ", vrijednost: " << *mPtrValue << '\n';
}
// ————————————————————————————————————————————————————————————

// Ručno oslobađa dinamički alocirani podatak
void DeepCopy::cleanup()
{
    delete mPtrValue;
    mPtrValue = nullptr;
}

/* ============================================================
                              main()
   ============================================================ */

// Demonstrira duboko kopiranje dinamički alociranog podatka
int main()
{
    DeepCopy objOriginal{10};
    DeepCopy objCopy{objOriginal};

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

    objOriginal.cleanup();
    objCopy.cleanup();

    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Nakon kopiranja:
Original: Adresa: 0x1cd68cde6c0, vrijednost: 10
Kopija:   Adresa: 0x1cd68cde550, vrijednost: 10
Nakon promjene kroz kopiju:
Original: Adresa: 0x1cd68cde6c0, vrijednost: 10
Kopija:   Adresa: 0x1cd68cde550, vrijednost: 20
*/
