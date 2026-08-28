# `enum` i `enum class`

Enumeracija je korisnički definirani tip podatka koji može imati jednu od unaprijed definiranih vrijednosti.
Umjesto da smjer kretanja lifta predstavljamo običnim brojevima:

```cpp
int direction{0};
```

možemo definirati poseban tip:

```cpp
enum Direction
{
    Idle,
    Up,
    Down
};
```

`Idle`, `Up` i `Down` su moguće vrijednosti tipa `Direction`.

## 1. `enum`

Klasični `enum` definira skup unaprijed zadanih `int` vrijednosti.

**Primjer 1:**

```cpp
enum Direction
{
    Idle,
    Up,
    Down
};

Direction currentDirection{Idle};
```

Vrijednosti `Idle`, `Up` i `Down` nazivaju se **enumeratori**.
Ako im ne zadamo vrijednosti ručno, kompajler im redom pridružuje cjelobrojne vrijednosti:

```text
Idle = 0
Up   = 1
Down = 2
```

Kod klasičnog `enum` tipa enumeratori su dostupni izravno u scope-u u kojem je `enum` definiran, pa ih možemo koristiti bez navođenja imena tipa:

```cpp
Direction currentDirection{Up};
```

To znači i da dva `enum` tipa u istom području vidljivosti ne mogu imati enumeratore jednakih imena.

**Primjer 2:**

```cpp
enum Direction
{
    Idle,
    Up,
    Down
};

enum MotorState
{
    Stopped,
    Up,       // Greška: Up već postoji
    Down      // Greška: Down već postoji
};
```

Enumeratori `Up` i `Down` iz prvog `enum` tipa već su dostupni izravno, pa bi drugi `enum` pokušao definirati ista imena u istom području vidljivosti.
Klasični `enum` također dopušta implicitnu pretvorbu enumeratora u cijeli broj.

**Primjer 3:**

```cpp
int value{Up};
```

## 2. `enum class`

`enum class` je uveden u C++11 i predstavlja scoped enumeraciju.

**Primjer 4:**

```cpp
enum class Direction
{
    Idle,
    Up,
    Down
};

Direction currentDirection{Direction::Up};
```

Enumeratorima pristupamo preko imena tipa:

```cpp
Direction::Idle
Direction::Up
Direction::Down
```

To jasno pokazuje kojem tipu određena vrijednost pripada.
`enum class` također koristi cjelobrojnu podlogu. Ako vrijednosti ne zadamo ručno, enumeratori ponovno dobivaju vrijednosti `0`, `1`, `2` i tako dalje.
Međutim, `enum class` ne dopušta implicitnu pretvorbu u `int`.
Ovo nije dopušteno:

```cpp
int value{Direction::Up};
```

Za pretvorbu je potrebno jasno navesti da je želimo:

```cpp
int value{static_cast<int>(Direction::Up)};
```

`enum class` ima dvije važne prednosti:
- enumeratori se nalaze u scopeu pripadajućeg tipa
- nema implicitne pretvorbe u cijeli broj

**Primjer 5:**

```cpp
enum class DoorState
{
    Open,
    Closed
};

enum class MotorState
{
    Open,
    Closed
};
```

Ovo je potpuno valjano jer su imena odvojena:

```cpp
DoorState::Open
MotorState::Open
```

## 3. `enum struct`

C++ dopušta i zapis:

```cpp
enum struct Direction
{
    Idle,
    Up,
    Down
};
```

`enum struct` i `enum class` imaju isto značenje. `enum struct` predstavlja samo alternativni oblik sintakse.

Dakle:

```cpp
enum class Direction
```

i:

```cpp
enum struct Direction
```

definiraju istu vrstu scoped enumeracije. 
U praksi se puno češće koristi `enum class`.

## 4. Kada koristiti enumeraciju?

Enumeracija je prikladna kada podatak može imati jednu vrijednost iz malog, unaprijed poznatog skupa mogućnosti.

**Primjer 6:**

```cpp
enum class Direction
{
    Idle,
    Up,
    Down
};
```

**Primjer 7:**

```cpp
enum class DoorState
{
    Open,
    Closed
};
```

**Primjer 8:**

```cpp
enum class ElevatorState
{
    Idle,
    Moving,
    DoorOpen,
    Error
};
```

Enumeracija je bolji izbor od proizvoljnih cijelih brojeva poput:

```cpp
int state{2};
```

jer iz same vrijednosti `2` nije jasno što ona predstavlja.

Kod enumeracije možemo napisati:

```cpp
ElevatorState state{ElevatorState::DoorOpen};
```

pa je značenje vrijednosti odmah jasno iz koda.

## 5. Sažetak

- `enum` definira korisnički tip s unaprijed zadanim vrijednostima
- enumeraciju koristimo kada podatak ima mali, unaprijed poznat skup mogućih vrijednosti
- pojedine vrijednosti enumeracije nazivaju se enumeratori
- enumeratori imaju cjelobrojnu vrijednost (ako vrijednosti ne navedemo ručno, počinju od `0` i rastu za `1`)
- kod `enum` tipa enumeratori su dostupni izravno u opsegu (scope) u kojem je `enum` definiran, stoga dva `enum` tipa u istom opsegu ne mogu imati enumeratore jednakih imena
- `enum` dopušta implicitnu pretvorbu u cijeli broj
- `enum class` uveden je u C++11 i koristi vlastiti scope (enumerator navodimo kao `Tip::Enumerator`) stoga je sigurniji kao tip podatka od `enum`
- `enum class` nema implicitnu pretvorbu u cijeli broj
- `enum struct` ima isto značenje kao `enum class`, ali uglavnom programeri preferiraju koristiti `enum class`