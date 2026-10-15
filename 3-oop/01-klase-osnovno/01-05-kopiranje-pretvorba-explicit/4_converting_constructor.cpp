#include <iostream>

using std::cout;

/* ============================================================
                         klasa AdcReading
   ============================================================ */

class AdcReading
{
private:
    int mRawValue; // Spremljena ADC vrijednost

public:
    // Inicijalizira objekt zadanom ADC vrijednošću
    AdcReading(int rawValue);

    // Vraća spremljenu ADC vrijednost
    int get_raw_value();
};
// ————————————————————————————————————————————————————————————

// Inicijalizira objekt zadanom ADC vrijednošću
AdcReading::AdcReading(int rawValue)
    : mRawValue{rawValue}
{
}
// ————————————————————————————————————————————————————————————

// Vraća spremljenu ADC vrijednost
int AdcReading::get_raw_value()
{
    return mRawValue;
}

/* ============================================================
                         FUNKCIJE
   ============================================================ */

// Ispisuje ADC vrijednost objekta proslijeđenog po vrijednosti
void print_reading(AdcReading objReading)
{
    cout << "ADC vrijednost: " << objReading.get_raw_value() << '\n';
}
// ————————————————————————————————————————————————————————————

// Uspoređuje izravnu inicijalizaciju listom i inicijalizaciju kopiranjem
void demonstrate_initialization()
{
    cout << "INICIJALIZACIJA PRETVORBENIM KONSTRUKTOROM\n";

    AdcReading objDirect{512};
    AdcReading objCopyInitialized = 768;

    cout << "Izravna inicijalizacija listom: "
         << objDirect.get_raw_value() << '\n';
    cout << "Inicijalizacija kopiranjem: "
         << objCopyInitialized.get_raw_value() << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Pokazuje implicitnu pretvorbu argumenta u objekt klase
void demonstrate_implicit_conversion()
{
    cout << "IMPLICITNA PRETVORBA ARGUMENTA\n";
    print_reading(900);
}

/* ============================================================
                              main()
   ============================================================ */

// Pokreće demonstracije pretvorbenog konstruktora
int main()
{
    demonstrate_initialization();
    demonstrate_implicit_conversion();

    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
INICIJALIZACIJA PRETVORBENIM KONSTRUKTOROM
Izravna inicijalizacija listom: 512
Inicijalizacija kopiranjem: 768
------------------------------
IMPLICITNA PRETVORBA ARGUMENTA
ADC vrijednost: 900
*/
