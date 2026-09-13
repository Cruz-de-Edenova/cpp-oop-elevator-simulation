# Polja fiksne veličine, dinamički alocirana polja i `std::vector`

U prethodnoj temi pokazivač smo koristili za pristup jednoj postojećoj varijabli ili jednom dinamički stvorenom objektu. U ovoj temi uspoređujemo polja fiksne veličine (*fixed-size arrays*) s dinamičkim poljima, koja se stvaraju tijekom izvođenja programa.

Glavni cilj je razumjeti kako rade `new[]` i `delete[]`, kako pokazivač omogućuje pristup elementima dinamičkog polja te zašto broj elemenata moramo čuvati zasebno.

Obradit ćemo i dvodimenzionalna te višedimenzionalna dinamička polja. Na kraju ćemo kratko usporediti ručno upravljanje dinamičkim poljima pomoću `new[]` i `delete[]` s korištenjem spremnika `std::vector`.

## Sadržaj

1. Polje fiksne veličine i dinamički alocirano polje
2. Range-based `for` petlja
3. Kratki osvrt na `auto`
4. Dinamički alocirano jednodimenzionalno polje
5. Prolazak kroz dinamičko polje
6. Oslobađanje dinamičkog polja operatorom `delete[]`
7. Dvodimenzionalno polje s dinamički alociranim redovima
8. Dinamički alocirano dvodimenzionalno polje pomoću pokazivača na pokazivač
9. Dinamički alocirana trodimenzionalna i N-dimenzionalna polja
10. `std::vector` kao alternativa dinamički alociranom polju
11. Aritmetika pokazivača
12. GDB demonstracija
13. Sažetak

Prateći primjeri:

- `basic_arrays.cpp`
- `dynamic_arrays.cpp`
- `multidimensional_arrays.cpp`

---

## 1. Polje fiksne veličine i dinamički alocirano polje

### Polje fiksne veličine (*fixed-size array*)

Možemo definirati kada je broj elemenata poznat pri kompajliranju:

```cpp
constexpr int elementCount{5};

int values[elementCount]{};  // Inicijalizira sve elemente na nulu
```

Broj elemenata dio je deklaracije polja fiksne veličine i mora biti poznat pri kompajliranju.

Lokalno polje `values` nalazi se na stacku, a njegovi elementi smješteni su uzastopno u memoriji. Ako radi jednostavnosti pretpostavimo da prvi element počinje na adresi `0x7000` i da `int` zauzima četiri bajta:

```text
                         STACK

values
+-------+-------+-------+-------+-------+
|   0   |   0   |   0   |   0   |   0   |
+-------+-------+-------+-------+-------+
   [0]     [1]     [2]     [3]     [4]
 0x7000  0x7004  0x7008  0x700C  0x7010
```

### Dinamički alocirano polje (*dynamically allocated array*)

Ako broj elemenata saznajemo tek tijekom izvođenja programa, možemo dinamički zauzeti potrebnu memoriju:

```cpp
int elementCount{};

cin >> elementCount;

int* ptrValues{new int[elementCount]{}};  // Svi elementi imaju vrijednost 0
```

`ptrValues` nije polje, nego pokazivačka varijabla koja sadrži adresu prvog elementa dinamičkog polja. Elementi dinamičkog polja, kao i elementi polja fiksne veličine, smješteni su uzastopno u memoriji.

Ako pretpostavimo početnu adresu dinamičkog polja `0x5000`, odnos možemo pojednostavljeno prikazati ovako:

```text
                              |
      STACK                   |                HEAP
                              |
+------------------------+    |      +-------+-------+-------+-------+
| ptrValues              |  --|-->   |   0   |   0   |   0   |  ...  |
| vrijednost: 0x5000     |    |      +-------+-------+-------+-------+
+------------------------+    |         [0]     [1]     [2]    [...]
                              |        0x5000  0x5004  0x5008
```

Na stacku se nalazi pokazivačka varijabla `ptrValues`, dok se elementi dinamičkog polja nalaze na heapu.

---

## 2. Range-based `for` petlja

Range-based `for` petlja omogućuje jednostavan prolazak kroz sve elemente polja fiksne veličine kada nam indeks nije potreban:

```cpp
int selectedFloors[]{2, 5, 1, 4};

for (int floor : selectedFloors)
{
    cout << floor << '\n';
}
```

Varijabla `floor` redom dobiva vrijednost svakog elementa polja.

Ekvivalentan prolazak indeksiranom `for` petljom izgleda ovako:

```cpp
constexpr int selectedFloorCount{4};
int selectedFloors[selectedFloorCount]{2, 5, 1, 4};

for (int index{0}; index < selectedFloorCount; ++index)
{
    cout << selectedFloors[index] << '\n';
}
```

Postoji i oblik range-based `for` petlje koji koristi reference i omogućuje izravnu promjenu elemenata. Reference ćemo formalno obraditi u temi 04, pa taj oblik ovdje ne koristimo.

---

## 3. Kratki osvrt na `auto`

Ključna riječ `auto` omogućuje kompajleru da zaključi tip varijable iz inicijalizatora:

```cpp
auto currentFloor{3};  // Kompajler zaključuje tip int
```

`auto` može biti koristan kada je tip potpuno jasan iz konteksta, ali u ovoj temi ne želimo njime sakriti tipove pokazivača koje upravo učimo.

Preferiramo:

```cpp
int* ptrValues{new int[elementCount]{}};
```

umjesto:

```cpp
auto ptrValues{new int[elementCount]{}};
```

Kasnije ćemo ga koristiti tamo gdje tip nije važan za koncept koji se objašnjava.

---

## 4. Dinamički alocirano jednodimenzionalno polje

Dinamičko polje stvaramo operatorom `new[]`:

```cpp
constexpr int elementCount{5};

int* ptrValues{new int[elementCount]{}};  // Stvara 5 int elemenata
```

`new[]` vraća adresu prvog elementa, a elementima pristupamo operatorom `[]`:

```cpp
ptrValues[0] = 2;
ptrValues[1] = 5;

cout << ptrValues[0] << '\n';
cout << ptrValues[1] << '\n';
```

Ako pretpostavimo početnu adresu `0x5000` i veličinu tipa `int` od četiri bajta:

```text
ptrValues
    ↓
+-----------+-----------+-----------+-----------+
|     2     |     5     |     0     |     0     |
+-----------+-----------+-----------+-----------+
    [0]         [1]         [2]         [3]
  0x5000      0x5004      0x5008      0x500C
```

Pokazivač sadrži samo početnu adresu, a indeks određuje kojem elementu pristupamo.

---

## 5. Prolazak kroz dinamičko polje

Pokazivač ne sadrži broj elemenata dinamičkog polja, pa veličinu čuvamo zasebno i koristimo je kao granicu indeksirane petlje:

```cpp
constexpr int elementCount{5};

int* ptrValues{new int[elementCount]{}};

for (int index{0}; index < elementCount; ++index)
{
    ptrValues[index] = index + 1;
}

for (int index{0}; index < elementCount; ++index)
{
    cout << ptrValues[index] << '\n';
}
```

Za dinamičko polje kojem pristupamo preko `int*` ne možemo izravno koristiti range-based `for` petlju jer pokazivač sam ne sadrži informaciju o granicama polja.

---

## 6. Oslobađanje dinamičkog polja operatorom `delete[]`

Polje stvoreno operatorom `new[]` oslobađamo odgovarajućim operatorom `delete[]`:

```cpp
int* ptrValues{new int[elementCount]{}};

// Rad s poljem

delete[] ptrValues;
ptrValues = nullptr;
```

Važno je pravilno upariti način stvaranja i oslobađanja:

```cpp
int* ptrValue{new int{7}};
delete ptrValue;

int* ptrValues{new int[elementCount]{}};
delete[] ptrValues;
```

Korištenje `delete` za memoriju dobivenu s `new[]` uzrokuje nedefinirano ponašanje (*undefined behavior*).

Nakon `delete[]` elementi polja više ne postoje, pa u početnim primjerima pokazivač odmah postavljamo na `nullptr`.

---

## 7. Dvodimenzionalno polje s dinamički alociranim redovima

Jedan način izgradnje dvodimenzionalnog polja jest koristiti polje pokazivača fiksne veličine, pri čemu svaki pokazivač vodi do zasebno dinamički alociranog retka:

```cpp
constexpr int floorCount{3};    // Broj katova
constexpr int readingCount{4};  // Broj očitanja senzora po katu

int* ptrSensorReadings[floorCount]{};

for (int floorIndex{0}; floorIndex < floorCount; ++floorIndex)
{
    ptrSensorReadings[floorIndex] = new int[readingCount]{};
}
```

Pojedinom elementu pristupamo s dva indeksa:

```cpp
ptrSensorReadings[1][2] = 25;
```

```text
    STACK            |                   HEAP
                     |
indeks kata:         |            indeks očitanja:
                     |            [0]   [1]   [2]   [3]
ptrSensorReadings    |
+---------+          |          +-----+-----+-----+-----+
| [0] ----+----------|--------> |  0  |  0  |  0  |  0  |
+---------+          |          +-----+-----+-----+-----+
| [1] ----+----------|--------> |  0  |  0  | 25  |  0  |
+---------+          |          +-----+-----+-----+-----+
| [2] ----+----------|--------> |  0  |  0  |  0  |  0  |
+---------+          |          +-----+-----+-----+-----+
                     |
elementi tipa int*   |              elementi tipa int
```

Svaki red stvoren je zasebnim `new[]`, pa svaki red zasebno oslobađamo:

```cpp
for (int floorIndex{0}; floorIndex < floorCount; ++floorIndex)
{
    delete[] ptrSensorReadings[floorIndex];
    ptrSensorReadings[floorIndex] = nullptr;
}
```

Vanjsko polje `ptrSensorReadings` polje je fiksne veličine, sastoji se od elemenata tipa `int*` i nije stvoreno pomoću `new[]`, pa se za njega ne poziva `delete[]`.

---

## 8. Dinamički alocirano dvodimenzionalno polje pomoću pokazivača na pokazivač

Ako ni broj redaka nije poznat pri kompajliranju, možemo dinamički alocirati i polje pokazivača:

```cpp
int** ptrSensorReadings{new int*[floorCount]{}};
```

Tip `int**` označava pokazivač na pokazivač na `int`.

Svaki element tog dinamičkog polja zatim dobiva adresu zasebno alociranog retka:

```cpp
for (int floorIndex{0}; floorIndex < floorCount; ++floorIndex)
{
    ptrSensorReadings[floorIndex] = new int[readingCount]{};
}
```

```text
      STACK            |                HEAP
                       |
ptrSensorReadings      |       indeks kata:        indeks očitanja:
+---------+            |                           [0] [1] [2] [3]
| int** --+------------|-----> +---------+        +---+---+---+---+
+---------+            |       | [0] ----+------> | 0 | 0 | 0 | 0 |
                       |       +---------+        +---+---+---+---+
                       |       | [1] ----+------> | 0 | 0 |25 | 0 |
                       |       +---------+        +---+---+---+---+
                       |       | [2] ----+------> | 0 | 0 | 0 | 0 |
                       |       +---------+        +---+---+---+---+
                       |
                       |       elementi             elementi
                       |       tipa int*            tipa int
```

Pristup elementu ostaje pregledan:

```cpp
ptrSensorReadings[floorIndex][readingIndex]
```

Oslobađanje mora slijediti obrnuti redoslijed od stvaranja:

```cpp
for (int floorIndex{0}; floorIndex < floorCount; ++floorIndex)
{
    delete[] ptrSensorReadings[floorIndex];
    ptrSensorReadings[floorIndex] = nullptr;
}

delete[] ptrSensorReadings;
ptrSensorReadings = nullptr;
```

Najprije oslobađamo retke, a zatim dinamički alocirano polje pokazivača.

---

## 9. Dinamički alocirana trodimenzionalna i N-dimenzionalna polja

Isti se princip može proširiti na dodatne dimenzije.

Primjer trodimenzionalnog dinamički alociranog polja može predstavljati:

```text
kat -> senzor -> očitanje
```

Za tri razine koristimo pokazivač na pokazivač na pokazivač:

```cpp
int*** ptrSensorReadings{};
```

Memorija se zauzima u tri koraka:

1. stvara se dinamičko polje elemenata tipa `int**`
2. za svaki element stvara se dinamičko polje elemenata tipa `int*`
3. za svaki od tih elemenata stvara se dinamičko polje elemenata tipa `int`

Pristup pojedinoj vrijednosti koristi tri indeksa:

```cpp
ptrSensorReadings[floorIndex][sensorIndex][readingIndex]
```

Oslobađanje se provodi obrnutim redoslijedom: najprije najunutarnja polja, zatim srednja polja pokazivača i na kraju vanjsko polje.

Isti obrazac može se nastavljati na četiri ili više dimenzija, ali broj razina pokazivača, alokacija i potrebnih `delete[]` operacija brzo raste. Cilj ovog poglavlja je razumjeti obrazac, a ne koristiti višedimenzionalnu ručnu alokaciju kao zadani dizajn.

---

## 10. `std::vector` kao alternativa dinamički alociranom polju

Standardna biblioteka nudi `std::vector`, spremnik čija se veličina može određivati i mijenjati tijekom izvođenja programa:

```cpp
#include <vector>

std::vector<int> objSelectedFloors{2, 5, 1, 4};

objSelectedFloors.push_back(6);  // Dodaje element na kraj
```

Broj elemenata dobivamo metodom `size()`, a kroz elemente možemo prolaziti range-based `for` petljom:

```cpp
cout << objSelectedFloors.size() << '\n';

for (auto floor : objSelectedFloors)
{
    cout << floor << '\n';
}
```

`std::vector` omogućuje i uklanjanje pojedinog elementa. Primjerice, možemo ukloniti element s indeksom `1`:

```cpp
std::vector<int> objSelectedFloors{2, 5, 1, 4};

objSelectedFloors.erase(objSelectedFloors.begin() + 1);
```

Nakon brisanja sadržaj spremnika je:

```text
indeks:       [0] [1] [2]
vrijednost:    2   1   4
```

Metoda `begin()` ovdje označava početak spremnika, a `+ 1` poziciju drugog elementa.

Nakon uklanjanja elementa `std::vector` sam preslaže preostale elemente tako da između njih ne ostane prazno mjesto.

To je značajna prednost u usporedbi s dinamičkim poljem stvorenim pomoću `new[]`, gdje pojedini element ne možemo ukloniti pomoću `delete[]`. Ako nakon logičkog uklanjanja želimo zadržati elemente zbijene, njihovo preslagivanje moramo napraviti vlastitim kodom.

Neke korisne metode spremnika `std::vector` su:

| Metoda | Značenje |
| --- | --- |
| `push_back(value)` | dodaje element na kraj |
| `pop_back()` | uklanja posljednji element |
| `erase(position)` | uklanja element na zadanoj poziciji |
| `size()` | vraća broj elemenata |
| `empty()` | provjerava je li spremnik prazan |
| `clear()` | uklanja sve elemente |

Primjer:

```cpp
objSelectedFloors.pop_back();  // Uklanja posljednji element

if (!objSelectedFloors.empty())
{
    cout << "Broj odabranih katova: "
         << objSelectedFloors.size() << '\n';
}

objSelectedFloors.clear();  // Uklanja sve elemente
```

`std::vector` sam upravlja memorijom koju koristi, pa ne pišemo ručno `new[]` i `delete[]`.

U modernom C++ kodu `std::vector` je često bolji izbor od dinamičkog polja stvorenog pomoću `new[]`. Dinamička polja ipak obrađujemo jer su važna za razumijevanje pokazivača, dinamičke memorije i višerazinske indirekcije.

---

## 11. Aritmetika pokazivača

Elementima dinamičkog polja možemo pristupati indeksima ili pomoću aritmetike pokazivača.

Za jednodimenzionalno polje ova su dva izraza ekvivalentna:

```cpp
ptrValues[index]
*(ptrValues + index)
```

Izraz `ptrValues + index` pomiče pokazivač za `index` elemenata tipa `int`, a operator `*` zatim dohvaća vrijednost na toj adresi.

Isti princip možemo primijeniti i na dvodimenzionalno dinamički alocirano polje.

### Primjer: tipke upravljačke ploče lifta

Pretpostavimo pojednostavljenu upravljačku ploču s dva retka i tri tipke. Vrijednost `false` znači da tipka nije pritisnuta, a `true` da je pritisnuta.

```cpp
constexpr int rowCount{2};     // Broj redaka tipki
constexpr int buttonCount{3};  // Broj tipki po retku

bool** ptrButtonStates{new bool*[rowCount]{}};

for (int rowIndex{0}; rowIndex < rowCount; ++rowIndex)
{
    ptrButtonStates[rowIndex] = new bool[buttonCount]{};
}

ptrButtonStates[1][2] = true;
```

Indeksni zapis i aritmetika pokazivača pristupaju istom elementu:

```cpp
ptrButtonStates[1][2]
*(*(ptrButtonStates + 1) + 2)
```

```text
                 indeks tipke
               [0]    [1]    [2]

redak [0]     false  false  false
redak [1]     false  false   true
                              ↑
                   ptrButtonStates[1][2]
                   *(*(ptrButtonStates + 1) + 2)
```

Izraz:

```cpp
ptrButtonStates + 1
```

pomiče se do drugog pokazivača u dinamički alociranom polju pokazivača.

Dereferenciranje:

```cpp
*(ptrButtonStates + 1)
```

daje pokazivač na početak drugog retka.

Dodavanjem još jednog pomaka:

```cpp
*(ptrButtonStates + 1) + 2
```

dolazimo do trećeg elementa tog retka, a završno dereferenciranje dohvaća njegovu vrijednost:

```cpp
*(*(ptrButtonStates + 1) + 2)
```

Zato vrijedi:

```cpp
ptrButtonStates[rowIndex][buttonIndex]
```

isto što i:

```cpp
*(*(ptrButtonStates + rowIndex) + buttonIndex)
```

Indeksni zapis je u pravilu čitljiviji i zato ga preferiramo za rad s poljima. Aritmetika pokazivača ovdje je korisna prvenstveno za razumijevanje veze između pokazivača, adresa i indeksnog pristupa elementima.

---

## 12. GDB demonstracija

Za GDB demonstraciju odabran je `dynamic_arrays.cpp` jer u funkciji `demonstrate_dynamic_array()` možemo promatrati stvaranje, sadržaj i oslobađanje dinamičkog polja.

```text
E:\Files\G++\OOP\03-pokazivaci\03-02-dinamicka-polja>gdb -silent dynamic_arrays.exe
Reading symbols from dynamic_arrays.exe...
(gdb) list 11,37
11      void demonstrate_dynamic_array()
12      {
13          constexpr int elementCount{5};
14
15          int* ptrValues{new int[elementCount]{}};
16
17          for (int index{0}; index < elementCount; ++index)
18          {
19              ptrValues[index] = index + 1;
20          }
21
22          cout << "Elementi dinamickog polja:\n";
23
24          for (int index{0}; index < elementCount; ++index)
25          {
26              cout << ptrValues[index] << '\n';
27          }
28
29          cout << "Velicina pokazivacke varijable: " << sizeof(ptrValues) << '\n';
30
31          delete[] ptrValues;
32          ptrValues = nullptr;
33
34          cout << "Pokazivac je nullptr: "
35               << (ptrValues == nullptr ? "da" : "ne") << '\n';
36          cout << "------------------------------\n";
37      }
(gdb) break demonstrate_dynamic_array
Breakpoint 1 at 0x140001718: file dynamic_arrays.cpp, line 13.
(gdb) run > NUL
Starting program: E:\Files\G++\OOP\03-pokazivaci\03-02-dinamicka-polja\dynamic_arrays.exe > NUL
[New Thread 11204.0x285c]
[New Thread 11204.0x24ac]
[New Thread 11204.0x10c]

Thread 1 hit Breakpoint 1, demonstrate_dynamic_array () at dynamic_arrays.cpp:13
13          constexpr int elementCount{5};
(gdb) until 22
demonstrate_dynamic_array () at dynamic_arrays.cpp:22
22          cout << "Elementi dinamickog polja:\n";
(gdb) p ptrValues
$1 = (int *) 0x98560
(gdb) p &ptrValues[0]
$2 = (int *) 0x98560
(gdb) p *ptrValues@elementCount
$3 = {1, 2, 3, 4, 5}
(gdb) until 32
demonstrate_dynamic_array () at dynamic_arrays.cpp:32
32          ptrValues = nullptr;
(gdb) p ptrValues
$4 = (int *) 0x98560
(gdb) n
[New Thread 11204.0x23ec]
35               << (ptrValues == nullptr ? "da" : "ne") << '\n';
(gdb) p ptrValues
$5 = (int *) 0x0
(gdb) q
```

### Sažeti opis gornje demonstracije

Adresa prvog elementa (`&ptrValues[0]`) mora odgovarati vrijednosti pokazivača (`ptrValues`).

Umjesto prolaska kroz svaku iteraciju pomoću `next`, naredbom `until` možemo nastaviti izvođenje do prvog izvršnog retka nakon petlje.

Nakon izvršene petlje sadržaj dinamičkog polja možemo provjeravati pojedinačno:

```text
(gdb) p ptrValues[0]
(gdb) p ptrValues[1]
...
(gdb) p ptrValues[4]
```

GDB omogućuje i praktičniji prikaz više uzastopnih elemenata pomoću operatora `@`. Ako znamo broj elemenata polja, u ovom slučaju spremljen u varijabli `elementCount`, cijelo dinamičko polje možemo prikazati naredbom:

```text
(gdb) p *ptrValues@elementCount
```

Izraz `*ptrValues` označava prvi element, a `@elementCount` govori GDB-u koliko uzastopnih elemenata treba prikazati.

Nakon izvršavanja:

```cpp
delete[] ptrValues;
```

dinamičko polje više ne postoji. Vrijednost pokazivačke varijable još možemo pregledati, ali pokazivač se više ne smije dereferencirati:

```text
(gdb) p ptrValues
```

Nakon sljedećeg retka:

```cpp
ptrValues = nullptr;
```

ponovno provjeravamo pokazivač:

```text
(gdb) p ptrValues
```

Očekujemo prikaz vrijednosti null pokazivača poput:

```text
(int *) 0x0
```

Ova demonstracija pokazuje razliku između pokazivačke varijable `ptrValues`, dinamičkog polja na koje ona pokazuje i pojedinih elemenata tog polja.

---

## 13. Sažetak

### Usporedba polja fiksne veličine, dinamičkog polja i `std::vector`

| Svojstvo | Polje fiksne veličine | Dinamičko polje stvoreno pomoću `new[]` | `std::vector` |
| --- | --- | --- | --- |
| Broj elemenata | poznat pri kompajliranju | može biti određen tijekom izvođenja | može biti određen tijekom izvođenja |
| Ručni `new[]` | ne | da | ne |
| Ručni `delete[]` | ne | da | ne |
| Informacija o broju elemenata | poznata iz tipa polja | pokazivač je ne sadrži | dostupna pomoću `size()` |
| Mogućnost korištenja range-based `for` petlje | da | ne, jer pokazivač ne sadrži broj elemenata | da |
| Upravljanje memorijom | automatsko | ručno | automatsko |

Dinamičko polje stvoreno pomoću `new[]` daje izravan uvid u mehanizam dinamičke memorije, dok `std::vector` uklanja potrebu za ručnim upravljanjem tom memorijom.

### Mogućnost upotrebe range-based `for` petlje

| Slučaj | Može li se izravno koristiti range-based `for`? | Objašnjenje |
| --- | --- | --- |
| Polje fiksne veličine, npr. `int values[5]` | da | kompajler zna broj elemenata polja |
| Polje fiksne veličine čiji su elementi pokazivači, npr. `int* rows[3]` | da | petlja prolazi kroz elemente tipa `int*` |
| Dinamičko 1D polje stvoreno pomoću `new[]` kojem pristupamo preko `int*` | ne | pokazivač ne sadrži broj elemenata dinamičkog polja |
| 2D dinamički alocirano polje kojem pristupamo preko `int**` | ne | pokazivač prve razine ne sadrži broj elemenata |
| 3D dinamički alocirano polje kojem pristupamo preko `int***` | ne | pokazivač prve razine ne sadrži broj elemenata |
| `std::vector<int>` | da | spremnik omogućuje određivanje početka i kraja raspona elemenata |

### Razine pokazivača

| Tip | Značenje tipa | Broj razina indirekcije | Tipičan primjer u ovoj temi | Indeksirani pristup |
| --- | --- | ---: | --- | --- |
| `int*` | pokazivač na `int` | 1 | dinamičko 1D polje | `ptrValues[i]` |
| `int**` | pokazivač na pokazivač na `int` | 2 | 2D dinamički alocirano polje | `ptrValues[i][j]` |
| `int***` | pokazivač na pokazivač na pokazivač na `int` | 3 | 3D dinamički alocirano polje | `ptrValues[i][j][k]` |

Sam tip `int*`, `int**` ili `int***` ne znači automatski da postoji 1D, 2D ili 3D polje. Tip određuje broj razina pokazivača, dok način na koji je memorija organizirana određuje stvarni raspored podataka. Primjer:

```cpp
int value{7};
int* ptrValue{&value};                // *ptrValue == 7
int** ptrPtrValue{&ptrValue};         // **ptrPtrValue == 7
int*** ptrPtrPtrValue{&ptrPtrValue};  // ***ptrPtrPtrValue == 7
```

### Uparivanje alokacije i oslobađanja

| Što stvaramo | Stvaranje | Oslobađanje |
| --- | --- | --- |
| Jedan dinamički objekt | `new int{7}` | `delete ptrValue` |
| Dinamičko polje | `new int[count]{}` | `delete[] ptrValues` |

Za višedimenzionalna dinamički alocirana polja svaka razina stvorena pomoću `new[]` mora imati odgovarajući `delete[]`, a oslobađanje se provodi obrnutim redoslijedom od stvaranja.

`auto` koristimo kada ne skriva tip važan za razumijevanje primjera, a `std::vector` u modernom C++-u često zamjenjuje potrebu za ručnim `new[]` i `delete[]`.
