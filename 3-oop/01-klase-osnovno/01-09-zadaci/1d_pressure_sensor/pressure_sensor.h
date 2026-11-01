#ifndef PRESSURE_SENSOR_H
#define PRESSURE_SENSOR_H

/* ============================================================
                       klasa PressureSensor
   ============================================================ */

class PressureSensor
{
private:
    int mPressureBar{0};      // Trenutno spremljena vrijednost tlaka u barima
    int mLowPressure;         // Donji prag tlaka
    int mHighPressure;        // Gornji prag tlaka

    // Provjerava valjanost donjeg i gornjeg praga tlaka
    bool are_thresholds_valid(int lowPressure, int highPressure) const;

public:
    // Zadavanje pragova na 60 i 95 bara
    PressureSensor();
    
    // Zadavanje pragova tlaka konstruktorom
    PressureSensor(int lowPressure, int highPressure);

    // Sprema novu vrijednost tlaka u privatni podatkovni član
    void set_pressure(int pressureBar);

    // Mijenja pragove tlaka ako su nove vrijednosti valjane
    bool set_thresholds(int lowPressure, int highPressure);

    // Vraća trenutno spremljenu vrijednost tlaka
    int get_pressure() const;

    // Vraća donji prag tlaka
    int get_low_pressure() const;

    // Vraća gornji prag tlaka
    int get_high_pressure() const;

    // Provjerava je li spremljena vrijednost tlaka ispod donjeg praga
    bool is_low() const;

    // Provjerava je li spremljena vrijednost tlaka iznad gornjeg praga
    bool is_high() const;
};

#endif