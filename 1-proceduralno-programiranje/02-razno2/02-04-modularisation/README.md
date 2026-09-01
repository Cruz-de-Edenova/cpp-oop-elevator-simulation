# Modularizacija programa

Kako program raste, držanje cijelog izvornog koda u jednoj `.cpp` datoteci postaje nepregledno. Kod se zato može podijeliti na više manjih datoteka koje imaju jasne odgovornosti.

U ovom primjeru program je podijeljen na tri datoteke:

```text
elevator.h
elevator.cpp
main.cpp
```

Datoteka `elevator.h` je **datoteka zaglavlja** i sadrži prototipove funkcija vezanih uz lift. Datoteka `elevator.cpp` sadrži njihove definicije, a `main.cpp` koristi te funkcije.

---

## 1. Uloga `.h` i `.cpp` datoteka

Kod jednostavnih funkcija možemo razlikovati dvije osnovne uloge:

```text
.h datoteka zaglavlja -> prototipovi funkcija
.cpp datoteka         -> definicije funkcija
```

Primjer prototipa u datoteci zaglavlja:

```cpp
int calculate_travel_time(int floorCount, int secondsPerFloor = 2);
```

Odgovarajuća definicija nalazi se u `.cpp` datoteci:

```cpp
int calculate_travel_time(int floorCount, int secondsPerFloor)
{
    return floorCount * secondsPerFloor;
}
```

Datoteka zaglavlja govori drugim dijelovima programa **koje funkcije postoje i kako se mogu pozvati**, dok `.cpp` datoteka sadrži njihovu implementaciju.

---

## 2. Datoteka zaglavlja `elevator.h`

Datoteka zaglavlja `elevator.h` sadrži prototipove funkcija koje druge `.cpp` datoteke mogu koristiti:

```cpp
#ifndef ELEVATOR_H
#define ELEVATOR_H

// Izračunava broj prijeđenih katova između početnog i odredišnog kata
int calculate_floor_count(int startFloor, int destinationFloor);

// Izračunava vrijeme vožnje prema broju katova i vremenu po katu
int calculate_travel_time(int floorCount, int secondsPerFloor = 2);

// Ispisuje podatke o početnom i odredišnom katu
void print_route(int startFloor, int destinationFloor, int floorCount);

// Ispisuje ukupno vrijeme vožnje
void print_travel_time(int travelTime);

#endif
```

Defaultni argument `2` naveden je u prototipu.

`cpp` datoteka koja uključuje ovu datoteku zaglavlja vidi prototip i zato zna za defaultni argument.

---

## 3. Implementacijska datoteka `elevator.cpp`

Definicije funkcija nalaze se u `elevator.cpp`.

```cpp
#include <iostream>

#include "elevator.h"

using std::cout;
```

Datoteka uključuje vlastitu datoteku zaglavlja:

```cpp
#include "elevator.h"
```

To omogućuje kompajleru da provjeri odgovaraju li definicije funkcija prototipovima iz datoteke zaglavlja.

Primjer definicije:

```cpp
int calculate_travel_time(int floorCount, int secondsPerFloor)
{
    return floorCount * secondsPerFloor;
}
```

Defaultni argument iz datoteke zaglavlja ne ponavlja se u definiciji:

```cpp
int calculate_travel_time(int floorCount, int secondsPerFloor)
```

`elevator.cpp` uključuje i `<iostream>` jer se u toj datoteci koristi `cout`.

---

## 4. `main.cpp`

`main.cpp` ne mora znati kako su funkcije implementirane. Dovoljno je uključiti datoteku zaglavlja koja sadrži njihove prototipove:

```cpp
#include "elevator.h"

int main()
{
    int startFloor{2};
    int destinationFloor{7};

    int floorCount{calculate_floor_count(startFloor, destinationFloor)};
    int travelTime{calculate_travel_time(floorCount)};

    print_route(startFloor, destinationFloor, floorCount);
    print_travel_time(travelTime);

    return 0;
}
```

Pojednostavljeni odnos datoteka je:

```text
main.cpp
   |
   +-- #include "elevator.h"
   |
   +-- koristi prototipove funkcija

elevator.cpp
   |
   +-- #include "elevator.h"
   |
   +-- sadrži definicije funkcija
```

`main.cpp` koristi funkcije preko njihovih prototipova, dok se stvarne definicije nalaze u `elevator.cpp`.

---

## 5. Direktiva `#include`

Direktiva:

```cpp
#include "elevator.h"
```

govori predprocesoru da sadržaj navedene datoteke zaglavlja uključi na to mjesto prije samog kompajliranja.

Za vlastite datoteke zaglavlja koristimo navodnike:

```cpp
#include "elevator.h"
```

Za zaglavlja standardne biblioteke koristimo znakove `< >`:

```cpp
#include <iostream>
```

Ne uključujemo `.cpp` datoteke:

```cpp
// Ne koristiti
// #include "elevator.cpp"
```

`.cpp` datoteke kompajliraju se zasebno i kasnije se povezuju u izvršni program.

---

## 6. Zaštita datoteke zaglavlja

Ista datoteka zaglavlja može tijekom kompajliranja biti uključena više puta, izravno ili neizravno.

Primjerice, `main.cpp` može izravno uključiti:

```cpp
#include "elevator.h"
```

ali neka druga datoteka zaglavlja koju `main.cpp` također uključuje može ponovno uključiti isti `elevator.h`.

Pojednostavljeni odnos može izgledati ovako:

```text
main.cpp
   |
   +-- elevator.h
   |
   +-- elevator_display.h
           |
           +-- elevator.h
```

U tom slučaju predprocesor bi bez dodatne zaštite sadržaj `elevator.h` uključio dva puta u istu jedinicu kompajliranja.

### Jedinica kompajliranja (*translation unit*)

**Jedinica kompajliranja** (*translation unit*) je sadržaj jedne `.cpp` datoteke nakon što predprocesor obradi direktive poput `#include` i uključi sadržaj pripadajućih datoteka zaglavlja. Takvu cjelinu kompajler zatim kompajlira kao jednu jedinicu.

Primjerice, `main.cpp` i `elevator.cpp` predstavljaju dvije različite jedinice kompajliranja, iako obje mogu uključivati isti `elevator.h`.

### Što se događa bez zaštite?

Pretpostavimo da `elevator.h` sadrži definiciju strukture:

```cpp
struct ElevatorStatus
{
    int mFloor;
    bool mIsMoving;
};
```

Ako se `elevator.h` uključi dva puta u istu jedinicu kompajliranja, nakon rada predprocesora rezultat bi pojednostavljeno izgledao kao da smo napisali:

```cpp
struct ElevatorStatus
{
    int mFloor;
    bool mIsMoving;
};

struct ElevatorStatus
{
    int mFloor;
    bool mIsMoving;
};
```

Isti tip `ElevatorStatus` sada je definiran dva puta u istoj jedinici kompajliranja, što uzrokuje pogrešku pri kompajliranju.

Važno je primijetiti da samo ponavljanje prototipa obične funkcije ne mora izazvati pogrešku:

```cpp
int calculate_travel_time(int floorCount);

int calculate_travel_time(int floorCount);
```

Takve ponovljene deklaracije mogu biti dopuštene.

Problem nastaje zato što datoteke zaglavlja s vremenom mogu sadržavati i druge elemente, primjerice definicije `struct` i `class` tipova, enumeracije i druge deklaracije ili definicije koje se ne smiju proizvoljno ponavljati.

Zato se datoteka zaglavlja štiti neovisno o tome stvara li njezin trenutačni sadržaj već problem pri višestrukom uključivanju.

### Zaštita pomoću `#ifndef`, `#define` i `#endif`

Za sprečavanje višestrukog uključivanja koristi se **zaštita datoteke zaglavlja**.

U engleskoj C++ terminologiji za isti se mehanizam koriste nazivi **include guard** i **header guard**.

Primjer za `elevator.h`:

```cpp
#ifndef ELEVATOR_H
#define ELEVATOR_H

// Sadržaj datoteke zaglavlja

#endif
```

Pri prvom uključivanju:

```cpp
#ifndef ELEVATOR_H
```

provjerava je li makronaredba `ELEVATOR_H` već definirana.

Budući da nije, izvršava se:

```cpp
#define ELEVATOR_H
```

i sadržaj datoteke zaglavlja se obrađuje.

Ako se tijekom kompajliranja iste jedinice kompajliranja `elevator.h` ponovno uključi, `ELEVATOR_H` već je definiran pa se sadržaj datoteke zaglavlja preskače.

### Jedinstveni naziv makronaredbe

Makronaredba koja služi za zaštitu mora imati jedinstven naziv.

Za datoteku:

```text
elevator.h
```

možemo koristiti:

```cpp
#ifndef ELEVATOR_H
#define ELEVATOR_H

// ...

#endif
```

Za drugu datoteku, primjerice:

```text
motor.h
```

koristili bismo drugu makronaredbu:

```cpp
#ifndef MOTOR_H
#define MOTOR_H

// ...

#endif
```

Ako bi dvije različite datoteke zaglavlja koristile isti naziv zaštitne makronaredbe, uključivanje jedne moglo bi uzrokovati preskakanje sadržaja druge.

### Zašto ne koristimo `#pragma once`?

Mnogi kompajleri podržavaju i kraći zapis:

```cpp
#pragma once
```

Njegova je namjena također spriječiti višestruko uključivanje iste datoteke zaglavlja.

Međutim, `#pragma once` nije dio standarda C++, iako ga podržavaju gotovo svi suvremeni kompajleri.

Klasična zaštita:

```cpp
#ifndef ELEVATOR_H
#define ELEVATOR_H

// ...

#endif
```

koristi standardne direktive predprocesora, jasno pokazuje kako zaštita radi i prenosiva je između različitih C++ kompajlera.

Zato se u ovom projektu koristi klasična zaštita datoteke zaglavlja, a ne `#pragma once`.

---

## 7. Kompajliranje i povezivanje

Kod programa s više `.cpp` datoteka svaka `.cpp` datoteka kompajlira se kao zasebna cjelina.

U ovom primjeru:

```text
main.cpp
        -> main.o

elevator.cpp
        -> elevator.o
```

Nakon toga linker povezuje objektne datoteke:

```text
main.o
elevator.o
    |
    v
   prog
```

Prototip iz datoteke zaglavlja omogućuje kompajleru da provjeri poziv funkcije, dok linker kasnije pronalazi odgovarajuću definiciju iz druge objektne datoteke.

Zato možemo u `main.cpp` napisati:

```cpp
int travelTime{calculate_travel_time(floorCount)};
```

iako definicija `calculate_travel_time()` nije u `main.cpp`.

---

## 8. Kompajliranje programa s više `.cpp` datoteka

Obje `.cpp` datoteke možemo navesti u jednom pozivu kompajlera:

```text
g++ -std=c++17 -g -O0 -Wall -Wextra -Wconversion -Werror main.cpp elevator.cpp -o prog
```

G++ tada obavlja potrebno kompajliranje i povezivanje.

---

## 9. Razvoj programa i novi `.h/.cpp` parovi

Za ovaj mali primjer dovoljan je jedan par:

```text
elevator.h
elevator.cpp
```

Nema potrebe prerano dijeliti nekoliko jednostavnih funkcija u velik broj malih datoteka.

Kako se program s vremenom razvija i pojavljuju se nove, jasno odvojene cjeline, mogu se postupno dodavati novi parovi datoteka zaglavlja i odgovarajućih `.cpp` datoteka.

Primjer buduće strukture mogao bi izgledati ovako:

```text
elevator.h
elevator.cpp

door.h
door.cpp

motor.h
motor.cpp

main.cpp
```

Takva podjela ima smisla tek kada pojedine cjeline postanu dovoljno samostalne da zaslužuju vlastiti par `.h/.cpp` datoteka.

Modularizaciju zato ne treba shvatiti kao cilj da program ima što više datoteka, nego kao način da se programski kod organizira u prirodne i pregledne cjeline.

---

## 10. Sažetak

- Datoteka zaglavlja .h sadrži prototipove funkcija, dok odgovarajuća .cpp datoteka sadrži njihove definicije.
- `#include` omogućuje da `.cpp` datoteka vidi prototipove iz datoteke zaglavlja. Vlastite `.cpp` datoteke ne uključuju se pomoću `#include`.
- Zaštita datoteke zaglavlja (*include guard*, odnosno *header guard*) sprječava višestruko uključivanje njezina sadržaja tijekom obrade iste jedinice kompajliranja.
- Svaka `.cpp` datoteka kompajlira se zasebno, a linker zatim povezuje objektne datoteke u završni program.
- Kako program raste, novi parovi `h` i `.cpp` datoteka dodaju se postupno za nove, prirodno odvojene cjeline programa.