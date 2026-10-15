#include <iostream>

using std::cout;

/* ============================================================
                     klasa SensorReading
   ============================================================ */

class SensorReading
{
private:
    int mChannel;     // Kanal s kojeg je očitana vrijednost
    int mRawValue;    // Očitana ADC vrijednost
    bool mValid;      // Označava je li očitanje valjano

public:
    // Inicijalizira podatke jednog očitanja senzora
    SensorReading(int channel, int rawValue, bool valid);

    // Postavlja novu očitanu ADC vrijednost
    void set_raw_value(int rawValue);

    // Ispisuje sve spremljene podatke očitanja
    void print_state();
};
// ————————————————————————————————————————————————————————————

// Inicijalizira podatke jednog očitanja senzora
SensorReading::SensorReading(int channel, int rawValue, bool valid)
    : mChannel{channel}, mRawValue{rawValue}, mValid{valid}
{
}
// ————————————————————————————————————————————————————————————

// Postavlja novu očitanu ADC vrijednost
void SensorReading::set_raw_value(int rawValue)
{
    mRawValue = rawValue;
}
// ————————————————————————————————————————————————————————————

// Ispisuje sve spremljene podatke očitanja
void SensorReading::print_state()
{
    cout << "Kanal: " << mChannel
         << ", ADC vrijednost: " << mRawValue
         << ", valjano: " << (mValid ? "da" : "ne") << '\n';
}

/* ============================================================
                              main()
   ============================================================ */

// Demonstrira kopiranje član po član i neovisnost kopije
int main()
{
    SensorReading objOriginal{2, 750, true};
    SensorReading objCopy{objOriginal};

    cout << "Nakon kopiranja:\n";
    cout << "Original: ";
    objOriginal.print_state();
    cout << "Kopija:   ";
    objCopy.print_state();

    objCopy.set_raw_value(900);

    cout << "Nakon promjene kopije:\n";
    cout << "Original: ";
    objOriginal.print_state();
    cout << "Kopija:   ";
    objCopy.print_state();

    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Nakon kopiranja:
Original: Kanal: 2, ADC vrijednost: 750, valjano: da
Kopija:   Kanal: 2, ADC vrijednost: 750, valjano: da
Nakon promjene kopije:
Original: Kanal: 2, ADC vrijednost: 750, valjano: da
Kopija:   Kanal: 2, ADC vrijednost: 900, valjano: da
*/
