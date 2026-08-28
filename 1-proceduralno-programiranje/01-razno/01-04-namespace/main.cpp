// Poglavlje 1.4 namespace i using namespace

#include <iostream>

namespace elevator
{
    // Ispisuje stanje lifta
    void print_status()
    {
        std::cout << "Lift je spreman\n";
    }
}

namespace building
{
    // Ispisuje stanje zgrade
    void print_status()
    {
        std::cout << "Zgrada je otvorena\n";
    }
}

/* ============================================================
                         FUNKCIJE
   ============================================================ */

// Pokazuje korištenje istoimenih funkcija iz različitih namespaceova
void demonstrate_qualified_names()
{
    std::cout << "Istoimene funkcije iz razlicitih namespaceova\n";

    elevator::print_status();
    building::print_status();
    std::cout << "------------------------------" << '\n';
}
// ————————————————————————————————————————————————————————————

// Pokazuje korištenje using namespace unutar ograničenog opsega
void demonstrate_using_namespace()
{
    using namespace elevator;

    std::cout << "'using namespace' primjer\n";

    /* Unutar ove funkcije funkciju print_status() možemo koristiti bez prefiksa
    elevator:: jer smo uključili namespace elevator. */
    print_status();
}

/* ============================================================
                           MAIN
   ============================================================ */

int main()
{
    demonstrate_qualified_names();
    demonstrate_using_namespace();

    return 0;
}
/* ============================================================
Istoimene funkcije iz razlicitih namespaceova
Lift je spreman
Zgrada je otvorena
------------------------------
'using namespace' primjer
Lift je spreman

*/