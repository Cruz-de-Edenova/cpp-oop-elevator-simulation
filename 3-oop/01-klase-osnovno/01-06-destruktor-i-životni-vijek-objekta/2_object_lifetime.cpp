#include <iostream>

using std::cout;

/* ============================================================
                         klasa Peripheral
   ============================================================ */

class Peripheral
{
private:
    int mId; // Identifikator periferije

public:
    // Inicijalizira periferiju i ispisuje redoslijed stvaranja
    Peripheral(int id);

    // Ispisuje redoslijed uništavanja periferije
    ~Peripheral();
};
// ————————————————————————————————————————————————————————————

// Inicijalizira periferiju i ispisuje redoslijed stvaranja
Peripheral::Peripheral(int id)
    : mId{id}
{
    cout << "Konstruktor: periferija " << mId << '\n';
}
// ————————————————————————————————————————————————————————————

// Ispisuje redoslijed uništavanja periferije
Peripheral::~Peripheral()
{
    cout << "Destruktor: periferija " << mId << '\n';
}

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    cout << "Vanjski blok\n";

    Peripheral objFirst{1};
    Peripheral objSecond{2};

    {
        cout << "Unutarnji blok\n";

        Peripheral objThird{3};
        Peripheral objFourth{4};

        cout << "Kraj unutarnjeg bloka\n";
    }

    cout << "Ponovno u vanjskom bloku\n";
    cout << "Prije izlaska iz funkcije main()\n";
    
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Vanjski blok
Konstruktor: periferija 1
Konstruktor: periferija 2
Unutarnji blok
Konstruktor: periferija 3
Konstruktor: periferija 4
Kraj unutarnjeg bloka
Destruktor: periferija 4
Destruktor: periferija 3
Ponovno u vanjskom bloku
Prije izlaska iz funkcije main()
Destruktor: periferija 2
Destruktor: periferija 1
*/
