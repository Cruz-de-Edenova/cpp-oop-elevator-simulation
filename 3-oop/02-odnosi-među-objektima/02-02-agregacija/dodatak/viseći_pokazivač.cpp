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
        cout << "Battery: tijelo konstruktora, adresa objekta =   " << this << '\n';
    }

    // Prikazuje završetak životnog vijeka objekta
    ~Battery()
    {
        cout << "Battery: tijelo destruktora, adresa objekta =    " << this << '\n';
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
    const Battery* mPtrBattery; // Nevlasnički pokazivač na bateriju

public:
    // Inicijalizira objekt bez povezane baterije
    MobileRobot()
        : mPtrBattery{nullptr}
    {
    }

    // Sprema adresu postojećeg objekta ili nullptr
    void set_battery(const Battery* ptrBattery)
    {
        mPtrBattery = ptrBattery;
        cout << "MobileRobot: vrijednost pokazivaca mPtrBattery = " 
             << mPtrBattery << '\n';
    }

    // Ispisuje napunjenost ili poruku ako veza nije postavljena
    void print_battery_charge() const
    {
        if (mPtrBattery != nullptr)
        {
            cout << "Napunjenost baterije: "
                 << mPtrBattery->get_charge_percent() << " %\n";
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

// Uspoređuje uklanjanje veze i pristup preko visećeg pokazivača
int main()
{
    MobileRobot objRobot{};

    {
        Battery objBattery{85};
        objRobot.set_battery(&objBattery);
        objRobot.print_battery_charge();
    }

    cout << "Nakon izlaska iz bloka\n";

#ifdef DEMONSTRATE_UB
    // Pokazivač je viseći jer je objekt Battery već uništen
    objRobot.print_battery_charge();
#else
    // Sprječava pristup uništenom objektu Battery
    objRobot.set_battery(nullptr);
    objRobot.print_battery_charge();
#endif

    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
ISPRAVNO KORIŠTENJE
Battery: tijelo konstruktora, adresa objekta =   0x17efbff9a4
MobileRobot: vrijednost pokazivaca mPtrBattery = 0x17efbff9a4
Napunjenost baterije: 85 %
Battery: tijelo destruktora, adresa objekta =    0x17efbff9a4
Nakon izlaska iz bloka
MobileRobot: vrijednost pokazivaca mPtrBattery = 0
Baterija nije povezana
-----------------------------------------------------------
NAMJERNO IZAZVANO UB PONAŠANJE
Battery: tijelo konstruktora, adresa objekta =   0x8dd31ff684
MobileRobot: vrijednost pokazivaca mPtrBattery = 0x8dd31ff684
Napunjenost baterije: 85 %
Battery: tijelo destruktora, adresa objekta =    0x8dd31ff684
Nakon izlaska iz bloka
Napunjenost baterije: 85 %
*/