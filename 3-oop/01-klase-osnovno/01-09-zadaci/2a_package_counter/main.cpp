#include <iostream>
using std::cout;

/* ============================================================
                        klasa PackageCounter
   ============================================================ */

class PackageCounter
{
private:
    const int kmSmallHeight;      // Granica visine malog paketa u mm
    int mSmallCount{0};           // Broj evidentiranih malih paketa
    int mLargeCount{0};           // Broj evidentiranih velikih paketa

public:
    // Postavlja granicu za razlikovanje malih i velikih paketa
    PackageCounter(int smallHeight)
        : kmSmallHeight{smallHeight}
    {
    }

    // Razvrstava jedno očitanje visine i povećava odgovarajući brojač
    void record_package(int height)
    {
        if (height <= kmSmallHeight)
        {
            ++mSmallCount;
        }
        else
        {
            ++mLargeCount;
        }
    }

    // Vraća broj evidentiranih malih paketa
    int get_small_count() const
    {
        return mSmallCount;
    }

    // Vraća broj evidentiranih velikih paketa
    int get_large_count() const
    {
        return mLargeCount;
    }

    // Vraća ukupan broj evidentiranih paketa
    int get_total_count() const
    {
        return mSmallCount + mLargeCount;
    }
};

/* ============================================================
                              main()
   ============================================================ */

// Obrađuje izmjerene visine paketa na jednoj pokretnoj traci
int main()
{
    PackageCounter objCounter{120}; // Paketi visine do 120 mm smatraju se malima

    // Svaki element predstavlja visinu jednoga paketa u milimetrima
    int packageList[]{90, 160, 110, 140, 85, 120};

    for (int height : packageList)
    {
        objCounter.record_package(height);
    }

    cout << "Mali paketi:   " << objCounter.get_small_count() << '\n';
    cout << "Veliki paketi: " << objCounter.get_large_count() << '\n';
    cout << "Ukupno:        " << objCounter.get_total_count() << '\n';

    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Mali paketi:   4
Veliki paketi: 2
Ukupno:        6
*/
