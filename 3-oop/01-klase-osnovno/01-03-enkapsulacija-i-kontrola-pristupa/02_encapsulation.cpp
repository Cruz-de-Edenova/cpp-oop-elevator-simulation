#include <iostream>

using std::cout;

/* ============================================================
                    klasa PlatformPosition
   ============================================================ */

class PlatformPosition
{
private:
    double mHeightCm;

    bool is_height_valid(double heightCm);

public:
    bool set_height(double heightCm);
    double get_height();
};

// Provjerava pripada li visina dopuštenom rasponu platforme
bool PlatformPosition::is_height_valid(double heightCm)
{
    const double minHeightCm{30.0};
    const double maxHeightCm{137.0};

    return (heightCm >= minHeightCm) && (heightCm <= maxHeightCm);
}

// Mijenja visinu samo ako nova vrijednost pripada dopuštenom rasponu
bool PlatformPosition::set_height(double heightCm)
{
    if (!is_height_valid(heightCm))
    {
        return false;
    }

    mHeightCm = heightCm;
    return true;
}

// Vraća trenutno spremljenu visinu platforme
double PlatformPosition::get_height()
{
    return mHeightCm;
}

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    PlatformPosition objPlatformPosition;

    // Objekt najprije dovodimo u valjano stanje
    objPlatformPosition.set_height(30.0);

    cout << "Pocetna visina: "
         << objPlatformPosition.get_height() << " cm\n";

    if (objPlatformPosition.set_height(100.0))
    {
        cout << "Nova visina: "
             << objPlatformPosition.get_height() << " cm\n";
    }

    if (!objPlatformPosition.set_height(150.0))
    {
        cout << "Visina 150 cm nije dopustena\n";
    }

    cout << "Spremljena visina nakon odbijenog zahtjeva: "
         << objPlatformPosition.get_height() << " cm\n";

    // Pogreška: provjera valjanosti dio je privatne implementacije klase
    // objPlatformPosition.is_height_valid(50.0);

    return 0;
}

/* ============================================================
Pocetna visina: 30 cm
Nova visina: 100 cm
Visina 150 cm nije dopustena
Spremljena visina nakon odbijenog zahtjeva: 100 cm
*/
