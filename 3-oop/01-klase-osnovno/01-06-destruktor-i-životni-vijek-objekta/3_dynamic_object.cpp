#include <iostream>

using std::cout;

/* ============================================================
                           klasa Timer
   ============================================================ */

class Timer
{
private:
    int mId; // Identifikator timera

public:
    // Inicijalizira dinamički stvoren objekt timera
    Timer(int id);

    // Ispisuje poruku kada završava životni vijek objekta timera
    ~Timer();

    // Ispisuje identifikator timera
    void print_id();
};
// ————————————————————————————————————————————————————————————

// Inicijalizira dinamički stvoren objekt timera
Timer::Timer(int id)
    : mId{id}
{
    cout << "Konstruktor: timer " << mId << '\n';
}
// ————————————————————————————————————————————————————————————

// Ispisuje poruku kada završava životni vijek objekta timera
Timer::~Timer()
{
    cout << "Destruktor: timer " << mId << '\n';
}
// ————————————————————————————————————————————————————————————

// Ispisuje identifikator timera
void Timer::print_id()
{
    cout << "Aktivni timer: " << mId << '\n';
}

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    cout << "Stvaranje dinamickog objekta\n";

    Timer* ptrTimer{new Timer{1}};
    ptrTimer->print_id();

    cout << "Poziv delete\n";
    delete ptrTimer;
    ptrTimer = nullptr;

    cout << "Nakon delete pokazivac je nullptr\n";
    return 0;
}

/* ============================================================
                       Ispis na CMD konzoli
   ============================================================ */

/*
Stvaranje dinamickog objekta
Konstruktor: timer 1
Aktivni timer: 1
Poziv delete
Destruktor: timer 1
Nakon delete pokazivac je nullptr
*/