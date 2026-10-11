#include <iostream>

using std::cout;

/* ============================================================
                       klasa ControlButton
   ============================================================ */

class ControlButton
{
private:
    bool mPressed;   // Stanje tipke

public:
    // Inicijalizira tipku u otpušteno stanje
    ControlButton();

    // Inicijalizira tipku proslijeđenim početnim stanjem
    ControlButton(bool pressed);

    // Vraća trenutno stanje tipke
    bool is_pressed();
};
// ————————————————————————————————————————————————————————————

// Inicijalizira tipku u otpušteno stanje
ControlButton::ControlButton()
    : mPressed{false}
{
}
// ————————————————————————————————————————————————————————————

// Inicijalizira tipku proslijeđenom vrijednošću
ControlButton::ControlButton(bool pressed)
    : mPressed{pressed}
{
}
// ————————————————————————————————————————————————————————————

// Vraća trenutno stanje tipke
bool ControlButton::is_pressed()
{
    return mPressed;
}

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    ControlButton objUpButton{};
    ControlButton objDownButton{true};

    cout << "UP tipka: "
         << (objUpButton.is_pressed() ? "pritisnuta" : "otpustena") << '\n';
    cout << "DOWN tipka: "
         << (objDownButton.is_pressed() ? "pritisnuta" : "otpustena") << '\n';

    return 0;
}

/* ============================================================
UP tipka: otpustena
DOWN tipka: pritisnuta
*/
