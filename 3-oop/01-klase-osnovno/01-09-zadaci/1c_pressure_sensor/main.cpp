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
// ————————————————————————————————————————————————————————————

    // Provjerava valjanost donjeg i gornjeg praga tlaka
    bool are_thresholds_valid(int lowPressure, int highPressure) const
    {
        if ((lowPressure >= highPressure) || (lowPressure < 0))
        {
            return false;
        }
         
        return true;
    }
// ————————————————————————————————————————————————————————————

public:
    // Zadavanje pragova tlaka konstruktorom
    PressureSensor(int lowPressure, int highPressure)
        : mLowPressure{lowPressure}, mHighPressure{highPressure}
    {
        if (!are_thresholds_valid(lowPressure, highPressure))
        {
            mLowPressure = 60;
            mHighPressure = 95;
        }
    }
// ————————————————————————————————————————————————————————————

    // Sprema novu vrijednost tlaka u privatni podatkovni član
    void set_pressure(int pressureBar)
    {
        mPressureBar = pressureBar;
    }
// ————————————————————————————————————————————————————————————

    // Mijenja pragove tlaka ako su nove vrijednosti valjane
    bool set_thresholds(int lowPressure, int highPressure)
    {
        bool valid = are_thresholds_valid(lowPressure, highPressure);

        if (valid)
        {
            mLowPressure = lowPressure;
            mHighPressure = highPressure;
            return true;
        }
        
        return false;
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
                            Funkcije
   ============================================================ */

// Ishod pokušaja promjene pragova tlaka
void set_thresholds_and_print_status(char sensorName, int lowPressure, 
                                     int highPressure, PressureSensor& refSensor)
{
    bool success = refSensor.set_thresholds(lowPressure, highPressure);
    cout << "Promjena pragova [" << lowPressure << ", " << highPressure << "] "
         << "za senzor " << sensorName
         << (success ? " je uspjesna.\n" 
         : " nije uspjesna. Postojeci pragovi ostaju nepromijenjeni.\n");
}
// ————————————————————————————————————————————————————————————

// Ispisuje donji i gornji prag tlaka
void print_thresholds(const PressureSensor& refSensor, char sensorName)
{
    cout << "Senzor " << sensorName << ": ["
        << refSensor.get_low_pressure() << ", "
        << refSensor.get_high_pressure() << "]\n";
}
 // ————————————————————————————————————————————————————————————

// Ispisuje stanje tlaka pojedinog senzora
void print_pressure_status(const PressureSensor& refSensor)
{
    if (refSensor.is_low())
    {
        cout << setw(20) << "prenizak";
    }
    else if (refSensor.is_high())
    {
        cout << setw(20) << "previsok";
    }
    else
    {
        cout << setw(20) << "u zadanom rasponu";
    }
}

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    // Objekt senzora sa nevaljanim pragovima 120 i 30 bara
    PressureSensor objSensorA{120, 30};
    print_thresholds(objSensorA, 'A');
    
    // Objekt senzora sa pragovima 50 i 100 bara
    PressureSensor objSensorB{50, 100};
    
    // Promjena pragova na 110 i 40 bara
    set_thresholds_and_print_status('B', 110, 40, objSensorB);
    print_thresholds(objSensorB, 'B');
    
    // Promjena pragova na 40 i 110 bara
    set_thresholds_and_print_status('B', 40, 110, objSensorB);
    print_thresholds(objSensorB, 'B');
    cout << "-------------------------------------------------------\n";

    // Polje vrijednosti tlaka za provjeru stanja senzora
    int pressureValues[]{25, 30, 45, 55, 60, 74, 95, 97, 100, 105, 120, 125};
    
    // Ispisuje zaglavlje tablice
    cout << left << setw(15) << "Tlak [bar]"
         << setw(20) << "Senzor A"
         << setw(20) << "Senzor B" << '\n';
    cout << "-------------------------------------------------------\n";
    
    // Ispisuje tablicu
    for (int pressureBar : pressureValues)
    {
        objSensorA.set_pressure(pressureBar);
        objSensorB.set_pressure(pressureBar);
        
        cout << setw(15) << pressureBar;
        print_pressure_status(objSensorA);
        print_pressure_status(objSensorB);
        cout << '\n';
    }
    
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Senzor A: [60, 95]
Promjena pragova [110, 40] za senzor B nije uspjesna. Postojeci pragovi ostaju nepromijenjeni.
Senzor B: [50, 100]
Promjena pragova [40, 110] za senzor B je uspjesna.
Senzor B: [40, 110]
-------------------------------------------------------
Tlak [bar]     Senzor A            Senzor B
-------------------------------------------------------
25             prenizak            prenizak
30             prenizak            prenizak
45             prenizak            u zadanom rasponu
55             prenizak            u zadanom rasponu
60             u zadanom rasponu   u zadanom rasponu
74             u zadanom rasponu   u zadanom rasponu
95             u zadanom rasponu   u zadanom rasponu
97             previsok            u zadanom rasponu
100            previsok            u zadanom rasponu
105            previsok            u zadanom rasponu
120            previsok            previsok
125            previsok            previsok
*/