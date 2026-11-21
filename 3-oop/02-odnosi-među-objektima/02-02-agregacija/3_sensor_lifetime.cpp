#include <iomanip>
#include <iostream>
#include <string>

using std::cout;
using std::left;
using std::setw;
using std::string;

/* ============================================================
                          FUNKCIJE
   ============================================================ */

// Ispisuje događaj, oznaku objekta i njegovu adresu u jednom retku tablice
void print_address_row(const string& event, const string& objectName,
                       const void* ptrObject)
{
    cout << left << setw(28) << event
         << setw(16) << objectName << ptrObject << '\n';
}

/* ============================================================
                    klasa TemperatureSensor
   ============================================================ */

class TemperatureSensor
{
private:
    string mName; // Oznaka objekta

public:
    // Inicijalizira oznaku i prikazuje adresu objekta pri konstrukciji
    TemperatureSensor(const string& name)
        : mName{name}
    {
        print_address_row("Konstruktor senzora", mName, this);
    }

    // Prikazuje adresu objekta pri izvršavanju destruktora
    ~TemperatureSensor()
    {
        print_address_row("Destruktor senzora", mName, this);
    }

    // Vraća oznaku objekta
    const string& get_name() const
    {
        return mName;
    }
};

/* ============================================================
                       klasa SensorGroup
   ============================================================ */

class SensorGroup
{
private:
    const TemperatureSensor& mFirstSensor;  // Referenca na prvi objekt izvan grupe
    const TemperatureSensor& mSecondSensor; // Referenca na drugi objekt izvan grupe

public:
    // Povezuje postojeće senzore i prikazuje adrese referenciranih objekata
    SensorGroup(const TemperatureSensor& refFirstSensor,
                const TemperatureSensor& refSecondSensor)
        : mFirstSensor{refFirstSensor}, mSecondSensor{refSecondSensor}
    {
        print_address_row("Konstruktor grupe", "SensorGroup", this);
        // Operator & primijenjen na referencu vraća adresu referenciranog objekta
        print_address_row("Referenca u grupi", mFirstSensor.get_name(),
                          &mFirstSensor);
        print_address_row("Referenca u grupi", mSecondSensor.get_name(),
                          &mSecondSensor);
    }

    // Prikazuje uništavanje grupe bez uništavanja povezanih objekata
    ~SensorGroup()
    {
        print_address_row("Destruktor grupe", "SensorGroup", this);
    }
};

/* ============================================================
                             main()
   ============================================================ */

// Pokazuje da povezani objekti postoje i nakon uništavanja grupe
int main()
{
    cout << left << setw(28) << "Dogadaj" << setw(16) << "Objekt"
         << "Adresa objekta\n";
    cout << "------------------------------------------------------------\n";

    TemperatureSensor objMotorSensor{"motor"};
    TemperatureSensor objBearingSensor{"lezaj"};

    // Referencirani objekti moraju postojati dok ih grupa koristi
    {
        SensorGroup objSensorGroup{objMotorSensor, objBearingSensor};
    }

    // Oba senzora ostaju dostupna nakon završetka životnog vijeka grupe
    print_address_row("Nakon izlaska iz bloka", objMotorSensor.get_name(),
                      &objMotorSensor);
    print_address_row("Nakon izlaska iz bloka", objBearingSensor.get_name(),
                      &objBearingSensor);
                      
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Dogadaj                     Objekt          Adresa objekta
------------------------------------------------------------
Konstruktor senzora         motor           0x512afff690
Konstruktor senzora         lezaj           0x512afff670
Konstruktor grupe           SensorGroup     0x512afff660
Referenca u grupi           motor           0x512afff690
Referenca u grupi           lezaj           0x512afff670
Destruktor grupe            SensorGroup     0x512afff660
Nakon izlaska iz bloka      motor           0x512afff690
Nakon izlaska iz bloka      lezaj           0x512afff670
Destruktor senzora          lezaj           0x512afff670
Destruktor senzora          motor           0x512afff690
*/
