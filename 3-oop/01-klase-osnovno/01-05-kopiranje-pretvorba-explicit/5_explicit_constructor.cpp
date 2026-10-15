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
    // Inicijalizira objekt bez dopuštanja implicitne pretvorbe
    explicit AdcReading(int rawValue);

    // Vraća spremljenu ADC vrijednost
    int get_raw_value();
};
// ————————————————————————————————————————————————————————————

// Inicijalizira objekt bez dopuštanja implicitne pretvorbe
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

// Pokazuje uporabu konstruktora označenog specifikatorom explicit
void demonstrate_explicit_constructor()
{
    cout << "EKSPLICITNI KONSTRUKTOR\n";

    AdcReading objReading{512};
    cout << "Izravna inicijalizacija listom: "
         << objReading.get_raw_value() << '\n';

    print_reading(AdcReading{900});

    // Ove naredbe ne prolaze kompajliranje zbog specifikatora explicit
    // AdcReading objCopyInitialized = 768;
    // print_reading(900);
}

/* ============================================================
                              main()
   ============================================================ */

// Pokreće demonstraciju eksplicitnog konstruktora
int main()
{
    demonstrate_explicit_constructor();
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
EKSPLICITNI KONSTRUKTOR
Izravna inicijalizacija listom: 512
ADC vrijednost: 900
*/
