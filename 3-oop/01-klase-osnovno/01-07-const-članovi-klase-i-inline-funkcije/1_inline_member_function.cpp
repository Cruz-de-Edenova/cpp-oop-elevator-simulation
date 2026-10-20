#include <iostream>

using std::cout;

/* ============================================================
                       klasa DownSolenoid
   ============================================================ */

class DownSolenoid
{
private:
    bool mEnergized; // Označava je li DOWN solenoid pobuđen

public:
    // Inicijalizira solenoid u nepobuđenom stanju
    DownSolenoid();

    // Pobuđuje solenoid; definicija unutar klase implicitno je inline
    void energize()
    {
        mEnergized = true;
        cout << "DOWN solenoid: aktiviran\n";
    }

    // Isključuje pobudu solenoida
    void deenergize();
};
// ————————————————————————————————————————————————————————————

// Inicijalizira solenoid u nepobuđenom stanju
DownSolenoid::DownSolenoid()
    : mEnergized{false}
{
}
// ————————————————————————————————————————————————————————————

// Isključuje pobudu solenoida; inline je naveden uz definiciju izvan klase
inline void DownSolenoid::deenergize()
{
    mEnergized = false;
    cout << "DOWN solenoid: deaktiviran\n";
}

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    DownSolenoid objDownSolenoid{};

    objDownSolenoid.energize();
    objDownSolenoid.deenergize();

    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
DOWN solenoid: aktiviran
DOWN solenoid: deaktiviran
*/