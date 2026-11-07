#include <iostream>
#include <iomanip>

using std::cout;
using std::right;
using std::setw;

/* ============================================================
                        klasa SampleBuffer
   ============================================================ */

class SampleBuffer
{
private:
    int* mPtrSamples;       // Pokazivač na dinamički alocirano polje
    int mCapacity;          // Maksimalan broj uzoraka koje spremnik može pohraniti
    int mSampleCount{0};    // Broj trenutno spremljenih uzoraka

public:
    // Alocira polje pomoću new[]
    SampleBuffer(int capacity)
        : mCapacity{capacity}
    {
        mPtrSamples = new int[mCapacity];
    }
    
    // Stvara neovisnu kopiju spremnika
    SampleBuffer(const SampleBuffer& refSource)
        : mPtrSamples{new int[refSource.mCapacity]},
          mCapacity{refSource.mCapacity},
          mSampleCount{refSource.mSampleCount}
    {
        for (int i{0}; i < mSampleCount; ++i)
        {
            mPtrSamples[i] = refSource.mPtrSamples[i];
        }
    }
    
    // Oslobađa polje pomoću delete[]
    ~SampleBuffer()
    {
        delete[] mPtrSamples;
    }

    // Dodaje uzorak ako ima slobodnog mjesta
    bool add_sample(int sample)
    {
        if (mSampleCount < mCapacity)
        {
            mPtrSamples[mSampleCount] = sample;
            ++mSampleCount;
            return true;
        }
    
        return false;
    }

    // Vraća kapacitet spremnika
    int get_capacity() const
    {
        return mCapacity;
    }
    
    // Vraća broj spremljenih uzoraka
    int get_sample_count() const
    {
        return mSampleCount;
    }
    
    // Vraća spremljeni uzorak na zadanom indeksu spremnika
    int get_sample(int index) const
    {
        return mPtrSamples[index];
    }
};

/* ============================================================
                             Funkcije
   ============================================================ */

// Ispisuje redak tablice s podacima o spremniku
void print_samples(const SampleBuffer& refBuffer, const char bufferNumber)
{
    cout << right << setw(8) << bufferNumber
         << setw(12) << refBuffer.get_capacity()
         << setw(15) << refBuffer.get_sample_count() << "    ";
         
    for (int i{0}; i < refBuffer.get_sample_count(); ++i)
    {
        cout << setw(5) << refBuffer.get_sample(i);
    }
    
    cout << '\n';
}
         
/* ============================================================
                              main()
   ============================================================ */

int main()
{
    // Zasebni blok radi demonstracije automatskog pozivanja destruktora
    {
        // Stvaranje prvog spremnika s kapacitetom od 5 uzoraka
        SampleBuffer objBuffer1{5};
        
        // Lista uzoraka
        int sampleList[]{120, 512, 890};
    
        // Pohranjivanje uzoraka u spremnik
        for (int sample : sampleList)
        {
            // Dodaje uzorak ako ima slobodnog mjesta u spremniku
            if (objBuffer1.add_sample(sample))
            {
                // Indeks spremnika počinje od nule
                int index = objBuffer1.get_sample_count() - 1;
        
                cout << "Spremljen je uzorak s indeksom " << index
                    << " i iznosi " << objBuffer1.get_sample(index) << ".\n";
            }
            else
            {
                cout << "Uzorak " << sample 
                    << " nije pohranjen, jer je spremnik pun.\n";
            }
        }
        
        // Stvaranje drugoga spremnika dubokim kopiranjem prvoga
        SampleBuffer objBuffer2{objBuffer1};
        
        // Dodavanje uzorka vrijednosti 222 u prvi spremnik
        objBuffer1.add_sample(222);
        
        // Dodavanje uzorka vrijednosti 111 u drugi spremnik
        objBuffer2.add_sample(111);
        
        // Ispisuje zaglavlje tablice
        cout << "\n\n" << right << setw(8) << "Spremnik"
             << setw(12) << "Kapacitet" << setw(15) << "Broj uzoraka"
             << "          Uzorci" << '\n';
        cout << "------------------------------------------------------------\n";
             
        print_samples(objBuffer1, '1');
        print_samples(objBuffer2, '2');
    }
    // Ovdje su oba destruktora već izvršena
    
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Spremljen je uzorak s indeksom 0 i iznosi 120.
Spremljen je uzorak s indeksom 1 i iznosi 512.
Spremljen je uzorak s indeksom 2 i iznosi 890.


Spremnik   Kapacitet   Broj uzoraka          Uzorci
------------------------------------------------------------
       1           5              4      120  512  890  222
       2           5              4      120  512  890  111
*/