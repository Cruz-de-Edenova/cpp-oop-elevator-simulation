#include <iostream>

using std::cout;

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
                              main()
   ============================================================ */

int main()
{
    // Zasebni blok radi demonstracije automatskog pozivanja destruktora
    {
        // Stvaranje spremnika s kapacitetom od 5 uzoraka
        SampleBuffer objBuffer{5};
        
        // Lista uzoraka
        int sampleList[]{120, 512, 890, 0, 1023, 700};
    
        // Pohranjivanje uzoraka u spremnik
        for (int sample : sampleList)
        {
            // Dodaje uzorak ako ima slobodnog mjesta u spremniku
            if (objBuffer.add_sample(sample))
            {
                // Indeks spremnika počinje od nule
                int index = objBuffer.get_sample_count() - 1;
        
                cout << "Spremljen je uzorak s indeksom " << index
                    << " i iznosi " << objBuffer.get_sample(index) << ".\n";
            }
            else
            {
                cout << "Uzorak " << sample 
                    << " nije pohranjen, jer je spremnik pun.\n";
            }
        }
            
        // Ispis kapaciteta i ukupnog broja spremljenih uzoraka    
        cout << "\nKapacitet spremnika: " << objBuffer.get_capacity() << '\n';
        cout << "Broj spremljenih uzoraka: " << objBuffer.get_sample_count() << '\n';
    }
    // Ovdje je destruktor već izvršen
    
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Spremljen je uzorak s indeksom 0 i iznosi 120.
Spremljen je uzorak s indeksom 1 i iznosi 512.
Spremljen je uzorak s indeksom 2 i iznosi 890.
Spremljen je uzorak s indeksom 3 i iznosi 0.
Spremljen je uzorak s indeksom 4 i iznosi 1023.
Uzorak 700 nije pohranjen, jer je spremnik pun.

Kapacitet spremnika: 5
Broj spremljenih uzoraka: 5
*/
