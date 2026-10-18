# Destruktor i životni vijek objekta

U prethodnim temama konstruktori su određivali početno stanje objekta, a konstruktor kopije način stvaranja novog objekta iz postojećeg. Ova tema obrađuje drugu stranu životnog ciklusa objekta: što se događa kada objekt prestaje postojati i kako se tada koristi destruktor.

Posebna pažnja posvećena je lokalnim objektima automatskog trajanja pohrane, objektima stvorenima pomoću `new` te oslobađanju resursa koje objekt posjeduje. Posljednji primjer nastavlja se na duboko kopiranje iz prethodne teme i pokazuje kako destruktor uklanja potrebu za ručnim pozivom funkcije poput `cleanup()`.

**Ključni pojmovi:**

- destruktor (*destructor*)
- životni vijek objekta (*object lifetime*)
- automatsko trajanje pohrane (*automatic storage duration*)
- dinamičko trajanje pohrane (*dynamic storage duration*)
- uništavanje objekta (*object destruction*)
- vlasništvo nad resursom (*resource ownership*)

## Sadržaj

1. Destruktor
2. Životni vijek lokalnih objekata
3. Dinamički objekt i `delete`
4. Destruktor i oslobađanje resursa
5. GDB analiza životnog vijeka objakata
   - 5.1. Ispis GDB-a
   - 5.2. Vrijednosti i adrese objekata
   - 5.3. Redoslijed poziva destruktora
   - 5.4. Sadržaj memorije nakon završetka destruktora
6. GDB analiza vlasništva nad dinamičkom memorijom i njezina oslobađanja
   - 6.1. Ispis GDB-a
   - 6.2. Zasebna dinamička alokacija originala i kopije
   - 6.3. Destruktor i dinamički alocirani podatak
   - 6.4. Redoslijed oslobađanja dinamičke memorije
    
**Prateći primjeri:**

- `1_destructor.cpp`       — osnovna sintaksa i automatski poziv destruktora
- `2_object_lifetime.cpp`  — ugniježđeni blokovi i redoslijed uništavanja lokalnih objekata
- `3_dynamic_object.cpp`   — poziv destruktora za dinamički stvoren objekt
- `4_resource_cleanup.cpp` — oslobađanje resursa koji objekt posjeduje
- `primjer2.gdb`           — GDB skripta za `2_object_lifetime.exe`
- `primjer4.gdb`           — GDB skripta za `4_resource_cleanup.exe`

---

## 1. Destruktor

Datoteka: `1_destructor.cpp`

**Destruktor** (*destructor*) posebna je članska funkcija koja se poziva pri uništavanju objekta. Naziv destruktora sastoji se od znaka `~` i imena klase:

```cpp
class AdcChannel
{
public:
    ~AdcChannel();
};
```

Destruktor nema povratni tip ni parametre. U C++17 klasa ima jedan destruktor pa se destruktor ne može preopteretiti različitim popisima parametara.

U primjeru je destruktor deklariran u `cpp: 19`, a definiran u `cpp: 35-38`:

```cpp
AdcChannel::~AdcChannel()
{
    cout << "Destruktor: ADC kanal " << mChannel << '\n';
}
```

Objekt se stvara u `cpp: 53`:

```cpp
AdcChannel objChannel{2};
```

`objChannel` je lokalni objekt automatskog trajanja pohrane. Njegova pohrana traje do izlaska iz bloka funkcije `main()`. Pri izlasku iz tog bloka poziva se destruktor, što se vidi iz ispisa:

```text
Konstruktor: ADC kanal 2
Aktivni ADC kanal: 2
Destruktor: ADC kanal 2
```

U uobičajenom objašnjenju kažemo da se destruktor poziva pri završetku životnog vijeka objekta. Preciznije, za objekt klase životni vijek završava kada započne poziv destruktora.

Ako klasa nema korisnički deklariran destruktor, kompajler deklarira destruktor za tu klasu. Korisnički definirani destruktor potreban je kada pri uništavanju objekta treba izvršiti dodatnu radnju, primjerice osloboditi resurs koji objekt posjeduje.

---

## 2. Životni vijek lokalnih objekata

Datoteka: `2_object_lifetime.cpp`

Lokalni objekti `objFirst` i `objSecond` stvaraju se u vanjskom bloku funkcije `main()`:

```cpp
Peripheral objFirst{1};
Peripheral objSecond{2};
```

To se nalazi u `cpp: 45-46`.

U `cpp: 48-55` nalazi se zaseban unutarnji blok. U njemu se stvaraju još dva objekta:

```cpp
{
    Peripheral objThird{3};
    Peripheral objFourth{4};
}
```

Svaki blok ima vlastiti opseg. Kada izvođenje dođe do zatvorene vitičaste zagrade unutarnjeg bloka, završava životni vijek lokalnih objekata toga bloka. Objekti se uništavaju obrnutim redoslijedom od redoslijeda njihova stvaranja:

```text
Konstruktor: periferija 3
Konstruktor: periferija 4
Kraj unutarnjeg bloka
Destruktor: periferija 4
Destruktor: periferija 3
```

`objFirst` i `objSecond` pripadaju vanjskom bloku pa nakon izlaska iz unutarnjeg bloka i dalje postoje. Njihovi se destruktori pozivaju tek pri izlasku iz funkcije `main()`:

```text
Ponovno u vanjskom bloku
Prije izlaska iz funkcije main()
Destruktor: periferija 2
Destruktor: periferija 1
```

Odnos se može prikazati ovako:

```text
main()
|
+-- objFirst
+-- objSecond
|
+-- unutarnji blok
|   |
|   +-- objThird
|   +-- objFourth
|   |
|   +-- kraj bloka -> ~objFourth, ~objThird
|
+-- izlazak iz main() -> ~objSecond, ~objFirst
```

Redak `Prije izlaska iz funkcije main()` namjerno se ispisuje prije `return 0;`. Sam ispis još ne znači da je funkcija završila. Tek izlazak iz bloka funkcije uzrokuje uništavanje preostalih lokalnih objekata.

---

## 3. Dinamički objekt i `delete`

Datoteka: `3_dynamic_object.cpp`

Objekt stvoren pomoću `new` ima dinamičko trajanje pohrane. U `cpp: 55` stvara se dinamički objekt klase `Timer`, a njegova se adresa sprema u lokalni pokazivač:

```cpp
Timer* ptrTimer{new Timer{1}};
```

Ovdje treba razlikovati dva objekta:

```text
ptrTimer
    lokalna pokazivačka varijabla
    automatsko trajanje pohrane

Timer{1}
    dinamički stvoren objekt
    dinamičko trajanje pohrane
```

Životni vijek dinamički stvorenog objekta ne završava samo zato što pokazivačka varijabla izlazi iz opsega. U ovom primjeru završava izrazom u `cpp: 59`:

```cpp
delete ptrTimer;
```

Za objekt klase, `delete` najprije pokreće njegovo uništavanje, pri čemu se poziva destruktor, a zatim se oslobađa pohrana dinamičkog objekta. Zato ispis ima ovaj redoslijed:

```text
Poziv delete
Destruktor: timer 1
Nakon delete pokazivac je nullptr
```

Nakon `delete` pokazivačka varijabla još postoji, ali adresa prethodno uništenog objekta više se ne smije koristiti. U `cpp: 60` pokazivač se zato postavlja na `nullptr`:

Postavljanje na `nullptr` ne oslobađa objekt. Objekt je već uništen i njegova je pohrana oslobođena naredbom `delete`.

---

## 4. Destruktor i oslobađanje resursa

Datoteka: `4_resource_cleanup.cpp`

Prethodni primjeri koristili su destruktor uglavnom za ispis kojim se mogao pratiti trenutak uništavanja objekta. Ovaj primjer pokazuje praktičniju svrhu destruktora: oslobađanje resursa koji objekt posjeduje.

Klasa `SampleStorage` sadrži pokazivački podatkovni član `mPtrValue`.

Konstruktor u `cpp: 36-37` dinamički alocira jedan `int`. Objekt zato tijekom svojeg postojanja posjeduje dinamički alocirani podatak na koji pokazuje `mPtrValue`.

Konstruktor kopije u `cpp: 44-48` ne kopira samo adresu. On alocira zaseban `int` i u njega kopira vrijednost izvornog objekta. To je duboko kopiranje obrađeno u prethodnoj temi. Original i kopija zato posjeduju dva zasebna dinamički alocirana podatka.

Destruktor u `cpp: 52-56` oslobađa podatak koji pripada objektu:

U `cpp: 85-86` stvaraju se original i njegova duboka kopija:

Kopija se zatim mijenja u `cpp: 88`, dok original zadržava vlastitu vrijednost i vlastitu dinamičku alokaciju. Različite adrese ispisuju se u `cpp: 90-94`.

U `cpp: 96` ispisuje se poruka neposredno prije izlaska iz funkcije `main()`:

Nakon toga funkcija završava i automatski se pozivaju destruktori lokalnih objekata. Budući da je `objCopy` stvoren poslije objekta `objOriginal`, uništava se prvi:

```text
Prije izlaska iz funkcije main()
Oslobadam adresu: adresa_kopije
Oslobadam adresu: adresa_originala
```

Adrese u stvarnom ispisu ovise o pojedinom izvođenju programa. Važno je da su različite jer svaki objekt posjeduje vlastitu alokaciju.

U ovom primjeru više nije potrebna javna funkcija `cleanup()` koju bi korisnik klase morao ručno pozvati. Oslobađanje resursa povezano je sa životnim vijekom objekta: kada se objekt uništava, njegov destruktor oslobađa resurs koji objekt posjeduje.

To je osnovna ideja na kojoj se kasnije gradi **RAII** (*Resource Acquisition Is Initialization*): upravljanje resursom veže se uz životni vijek objekta.

---

## 5. GDB analiza životnog vijeka objekata

Datoteke:
- `2_object_lifetime.cpp`
- `2_object_lifetime.exe`
- `primjer2.gdb`

Analiza prati četiri objekta klase `Peripheral`, njihove adrese, redoslijed poziva destruktora i sadržaj memorije nakon završetka destruktora.

Kompajliranje programa i pokretanje GDB-a:
```text
g++ -std=c++17 -g -O0 -Wall -Wextra -Wconversion -Werror 2_object_lifetime.cpp -o 2_object_lifetime.exe
gdb -silent 2_object_lifetime.exe
```

Učitavanje skripte i postavljanje točaka prekida:
```text
(gdb) source primjer2.gdb
(gdb) setup
(gdb) run > NUL
```

### 5.1. Ispis GDB-a

```text
E:\Files\G++\Lift\3-oop\01-klase-osnovno\01-06-destruktor-i-zivotni-vijek-objekta>gdb -silent 2_object_lifetime.exe
Reading symbols from 2_object_lifetime.exe...
(gdb) source primjer2.gdb
(gdb) setup
Temporary breakpoint 1 at 0x140001828: file 2_object_lifetime.cpp, line 54.
Breakpoint 2 at 0x14000176e: file 2_object_lifetime.cpp, line 34.
(gdb) run > NUL
Starting program: E:\Files\G++\Lift\3-oop\01-klase-osnovno\01-06-destruktor-i-zivotni-vijek-objekta\2_object_lifetime.exe > NUL
[New Thread 4968.0x1d08]
[New Thread 4968.0x2be8]
[New Thread 4968.0x255c]

Thread 1 hit Temporary breakpoint 1, main () at 2_object_lifetime.cpp:54
54              cout << "Kraj unutarnjeg bloka\n";
(gdb) objects
$1 = {mId = 1}
$2 = {mId = 2}
$3 = {mId = 3}
$4 = {mId = 4}
(gdb) addresses
$5 = (Peripheral *) 0x5ffe2c
$6 = (Peripheral *) 0x5ffe28
$7 = (Peripheral *) 0x5ffe24
$8 = (Peripheral *) 0x5ffe20
(gdb) continue
Continuing.

Thread 1 hit Breakpoint 2, Peripheral::~Peripheral (this=0x5ffe20) at 2_object_lifetime.cpp:34
34          cout << "Destruktor: periferija " << mId << '\n';
(gdb) destructor
mId = 4
this = 0x5ffe20
(gdb) continue
Continuing.

Thread 1 hit Breakpoint 2, Peripheral::~Peripheral (this=0x5ffe24) at 2_object_lifetime.cpp:34
34          cout << "Destruktor: periferija " << mId << '\n';
(gdb) destructor
mId = 3
this = 0x5ffe24
(gdb) continue
Continuing.
[New Thread 4968.0x1510]

Thread 1 hit Breakpoint 2, Peripheral::~Peripheral (this=0x5ffe28) at 2_object_lifetime.cpp:34
34          cout << "Destruktor: periferija " << mId << '\n';
(gdb) destructor
mId = 2
this = 0x5ffe28
(gdb) continue
Continuing.

Thread 1 hit Breakpoint 2, Peripheral::~Peripheral (this=0x5ffe2c) at 2_object_lifetime.cpp:34
34          cout << "Destruktor: periferija " << mId << '\n';
(gdb) destructor
mId = 1
this = 0x5ffe2c
(gdb) finish
Run till exit from #0  Peripheral::~Peripheral (this=0x5ffe2c) at 2_object_lifetime.cpp:34
0x00007ff7504c189f in main () at 2_object_lifetime.cpp:61
61      }
(gdb) memory
0x5ffe2c:       1
0x5ffe28:       2
0x5ffe24:       3
0x5ffe20:       4
(gdb) continue
Continuing.
[New Thread 4968.0x135c]
[Thread 4968.0x135c exited with code 0]
[Thread 4968.0x2be8 exited with code 0]
[Thread 4968.0x255c exited with code 0]
[Thread 4968.0x1d08 exited with code 0]
[Thread 4968.0x1510 exited with code 0]
[Inferior 1 (process 4968) exited normally]
(gdb)
```

### 5.2. Vrijednosti i adrese objekata

GDB se prvo zaustavlja na `cpp: 54`, prije izlaska iz unutarnjeg bloka, dok sva četiri objekta još postoje.

Naredba:
```text
(gdb) objects
```

daje:
```text
$1 = {mId = 1}
$2 = {mId = 2}
$3 = {mId = 3}
$4 = {mId = 4}
```

Naredba:
```text
(gdb) addresses
```

daje:
```text
$5 = (Peripheral *) 0x5ffe2c
$6 = (Peripheral *) 0x5ffe28
$7 = (Peripheral *) 0x5ffe24
$8 = (Peripheral *) 0x5ffe20
```

Adrese pripadaju objektima redoslijedom:
```text
objFirst   -> 0x5ffe2c
objSecond  -> 0x5ffe28
objThird   -> 0x5ffe24
objFourth  -> 0x5ffe20
```

Skripta ih istodobno sprema u GDB pomoćne varijable kako bi se iste memorijske lokacije mogle pregledavati i nakon završetka životnog vijeka objekata.

### 5.3. Redoslijed poziva destruktora

Nakon svakog:
```text
(gdb) continue
```

GDB se zaustavlja u `Peripheral::~Peripheral()` na `cpp: 34`. Naredba:
```text
(gdb) destructor
```

prikazuje `mId` i `this`.

Dobiven je sljedeći redoslijed:
```text
mId = 4
this = 0x5ffe20

mId = 3
this = 0x5ffe24

mId = 2
this = 0x5ffe28

mId = 1
this = 0x5ffe2c
```

Vrijednost pokazivača `this` pri svakom pozivu odgovara adresi objekta čiji se destruktor izvršava.
Objekti se zato uništavaju redoslijedom:
```text
objFourth -> objThird -> objSecond -> objFirst
```

To je obrnuti redoslijed od redoslijeda njihova stvaranja unutar pripadajućih blokova.

### 5.4. Sadržaj memorije nakon završetka destruktora

Na posljednjem pozivu destruktora naredbom:
```text
(gdb) finish
```

Nakon završetka destruktora izvođenje se vraća u `main()`. Zatim se pokreće:
```text
(gdb) memory
```

Dobiven je ispis:
```text
0x5ffe2c:       1
0x5ffe28:       2
0x5ffe24:       3
0x5ffe20:       4
```

Sva četiri objekta više nemaju aktivan životni vijek, ali prethodni sadržaj njihovih memorijskih lokacija još je ostao nepromijenjen.

To **ne** znači da objekti još postoje. GDB samo čita 4 bajta na ranije spremljenim adresama i prikazuje ih kao decimalne vrijednosti.

---

## 6. GDB analiza vlasništva nad dinamičkom memorijom i njezina oslobađanja

Datoteke:

- `4_resource_cleanup.cpp`
- `4_resource_cleanup.exe`
- `primjer4.gdb`

U ovom primjeru prati se odnos između objekta klase `SampleStorage` i dinamički alociranog `int` podatka koji mu pripada. Takva dinamički alocirana memorija predstavlja resurs kojim objekt mora upravljati.

Program se kompajlira i pokreće u GDB-u:

```text
g++ -std=c++17 -g -O0 -Wall -Wextra -Wconversion -Werror 4_resource_cleanup.cpp -o 4_resource_cleanup.exe
gdb -silent 4_resource_cleanup.exe
```

Skripta se učitava, postavljaju se potrebne točke prekida i program se pokreće bez `cout` ispisa:

```text
(gdb) source primjer4.gdb
(gdb) setup
(gdb) run > NUL
```

### 6.1. Ispis GDB-a

```text
E:\Files\G++\Lift\3-oop\01-klase-osnovno\01-06-destruktor-i-zivotni-vijek-objekta>gdb -silent 4_resource_cleanup.exe
Reading symbols from 4_resource_cleanup.exe...
(gdb) source primjer4.gdb
(gdb) setup
Temporary breakpoint 1 at 0x1400019c8: file 4_resource_cleanup.cpp, line 98.
Breakpoint 2 at 0x140001814: file 4_resource_cleanup.cpp, line 54.
(gdb) run > NUL
Starting program: E:\Files\G++\Lift\3-oop\01-klase-osnovno\01-06-destruktor-i-zivotni-vijek-objekta\4_resource_cleanup.exe > NUL
[New Thread 8416.0x1134]
[New Thread 8416.0x1904]
[New Thread 8416.0xd88]

Thread 1 hit Temporary breakpoint 1, main () at 4_resource_cleanup.cpp:98
98          return 0;
(gdb) objects
objOriginal:
  object    = 0x5ffe28
  mPtrValue = 0x73640
  value     = 10
objCopy:
  object    = 0x5ffe20
  mPtrValue = 0x73680
  value     = 20
(gdb) continue
Continuing.
[New Thread 8416.0x1550]

Thread 1 hit Breakpoint 2, SampleStorage::~SampleStorage (this=0x5ffe20) at 4_resource_cleanup.cpp:54
54          cout << "Oslobadam adresu:        " << mPtrValue << '\n';
(gdb) destructor
this      = 0x5ffe20
mPtrValue = 0x73680
value     = 20
(gdb) continue
Continuing.

Thread 1 hit Breakpoint 2, SampleStorage::~SampleStorage (this=0x5ffe28) at 4_resource_cleanup.cpp:54
54          cout << "Oslobadam adresu:        " << mPtrValue << '\n';
(gdb) destructor
this      = 0x5ffe28
mPtrValue = 0x73640
value     = 10
(gdb) continue
Continuing.
[New Thread 8416.0xd70]
[Thread 8416.0x1904 exited with code 0]
[Thread 8416.0xd88 exited with code 0]
[Thread 8416.0x1550 exited with code 0]
[Thread 8416.0xd70 exited with code 0]
[Thread 8416.0x1134 exited with code 0]
[Inferior 1 (process 8416) exited normally]
(gdb)
```

### 6.2. Zasebna dinamička alokacija originala i kopije

Prva točka prekida postavljena je na posljednju naredbu funkcije `main()` (`cpp: 98`).
`objOriginal` i `objCopy` još postoje.

Naredbom:
```text
(gdb) objects
```
prikazuju se adrese objekata, vrijednosti njihovih članova `mPtrValue` i vrijednosti na adresama na koje ti pokazivači pokazuju.

Treba razlikovati adresu objekta od adrese dinamički alociranog podatka:
```text
&objOriginal            -> adresa objekta objOriginal
objOriginal.mPtrValue   -> adresa njegova dinamicki alociranog int podatka

&objCopy                -> adresa objekta objCopy
objCopy.mPtrValue       -> adresa njegova dinamicki alociranog int podatka
```

Vrijednosti pokazivača `mPtrValue` moraju biti različite jer se u konstruktoru kopije, `cpp: 44-48`, izvodi nova dinamička alokacija.

Nakon promjene u `cpp: 88` preko tih se pokazivača mogu pročitati različite vrijednosti:
```text
objOriginal -> 10
objCopy     -> 20
```
Time se potvrđuje duboko kopiranje: kopija ne pokazuje na isti `int` kao original, nego posjeduje vlastiti dinamički alocirani podatak.

### 6.3. Destruktor i dinamički alocirani podatak

Nakon:
```text
(gdb) continue
```

izvođenje se zaustavlja u `SampleStorage::~SampleStorage()`, `cpp: 54`.

Naredbom:
```text
(gdb) destructor
```

prikazuju se:
```text
this
mPtrValue
*mPtrValue
```

`this` pokazuje na objekt čiji se destruktor trenutačno izvršava. `mPtrValue` sadrži adresu dinamički alociranog `int` podatka koji pripada tom objektu, a `*mPtrValue` njegovu vrijednost.

Pri prvom pozivu destruktora `this` odgovara adresi objekta `objCopy`. Njegov `mPtrValue` pokazuje na zasebnu dinamičku alokaciju kopije.

U `cpp: 55` ta se memorija oslobađa:
```cpp
delete mPtrValue;
```

Nakon sljedećeg:
```text
(gdb) continue
```

destruktor se poziva za `objOriginal`. Pokazivač `this` tada odgovara adresi originala, a `mPtrValue` pokazuje na njegovu zasebnu dinamičku alokaciju.

Odnos se može prikazati ovako:
```text
objCopy     -> mPtrValue -> vlastiti dinamički alocirani int
objOriginal -> mPtrValue -> vlastiti dinamički alocirani int
```

### 6.4. Redoslijed oslobađanja dinamičke memorije

Objekti se u `cpp: 85-86` stvaraju redoslijedom:

```text
objOriginal -> objCopy
```

Pri izlasku iz funkcije `main()` uništavaju se obrnutim redoslijedom:
```text
objCopy -> objOriginal
```

Zbog dubokog kopiranja svaki objekt ima vlastitu dinamičku alokaciju. Zato se pri svakom pozivu destruktora naredbom:
```cpp
delete mPtrValue;
```
oslobađa memorija koja pripada upravo tom objektu.

GDB analiza time povezuje tri prethodno obrađena pojma:
```text
konstruktor kopije -> stvara zasebnu dinamičku alokaciju
vlasništvo         -> svaki objekt posjeduje vlastiti podatak
destruktor         -> oslobađa pripadajuću dinamičku memoriju
```
