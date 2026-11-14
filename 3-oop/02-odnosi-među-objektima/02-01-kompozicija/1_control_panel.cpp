#include <iostream>

using std::cout;

/* ============================================================
                      klasa ControlButton
   ============================================================ */

class ControlButton
{
private:
    bool mPressed; // Trenutno stanje tipke

public:
    // Inicijalizira tipku u otpuštenom stanju
    ControlButton()
        : mPressed{false}
    {
    }

    // Postavlja stanje tipke
    void set_pressed(bool pressed)
    {
        mPressed = pressed;
    }

    // Vraća stanje tipke
    bool get_pressed() const
    {
        return mPressed;
    }
};

/* ============================================================
                       klasa ControlPanel
   ============================================================ */

class ControlPanel
{
private:
    ControlButton mUpButton;   // UP tipka
    ControlButton mDownButton; // DOWN tipka

public:
    // Inicijalizira obje tipke defaultnim konstruktorom klase ControlButton
    ControlPanel()
        : mUpButton{}, mDownButton{}
    {
    }

    // Postavlja stanje UP tipke
    void set_up_pressed(bool pressed)
    {
        mUpButton.set_pressed(pressed);
    }

    // Postavlja stanje DOWN tipke
    void set_down_pressed(bool pressed)
    {
        mDownButton.set_pressed(pressed);
    }

    // Vraća stanje UP tipke
    bool get_up_pressed() const
    {
        return mUpButton.get_pressed();
    }

    // Vraća stanje DOWN tipke
    bool get_down_pressed() const
    {
        return mDownButton.get_pressed();
    }
};

/* ============================================================
                          FUNKCIJE
   ============================================================ */

// Ispisuje stanja tipki na upravljačkoj ploči
void print_panel_state(const ControlPanel& refPanel)
{
    cout << "UP:   " << (refPanel.get_up_pressed() ? "pritisnuta" : "otpustena");
    cout << '\n';
    cout << "DOWN: " << (refPanel.get_down_pressed() ? "pritisnuta" : "otpustena");
    cout << '\n';
}
// ————————————————————————————————————————————————————————————

// Pokazuje promjenu stanja tipke preko objekta upravljačke ploče
void demonstrate_composition()
{
    ControlPanel objPanel{};

    cout << "Pocetno stanje:\n";
    print_panel_state(objPanel);
    cout << "------------------------------" << '\n';

    objPanel.set_up_pressed(true);
    cout << "Nakon pritiska UP:\n";
    print_panel_state(objPanel);
    cout << "------------------------------" << '\n';

    objPanel.set_up_pressed(false);
    cout << "Nakon otpustanja UP:\n";
    print_panel_state(objPanel);
}

/* ============================================================
                             main()
   ============================================================ */

// Pokreće primjer kompozicije upravljačke ploče i tipki
int main()
{
    demonstrate_composition();
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Pocetno stanje:
UP:   otpustena
DOWN: otpustena
------------------------------
Nakon pritiska UP:
UP:   pritisnuta
DOWN: otpustena
------------------------------
Nakon otpustanja UP:
UP:   otpustena
DOWN: otpustena
*/