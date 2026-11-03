#include <iostream>
#include <iomanip>
using std::cout;
using std::setw;
using std::left;
using std::right;

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
    
    // Vraća graničnu visinu
    int get_small_height() const
    {
        return kmSmallHeight;
    }
};

/* ============================================================
                           Funkcije
   ============================================================ */

// Ispisuje rezultat evidencije paketa pojedine trake
void print_results(const PackageCounter& refCounter, char conveyorName)
{
    cout << left << setw(8) << conveyorName
         << right << setw(12) << refCounter.get_small_height()
         << setw(10) << refCounter.get_small_count()                        
         << setw(10) << refCounter.get_large_count()
         << setw(10) << refCounter.get_total_count() << '\n';
}

/* ============================================================
                              main()
   ============================================================ */

// Obrađuje izmjerene visine paketa na dvije pokretne trake
int main()
{
    PackageCounter objCounterA{120}; // Granična visina za traku A
    PackageCounter objCounterB{140}; // Granična visina za traku B     

    // Svaki element predstavlja visinu jednoga paketa u milimetrima
    int packageList[]{90, 160, 110, 140, 85, 120};

    // Brojenje malih i velikih paketa
    for (int height : packageList)
    {
        objCounterA.record_package(height);
        objCounterB.record_package(height);
    }

    // Zaglavlje tablice
    cout << left << setw(8) << "Traka"
         << right << setw(12) << "Prag [mm]" << setw(10) << "Mali"
         << setw(10) << "Veliki" << setw(10) << "Ukupno" << '\n';
    cout << "--------------------------------------------------\n";

    // Ispisuje rezultate brojanja paketa
    print_results(objCounterA, 'A');
    print_results(objCounterB, 'B');
    
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Traka      Prag [mm]      Mali    Veliki    Ukupno
--------------------------------------------------
A                120         4         2         6
B                140         5         1         6
*/
