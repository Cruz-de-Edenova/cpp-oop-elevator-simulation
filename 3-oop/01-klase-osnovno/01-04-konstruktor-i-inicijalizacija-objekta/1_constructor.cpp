#include <iostream>

using std::cout;

/* ============================================================
                    klasa PlatformPosition
   ============================================================ */

class PlatformPosition
{
private:
    double mHeightCm;   // Trenutno spremljena visina platforme

    // Provjerava pripada li visina dopuštenom rasponu platforme
    bool is_height_valid(double heightCm);

public:
    // Inicijalizira platformu na minimalnu visinu
    PlatformPosition();

    // Mijenja visinu samo ako nova vrijednost pripada dopuštenom rasponu
    bool set_height(double heightCm);

    // Vraća trenutno spremljenu visinu platforme
    double get_height();
};
// ————————————————————————————————————————————————————————————

// Inicijalizira platformu na minimalnu visinu
PlatformPosition::PlatformPosition()
    : mHeightCm{30.0}
{
}
// ————————————————————————————————————————————————————————————

// Provjerava pripada li visina dopuštenom rasponu platforme
bool PlatformPosition::is_height_valid(double heightCm)
{
    const double minHeightCm{30.0};
    const double maxHeightCm{137.0};

    return (heightCm >= minHeightCm) && (heightCm <= maxHeightCm);
}
// ————————————————————————————————————————————————————————————

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
// ————————————————————————————————————————————————————————————

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
    PlatformPosition objPlatformPosition{};

    cout << "Pocetna visina: "
         << objPlatformPosition.get_height() << " cm\n";

    if (objPlatformPosition.set_height(100.0))
    {
        cout << "Nova visina: "
             << objPlatformPosition.get_height() << " cm\n";
    }

    return 0;
}

/* ============================================================
Pocetna visina: 30 cm
Nova visina: 100 cm
*/
