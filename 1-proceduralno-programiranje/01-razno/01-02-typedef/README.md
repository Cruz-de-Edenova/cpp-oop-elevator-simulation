# Alias deklaracije pomoću `typedef` i `using`

Alias tipa omogućuje da postojećem C++ tipu podatka damo drugo ime.
To može poboljšati čitljivost programa kada želimo da naziv tipa bolje opisuje značenje podatka u programu.

**Važno:**

- Alias ne stvara novi tip podatka. On samo uvodi drugo ime za već postojeći tip podatka.

## 1. `typedef`

Stariji C i C++ način definiranja aliasa koristi ključnu riječ `typedef`.

**Primjer 1:**

```cpp
typedef unsigned int FloorNumber;
```

Nakon toga možemo pisati:

```cpp
FloorNumber currentFloor{1};
FloorNumber targetFloor{5};
```

`FloorNumber` je i dalje tip `unsigned int`. Sam naziv jasnije govori što vrijednost predstavlja.

Sintaksa `typedef` deklaracije može se čitati ovako:

```text
typedef POSTOJEĆI_TIP NOVO_IME;
```

**Primjer 2:**

```cpp
typedef double Temperature;
typedef unsigned int RequestCount;
```

## 2. `using`

Moderniji C++ način definiranja aliasa koristi `using`.

**Primjer 3:**

```cpp
using FloorNumber = unsigned int;
```

Nakon toga:

```cpp
FloorNumber currentFloor{1};
FloorNumber targetFloor{5};
```

Sintaksa se može čitati prirodnije:

```text
using NOVO_IME = POSTOJEĆI_TIP;
```

**Primjer 4:**

```cpp
using Temperature = double;
using RequestCount = unsigned int;
```

## 3. Alias ne stvara novi tip podatka

Ako napišemo:

```cpp
using FloorNumber = unsigned int;
```

onda su:

```cpp
FloorNumber floor{3};
unsigned int value{3};
```

istog stvarnog tipa.

Zato je dopušteno:

```cpp
floor = value;
```

## 4. Alias za složeni tip podatka

Alias se može koristiti i za korisnički definirani tip podatka.

**Primjer 5:**

```cpp
struct ElevatorState
{
    unsigned int currentFloor_;
    bool doorsOpen_;
};

using State = ElevatorState;
```

Sada možemo napisati:

```cpp
State objState{1, false};
```

`State` i `ElevatorState` predstavljaju isti tip podatka.

**Primjer 6:**

```cpp
std::array<std::array<int, 3>, 4> objMatrix0{};
using Matrix4x3 = std::array<std::array<int, 3>, 4>;
```

Sada možemo napisati:

```cpp
Matrix4x3 objMatrix1{};
Matrix4x3 objMatrix2{};
```

`objMatrix0`, `objMatrix1` i `objMatrix2` su objekti istoga tipa podatka `std::array<std::array<int, 3>, 4>`.
`Matrix4x3` je samo drugo ime za taj isti tip.

## 5. Sažetak

- alias daje drugo ime postojećem tipu podatka
- `typedef` je stariji način definiranja aliasa
- `using` je moderniji i čitljiviji C++ način
- alias ne stvara novi tip podatka
- počevši od C++11 uglavnom preferiramo `using`
- `typedef` treba poznavati zbog postojećeg C i C++ koda
- alias treba koristiti kada stvarno poboljšava značenje ili čitljivost:
  - dugačak naziv tipa želimo učiniti kraćim
  - želimo pojednostavniti složeniju deklaraciju
  - želimo jasnije izraziti značenje podatka