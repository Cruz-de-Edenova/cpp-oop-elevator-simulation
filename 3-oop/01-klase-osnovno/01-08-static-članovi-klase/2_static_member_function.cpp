#include <iostream>

using std::cout;

/* ============================================================
                         klasa PwmChannel
   ============================================================ */

class PwmChannel
{
private:
    int mChannel;             // Broj PWM kanala
    int mDutyCyclePercent;    // Radni ciklus izražen u postocima
    static int mFrequencyHz;  // Zajednička PWM frekvencija

public:
    // Inicijalizira broj kanala i njegov radni ciklus
    PwmChannel(int channel, int dutyCyclePercent);

    // Vraća zajedničku PWM frekvenciju
    static int get_frequency_hz();

    // Postavlja zajedničku PWM frekvenciju
    static void set_frequency_hz(int frequencyHz);

    // Ispisuje stanje kanala i zajedničku PWM frekvenciju
    void print_state() const;
};
// ————————————————————————————————————————————————————————————

// Definira i inicijalizira static podatkovni član klase
int PwmChannel::mFrequencyHz{1000};
// ————————————————————————————————————————————————————————————

// Inicijalizira broj kanala i njegov radni ciklus
PwmChannel::PwmChannel(int channel, int dutyCyclePercent)
    : mChannel{channel}, mDutyCyclePercent{dutyCyclePercent}
{
}
// ————————————————————————————————————————————————————————————

// Vraća zajedničku PWM frekvenciju
int PwmChannel::get_frequency_hz()
{
    // Pogreška: static članska funkcija nema pokazivač this
    // cout << this << '\n';

    // Pogreška: bez objekta se ne može pristupiti nestatičkom podatkovnom članu
    // return mDutyCyclePercent;

    return mFrequencyHz;
}
// ————————————————————————————————————————————————————————————

// Postavlja zajedničku PWM frekvenciju
void PwmChannel::set_frequency_hz(int frequencyHz)
{
    mFrequencyHz = frequencyHz;
}
// ————————————————————————————————————————————————————————————

// Ispisuje stanje kanala i zajedničku PWM frekvenciju
void PwmChannel::print_state() const
{
    cout << "PWM kanal: " << mChannel
         << ", radni ciklus: " << mDutyCyclePercent << " %"
         << ", frekvencija: " << mFrequencyHz << " Hz\n";
}

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    PwmChannel objChannel1{1, 25};
    PwmChannel objChannel2{2, 75};

    cout << "Pocetna frekvencija: "
         << PwmChannel::get_frequency_hz() << " Hz\n";

    objChannel1.print_state();
    objChannel2.print_state();

    PwmChannel::set_frequency_hz(2000);

    cout << "Nova frekvencija: "
         << PwmChannel::get_frequency_hz() << " Hz\n";

    objChannel1.print_state();
    objChannel2.print_state();

    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Pocetna frekvencija: 1000 Hz
PWM kanal: 1, radni ciklus: 25 %, frekvencija: 1000 Hz
PWM kanal: 2, radni ciklus: 75 %, frekvencija: 1000 Hz
Nova frekvencija: 2000 Hz
PWM kanal: 1, radni ciklus: 25 %, frekvencija: 2000 Hz
PWM kanal: 2, radni ciklus: 75 %, frekvencija: 2000 Hz
*/
