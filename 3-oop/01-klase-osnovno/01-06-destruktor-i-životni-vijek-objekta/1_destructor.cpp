#include <iostream>

using std::cout;

/* ============================================================
                         klasa AdcChannel
   ============================================================ */

class AdcChannel
{
private:
    int mChannel; // Redni broj ADC kanala

public:
    // Inicijalizira ADC kanal pri stvaranju objekta
    AdcChannel(int channel);

    // Ispisuje poruku pri završetku životnog vijeka objekta
    ~AdcChannel();

    // Ispisuje redni broj kanala
    void print_channel();
};
// ————————————————————————————————————————————————————————————

// Inicijalizira kanal i označava početak životnog vijeka objekta
AdcChannel::AdcChannel(int channel)
    : mChannel{channel}
{
    cout << "Konstruktor: ADC kanal " << mChannel << '\n';
}
// ————————————————————————————————————————————————————————————

// Ispisuje poruku pri završetku životnog vijeka objekta
AdcChannel::~AdcChannel()
{
    cout << "Destruktor: ADC kanal " << mChannel << '\n';
}
// ————————————————————————————————————————————————————————————

// Ispisuje redni broj kanala
void AdcChannel::print_channel()
{
    cout << "Aktivni ADC kanal: " << mChannel << '\n';
}

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    AdcChannel objChannel{2};
    objChannel.print_channel();
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */
   
/*
Konstruktor: ADC kanal 2
Aktivni ADC kanal: 2
Destruktor: ADC kanal 2
*/