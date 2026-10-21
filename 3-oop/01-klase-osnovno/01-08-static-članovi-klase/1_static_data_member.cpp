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

    objChannel1.print_state();
    objChannel2.print_state();

    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
PWM kanal: 1, radni ciklus: 25 %, frekvencija: 1000 Hz
PWM kanal: 2, radni ciklus: 75 %, frekvencija: 1000 Hz
*/
