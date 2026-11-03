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
    
    // Resetira brojače paketa
    void reset_record()
    {
        mSmallCount = 0;
        mLargeCount = 0;
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
// ————————————————————————————————————————————————————————————

// Evidentiranje paketa pojedine trake
void count_packages(PackageCounter& refCounter,
                    const int* ptrPackageList, int packageCount)
{
    for (int i = 0; i < packageCount; ++i)
    {
        refCounter.record_package(ptrPackageList[i]);
    }
}
// ————————————————————————————————————————————————————————————

// Ispisuje rezultate evidencije paketa za obje trake
void print_table(const PackageCounter& refCounterA,
                 const PackageCounter& refCounterB)
{
    // Zaglavlje tablice
    cout << left << setw(8) << "Traka"
         << right << setw(12) << "Prag [mm]" << setw(10) << "Mali"
         << setw(10) << "Veliki" << setw(10) << "Ukupno" << '\n';
    cout << "--------------------------------------------------\n";

    print_results(refCounterA, 'A');
    print_results(refCounterB, 'B');
}    

/* ============================================================
                              main()
   ============================================================ */

// Obrađuje izmjerene visine paketa na dvije pokretne trake
int main()
{
    PackageCounter objCounterA{120}; // Granična visina za traku A
    PackageCounter objCounterB{140}; // Granična visina za traku B     

    cout << "***************************\n";
    cout << "Evidencija 1. serije paketa\n";
    cout << "***************************\n";
    
    // Lista visina paketa 1. serije (ista je za obje trake)
    int packageList1[]{90, 160, 110, 140, 85, 120};
    
    // Evidentiranje paketa pojedine trake
    count_packages(objCounterA, packageList1, 6);
    count_packages(objCounterB, packageList1, 6);
    
    print_table(objCounterA, objCounterB);

    cout << "\n********************************\n";
    cout << "Ponistavanje vrijednosti brojaca\n";
    cout << "********************************\n";
    
    objCounterA.reset_record();
    objCounterB.reset_record();
    
    print_table(objCounterA, objCounterB);
    
    cout << "\n***************************\n";
    cout << "Evidencija 2. serije paketa\n";
    cout << "***************************\n";
    
    // Lista visina paketa 2. serije
    int packageList2A[]{90, 120, 80, 150};
    int packageList2B[]{140, 160, 130, 170};
    
    // Evidentiranje paketa pojedine trake
    count_packages(objCounterA, packageList2A, 4);
    count_packages(objCounterB, packageList2B, 4);
    
    print_table(objCounterA, objCounterB);
    
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
***************************
Evidencija 1. serije paketa
***************************
Traka      Prag [mm]      Mali    Veliki    Ukupno
--------------------------------------------------
A                120         4         2         6
B                140         5         1         6

********************************
Ponistavanje vrijednosti brojaca
********************************
Traka      Prag [mm]      Mali    Veliki    Ukupno
--------------------------------------------------
A                120         0         0         0
B                140         0         0         0

***************************
Evidencija 2. serije paketa
***************************
Traka      Prag [mm]      Mali    Veliki    Ukupno
--------------------------------------------------
A                120         3         1         4
B                140         2         2         4
*/
