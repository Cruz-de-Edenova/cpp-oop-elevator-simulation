# Preopterećenje funkcija

Preopterećenje funkcija (*function overloading*) omogućuje da više funkcija ima isti naziv, ako se razlikuju po parametrima. Kompajler pri svakom pozivu određuje koja verzija funkcije najbolje odgovara navedenim argumentima.

Preopterećenje je korisno kada različite funkcije obavljaju isti logički zadatak nad različitim tipovima podataka.

---

## 1. Preopterećenje funkcija različitim tipovima parametara

Dvije funkcije mogu imati isti naziv ako imaju različite potpise.

```cpp
void print_travel_time(int seconds);
void print_travel_time(double seconds);
```

Za obične funkcije, potpis možemo pojednostavljeno promatrati kao naziv funkcije i tipove njezinih parametara.

```text
print_travel_time(int)
print_travel_time(double)
```

Kada pozovemo:

```cpp
print_travel_time(10);
```

argument `10` je tipa `int`, pa se odabire:

```cpp
void print_travel_time(int seconds);
```

Kod poziva:

```cpp
print_travel_time(10.5);
```

argument `10.5` je tipa `double`, pa se odabire:

```cpp
void print_travel_time(double seconds);
```

Kompajler taj postupak odabira odgovarajuće funkcije obavlja automatski.

---

## 2. Preopterećenje s različitim brojem parametara

Funkcije se mogu razlikovati i po broju parametara.

```cpp
void move_elevator(int floor);
void move_elevator(int floor, int speed);
```

Njihovi potpisi su:

```text
move_elevator(int)
move_elevator(int, int)
```

Poziv s jednim argumentom odabire prvu funkciju:

```cpp
move_elevator(5);
```

Poziv s dva argumenta odabire drugu:

```cpp
move_elevator(5, 2);
```

Preopterećenje zato može razlikovati funkcije prema broju parametara i prema njihovim tipovima.

### Preopterećenje prema broju i tipovima parametara

Preopterećene funkcije mogu se međusobno razlikovati istodobno i po broju parametara i po njihovim tipovima.

```cpp
void print_status(int floor);
void print_status(int floor, int direction);
void print_status(double speed);
void print_status(double speed, int direction);
```

Njihovi potpisi su:

```text
print_status(int)
print_status(int, int)
print_status(double)
print_status(double, int)
```

Svaki potpis je različit, pa funkcije mogu imati isti naziv.

Dakle, kod preopterećenja nije potrebno da se sve verzije funkcije razlikuju samo na jedan način. Dovoljno je da svaki overload ima jedinstven potpis funkcije.

---

## 3. Povratni tip ne razlikuje preopterećene funkcije

Povratni tip nije dio potpisa obične funkcije, pa se funkcije ne mogu preopteretiti samo promjenom povratnog tipa.

Ovo nije dopušteno:

```cpp
// Pogreška: obje funkcije imaju isti potpis get_floor(int)
int get_floor(int floor);
double get_floor(int floor);
```

Obje funkcije imaju isti naziv i isti tip parametra:

```text
get_floor(int)
```

Zato kompajler ne može razlikovati te dvije funkcije prema pozivu.

---

## 4. Preopterećenje funkcija sa `struct` tipovima

Preopterećenje nije ograničeno na osnovne tipove. Funkcije se mogu razlikovati i prema korisnički definiranim tipovima, primjerice `struct` tipovima.

```cpp
struct FloorRequest
{
    int mFloor;
};

struct DoorRequest
{
    bool mOpen;
};
```

Možemo definirati dvije funkcije istog naziva:

```cpp
void print_request(FloorRequest objRequest);
void print_request(DoorRequest objRequest);
```

Njihovi potpisi su različiti:

```text
print_request(FloorRequest)
print_request(DoorRequest)
```

Kod poziva:

```cpp
FloorRequest objFloorRequest{4};
DoorRequest objDoorRequest{true};

print_request(objFloorRequest);
print_request(objDoorRequest);
```

kompajler odabire odgovarajuću funkciju prema tipu argumenta.

Ovaj primjer pokazuje važnu ideju: isti naziv funkcije može predstavljati isti logički postupak nad različitim vrstama podataka.

---

## 5. Izbjegavanje pretjeranog preopterećenja standardnim konverzijama

Nije potrebno pisati zasebnu preopterećenu funkciju za svaki osnovni tip podatka. C++ pri pozivu funkcije može automatski napraviti određene **standardne konverzije tipova** (*standard conversions*).

Primjer:

```cpp
void print_floor(int floor);
```

Funkciju možemo pozvati i argumentom tipa `short`:

```cpp
short floor{3};
print_floor(floor);
```

Vrijednost tipa `short` automatski se pretvara u `int`, pa nije potrebno dodavati zasebnu funkciju:

```cpp
// Najčešće nije potrebno
void print_floor(short floor);
```

### Promocija

**Promocija** (*promotion*) je posebna vrsta standardne konverzije koju C++ izričito svrstava u viši rang pri odabiru preopterećene funkcije. Promocija **ne** znači općenito pretvaranje u "širi" tip. Tipični primjeri su: `bool -> int`, `short -> int`, `char -> int` i `float -> double`, dok je primjerice `int -> long` standardna cjelobrojna konverzija, ali nije promocija.

U određenim slučajevima cilj promocije može biti i `unsigned int`.

Primjer:

```cpp
void print_floor(int floor);

short floor{3};
print_floor(floor);
```

Pretvorba:

```text
short -> int
```

je promocija.

Međutim:

```text
int -> long
```

nije promocija, iako je `long` tipično širi tip od `int`. To je drugačija standardna konverzija.

Slično tome:

```text
int -> double
```

također je standardna konverzija, ali nije promocija.

Dakle, promociju ne treba shvatiti kao:

```text
manji tip -> bilo koji veći tip
```

nego kao posebnu skupinu konverzija koju C++ izričito definira kao promocije.

### Ostale standardne konverzije

C++ može automatski napraviti i druge standardne konverzije koje nisu promocije.

Primjeri:

```text
int    -> double
double -> int
int    -> long
double -> float
```

Primjer:

```cpp
void print_speed(double speed);

int speed{2};
print_speed(speed);
```

Pretvorba:

```text
int -> double
```

je standardna konverzija, ali nije promocija.

### Odabir preopterećene funkcije (*overload resolution*) 

Kod odabira preopterećene funkcije, kompajler uspoređuje koliko dobro argumenti odgovaraju parametrima dostupnih funkcija.

Pojednostavljeno, prednost imaju:

```text
točno podudaranje
        ↓
promocija
        ↓
ostala standardna konverzija
```

Primjer:

```cpp
void print_value(int value);
void print_value(double value);

short value{3};
print_value(value);
```

Za argument tipa `short` postoje dvije mogućnosti:

```text
short -> int      promocija
short -> double   standardna konverzija
```

Promocija ima prednost pred ostalom standardnom konverzijom, pa kompajler odabire:

```cpp
print_value(int);
```

Standardne konverzije zato mogu smanjiti potrebu za velikim brojem gotovo jednakih preopterećenih funkcija.

Ipak, treba biti oprezan: ako se argument može pretvoriti u više tipova bez jasnog boljeg izbora, može nastati dvosmislen poziv. Takav slučaj obrađen je u sljedećem poglavlju.

---

## 6. Dvosmislenost zbog preopterećenja i konverzije tipova

Standardne konverzije mogu pomoći u izbjegavanju nepotrebnih preopterećenja, ali u određenim kombinacijama mogu stvoriti dvosmislen poziv.

Pretpostavimo da postoje dvije funkcije:

```cpp
void set_door_delay(long seconds);
void set_door_delay(double seconds);
```

Poziv:

```cpp
// Pogreška: dvosmislen poziv
// set_door_delay(3);
```

koristi argument `3` tipa `int`.

Za prvu funkciju kompajler može napraviti standardnu konverziju:

```text
int -> long
```

Za drugu može napraviti:

```text
int -> double
```

Obje su dopuštene standardne konverzije i u ovom slučaju nijedna funkcija nije bolji izbor. Kompajler zato ne može jednoznačno odabrati overload i prijavljuje pogrešku zbog dvosmislenog poziva.

Dvosmislenost možemo ukloniti tako da argument već ima tip koji jednoznačno odgovara željenom preopterećenju:

```cpp
long wholeDelay{3};
double preciseDelay{3.0};

set_door_delay(wholeDelay);
set_door_delay(preciseDelay);
```

Sada prvi poziv ima točno podudaranje s `long`, a drugi s `double`.

---

## 7. Kada koristiti preopterećenje?

Preopterećenje je korisno kada funkcije:

- obavljaju isti logički zadatak
- prirodno trebaju isti naziv
- razlikuju se po broju ili tipovima parametara
- za različite tipove trebaju različitu implementaciju

Ako bi više preopterećenja imalo potpuno isto ponašanje i razlikovalo se samo po osnovnim tipovima koji se mogu sigurno standardno pretvoriti, često je jednostavnije zadržati manji broj funkcija i iskoristiti standardnu konverziju.

Treba izbjegavati skupove preopterećenja kod kojih više standardnih konverzija može biti jednako dobar izbor, jer tada poziv može postati dvosmislen.

---

## 8. Sažetak

- Preopterećenje omogućuje da više funkcija ima isti naziv ako se razlikuju po broju ili tipovima parametara. Povratni tip sam po sebi ne može razlikovati preopterećene funkcije.
- Kompajler pri pozivu provodi odabir preopterećene funkcije. Pojednostavljeno, točno podudaranje ima prednost pred promocijom, a promocija pred ostalim standardnim konverzijama.
- Preopterećenje se može koristiti i s korisnički definiranim tipovima poput `struct` tipova.
- Nije potrebno stvarati preopterećenje za svaki osnovni tip, ako standardna konverzija omogućuje korištenje postojeće funkcije bez promjene željenog ponašanja.
- Ako više preopterećenja zahtijeva jednako dobre konverzije, poziv može biti dvosmislen i kompajler prijavljuje pogrešku.

Reference i pokazivači nisu potrebni za primjere u ovoj temi i bit će obrađeni zasebno kasnije.
