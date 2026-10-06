#include "virtual_io.h"

namespace ns_virtual_io
{
/* ============================================================
                      INTERNA STANJA
   ============================================================ */
    namespace
    {
        bool upButtonPressed{false};
        bool downButtonPressed{false};
        bool upLimitSwitchActive{false};

        bool motorStarterActive{false};
        bool downSolenoidActive{false};
    }

/* ============================================================
                         CONTROLLER
   ============================================================ */
    namespace ns_controller
    {
        // Čita stanje UP tipke
        bool read_up_button()
        {
            return upButtonPressed;
        }

        // Čita stanje DOWN tipke
        bool read_down_button()
        {
            return downButtonPressed;
        }

        // Čita stanje gornjeg graničnog prekidača
        bool read_up_limit_switch()
        {
            return upLimitSwitchActive;
        }

        // Postavlja stanje startera motora
        void set_motor_starter(bool active)
        {
            motorStarterActive = active;
        }

        // Postavlja stanje DOWN solenoida
        void set_down_solenoid(bool active)
        {
            downSolenoidActive = active;
        }
    }

/* ============================================================
                         SIMULATION
   ============================================================ */
    namespace ns_simulation
    {
        // Postavlja stanje UP tipke
        void set_up_button(bool pressed)
        {
            upButtonPressed = pressed;
        }

        // Postavlja stanje DOWN tipke
        void set_down_button(bool pressed)
        {
            downButtonPressed = pressed;
        }

        // Postavlja stanje gornjeg graničnog prekidača
        void set_up_limit_switch(bool active)
        {
            upLimitSwitchActive = active;
        }

        // Čita stanje startera motora
        bool read_motor_starter()
        {
            return motorStarterActive;
        }

        // Čita stanje DOWN solenoida
        bool read_down_solenoid()
        {
            return downSolenoidActive;
        }
    }

/* ============================================================
                           RESET
   ============================================================ */
    // Vraća sva virtualna I/O stanja u početno neaktivno stanje
    void reset()
    {
        upButtonPressed = false;
        downButtonPressed = false;
        upLimitSwitchActive = false;

        motorStarterActive = false;
        downSolenoidActive = false;
    }
}
