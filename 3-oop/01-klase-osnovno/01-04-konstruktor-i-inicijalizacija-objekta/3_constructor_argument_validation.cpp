#include <iostream>
#include "3_platform_position.h"

using std::cout;

/* ============================================================
                         FUNKCIJE
   ============================================================ */

// Demonstrira odbijanje nedopuštene vrijednosti i pamćenje rezultata provjere
void demonstrate_status()
{
    // Za drugi parametar koristi se defaultni argument
    PlatformPositionStatus objPosition{150.0};

    cout << "Zatrazena visina: "
         << objPosition.get_requested_height() << " cm\n";
    cout << "Spremljena visina: "
         << objPosition.get_height() << " cm\n";
    cout << "Ulaz prihvacen: "
         << (objPosition.was_input_accepted() ? "da" : "ne") << '\n';
    cout << "------------------------------\n";
}
// ————————————————————————————————————————————————————————————

// Demonstrira ograničavanje previsoke vrijednosti na maksimum
void demonstrate_clamp()
{
    PlatformPositionClamp objPosition{150.0};

    cout << "Zatrazena visina: 150 cm\n";
    cout << "Ogranicena visina: "
         << objPosition.get_height() << " cm\n";
}

/* ============================================================
                              main()
   ============================================================ */

int main()
{
    demonstrate_status();
    demonstrate_clamp();

    return 0;
}

/* ============================================================
Zatrazena visina: 150 cm
Spremljena visina: 30 cm
Ulaz prihvacen: ne
------------------------------
Zatrazena visina: 150 cm
Ogranicena visina: 137 cm
*/
