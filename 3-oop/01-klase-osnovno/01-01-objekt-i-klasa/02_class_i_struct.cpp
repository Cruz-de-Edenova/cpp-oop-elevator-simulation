#include <iomanip>
#include <iostream>

using std::cout;
using std::left;
using std::setw;

// ============================================================
struct ButtonState
{
    bool mPressed;
};

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
// Demonstrira razliku u pristupu članovima strukture i klase
void demonstrate_class_and_struct()
{
    ButtonState objState{false};
    ControlButton objButton;

    objState.mPressed = true;
    objButton.set_pressed(true);

    cout << left;
    cout << setw(12) << "Tip:" << "Stanje tipke:\n";
    cout << setw(12) << "struct" << (objState.mPressed ? "pritisnuta" : "otpustena")
         << '\n' << setw(12) << "class";
    objButton.print_state();
}

// ============================================================
int main()
{
    demonstrate_class_and_struct();
    return 0;
}

/* ============================================================
Tip:        Stanje tipke:
struct      pritisnuta
class       pritisnuta
*/
