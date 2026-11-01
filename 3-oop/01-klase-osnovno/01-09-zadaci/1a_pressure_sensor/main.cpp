#include <iostream>
#include <iomanip>

using std::cout;
using std::left;
using std::setw;

constexpr int kLowPressure{60};  // Donji prag tlaka u barima
constexpr int kHighPressure{95}; // Gornji prag tlaka u barima

/* ============================================================
                       klasa PressureSensor
   ============================================================ */

class PressureSensor
{
private:
    int mPressureBar{0};      // Trenutno spremljena vrijednost tlaka u barima

public:
    // Sprema novu vrijednost tlaka u privatni podatkovni član
    void set_pressure(int pressureBar)
    {
        mPressureBar = pressureBar;
    }
// ————————————————————————————————————————————————————————————

    // Vraća trenutno spremljenu vrijednost tlaka
    int get_pressure() const
    {
        return mPressureBar;
    }
// ————————————————————————————————————————————————————————————

    // Provjerava je li spremljena vrijednost tlaka ispod donjeg praga
    bool is_low() const
    {
        return mPressureBar < kLowPressure;
    }
// ————————————————————————————————————————————————————————————

    // Provjerava je li spremljena vrijednost tlaka iznad gornjeg praga
    bool is_high() const
    {
        return mPressureBar > kHighPressure;
    }
};

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    // Objekt senzora koji sprema trenutnu vrijednost tlaka
    PressureSensor objSensor{};
    
    // Polje vrijednosti tlaka za provjeru stanja senzora
    int pressureValues[]{45, 74, 105, 97, 87};

    cout << left << setw(15) << "Tlak [bar]" << "Stanje tlaka\n";
    cout << "------------------------------\n";
    
    // Provjera stanja senzora za svaku vrijednost tlaka iz polja
    for (int pressureBar : pressureValues)
    {
        objSensor.set_pressure(pressureBar);
    
        cout << setw(15) << objSensor.get_pressure();
    
        if (objSensor.is_low())
        {
            cout << "prenizak\n";
        }
        else if (objSensor.is_high())
        {
            cout << "previsok\n";
        }
        else
        {
            cout << "u zadanom rasponu\n";
        }
    }
    
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Tlak [bar]     Stanje tlaka
------------------------------
45             prenizak
74             u zadanom rasponu
105            previsok
97             previsok
87             u zadanom rasponu
*/