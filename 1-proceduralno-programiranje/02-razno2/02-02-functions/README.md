# Funkcije

**Funkcija** je imenovani dio programa koji obavlja određeni zadatak. Funkcija može primati podatke kroz parametre, izvršiti određene naredbe i po potrebi vratiti rezultat pozivatelju.

Funkcije omogućuju da se veći program podijeli na manje, jasnije i višekratno upotrebljive cjeline.

---

## 1. Definicija funkcije

Definicija funkcije sadrži povratni tip, naziv funkcije, popis parametara i tijelo funkcije.

```cpp
int calculate_travel_time(int floorCount, int secondsPerFloor)
{
    return floorCount * secondsPerFloor;
}
```

Pojedini dijelovi definicije su:

```text
int                     -> povratni tip
calculate_travel_time   -> naziv funkcije
floorCount              -> prvi parametar
secondsPerFloor         -> drugi parametar
{ ... }                 -> tijelo funkcije
```

Naredba `return` završava izvođenje funkcije i vraća vrijednost pozivatelju. Funkcija koja ne vraća vrijednost koristi povratni tip `void`.

```cpp
void print_floor(int floor)
{
    cout << "Kat: " << floor << '\n';
}
```

---

## 2. Prototip funkcije

Ako se funkcija poziva prije njezine definicije, kompajler prije tog poziva mora znati da funkcija postoji i kako se može pozvati. To se može postići prototipom funkcije.

```cpp
int calculate_travel_time(int floorCount, int secondsPerFloor);
```

Prototip završava znakom `;` i nema tijelo funkcije. Njime kompajler prije poziva saznaje naziv funkcije, povratni tip te broj i tipove parametara.

Nakon prototipa funkcija se može definirati kasnije u datoteci:

```cpp
int calculate_travel_time(int floorCount, int secondsPerFloor)
{
    return floorCount * secondsPerFloor;
}
```

Nazivi parametara u prototipu nisu obavezni:

```cpp
int calculate_travel_time(int, int);
```

Ipak, u nastavnim primjerima korisno ih je navoditi jer dokumentiraju značenje pojedinih parametara.

### Prototip i deklaracija

Za prototip funkcije često se koristi i izraz **deklaracija funkcije**. U kontekstu deklaracije funkcije bez tijela ta se dva izraza često koriste kao sinonimi.

Ipak, deklaracija je širi pojam. Definicija funkcije također predstavlja njezinu deklaraciju, ali sadrži i tijelo funkcije.

U ovoj temi radi jednostavnosti i dosljednosti za deklaraciju funkcije koristi se izraz **prototip funkcije**.

### Kada prototip funkcije nije potreban

Prototip funkcije nije potreban ako se potpuna definicija funkcije nalazi prije mjesta na kojem se funkcija prvi put poziva.

Primjer:

```cpp
int calculate_travel_time(int floorCount, int secondsPerFloor)
{
    return floorCount * secondsPerFloor;
}

int main()
{
    int travelTime{calculate_travel_time(5, 2)};

    return 0;
}
```

Kada kompajler dođe do poziva:

```cpp
calculate_travel_time(5, 2);
```

već je prethodno pročitao cijelu definiciju funkcije i zato već zna:

- naziv funkcije
- tip povratne vrijednosti
- broj parametara
- tipove parametara

Zaseban prototip zato nije potreban.

Ako se definicija funkcije nalazi **nakon** mjesta njezina prvog poziva, prije poziva mora postojati njezin prototip:

```cpp
int calculate_travel_time(int floorCount, int secondsPerFloor);

int main()
{
    int travelTime{calculate_travel_time(5, 2)};

    return 0;
}

int calculate_travel_time(int floorCount, int secondsPerFloor)
{
    return floorCount * secondsPerFloor;
}
```

U manjim programima funkcije se mogu jednostavno definirati prije `main()` i tada zasebni prototipi često nisu potrebni.

U većim programima prototipi funkcija obično se odvajaju od njihovih definicija. Takva organizacija bit će važnija kada program počnemo dijeliti na `.h` i `.cpp` datoteke.

---

## 3. Parametri i argumenti

**Parametar** je varijabla navedena u prototipu i definiciji funkcije.

```cpp
void print_floor(int floor);
```

`floor` je parametar funkcije `print_floor()`.

**Argument** je vrijednost ili izraz koji se navodi pri pozivu funkcije.

```cpp
int currentFloor{3};
print_floor(currentFloor);
```

`currentFloor` je argument poziva funkcije.

Kod funkcije s više parametara argumenti se povezuju s parametrima prema njihovom redoslijedu:

```cpp
int travelTime{calculate_travel_time(5, 2)};
```

U ovom pozivu:

```text
5   -> argument za parametar floorCount
2   -> argument za parametar secondsPerFloor
```

U primjerima ove teme svi parametri prosljeđuju se po vrijednosti (*pass by value*). Funkcija zato dobiva vlastite kopije proslijeđenih vrijednosti.

Prosljeđivanje pomoću referenci i pokazivača bit će zasebne teme kasnije.

---

## 4. Poziv funkcije

Funkcija se izvršava kada je pozovemo pomoću njezina naziva i oblih zagrada.

```cpp
print_floor(3);
```

Vrijednosti ili izrazi navedeni unutar oblih zagrada predstavljaju argumente poziva funkcije.

Ako funkcija vraća vrijednost, rezultat poziva može se spremiti u varijablu:

```cpp
int travelTime{calculate_travel_time(5, 2)};
```

Pojednostavljeni prikaz tijeka poziva funkcije:

```text
poziv funkcije
    |
    +-- argumenti se predaju parametrima
    |
    +-- izvršava se tijelo funkcije
    |
    +-- return vraća rezultat pozivatelju
```

Kod funkcije s povratnim tipom `void` nema povratne vrijednosti koju bi pozivatelj spremio.

---

## 5. Defaultni argumenti

Parametru funkcije može se u prototipu pridružiti **defaultni argument** (*default argument*). Ako pozivatelj pri pozivu funkcije ne navede odgovarajući argument, koristi se defaultni argument naveden u prototipu.

Iako se defaultni argument zapisuje uz parametar u prototipu, standardni C++ naziv za taj koncept je *default argument*.

Primjer funkcije s tri parametra, od kojih posljednja dva imaju defaultne argumente:

```cpp
int calculate_travel_time(
    int floorCount,
    int secondsPerFloor = 2,
    int doorDelay = 3);
```

U ovom prototipu:

```text
floorCount       -> parametar bez defaultnog argumenta
secondsPerFloor  -> parametar sa defaultnim argumentom 2
doorDelay        -> parametar sa defaultnim argumentom 3
```

Pozivatelj sada može navesti različit broj argumenata:

```cpp
calculate_travel_time(5);
calculate_travel_time(5, 4);
calculate_travel_time(5, 4, 6);
```

Kod prvog poziva:

```cpp
calculate_travel_time(5);
```

pozivatelj navodi samo jedan argument. Za preostala dva parametra koriste se defaultni argumenti:

```text
floorCount       = 5   // argument pozivatelja
secondsPerFloor  = 2   // defaultni argument
doorDelay        = 3   // defaultni argument
```

Kod drugog poziva:

```cpp
calculate_travel_time(5, 4);
```

vrijedi:

```text
floorCount       = 5   // argument pozivatelja
secondsPerFloor  = 4   // argument pozivatelja
doorDelay        = 3   // defaultni argument
```

Kod trećeg poziva:

```cpp
calculate_travel_time(5, 4, 6);
```

sve argumente navodi pozivatelj pa se defaultni argumenti ne koriste.

### Redoslijed parametara sa defaultnim argumentima

Kada jedan parametar dobije defaultni argument, svi parametri koji slijede iza njega također moraju imati defaultne argumente.

Ispravno:

```cpp
int calculate_travel_time(
    int floorCount,
    int secondsPerFloor = 2,
    int doorDelay = 3);
```

Nije ispravno:

```cpp
// Pogreška
int calculate_travel_time(
    int floorCount = 5,
    int secondsPerFloor,
    int doorDelay = 3);
```

Problem je u parametru `secondsPerFloor`. On nema defaultni argument, a nalazi se iza parametra `floorCount` koji ga već ima.

Argumenti pri pozivu povezuju se s parametrima prema njihovu položaju, slijeva nadesno. Zato parametri sa zadanim argumentima moraju biti na kraju popisa parametara.

Opći ispravni oblik je:

```text
parametar bez defaultnog argumenta
parametar bez defaultnog argumenta
parametar sa defaultnim argumentom
parametar sa defaultnim argumentom
```

Neispravan raspored bio bi:

```text
parametar sa defaultnim argumentom
parametar bez defaultnog argumenta
parametar sa defaultnim argumentom
```

Također nije moguće preskočiti srednji argument i navesti samo argument za parametar koji dolazi iza njega. Argumenti se uvijek povezuju s parametrima prema njihovu položaju.

---

## 6. Defaultni argumenti u različitim opsezima

Defaultni argument nije dio same funkcije. On pripada prototipu funkcije koji je vidljiv na mjestu poziva.

U vanjskom opsegu možemo imati prototip:

```cpp
int calculate_travel_time(int floorCount, int secondsPerFloor = 2);
```

Poziv u tom opsegu koristi defaultni argument `2`:

```cpp
int travelTime{calculate_travel_time(5)};
```

U unutarnjem opsegu može se pojaviti novi prototip iste funkcije s drugim defaultnim argumentom:

```cpp
{
    int calculate_travel_time(int floorCount, int secondsPerFloor = 3);

    int travelTime{calculate_travel_time(5)};
}
```

U tom unutarnjem opsegu izostavljeni drugi argument dobiva defaultni argument `3`. Nakon izlaska iz unutarnjeg opsega ponovno vrijedi prototip iz vanjskog opsega sa defaultnim argumentom `2`.

```text
vanjski opseg           -> defaultni argument: 2
    |
    +-- unutarnji opseg -> defaultni argument: 3
    |
vanjski opseg           -> defaultni argument: 2
```

Ovaj primjer je demonstrativan. U stvarnom programu različiti defaultni argumenti za istu funkciju u različitim opsezima mogu otežati čitanje koda i zato ih treba koristiti vrlo oprezno.

U istom opsegu ne možemo istom parametru ponovno zadati drugi defaultni argument.

---

## 7. Potpis funkcije

Budući da su u ovom poglavlju sve funkcije u istom globalnom opsegu, potpis funkcije možemo pojednostavljeno promatrati kao kombinaciju naziva funkcije i tipova njezinih parametara.

Za prototip:

```cpp
int calculate_travel_time(int floorCount, int secondsPerFloor = 2);
```

potpis možemo zapisati kao:

```text
calculate_travel_time(int, int)
```

U potpis ne ulaze:

- povratni tip `int`
- nazivi parametara `floorCount` i `secondsPerFloor`
- defaultni argument `2`

Zato prototip i definicija imaju isti potpis iako se defaultni argument nalazi samo u prototipu:

```cpp
int calculate_travel_time(int floorCount, int secondsPerFloor = 2);

int calculate_travel_time(int floorCount, int secondsPerFloor)
{
    return floorCount * secondsPerFloor;
}
```

---

## 8. Tip funkcije

Obične funkcije možemo pojednostavljeno promatrati kao kombinaciju povratnog tipa i tipova parametara.

Primjer:

```cpp
int calculate_travel_time(int floorCount, int secondsPerFloor);
```

Za ovu funkciju vrijedi:

```text
Povratni tip: int
Tipovi parametara: int, int
```

Zato je tip funkcije:

```text
int(int, int)
```

Naziv funkcije nije dio tipa funkcije.

Dakle:

```text
Potpis funkcije:
calculate_travel_time(int, int)

Tip funkcije:
int(int, int)
```

Važno je razlikovati ta dva pojma:

```text
potpis funkcije -> naziv funkcije + tipovi parametara

tip funkcije    -> povratni tip + tipovi parametara
```

Nazivi parametara također nisu dio tipa funkcije.

Primjerice, ovi prototipovi imaju isti tip funkcije:

```cpp
int calculate_travel_time(int floorCount, int secondsPerFloor);

int calculate_travel_time(int floors, int seconds);
```

U oba slučaja tip funkcije je:

```text
int(int, int)
```

Razlika između potpisa i tipa funkcije postat će važnija u kasnijim temama C++-a.

---

## 9. Sažetak

- Funkcija može primati podatke kroz parametre, a pri pozivu joj se prosljeđuju argumenti.
- Prototip funkcije potreban je kada se funkcija poziva prije njezine definicije. Ako se definicija nalazi prije prvog poziva, zaseban prototip nije potreban.
- Defaultni argumenti (*default arguments*) omogućuju izostavljanje odgovarajućih argumenata pri pozivu. Nakon prvog parametra sa defaultnim argumentom svi sljedeći parametri također moraju imati defaultne argumente. Ista funkcija može u različitim opsezima imati prototipove s različitim defaultnim argumentima.
- Potpis obične funkcije čine naziv funkcije i tipovi parametara.
- Tip funkcije čine povratni tip i tipovi parametara.

Reference i pokazivači kao načini prosljeđivanja podataka funkcijama bit će obrađeni kasnije kao zasebne teme.