#include <iostream>
#include "virtual_io.h"

using std::cout;

namespace controller = ns_virtual_io::ns_controller;
namespace simulation = ns_virtual_io::ns_simulation;

/* ============================================================
                         FUNKCIJE
   ============================================================ */

// Demonstrira kako simulacija postavlja ulaze koje upravljački program čita
void demonstrate_input_signal_flow()
{
    simulation::set_up_button(true);
    simulation::set_down_button(false);
    simulation::set_up_limit_switch(false);

    cout << "ULAZI UPRAVLJACKOG PROGRAMA\n";
    cout << "UP tipka: "
         << (controller::read_up_button() ? "pritisnuta" : "otpustena") << '\n';
    cout << "DOWN tipka: "
         << (controller::read_down_button() ? "pritisnuta" : "otpustena") << '\n';
    cout << "Gornji granicni prekidac: "
         << (controller::read_up_limit_switch() ? "aktivan" : "neaktivan") << '\n';
    cout << "------------------------------\n";
}

// Demonstrira kako upravljački program postavlja izlaze koje simulacija čita
void demonstrate_output_signal_flow()
{
    controller::set_motor_starter(true);
    controller::set_down_solenoid(false);

    cout << "IZLAZI UPRAVLJACKOG PROGRAMA\n";
    cout << "Starter motora: "
         << (simulation::read_motor_starter() ? "aktivan" : "neaktivan") << '\n';
    cout << "DOWN solenoid: "
         << (simulation::read_down_solenoid() ? "aktivan" : "neaktivan") << '\n';

    controller::set_motor_starter(false);
    controller::set_down_solenoid(true);

    cout << "\nStarter motora: "
         << (simulation::read_motor_starter() ? "aktivan" : "neaktivan") << '\n';
    cout << "DOWN solenoid: "
         << (simulation::read_down_solenoid() ? "aktivan" : "neaktivan") << '\n';
}
/* ============================================================
                         MAIN
   ============================================================ */
int main()
{
    ns_virtual_io::reset();

    demonstrate_input_signal_flow();
    demonstrate_output_signal_flow();

    return 0;
}
/* ============================================================
ULAZI UPRAVLJACKOG PROGRAMA
UP tipka: pritisnuta
DOWN tipka: otpustena
Gornji granicni prekidac: neaktivan
------------------------------
IZLAZI UPRAVLJACKOG PROGRAMA
Starter motora: aktivan
DOWN solenoid: neaktivan

Starter motora: neaktivan
DOWN solenoid: aktivan
*/