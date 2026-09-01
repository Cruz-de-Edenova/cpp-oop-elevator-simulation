# `const` i `constexpr`

`const` i `constexpr` koriste se kada želimo jasno izraziti da se neka vrijednost ne smije mijenjati. Ipak, ta dva pojma nisu ista.

- `const` je kvalifikator tipa (type qualifier), što znači da se vrijednost nakon inicijalizacije ne može mijenjati kroz taj naziv.
- `constexpr` je specifikator (specifier). Kod varijable znači da vrijednost mora biti poznata za vrijeme kompajliranja programa, te je zato ujedno konstantna. Dodatna osobina `constexpr` je da se može koristiti i kao specifikator funkcije.
---

## 1. `const` varijable

Varijabla označena s `const` mora biti inicijalizirana pri stvaranju jer joj se kasnije ne može dodijeliti nova vrijednost.

```cpp
const int minimumFloor{0};
const int maximumFloor{10};
```

Nakon inicijalizacije nije dopušteno:

```cpp
minimumFloor = 1;   // Pogreška: minimumFloor je const
```

Vrijednost `const` varijable ne mora nužno biti poznata za vrijeme kompajliranja. Može se dobiti i tijekom izvođenja programa.

```cpp
int currentFloor{3};
const int startingFloor{currentFloor};
```

`startingFloor` se nakon inicijalizacije više ne može mijenjati, ali njegova početna vrijednost nije nužno 'compile-time' konstanta.

### Praktična korist

`const`:

- sprječava slučajnu promjenu vrijednosti
- dokumentira namjeru programera
- omogućuje kompajleru da prijavi pokušaj nedopuštene promjene
- posebno je važan kada kasnije počnemo prosljeđivati objekte pomoću referenci i pokazivača

---

## 2. `constexpr` varijable

`constexpr` varijabla također se ne može mijenjati, ali dodatno zahtijeva da njezina vrijednost bude određena za vrijeme kompajliranja.

```cpp
constexpr int floorCount{10};
constexpr int secondsPerFloor{2};
constexpr int fullTravelTime{floorCount * secondsPerFloor};
```

Ovdje kompajler može izračunati vrijednost `fullTravelTime`.

`constexpr` varijabla mora biti inicijalizirana izrazom koji se može izračunati za vrijeme kompajliranja.

```cpp
//int currentFloor{3};   // Pogrešno: currentFloor nije 'compile-time' konstanta
constexpr int currentFloor{3};   // Ispravno
constexpr int startingFloor{currentFloor};
```

---

## 3. `const` parametar funkcije proslijeđen po vrijednosti

Kod običnih tipova, primjerice `int`, parametar proslijeđen po vrijednosti je kopija argumenta pozivatelja.

```cpp
void print_floor(const int floor)
{
    // floor je lokalna kopija i ova funkcija je ne smije mijenjati
}
```

Ako pozovemo:

```cpp
int currentFloor{4};
print_floor(currentFloor);
```

funkcija dobiva svoju kopiju vrijednosti `currentFloor`. Kvalifikator `const` štiti samo tu lokalnu kopiju. Ne pruža dodatnu zaštitu varijabli `currentFloor` kod pozivatelja jer se ona ionako ne prosljeđuje izravno.

Zbog toga se `const` na parametru koji se prosljeđuje po vrijednosti najčešće ne koristi kao dio sučelja funkcije.

```cpp
void print_floor(int floor);
```

Unutar same definicije funkcije programer ipak može koristiti `const` ako želi spriječiti slučajnu promjenu lokalne kopije.

```cpp
void print_floor(const int floor)
{
    // floor = 5;   // Nije dopušteno
}
```

---

## 4. `const` s referencama i pokazivačima

Kod referenci i pokazivača situacija je drugačija jer funkcija tada može pristupati postojećem objektu pozivatelja, a ne samo vlastitoj kopiji.

```cpp
void print_value(const int& refValue);
void print_value(const int* ptrValue);
```

U takvim slučajevima `const` ima stvarnu važnost za sučelje funkcije, jer govori da funkcija neće mijenjati objekt kojem pristupa kroz tu referencu ili pokazivač.

Ovo će se obrađivati detaljnije u temama vezanim za reference i pokazivače.

---

## 5. `constexpr` i parametri funkcije

`constexpr` se ne može staviti na parametar funkcije.

Ovo nije ispravan C++ kod:

```cpp
// Neispravno
// int calculate_time(constexpr int floorCount);
```

Vrijednost parametra određuje se pri svakom pojedinom pozivu funkcije. Pri jednom pozivu argument može biti poznat tijekom kompajliranja, a pri drugom tek tijekom izvođenja programa.

Zbog toga parametar sam po sebi nije `constexpr` varijabla i ne može se deklarirati pomoću specifikatora `constexpr`.

```cpp
constexpr int floorCount{5};
calculate_time(floorCount);   // Vrijednost poznata tijekom kompajliranja

int currentFloor{0};
cin >> currentFloor;
calculate_time(currentFloor); // Vrijednost poznata tek tijekom izvođenja
```

---

## 6. `constexpr` funkcije

Ključna riječ `constexpr` može se koristiti i pri deklaraciji funkcije.

```cpp
constexpr int calculate_travel_time(int floorCount, int secondsPerFloor)
{
    return floorCount * secondsPerFloor;
}
```

U ovoj deklaraciji:

```text
constexpr              -> specifikator funkcije
int                    -> tip povratne vrijednosti
calculate_travel_time  -> naziv funkcije
(int, int)             -> tipovi parametara
```

Prema tome, `constexpr` ovdje **ne označava povratnu vrijednost funkcije**. Funkcija vraća običnu vrijednost tipa `int`.

`constexpr` je specifikator same funkcije i označava da se funkcija može koristiti u konstantnom izrazu ako su za to ispunjeni potrebni uvjeti.

### Poziv funkcije s vrijednostima poznatima za vrijeme kompajliranja

```cpp
constexpr int floors{5};
constexpr int secondsPerFloor{2};

constexpr int travelTime{calculate_travel_time(floors, secondsPerFloor)};
```

Varijabla `travelTime` deklarirana je kao `constexpr`, pa njezina vrijednost mora biti poznata tijekom prevođenja programa.

Argumenti `floors` i `secondsPerFloor` također su `constexpr`, pa kompajler može tijekom prevođenja izračunati:

```text
5 * 2 = 10
```

U ovom slučaju poziv funkcije sudjeluje u izračunu konstantnog izraza.

### Poziv iste funkcije s runtime vrijednošću

`constexpr` funkcija nije posebna funkcija namijenjena samo compile-time izračunima. Ista funkcija može se pozvati i s vrijednostima koje su poznate tek tijekom izvođenja programa.

```cpp
int floors{0};
cin >> floors;

int travelTime{calculate_travel_time(floors, 2)};
```

Vrijednost varijable `floors` ovisi o unosu korisnika i zato nije poznata tijekom prevođenja.

Poziva se ista funkcija:

```cpp
calculate_travel_time(floors, 2)
```

ali njezin se rezultat u ovom slučaju određuje tijekom izvođenja programa.

Ne postoje dvije različite funkcije. Postoji samo jedna `constexpr` funkcija koja se može pozivati u različitim okolnostima.

```text
constexpr funkcija
        |
        +-- poziv s compile-time vrijednostima
        |       -> može sudjelovati u compile-time izračunu
        |
        +-- poziv s runtime vrijednostima
                -> koristi se kao običan runtime izračun
```

### `constexpr` varijabla i `constexpr` funkcija

Važno je razlikovati značenje `constexpr` kod varijable i kod funkcije.

```cpp
constexpr int secondsPerFloor{2};
```

Kod varijable `constexpr` znači da njezina vrijednost mora biti poznata tijekom prevođenja programa.

```cpp
constexpr int calculate_travel_time(int floorCount, int secondsPerFloor);
```

Kod funkcije `constexpr` je specifikator funkcije. On ne označava povratni tip i ne znači da se svaki poziv te funkcije mora izvršiti za vrijeme kompajliranja.

---

## 7. Povratna vrijednost funkcije s `const`

Kod obične povratne vrijednosti funkcija vraća novu vrijednost, odnosno rezultat koji pozivatelj prima kao zasebnu vrijednost.

Dodavanje `const` na povratnu vrijednost osnovnog tipa **nema praktičnu korist**:

```cpp
const int get_default_floor();
```

Pozivatelj svejedno može rezultat spremiti u običnu promjenjivu varijablu:

```cpp
int floor{get_default_floor()};
floor = 3;
```

---

## 8. Sažetak

- `const` je kvalifikator tipa i znači da se vrijednost nakon inicijalizacije ne može mijenjati kroz taj naziv
- `constexpr` je specifikator i kod varijable znači da vrijednost mora biti poznata tijekom kompajliranja
- `const` na parametru proslijeđenom po vrijednosti štiti samo lokalnu kopiju
- `constexpr` se ne može primijeniti izravno na parametar funkcije
- `constexpr` kod funkcije označava samu funkciju, a ne njezin povratni tip
- `constexpr` funkcija može se koristiti u compile-time izračunu kada su za to ispunjeni uvjeti
- ista `constexpr` funkcija može se koristiti i s runtime vrijednostima
- dodavanje `const` na povratnu vrijednost osnovnog tipa nema praktičnu korist

**Napomena**: `const` iza deklaracije članske funkcije klase, npr.: `get_floor() const;` ima drugo značenje. Taj oblik će biti objašnjen kada uvedemo klase i `const` objekte.

| Svojstvo / primjena | `const` | `constexpr` |
| :--- | :--- | :--- |
| **Varijable** |  |  |
| Može se koristiti pri deklaraciji varijable | da | da |
| Vrijednost varijable se nakon inicijalizacije može mijenjati | ne | ne |
| Varijabla mora biti inicijalizirana | da | da |
| Vrijednost varijable mora biti poznata tijekom kompajliranja | ne uvijek | da |
| Varijabla se može inicijalizirati 'runtime' vrijednošću | da | ne |
| Varijabla može sudjelovati u 'compile-time' izrazu | da, ako su ispunjeni dodatni uvjeti | da |
| **Funkcije** |  |  |
| Može označavati samu običnu funkciju | ne | da |
| `constexpr` funkcija može sudjelovati u 'compile-time' izračunu | nije primjenjivo | da, ako su ispunjeni potrebni uvjeti |
| `constexpr` funkcija može se pozvati s 'runtime' vrijednostima | nije primjenjivo | da |
| `const` iza deklaracije članske funkcije, npr. `get_floor() const` | da, posebno značenje koje će se obraditi u OOP poglavljima | nije primjenjivo |
| Može se koristiti na parametru proslijeđenom po vrijednosti | da, ali štiti samo lokalnu kopiju | ne |
| Može se navesti uz povratni osnovni tip funkcije | da, ali nema praktičnu korist | ne označava povratni tip, nego samu funkciju |