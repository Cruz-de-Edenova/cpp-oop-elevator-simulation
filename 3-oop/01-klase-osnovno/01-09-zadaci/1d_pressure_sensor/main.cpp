#include "pressure_sensor.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::left;
using std::setw;

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
    cout << "-------------------------------------------------------\n";
    
    // Objekt senzora sa pragovima 50 i 100 bara
    PressureSensor objSensorB{50, 100};
    
    // Promjena pragova na 110 i 40 bara
    set_thresholds_and_print_status('B', 110, 40, objSensorB);
    print_thresholds(objSensorB, 'B');
    
    // Promjena pragova na 40 i 110 bara
    set_thresholds_and_print_status('B', 40, 110, objSensorB);
    print_thresholds(objSensorB, 'B');
    cout << "-------------------------------------------------------\n";
    
    // Objekt senzora sa pragovima 60 i 95 bara
    PressureSensor objSensorC{};
    print_thresholds(objSensorC, 'C');
    
    // Promjena pragova na 30 i 120 bara
    set_thresholds_and_print_status('C', 30, 120, objSensorC);
    print_thresholds(objSensorC, 'C');
    cout << "-------------------------------------------------------\n\n";

    // Polje vrijednosti tlaka za provjeru stanja senzora
    int pressureValues[]{25, 30, 45, 55, 60, 74, 95, 97, 100, 105, 120, 125};
    
    // Ispisuje zaglavlje tablice
    cout << left << setw(15) << "Tlak [bar]"
         << setw(20) << "Senzor A"
         << setw(20) << "Senzor B"
         << setw(20) << "Senzor C" << '\n';
    cout << "-------------------------------------------------------";
    cout << "--------------------\n";
    
    // Ispisuje tablicu
    for (int pressureBar : pressureValues)
    {
        objSensorA.set_pressure(pressureBar);
        objSensorB.set_pressure(pressureBar);
        objSensorC.set_pressure(pressureBar);
        
        cout << setw(15) << pressureBar;
        print_pressure_status(objSensorA);
        print_pressure_status(objSensorB);
        print_pressure_status(objSensorC);
        cout << '\n';
    }
    
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Senzor A: [60, 95]
-------------------------------------------------------
Promjena pragova [110, 40] za senzor B nije uspjesna. Postojeci pragovi ostaju nepromijenjeni.
Senzor B: [50, 100]
Promjena pragova [40, 110] za senzor B je uspjesna.
Senzor B: [40, 110]
-------------------------------------------------------
Senzor C: [60, 95]
Promjena pragova [30, 120] za senzor C je uspjesna.
Senzor C: [30, 120]
-------------------------------------------------------

Tlak [bar]     Senzor A            Senzor B            Senzor C
---------------------------------------------------------------------------
25             prenizak            prenizak            prenizak
30             prenizak            prenizak            u zadanom rasponu
45             prenizak            u zadanom rasponu   u zadanom rasponu
55             prenizak            u zadanom rasponu   u zadanom rasponu
60             u zadanom rasponu   u zadanom rasponu   u zadanom rasponu
74             u zadanom rasponu   u zadanom rasponu   u zadanom rasponu
95             u zadanom rasponu   u zadanom rasponu   u zadanom rasponu
97             previsok            u zadanom rasponu   u zadanom rasponu
100            previsok            u zadanom rasponu   u zadanom rasponu
105            previsok            u zadanom rasponu   u zadanom rasponu
120            previsok            previsok            u zadanom rasponu
125            previsok            previsok            previsok
*/