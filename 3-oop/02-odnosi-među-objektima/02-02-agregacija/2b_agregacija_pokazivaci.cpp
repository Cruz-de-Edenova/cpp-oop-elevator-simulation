#include <iostream>

using std::cout;

/* ============================================================
                    klasa TemperatureSensor
   ============================================================ */

class TemperatureSensor
{
private:
    int mTemperatureCelsius; // Spremljena temperatura u stupnjevima Celzija

public:
    // Inicijalizira početnu temperaturu objekta
    TemperatureSensor(int temperatureCelsius)
        : mTemperatureCelsius{temperatureCelsius}
    {
    }

    // Ažurira spremljenu temperaturu
    void set_temperature(int temperatureCelsius)
    {
        mTemperatureCelsius = temperatureCelsius;
    }

    // Vraća spremljenu temperaturu
    int get_temperature() const
    {
        return mTemperatureCelsius;
    }
};

/* ============================================================
                       klasa SensorGroup
   ============================================================ */

class SensorGroup
{
private:
    const TemperatureSensor* mFirstSensor;  // Pokazivač na prvi povezani objekt
    const TemperatureSensor* mSecondSensor; // Pokazivač na drugi povezani objekt

public:
    // Sprema pokazivače na postojeće objekte bez preuzimanja vlasništva
    SensorGroup(const TemperatureSensor* ptrFirstSensor,
                const TemperatureSensor* ptrSecondSensor)
        : mFirstSensor{ptrFirstSensor}, mSecondSensor{ptrSecondSensor}
    {
    }

    // Očekuje valjane pokazivače i vraća prosjek spremljenih temperatura
    double get_average_temperature() const
    {
        return (mFirstSensor->get_temperature() +
                mSecondSensor->get_temperature()) / 2.0;
    }
};

/* ============================================================
                             main()
   ============================================================ */

// Prikazuje dvije grupe koje dijele jedan objekt TemperatureSensor
int main()
{
    TemperatureSensor objMotorSensor{58};
    TemperatureSensor objBearingSensor{47};
    TemperatureSensor objPumpSensor{62};

    {
        SensorGroup objMotorBearing{&objMotorSensor, &objBearingSensor};
        SensorGroup objMotorPump{&objMotorSensor, &objPumpSensor};

        cout << "Pocetni prosjek motor-lezaj: "
             << objMotorBearing.get_average_temperature() << " C\n";
        cout << "Pocetni prosjek motor-pumpa: "
             << objMotorPump.get_average_temperature() << " C\n";
        cout << "------------------------------\n";

        // Obje grupe pristupaju novoj vrijednosti zajedničkog objekta
        objMotorSensor.set_temperature(55);

        cout << "Novi prosjek motor-lezaj: "
             << objMotorBearing.get_average_temperature() << " C\n";
        cout << "Novi prosjek motor-pumpa: "
             << objMotorPump.get_average_temperature() << " C\n";
    }

    // Objekt senzora postoji i nakon uništavanja obiju grupa
    cout << "Temperatura motora nakon unistavanja obiju grupa: "
         << objMotorSensor.get_temperature() << " C\n";
         
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Pocetni prosjek motor-lezaj: 52.5 C
Pocetni prosjek motor-pumpa: 60 C
------------------------------
Novi prosjek motor-lezaj: 51 C
Novi prosjek motor-pumpa: 58.5 C
Temperatura motora nakon unistavanja obiju grupa: 55 C
*/
