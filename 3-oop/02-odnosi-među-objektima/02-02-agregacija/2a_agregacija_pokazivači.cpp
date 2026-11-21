#include <iostream>

using std::cout;

/* ============================================================
                          klasa Battery
   ============================================================ */

class Battery
{
private:
    int mChargePercent; // Spremljena napunjenost baterije

public:
    // Inicijalizira podatak o napunjenosti baterije
    Battery(int chargePercent)
        : mChargePercent{chargePercent}
    {
    }

    // Vraća spremljenu napunjenost baterije
    int get_charge_percent() const
    {
        return mChargePercent;
    }
};

/* ============================================================
                        klasa MobileRobot
   ============================================================ */

class MobileRobot
{
private:
    const Battery* mBattery; // Pokazivač na vanjski objekt ili nullptr

public:
    // Stvara objekt bez povezane baterije
    MobileRobot()
        : mBattery{nullptr}
    {
    }

    // Postavlja vezu s postojećim objektom baterije
    void set_battery(const Battery* ptrBattery)
    {
        mBattery = ptrBattery;
    }

    // Ispisuje podatak o napunjenosti ako postoji veza
    void print_battery_charge() const
    {
        if (mBattery != nullptr)
        {
            cout << "Napunjenost baterije: "
                 << mBattery->get_charge_percent() << " %\n";
        }
        else
        {
            cout << "Baterija nije povezana\n";
        }
    }
};

/* ============================================================
                              main()
   ============================================================ */

// Prikazuje povezivanje postojećeg objekta pomoću pokazivača
int main()
{
    Battery objBattery{85};
    MobileRobot objRobot{};

    objRobot.print_battery_charge();
    cout << "------------------------------\n";
    objRobot.set_battery(&objBattery);
    objRobot.print_battery_charge();
    
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Baterija nije povezana
------------------------------
Napunjenost baterije: 85 %
*/
