#ifndef PLATFORM_POSITION_H
#define PLATFORM_POSITION_H

constexpr double minHeightCm{30.0};    // Najniža moguća visina platforme
constexpr double maxHeightCm{137.0};   // Najviša moguća visina platforme

/* ============================================================
                klasa PlatformPositionStatus
   ============================================================ */

class PlatformPositionStatus
{
private:
    double mRequestedHeightCm; // Zatražena visina platforme
    double mHeightCm;          // Trenutno spremljena visina platforme
    bool mInputAccepted;       // Označava je li zatražena visina prihvaćena

    // Provjerava pripada li visina dopuštenom rasponu platforme
    bool is_height_valid(double heightCm);

public:
    // Sprema zatraženu visinu i pamti je li zahtjev prihvaćen
    PlatformPositionStatus(
        double requestedHeightCm,
        double defaultHeightCm = minHeightCm);

    // Vraća zatraženu visinu platforme
    double get_requested_height();

    // Vraća trenutno spremljenu visinu platforme
    double get_height();

    // Vraća informaciju je li vrijednost konstruktora bila prihvaćena
    bool was_input_accepted();
};

/* ============================================================
                 klasa PlatformPositionClamp
   ============================================================ */

class PlatformPositionClamp
{
private:
    double mHeightCm; // Trenutno spremljena visina platforme

public:
    // Ograničava zadanu visinu na dopušteni raspon platforme
    PlatformPositionClamp(double heightCm);

    // Vraća trenutno spremljenu visinu platforme
    double get_height();
};

#endif
