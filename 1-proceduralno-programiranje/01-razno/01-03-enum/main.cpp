// Poglavlje 1.3 enum i enum class

#include <iostream>

/* ============================================================
                         FUNKCIJE
   ============================================================ */

// Pokazuje osnovno korištenje klasičnog enum tipa
void demonstrate_enum()
{
    enum Direction
    {
        Idle,
        Up,
        Down
    };

    Direction currentDirection{Up};

    std::cout << "'enum' primjer\n";

    // Kod 'enum' tipa enumerator Up dostupan je bez navođenja imena tipa Direction
    if (currentDirection == Up)
    {
        std::cout << "Lift se krece prema gore\n";
    }
}
// ————————————————————————————————————————————————————————————

// Pokazuje scoped enumeraciju pomoću 'enum class'
void demonstrate_enum_class()
{
    enum class Direction
    {
        Idle,
        Up,
        Down
    };

    /* Kod 'enum class' tipa enumerator pripada vlastitom scopeu, pa moramo
    napisati Direction::Down */
    Direction currentDirection{Direction::Down};

    std::cout << "\n'enum class' primjer\n";

    if (currentDirection == Direction::Down)
    {
        std::cout << "Lift se krece prema dolje\n";
    }
}
// ————————————————————————————————————————————————————————————

// Pokazuje da isti enumerator može postojati u različitim enum class tipovima
void demonstrate_scoped_names()
{
    enum class DoorState
    {
        Open,
        Closed
    };

    enum class MotorState
    {
        Open,
        Closed
    };

    DoorState doorState{DoorState::Open};
    MotorState motorState{MotorState::Closed};

    std::cout << "\nOdvojeni scopeovi\n";

    if (doorState == DoorState::Open)
    {
        std::cout << "Vrata su otvorena\n";
    }

    if (motorState == MotorState::Closed)
    {
        std::cout << "Motor je iskljucen\n";
    }
}
// ————————————————————————————————————————————————————————————

// Pokazuje da je 'enum struct' alternativni zapis za 'enum class'
void demonstrate_enum_struct()
{
    enum struct DoorState
    {
        Open,
        Closed
    };

    DoorState doorState{DoorState::Closed};

    std::cout << "\n'enum struct' primjer\n";

    if (doorState == DoorState::Closed)
    {
        std::cout << "Vrata su zatvorena\n";
    }
}

/* ============================================================
                           MAIN
   ============================================================ */

int main()
{
    demonstrate_enum();
    demonstrate_enum_class();
    demonstrate_scoped_names();
    demonstrate_enum_struct();

    return 0;
}
/* ============================================================
'enum' primjer
Lift se krece prema gore

'enum class' primjer
Lift se krece prema dolje

Odvojeni scopeovi
Vrata su otvorena
Motor je iskljucen

'enum struct' primjer
Vrata su zatvorena

*/