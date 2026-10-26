#include <iostream>

using std::cout;

constexpr int kDefaultLowPressure{60};  // Defaultni donji prag u barima
constexpr int kDefaultHighPressure{95}; // Defaultni gornji prag u barima

/* ============================================================
                        klasa PressureRange
   ============================================================ */

class PressureRange
{
private:
    int mLowPressure;  // Donji prag tlaka u barima
    int mHighPressure; // Gornji prag tlaka u barima

public:
    // Delegira konstruktoru s dva parametra: oba argumenta su defaultne vrijednosti
    PressureRange();

    // Delegira konstruktoru s dva parametra: prvi argument zadan, drugi defaultni
    PressureRange(int lowPressure);

    // Izravno inicijalizira oba praga tlaka bez delegiranja
    PressureRange(int lowPressure, int highPressure);

    // Vraća donji prag tlaka
    int get_low_pressure();

    // Vraća gornji prag tlaka
    int get_high_pressure();
};
// ————————————————————————————————————————————————————————————

// Delegira konstruktoru s dva parametra: oba argumenta su defaultne vrijednosti
PressureRange::PressureRange()
    : PressureRange{kDefaultLowPressure, kDefaultHighPressure}
{
    cout << "Tijelo konstruktora: PressureRange()\n";
}
// ————————————————————————————————————————————————————————————

// Delegira konstruktoru s dva parametra: prvi argument zadan, drugi defaultni
PressureRange::PressureRange(int lowPressure)
    : PressureRange{lowPressure, kDefaultHighPressure}
    // Pogreška: uz delegiranje nije dopuštena inicijalizacija člana
    // , mLowPressure{lowPressure}
{
    cout << "Tijelo konstruktora: PressureRange(int)\n";
}
// ————————————————————————————————————————————————————————————

// Izravno inicijalizira oba praga tlaka bez delegiranja
PressureRange::PressureRange(int lowPressure, int highPressure)
    : mLowPressure{lowPressure}, mHighPressure{highPressure}
{
    cout << "Tijelo konstruktora: PressureRange(int, int)\n";
}
// ————————————————————————————————————————————————————————————

// Vraća donji prag tlaka
int PressureRange::get_low_pressure()
{
    return mLowPressure;
}
// ————————————————————————————————————————————————————————————

// Vraća gornji prag tlaka
int PressureRange::get_high_pressure()
{
    return mHighPressure;
}

/* ============================================================
                             FUNKCIJE
   ============================================================ */

// Ispisuje raspon tlaka pohranjen u objektu
void print_pressure_range(PressureRange& refRange)
{
    cout << "Raspon tlaka: " << refRange.get_low_pressure() << "-"
         << refRange.get_high_pressure() << " bar\n";
}

/* ============================================================
                              main()
   ============================================================ */

// Uspoređuje tri načina stvaranja objekata iste klase
int main()
{
    cout << "Bez argumenata:\n";
    cout << "Delegirajuci: PressureRange() -> ciljni: PressureRange(int, int)\n";
    PressureRange objDefault{};
    print_pressure_range(objDefault);
    cout << "------------------------------\n";

    cout << "Jedan argument:\n";
    cout << "Delegirajuci: PressureRange(int) -> ciljni: PressureRange(int, int)\n";
    PressureRange objLow{50};
    print_pressure_range(objLow);
    cout << "------------------------------\n";

    cout << "Dva argumenta:\n";
    cout << "Bez delegiranja: PressureRange(int, int)\n";
    PressureRange objCustom{40, 110};
    print_pressure_range(objCustom);

    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Bez argumenata:
Delegirajuci: PressureRange() -> ciljni: PressureRange(int, int)
Tijelo konstruktora: PressureRange(int, int)
Tijelo konstruktora: PressureRange()
Raspon tlaka: 60-95 bar
------------------------------
Jedan argument:
Delegirajuci: PressureRange(int) -> ciljni: PressureRange(int, int)
Tijelo konstruktora: PressureRange(int, int)
Tijelo konstruktora: PressureRange(int)
Raspon tlaka: 50-95 bar
------------------------------
Dva argumenta:
Bez delegiranja: PressureRange(int, int)
Tijelo konstruktora: PressureRange(int, int)
Raspon tlaka: 40-110 bar
*/
