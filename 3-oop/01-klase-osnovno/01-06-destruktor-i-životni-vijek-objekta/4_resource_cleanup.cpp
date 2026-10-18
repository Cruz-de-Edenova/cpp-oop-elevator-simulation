#include <iostream>

using std::cout;

/* ============================================================
                      klasa SampleStorage
   ============================================================ */

class SampleStorage
{
private:
    int* mPtrValue; // Adresa dinamički alocirane vrijednosti uzorka

public:
    // Alocira i inicijalizira vrijednost uzorka
    SampleStorage(int value);

    // Stvara zasebnu dinamičku kopiju vrijednosti uzorka
    SampleStorage(const SampleStorage& refSource);

    // Oslobađa dinamički alocirani podatak u vlasništvu objekta
    ~SampleStorage();

    // Postavlja spremljenu vrijednost uzorka
    void set_value(int value);

    // Vraća spremljenu vrijednost uzorka
    int get_value();

    // Ispisuje adresu dinamički alociranog podatka
    void print_address();
};
// ————————————————————————————————————————————————————————————

// Alocira i inicijalizira vrijednost uzorka
SampleStorage::SampleStorage(int value)
    : mPtrValue{new int{value}}
{
    cout << "Alocirana adresa:        " << mPtrValue << '\n';
}
// ————————————————————————————————————————————————————————————

// Stvara zasebnu dinamičku kopiju vrijednosti uzorka
SampleStorage::SampleStorage(const SampleStorage& refSource)
    : mPtrValue{new int{*refSource.mPtrValue}}
{
    cout << "Alocirana adresa kopije: " << mPtrValue << '\n';
}
// ————————————————————————————————————————————————————————————

// Oslobađa dinamički alocirani podatak u vlasništvu objekta
SampleStorage::~SampleStorage()
{
    cout << "Oslobadam adresu:        " << mPtrValue << '\n';
    delete mPtrValue;
}
// ————————————————————————————————————————————————————————————

// Postavlja spremljenu vrijednost uzorka
void SampleStorage::set_value(int value)
{
    *mPtrValue = value;
}
// ————————————————————————————————————————————————————————————

// Vraća spremljenu vrijednost uzorka
int SampleStorage::get_value()
{
    return *mPtrValue;
}
// ————————————————————————————————————————————————————————————

// Ispisuje adresu dinamički alociranog podatka
void SampleStorage::print_address()
{
    cout << "Adresa podatka:          " << mPtrValue << '\n';
}

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    SampleStorage objOriginal{10};
    SampleStorage objCopy{objOriginal};

    objCopy.set_value(20);

    cout << "Original: " << objOriginal.get_value() << '\n';
    objOriginal.print_address();

    cout << "Kopija:   " << objCopy.get_value() << '\n';
    objCopy.print_address();

    cout << "Prije izlaska iz funkcije main() \n";
    
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Alocirana adresa:        0x138202a6f60
Alocirana adresa kopije: 0x138202a6f80
Original: 10
Adresa podatka:          0x138202a6f60
Kopija:   20
Adresa podatka:          0x138202a6f80
Prije izlaska iz funkcije main()
Oslobadam adresu:        0x138202a6f80
Oslobadam adresu:        0x138202a6f60
*/