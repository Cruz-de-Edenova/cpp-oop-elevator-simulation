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
    const Battery& mBattery; // Referenca na zasebno stvoren objekt baterije

public:
    // Povezuje objekt robota s postojećim objektom baterije
    MobileRobot(const Battery& refBattery)
        : mBattery{refBattery}
    {
    }

    // Ispisuje podatak iz povezanog objekta baterije
    void print_battery_charge() const
    {
        cout << "Napunjenost baterije: "
             << mBattery.get_charge_percent() << " %\n";
    }
};

/* ============================================================
                              main()
   ============================================================ */

// Prikazuje agregaciju pomoću reference na postojeći objekt
int main()
{
    Battery objBattery{85};
    MobileRobot objRobot{objBattery};
    objRobot.print_battery_charge();
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Napunjenost baterije: 85 %
*/
