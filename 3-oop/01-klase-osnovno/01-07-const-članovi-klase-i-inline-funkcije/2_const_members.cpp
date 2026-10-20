#include <iostream>

using std::cout;

/* ============================================================
                         klasa AdcChannel
   ============================================================ */

class AdcChannel
{
private:
    const int mChannel; // Broj kanala koji se nakon konstrukcije ne mijenja
    int mRawValue;      // Trenutno spremljena "sirova" ADC vrijednost

public:
    // Inicijalizira nepromjenjivi broj kanala i početnu ADC vrijednost
    AdcChannel(int channel, int rawValue);

    // Vraća broj ADC kanala bez promjene objekta
    int get_channel() const;

    // Vraća spremljenu ADC vrijednost bez promjene objekta
    int get_raw_value() const;

    // Postavlja novu ADC vrijednost
    void set_raw_value(int rawValue);
};
// ————————————————————————————————————————————————————————————

// Inicijalizira nepromjenjivi broj kanala i početnu ADC vrijednost
AdcChannel::AdcChannel(int channel, int rawValue)
    : mChannel{channel}, mRawValue{rawValue}
{
}
// ————————————————————————————————————————————————————————————

// Vraća broj ADC kanala bez promjene objekta
int AdcChannel::get_channel() const
{
    return mChannel;
}
// ————————————————————————————————————————————————————————————

// Vraća spremljenu ADC vrijednost bez promjene objekta
int AdcChannel::get_raw_value() const
{
    // Pogreška: const članska funkcija ne može mijenjati obični podatkovni član
    // mRawValue = 0;

    /* const članska funkcija ne može pozvati ne-const člansku funkciju nad
    istim objektom */
    // set_raw_value(0);

    return mRawValue;
}
// ————————————————————————————————————————————————————————————

// Postavlja novu ADC vrijednost
void AdcChannel::set_raw_value(int rawValue)
{
    // Pogreška: const podatkovni član ne može se mijenjati
    // mChannel = 3;

    mRawValue = rawValue;
}

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    AdcChannel objChannel{2, 512};
    const AdcChannel objReferenceChannel{7, 1023};

    cout << "Kanal " << objChannel.get_channel()
         << ": " << objChannel.get_raw_value() << '\n';

    objChannel.set_raw_value(640);

    cout << "Kanal " << objChannel.get_channel()
         << ": " << objChannel.get_raw_value() << '\n';

    cout << "Referentni kanal " << objReferenceChannel.get_channel()
         << ": " << objReferenceChannel.get_raw_value() << '\n';

    // Pogreška: const objekt ne može pozvati ne-const člansku funkciju
    // objReferenceChannel.set_raw_value(900);

    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Kanal 2: 512
Kanal 2: 640
Referentni kanal 7: 1023
*/