#include "sample_buffer.h"
#include <iostream>
#include <iomanip>

using std::cout;
using std::right;
using std::setw;

/* ============================================================
                             Funkcije
   ============================================================ */

// Ispisuje redak tablice s podacima o spremniku
void print_samples(const SampleBuffer& refBuffer, const char bufferNumber,
                   const int channelNumber)
{
    cout << right << setw(8) << bufferNumber << setw(8) << channelNumber
         << setw(12) << refBuffer.get_capacity()
         << setw(15) << refBuffer.get_sample_count(channelNumber) << "    ";
         
    for (int i{0}; i < refBuffer.get_sample_count(channelNumber); ++i)
    {
        cout << setw(5) << refBuffer.get_sample(channelNumber, i);
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
        // Stvaranje prvog spremnika s dva kanala, svaki kapaciteta pet uzoraka
        SampleBuffer objBuffer1{2, 5};
        
        // Lista uzoraka namijenjena za kanal 0
        int sampleList[]{120, 512, 890};
    
        // Pohranjivanje uzoraka u kanal 0 prvog spremnika
        for (int sample : sampleList)
        {
            // Dodaje uzorak u kanal 0 ako ima slobodnog mjesta
            if (objBuffer1.add_sample(0, sample))
            {
                // Indeks posljednjeg spremljenog uzorka
                int index = objBuffer1.get_sample_count(0) - 1;
        
                cout << "Spremljen je uzorak s indeksom " << index
                    << " i iznosi " << objBuffer1.get_sample(0, index) << ".\n";
            }
            else
            {
                cout << "Uzorak " << sample 
                    << " nije pohranjen, jer je kanal 0 pun.\n";
            }
        }
        
        // Dodavanje uzoraka vrijednosti 250 i 750 u kanal 1 prvoga spremnika
        objBuffer1.add_sample(1, 250);
        objBuffer1.add_sample(1, 750);

        // Stvaranje drugoga spremnika dubokim kopiranjem prvoga
        SampleBuffer objBuffer2{objBuffer1};
        
        // Dodavanje uzoraka u prvi spremnik
        objBuffer1.add_sample(0, 222);
        objBuffer1.add_sample(1, 333);

        // Dodavanje uzoraka u drugi spremnik
        objBuffer2.add_sample(0, 111);
        objBuffer2.add_sample(1, 444);
        
        // Ispisuje zaglavlje tablice
        cout << "\n\n" << right << setw(8) << "Spremnik" << setw(8) << "Kanal"
             << setw(12) << "Kapacitet" << setw(15) << "Broj uzoraka"
             << "          Uzorci" << '\n';
        cout << "------------------------------------------------------------\n";
             
        print_samples(objBuffer1, '1', 0);
        print_samples(objBuffer1, '1', 1);
        print_samples(objBuffer2, '2', 0);
        print_samples(objBuffer2, '2', 1);
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


Spremnik   Kanal   Kapacitet   Broj uzoraka          Uzorci
------------------------------------------------------------
       1       0           5              4      120  512  890  222
       1       1           5              3      250  750  333
       2       0           5              4      120  512  890  111
       2       1           5              3      250  750  444
*/