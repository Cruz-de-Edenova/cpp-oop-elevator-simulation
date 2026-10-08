#include <iostream>

using std::cout;

/* ============================================================
                       klasa ControlPanel
   ============================================================ */

class ControlPanel
{
private:
    bool mUpButtonPressed;
    bool mDownButtonPressed;

public:
    void set_up_button(bool pressed);
    void set_down_button(bool pressed);
    void print_state();
};

// Postavlja simulirano stanje UP tipke
void ControlPanel::set_up_button(bool pressed)
{
    mUpButtonPressed = pressed;
}

// Postavlja simulirano stanje DOWN tipke
void ControlPanel::set_down_button(bool pressed)
{
    mDownButtonPressed = pressed;
}

// Ispisuje simulirana stanja upravljačkih tipki
void ControlPanel::print_state()
{
    cout << "UP tipka:   "
         << (mUpButtonPressed ? "pritisnuta" : "otpustena") << '\n';
    cout << "DOWN tipka: "
         << (mDownButtonPressed ? "pritisnuta" : "otpustena") << '\n';
}

/* ============================================================
                    klasa ControllerOutputs
   ============================================================ */

class ControllerOutputs
{
private:
    bool mMotorStarter;
    bool mDownSolenoid;

public:
    void set_motor_starter(bool energized);
    void set_down_solenoid(bool energized);
    void print_state();
};

// Postavlja izlazni signal za sklopnik motora
void ControllerOutputs::set_motor_starter(bool energized)
{
    mMotorStarter = energized;
}

// Postavlja izlazni signal za DOWN solenoid
void ControllerOutputs::set_down_solenoid(bool energized)
{
    mDownSolenoid = energized;
}

// Ispisuje simulirana stanja izlaznih signala
void ControllerOutputs::print_state()
{
    cout << "Motor starter: "
         << (mMotorStarter ? "ukljucen" : "iskljucen") << '\n';
    cout << "DOWN solenoid: "
         << (mDownSolenoid ? "ukljucen" : "iskljucen") << '\n';
}

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    // Demonstracija članskih funkcija klase ControlPanel
    {
        ControlPanel objControlPanel;
    
        objControlPanel.set_up_button(true);
        objControlPanel.set_down_button(false);
        objControlPanel.print_state();
    }
    cout << "------------------------------\n";

    // Demonstracija članskih funkcija klase ControllerOutputs
    {
        ControllerOutputs objControllerOutputs;
    
        objControllerOutputs.set_motor_starter(true);
        objControllerOutputs.set_down_solenoid(false);
        objControllerOutputs.print_state();
    }
    
    return 0;
}

/* ============================================================
UP tipka:   pritisnuta
DOWN tipka: otpustena
------------------------------
Motor starter: ukljucen
DOWN solenoid: iskljucen
*/
