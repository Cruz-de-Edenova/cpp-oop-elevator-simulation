#include "3_platform_position.h"

/* ============================================================
                klasa PlatformPositionStatus
   ============================================================ */

// Sprema zatraženu visinu i pamti je li zahtjev prihvaćen
PlatformPositionStatus::PlatformPositionStatus(
    double requestedHeightCm,
    double defaultHeightCm)
    : mRequestedHeightCm{requestedHeightCm},
      mHeightCm{minHeightCm},
      mInputAccepted{false}
{
    if (is_height_valid(defaultHeightCm))
    {
        mHeightCm = defaultHeightCm;
    }

    if (is_height_valid(requestedHeightCm))
    {
        mHeightCm = requestedHeightCm;
        mInputAccepted = true;
    }
}
// ————————————————————————————————————————————————————————————

// Provjerava pripada li visina dopuštenom rasponu platforme
bool PlatformPositionStatus::is_height_valid(double heightCm)
{
    return (heightCm >= minHeightCm) && (heightCm <= maxHeightCm);
}
// ————————————————————————————————————————————————————————————

// Vraća zatraženu visinu platforme
double PlatformPositionStatus::get_requested_height()
{
    return mRequestedHeightCm;
}
// ————————————————————————————————————————————————————————————

// Vraća trenutno spremljenu visinu platforme
double PlatformPositionStatus::get_height()
{
    return mHeightCm;
}
// ————————————————————————————————————————————————————————————

// Vraća informaciju je li vrijednost konstruktora bila prihvaćena
bool PlatformPositionStatus::was_input_accepted()
{
    return mInputAccepted;
}

/* ============================================================
                 klasa PlatformPositionClamp
   ============================================================ */

// Ograničava zadanu visinu na dopušteni raspon platforme
PlatformPositionClamp::PlatformPositionClamp(double heightCm)
    : mHeightCm{heightCm}
{
    if (mHeightCm < minHeightCm)
    {
        mHeightCm = minHeightCm;
    }
    else if (mHeightCm > maxHeightCm)
    {
        mHeightCm = maxHeightCm;
    }
}
// ————————————————————————————————————————————————————————————

// Vraća trenutno spremljenu visinu platforme
double PlatformPositionClamp::get_height()
{
    return mHeightCm;
}
