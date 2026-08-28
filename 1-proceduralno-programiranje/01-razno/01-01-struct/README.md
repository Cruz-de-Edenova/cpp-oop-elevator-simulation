# `struct`

`struct` je korisnički definirani složeni tip podataka koji omogućuje grupiranje više međusobno povezanih podataka pod jednim zajedničkim imenom.

Umjesto da podatke držimo u više nepovezanih varijabli:

```cpp
int currentFloor{1};
bool doorsOpen{false};
bool moving{false};
```

možemo definirati novi tip koji ih objedinjuje:

```cpp
struct ElevatorState
{
    int currentFloor_;
    bool doorsOpen_;
    bool moving_;
};
```

`ElevatorState` je sada novi tip podatka koji smo sami definirali.

## 1. Stvaranje objekta tipa `struct` 

Nakon definicije tipa možemo stvarati njegove objekte:

```cpp
ElevatorState objElevator{1, false, false};
```

Ovdje objekt `objElevator` sadrži tri vrijednosti:

- trenutni kat
- stanje vrata
- informaciju kreće li se lift

Vrijednosti se inicijaliziraju istim redoslijedom kojim su članovi navedeni u definiciji `struct` tipa.

## 2. Pristup članovima

Članovima objekta pristupamo operatorom `.`:

```cpp
objElevator.currentFloor_ = 3;
objElevator.doorsOpen_ = true;
objElevator.moving_ = false;
```

Vrijednosti članova možemo i čitati:

```cpp
std::cout << objElevator.currentFloor_ << '\n';
```

## 3. Kada koristiti `struct`

`struct` je posebno prikladan kada nekoliko podataka prirodno pripada zajedno i želimo ih tretirati kao jednu cjelinu.

Primjer koordinata:

```cpp
struct Point
{
    int x_;
    int y_;
};
```

Primjer mjerenja senzora:

```cpp
struct TemperatureReading
{
    double temperature_;
    int sensorId_;
};
```

Primjer stanja lifta:

```cpp
struct ElevatorState
{
    int currentFloor_;
    bool doorsOpen_;
    bool moving_;
};
```

Glavna korist je u tome što povezani podaci više nisu raspršeni kroz program, nego pripadaju jednom jasno definiranom tipu.

## 4. `struct` je novi složeni tip podatka

`struct` nije samo skup varijabli.

Nakon što ga definiramo, njegov naziv možemo koristiti kao bilo koji drugi tip:

```cpp
ElevatorState objFirstElevator{1, false, false};
ElevatorState objSecondElevator{5, true, false};
```

Svaki objekt ima vlastite vrijednosti članova.

Promjena jednog objekta ne mijenja drugi:

```cpp
objFirstElevator.currentFloor_ = 2;
```

`objSecondElevator.currentFloor_` ostaje nepromijenjen.

## 5. `struct` i `class`

U C++-u su `struct` i `class` vrlo slični.

Oba mogu sadržavati:

- podatkovne članove
- funkcije članice
- konstruktore
- destruktore
- nasljeđivanje

Najvažnija osnovna razlika je zadani pristup članovima.

Kod `struct` tipa članovi su po defaultu `public`:

```cpp
struct Point
{
    int x_;
    int y_;
};
```

Kod `class` tipa članovi su po defaultu `private`:

```cpp
class Point
{
    int x_;
    int y_;
};
```

U početnim primjerima korisno je `struct` promatrati prvenstveno kao jednostavan način grupiranja povezanih podataka.

Kasnije, kada se uvedu klase, enkapsulacija i metode, razlika između podatkovnog `struct` tipa i klase postat će jasnija.

## 6. Sažetak

- `struct` definira novi složeni tip podatka
- služi za grupiranje povezanih podataka
- članovima pristupamo operatorom `.`
- možemo stvarati više neovisnih objekata istog `struct` tipa
- u C++-u `struct` može imati gotovo sve mogućnosti kao i `class`
- članovi `struct` tipa po defaultu su `public`
- `struct` je koristan prijelaz prema razumijevanju klasa i objekata
