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
    // Inicijalizira napunjenost i prikazuje konstrukciju objekta
    Battery(int chargePercent)
        : mChargePercent{chargePercent}
    {
        cout << "Battery: tijelo konstruktora, adresa objekta = " << this << '\n';
    }

    // Prikazuje završetak životnog vijeka objekta
    ~Battery()
    {
        cout << "Battery: tijelo destruktora, adresa objekta =  " << this << '\n';
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
    const Battery& mBattery; // Referenca na objekt baterije

public:
    // Povezuje objekt robota s predanim objektom baterije
    MobileRobot(const Battery& refBattery)
        : mBattery{refBattery}
    {
        cout << "MobileRobot: adresa objekta Battery =          " << &mBattery 
             << '\n';
    }

    // Ispisuje napunjenost preko reference
    void print_battery_charge() const
    {
        cout << "Napunjenost baterije: "
             << mBattery.get_charge_percent() << " %\n";
    }
};

/* ============================================================
                              main()
   ============================================================ */

// Uspoređuje valjanu referencu i pristup visećoj referenci
int main()
{
#ifdef DEMONSTRATE_UB
    // Privremeni objekt Battery uništava se na kraju ove naredbe
    MobileRobot objRobot{Battery{85}};
#else
    Battery objBattery{85};
    MobileRobot objRobot{objBattery};
#endif

    // Robot još postoji, ali u DEMONSTRATE_UB referenca je viseća
    cout << "Nakon inicijalizacije objekta MobileRobot\n";
    objRobot.print_battery_charge();
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
KONZOLNI ISPIS — ISPRAVNO KORISTENJE
Battery: tijelo konstruktora, adresa objekta = 0x75081ffe2c
MobileRobot: adresa objekta Battery =          0x75081ffe2c
Nakon inicijalizacije objekta MobileRobot
Napunjenost baterije: 85 %
Battery: tijelo destruktora, adresa objekta =  0x75081ffe2c

KONZOLNI ISPIS — NAMJERNO IZAZVANO UB PONASANJE
Battery: tijelo konstruktora, adresa objekta = 0x49095ff66c
MobileRobot: adresa objekta Battery =          0x49095ff66c
Battery: tijelo destruktora, adresa objekta =  0x49095ff66c
Nakon inicijalizacije objekta MobileRobot
Napunjenost baterije: 85 %
*/