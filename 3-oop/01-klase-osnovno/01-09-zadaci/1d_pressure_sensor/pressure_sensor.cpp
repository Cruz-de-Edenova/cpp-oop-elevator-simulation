#include "pressure_sensor.h"
#include <iostream>

/* ============================================================
                       klasa PressureSensor
   ============================================================ */

// Provjerava valjanost donjeg i gornjeg praga tlaka
bool PressureSensor::are_thresholds_valid(int lowPressure, int highPressure) const
{
    if ((lowPressure >= highPressure) || (lowPressure < 0))
    {
        return false;
    }
     
    return true;
}
// ————————————————————————————————————————————————————————————

// Zadavanje pragova na 60 i 95 bara
PressureSensor::PressureSensor()
    : mLowPressure{60}, mHighPressure{95}
{
}
// ————————————————————————————————————————————————————————————

// Zadavanje pragova tlaka konstruktorom
PressureSensor::PressureSensor(int lowPressure, int highPressure)
    : mLowPressure{lowPressure}, mHighPressure{highPressure}
{
    if (!are_thresholds_valid(lowPressure, highPressure))
    {
        mLowPressure = 60;
        mHighPressure = 95;
    }
}
// ————————————————————————————————————————————————————————————

// Sprema novu vrijednost tlaka u privatni podatkovni član
void PressureSensor::set_pressure(int pressureBar)
{
    mPressureBar = pressureBar;
}
// ————————————————————————————————————————————————————————————

// Mijenja pragove tlaka ako su nove vrijednosti valjane
bool PressureSensor::set_thresholds(int lowPressure, int highPressure)
{
    bool valid = are_thresholds_valid(lowPressure, highPressure);

    if (valid)
    {
        mLowPressure = lowPressure;
        mHighPressure = highPressure;
        return true;
    }
    
    return false;
}
// ————————————————————————————————————————————————————————————

// Vraća trenutno spremljenu vrijednost tlaka
int PressureSensor::get_pressure() const
{
    return mPressureBar;
}
// ————————————————————————————————————————————————————————————

// Vraća donji prag tlaka
int PressureSensor::get_low_pressure() const
{
    return mLowPressure;
}
// ————————————————————————————————————————————————————————————

// Vraća gornji prag tlaka
int PressureSensor::get_high_pressure() const
{
    return mHighPressure;
}
// ————————————————————————————————————————————————————————————

// Provjerava je li spremljena vrijednost tlaka ispod donjeg praga
bool PressureSensor::is_low() const
{
    return mPressureBar < mLowPressure;
}
// ————————————————————————————————————————————————————————————

// Provjerava je li spremljena vrijednost tlaka iznad gornjeg praga
bool PressureSensor::is_high() const
{
    return mPressureBar > mHighPressure;
}
