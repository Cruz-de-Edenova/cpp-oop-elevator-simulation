#include <iostream>
#include <string>

using std::cout;
using std::string;

/* ============================================================
                      klasa ControlButton
   ============================================================ */

class ControlButton
{
private:
    string mLabel; // Oznaka upravljačke tipke

public:
    // Inicijalizira oznaku tipke i prikazuje izvršavanje konstruktora
    ControlButton(const string& label)
        : mLabel{label}
    {
        cout << "ControlButton \"" << mLabel << "\": tijelo konstruktora\n";
    }

    // Prikazuje izvršavanje destruktora tipke
    ~ControlButton()
    {
        cout << "ControlButton \"" << mLabel << "\": tijelo destruktora\n";
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
    // Inicijalizira obje tipke i prikazuje izvršavanje konstruktora
    ControlPanel()
        : mUpButton{"UP"}, mDownButton{"DOWN"}
    {
        cout << "ControlPanel: tijelo konstruktora\n";
    }

    // Prikazuje izvršavanje destruktora
    ~ControlPanel()
    {
        cout << "ControlPanel: tijelo destruktora\n";
    }
};

/* ============================================================
                             main()
   ============================================================ */

// Prikazuje redoslijed konstrukcije i uništavanja objekata
int main()
{
    cout << "Prije stvaranja kontrolne ploce\n";

    // Ograničava životni vijek objekta ControlPanel na ovaj blok
    {
        ControlPanel objPanel{};
        cout << "------------------------------\n";
    }

    cout << "Nakon izlaska iz bloka\n";
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Prije stvaranja kontrolne ploce
ControlButton "UP": tijelo konstruktora
ControlButton "DOWN": tijelo konstruktora
ControlPanel: tijelo konstruktora
------------------------------
ControlPanel: tijelo destruktora
ControlButton "DOWN": tijelo destruktora
ControlButton "UP": tijelo destruktora
Nakon izlaska iz bloka
*/