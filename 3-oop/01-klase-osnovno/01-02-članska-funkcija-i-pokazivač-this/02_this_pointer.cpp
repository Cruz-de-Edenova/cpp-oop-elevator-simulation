#include <iostream>

using std::cout;

/* ============================================================
                klasa ControllerSignalSnapshot
   ============================================================ */

class ControllerSignalSnapshot
{
private:
    bool mUpButtonPressed;
    bool mDownButtonPressed;
    bool mUpLimitSwitchActive;
    bool mMotorStarter;
    bool mDownSolenoid;

public:
    void set_inputs(bool upPressed, bool downPressed, bool limitActive);
    void set_outputs(bool motorStarter, bool downSolenoid);
    void print_state();
    void print_snapshot();
    void print_this_address();
};
// ————————————————————————————————————————————————————————————

// Postavlja ulazne signale spremljene u ovom objektu
void ControllerSignalSnapshot::set_inputs(
    bool upPressed,
    bool downPressed,
    bool limitActive)
{
    this->mUpButtonPressed = upPressed;
    this->mDownButtonPressed = downPressed;
    this->mUpLimitSwitchActive = limitActive;
}
// ————————————————————————————————————————————————————————————

// Postavlja izlazne signale spremljene u ovom objektu
void ControllerSignalSnapshot::set_outputs(
    bool motorStarter,
    bool downSolenoid)
{
    this->mMotorStarter = motorStarter;
    this->mDownSolenoid = downSolenoid;
}
// ————————————————————————————————————————————————————————————

// Ispisuje stanje signala spremljenih u ovom objektu
void ControllerSignalSnapshot::print_state()
{
    cout << "UP tipka:          "
         << (this->mUpButtonPressed ? "pritisnuta" : "otpustena") << '\n';
    cout << "DOWN tipka:        "
         << (this->mDownButtonPressed ? "pritisnuta" : "otpustena") << '\n';
    cout << "Gornji prekidac:   "
         << (this->mUpLimitSwitchActive ? "aktivan" : "neaktivan") << '\n';
    cout << "Motor starter:     "
         << (this->mMotorStarter ? "ukljucen" : "iskljucen") << '\n';
    cout << "DOWN solenoid:     "
         << (this->mDownSolenoid ? "ukljucen" : "iskljucen") << '\n';
}
// ————————————————————————————————————————————————————————————

// Demonstrira poziv druge članske funkcije preko pokazivača this
void ControllerSignalSnapshot::print_snapshot()
{
    this->print_state();
}
// ————————————————————————————————————————————————————————————

// Ispisuje adresu objekta na koji pokazuje this
void ControllerSignalSnapshot::print_this_address()
{
    cout << "this:              " << this << '\n';
}

/* ============================================================
                           FUNKCIJE
   ============================================================ */

// Demonstrira dva objekta iste klase s različitim stanjima
void demonstrate_signal_snapshots()
{
    ControllerSignalSnapshot objRaiseSnapshot;
    ControllerSignalSnapshot objLowerSnapshot;

    objRaiseSnapshot.set_inputs(true, false, false);
    objRaiseSnapshot.set_outputs(true, false);

    objLowerSnapshot.set_inputs(false, true, false);
    objLowerSnapshot.set_outputs(false, true);

    cout << "Podizanje:\n";
    objRaiseSnapshot.print_snapshot();

    cout << "\nSpustanje:\n";
    objLowerSnapshot.print_snapshot();

    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Uspoređuje adresu objekta s vrijednošću pokazivača this
void demonstrate_this_address()
{
    ControllerSignalSnapshot objRaiseSnapshot;
    ControllerSignalSnapshot objLowerSnapshot;

    cout << "&objRaiseSnapshot: " << &objRaiseSnapshot << '\n';
    objRaiseSnapshot.print_this_address();

    cout << "&objLowerSnapshot: " << &objLowerSnapshot << '\n';
    objLowerSnapshot.print_this_address();
}

/* ============================================================
                           main()
   ============================================================ */

int main()
{
    demonstrate_signal_snapshots();
    demonstrate_this_address();
    return 0;
}

/* ============================================================
Podizanje:
UP tipka:          pritisnuta
DOWN tipka:        otpustena
Gornji prekidac:   neaktivan
Motor starter:     ukljucen
DOWN solenoid:     iskljucen

Spustanje:
UP tipka:          otpustena
DOWN tipka:        pritisnuta
Gornji prekidac:   neaktivan
Motor starter:     iskljucen
DOWN solenoid:     ukljucen
------------------------------
&objRaiseSnapshot: 0xa6cb3ff6eb
this:              0xa6cb3ff6eb
&objLowerSnapshot: 0xa6cb3ff6e6
this:              0xa6cb3ff6e6
*/
