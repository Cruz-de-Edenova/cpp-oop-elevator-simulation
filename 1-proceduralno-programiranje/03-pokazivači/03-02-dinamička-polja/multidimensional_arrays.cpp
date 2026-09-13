#include <iostream>

using std::cout;

/* ============================================================
                         FUNKCIJE
   ============================================================ */

// ————————————————————————————————————————————————————————————

// Demonstrira 2D polje s dinamički alociranim redovima
void demonstrate_array_of_pointers()
{
    constexpr int floorCount{3};     // Broj katova
    constexpr int readingCount{4};   // Broj očitanja senzora po katu

    int* ptrSensorReadings[floorCount]{};

    for (int floorIndex{0}; floorIndex < floorCount; ++floorIndex)
    {
        ptrSensorReadings[floorIndex] = new int[readingCount]{};
    }

    ptrSensorReadings[1][2] = 25;

    cout << "Ocitanje senzora: " << ptrSensorReadings[1][2] << '\n';

    for (int floorIndex{0}; floorIndex < floorCount; ++floorIndex)
    {
        delete[] ptrSensorReadings[floorIndex];
        ptrSensorReadings[floorIndex] = nullptr;
    }

    cout << "------------------------------\n";
}

// ————————————————————————————————————————————————————————————

// Demonstrira 2D dinamički alocirano polje pomoću int**
void demonstrate_pointer_to_pointer()
{
    constexpr int floorCount{3};     // Broj katova
    constexpr int readingCount{4};   // Broj očitanja senzora po katu

    int** ptrSensorReadings{new int*[floorCount]{}};

    for (int floorIndex{0}; floorIndex < floorCount; ++floorIndex)
    {
        ptrSensorReadings[floorIndex] = new int[readingCount]{};
    }

    ptrSensorReadings[2][1] = 18;

    cout << "Ocitanje senzora: " << ptrSensorReadings[2][1] << '\n';

    for (int floorIndex{0}; floorIndex < floorCount; ++floorIndex)
    {
        delete[] ptrSensorReadings[floorIndex];
        ptrSensorReadings[floorIndex] = nullptr;
    }

    delete[] ptrSensorReadings;
    ptrSensorReadings = nullptr;

    cout << "------------------------------\n";
}

// ————————————————————————————————————————————————————————————

// Demonstrira 3D dinamički alocirano polje pomoću int***
void demonstrate_three_dimensional_array()
{
    constexpr int floorCount{2};     // Broj katova
    constexpr int sensorCount{2};    // Broj senzora po katu
    constexpr int readingCount{3};   // Broj očitanja po senzoru

    int*** ptrSensorReadings{new int**[floorCount]{}};

    for (int floorIndex{0}; floorIndex < floorCount; ++floorIndex)
    {
        ptrSensorReadings[floorIndex] = new int*[sensorCount]{};

        for (int sensorIndex{0}; sensorIndex < sensorCount; ++sensorIndex)
        {
            ptrSensorReadings[floorIndex][sensorIndex] = new int[readingCount]{};
        }
    }

    ptrSensorReadings[1][0][2] = 42;

    cout << "Ocitanje senzora: " << ptrSensorReadings[1][0][2] << '\n';

    for (int floorIndex{0}; floorIndex < floorCount; ++floorIndex)
    {
        for (int sensorIndex{0}; sensorIndex < sensorCount; ++sensorIndex)
        {
            delete[] ptrSensorReadings[floorIndex][sensorIndex];
            ptrSensorReadings[floorIndex][sensorIndex] = nullptr;
        }

        delete[] ptrSensorReadings[floorIndex];
        ptrSensorReadings[floorIndex] = nullptr;
    }

    delete[] ptrSensorReadings;
    ptrSensorReadings = nullptr;

    cout << "------------------------------\n";
}

// ————————————————————————————————————————————————————————————

// Uspoređuje indeksni pristup i aritmetiku pokazivača za 2D dinamički alocirano
// polje pomoću int**
void demonstrate_pointer_arithmetic()
{
    constexpr int rowCount{2};      // Broj redaka tipki
    constexpr int buttonCount{3};   // Broj tipki po retku

    bool** ptrButtonStates{new bool*[rowCount]{}};

    for (int rowIndex{0}; rowIndex < rowCount; ++rowIndex)
    {
        ptrButtonStates[rowIndex] = new bool[buttonCount]{};
    }

    ptrButtonStates[1][2] = true;

    cout << "Indeksni pristup: tipka "
        << (ptrButtonStates[1][2] ? "je pritisnuta" : "nije pritisnuta") << '\n';

    cout << "Aritmetika pokazivaca: tipka "
        << (*(*(ptrButtonStates + 1) + 2) ? "je pritisnuta" : "nije pritisnuta")
        << '\n';

    for (int rowIndex{0}; rowIndex < rowCount; ++rowIndex)
    {
        delete[] ptrButtonStates[rowIndex];
        ptrButtonStates[rowIndex] = nullptr;
    }

    delete[] ptrButtonStates;
    ptrButtonStates = nullptr;
}

/* ============================================================
                         MAIN
   ============================================================ */

int main()
{
    demonstrate_array_of_pointers();
    demonstrate_pointer_to_pointer();
    demonstrate_three_dimensional_array();
    demonstrate_pointer_arithmetic();

    return 0;
}
/* ============================================================
Ocitanje senzora: 25
------------------------------
Ocitanje senzora: 18
------------------------------
Ocitanje senzora: 42
------------------------------
Indeksni pristup: tipka je pritisnuta
Aritmetika pokazivaca: tipka je pritisnuta
*/