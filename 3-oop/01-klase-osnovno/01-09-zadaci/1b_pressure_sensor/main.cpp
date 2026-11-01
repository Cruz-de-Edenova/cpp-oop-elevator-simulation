#include <iostream>
#include <iomanip>

using std::cout;
using std::left;
using std::setw;

/* ============================================================
                       klasa PressureSensor
   ============================================================ */

class PressureSensor
{
private:
    int mPressureBar{0};      // Trenutno spremljena vrijednost tlaka u barima
    int mLowPressure;         // Donji prag tlaka
    int mHighPressure;        // Gornji prag tlaka  

public:
    // Zadavanje pragova tlaka konstruktorom
    PressureSensor(int lowPressure, int highPressure)
        : mLowPressure{lowPressure}, mHighPressure{highPressure}
    {
    }
// ————————————————————————————————————————————————————————————

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

    // Vraća donji prag tlaka
    int get_low_pressure() const
    {
        return mLowPressure;
    }
// ————————————————————————————————————————————————————————————

    // Vraća gornji prag tlaka
    int get_high_pressure() const
    {
        return mHighPressure;
    }
// ————————————————————————————————————————————————————————————

    // Provjerava je li spremljena vrijednost tlaka ispod donjeg praga
    bool is_low() const
    {
        return mPressureBar < mLowPressure;
    }
// ————————————————————————————————————————————————————————————

    // Provjerava je li spremljena vrijednost tlaka iznad gornjeg praga
    bool is_high() const
    {
        return mPressureBar > mHighPressure;
    }
};

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    // Objekt senzora sa pragovima 50 i 100 bara
    PressureSensor objSensor{50, 100};
    
    // Polje vrijednosti tlaka za provjeru stanja senzora
    int pressureValues[]{25, 30, 45, 55, 60, 74, 95, 97, 100, 105, 120, 125};

    // Ispis pragova tlaka
    cout << "Donji prag:  " << objSensor.get_low_pressure() << " bar" << '\n';
    cout << "Gornji prag: " << objSensor.get_high_pressure() << " bar" << '\n';
    cout << "------------------------------\n";
    
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
Donji prag:  50 bar
Gornji prag: 100 bar
------------------------------
Tlak [bar]     Stanje tlaka
------------------------------
25             prenizak
30             prenizak
45             prenizak
55             u zadanom rasponu
60             u zadanom rasponu
74             u zadanom rasponu
95             u zadanom rasponu
97             u zadanom rasponu
100            u zadanom rasponu
105            previsok
120            previsok
125            previsok
*/