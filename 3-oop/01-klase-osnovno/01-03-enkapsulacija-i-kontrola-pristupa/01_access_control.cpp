#include <iostream>

using std::cout;

/* ============================================================
                       klasa ControlButton
   ============================================================ */

class ControlButton
{
private:
    bool mPressed;

    void set_pressed(bool pressed);

public:
    void press();
    void release();
    bool is_pressed();
};

// Mijenja unutarnje stanje tipke unutar same klase
void ControlButton::set_pressed(bool pressed)
{
    mPressed = pressed;
}

// Postavlja tipku u pritisnuto stanje kroz javno sučelje klase
void ControlButton::press()
{
    set_pressed(true);
}

// Postavlja tipku u otpušteno stanje kroz javno sučelje klase
void ControlButton::release()
{
    set_pressed(false);
}

// Vraća trenutno stanje tipke kroz javno sučelje klase
bool ControlButton::is_pressed()
{
    return mPressed;
}

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    ControlButton objUpButton;

    objUpButton.press();

    cout << "UP tipka: "
         << (objUpButton.is_pressed() ? "pritisnuta" : "otpustena") << '\n';

    objUpButton.release();

    cout << "UP tipka: "
         << (objUpButton.is_pressed() ? "pritisnuta" : "otpustena") << '\n';

    // Pogreška: privatnom podatkovnom članu ne pristupamo izvana
    // objUpButton.mPressed = true;

    // Pogreška: privatnu člansku funkciju ne pozivamo izvana
    // objUpButton.set_pressed(true);

    return 0;
}

/* ============================================================
UP tipka: pritisnuta
UP tipka: otpustena
*/
