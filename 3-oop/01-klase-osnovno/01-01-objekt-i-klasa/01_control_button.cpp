#include <iostream>

using std::cout;

// ============================================================
class ControlButton
{
private:
    bool mPressed;

public:
    // Mijenja simulirano stanje tipke
    void set_pressed(bool pressed)
    {
        mPressed = pressed;
    }

    // Ispisuje trenutačno simulirano stanje tipke
    void print_state()
    {
        cout << (mPressed ? "pritisnuta" : "otpustena") << '\n';
    }
};

// ============================================================
// Demonstrira stanje jednog objekta
void demonstrate_single_object()
{
    ControlButton objUpButton;
    objUpButton.set_pressed(true);

    cout << "UP tipka: ";
    objUpButton.print_state();
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira da dva objekta iste klase imaju zasebna stanja
void demonstrate_multiple_objects()
{
    ControlButton objUpButton;
    ControlButton objDownButton;

    objUpButton.set_pressed(true);
    objDownButton.set_pressed(false);

    cout << "UP tipka: ";
    objUpButton.print_state();

    cout << "DOWN tipka: ";
    objDownButton.print_state();
}

// ============================================================
int main()
{
    demonstrate_single_object();
    demonstrate_multiple_objects();
    return 0;
}

/* ============================================================
UP tipka: pritisnuta
------------------------------
UP tipka: pritisnuta
DOWN tipka: otpustena
*/