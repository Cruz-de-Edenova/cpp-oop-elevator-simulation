#ifndef VIRTUAL_IO_H
#define VIRTUAL_IO_H

namespace ns_virtual_io
{
/* ============================================================
                         CONTROLLER
   ============================================================ */
    namespace ns_controller
    {
        // Čita stanje UP tipke
        bool read_up_button();

        // Čita stanje DOWN tipke
        bool read_down_button();

        // Čita stanje gornjeg graničnog prekidača
        bool read_up_limit_switch();

        // Postavlja stanje startera motora
        void set_motor_starter(bool active);

        // Postavlja stanje DOWN solenoida
        void set_down_solenoid(bool active);
    }

/* ============================================================
                         SIMULATION
   ============================================================ */
    namespace ns_simulation
    {
        // Postavlja stanje UP tipke
        void set_up_button(bool pressed);

        // Postavlja stanje DOWN tipke
        void set_down_button(bool pressed);

        // Postavlja stanje gornjeg graničnog prekidača
        void set_up_limit_switch(bool active);

        // Čita stanje startera motora
        bool read_motor_starter();

        // Čita stanje DOWN solenoida
        bool read_down_solenoid();
    }

/* ============================================================
                           RESET
   ============================================================ */
    // Vraća sva virtualna I/O stanja u početno neaktivno stanje
    void reset();
}

#endif
