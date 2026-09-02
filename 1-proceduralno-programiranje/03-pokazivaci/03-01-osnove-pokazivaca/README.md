# Osnove pokazivača

Pokazivač je varijabla koja sadrži memorijsku adresu drugog podatka.

U ovoj temi cilj je razumjeti osnovni mehanizam indirektnog pristupa podacima prije nego što pokazivače počnemo koristiti u složenijim situacijama. Poseban naglasak je na vezi između varijable, njezine adrese i pokazivačke varijable koja tu adresu čuva.

Pokazivači sami po sebi nisu OOP koncept, ali će kasnije biti važni za rad s instancama klasa, dinamičkim životnim vijekom, odnosima pridruživanja (*association*), polimorfizmom tijekom izvođenja programa (*runtime polymorphism*) i vlasništvom nad resursima (*ownership*).

---

## 1. Varijabla, adresa i pokazivač

Promotrimo običnu varijablu:

```cpp
int currentFloor{3};
```

Varijabla `currentFloor` tipa je `int` i zauzima određeno mjesto u memoriji u kojem se čuva njezina vrijednost.

Operator `&` vraća adresu te varijable:

```cpp
&currentFloor
```

Pokazivačku varijablu tipa `int*` deklariramo ovako:

```cpp
int* ptrCurrentFloor{&currentFloor};
```

Ovdje imamo tri različite stvari:

- `currentFloor` je varijabla tipa `int`
- `&currentFloor` je adresa varijable `currentFloor`
- `ptrCurrentFloor` je pokazivačka varijabla koja sadrži tu adresu

Tip pokazivača važan je jer određuje kojem tipu podatka pokazivač može pristupati.

```cpp
int* ptrCurrentFloor{&currentFloor};
double* ptrSensorValue{nullptr};
```

`ptrCurrentFloor` je pokazivač na `int`, a `ptrSensorValue` pokazivač na `double`.

### Vizualni prikaz

Ako pretpostavimo proizvoljne adrese, odnos između varijable `currentFloor` i pokazivačke varijable `ptrCurrentFloor` možemo prikazati ovako:

```text
+------------------------+          +------------------------+
| ptrCurrentFloor        |  ----->  | currentFloor           |
| adresa:    0x2000      |          | adresa:    0x1000      |
| vrijednost: 0x1000     |          | vrijednost: 3          |
+------------------------+          +------------------------+
```

Treba uočiti dvije različite adrese:

- `0x2000` je adresa same pokazivačke varijable `ptrCurrentFloor`
- `0x1000` je vrijednost spremljena u `ptrCurrentFloor`, ali istodobno i adresa varijable `currentFloor`

Strelica zato predstavlja činjenicu da vrijednost pokazivačke varijable odgovara adresi varijable na koju pokazuje.

Pokazivač je također varijabla i zato zauzima vlastito mjesto u memoriji te ima vlastitu adresu.

Stvarne adrese ovise o izvođenju programa i ne treba očekivati da će uvijek biti jednake.

### Veličina pokazivačke varijable

Veličina pokazivačke varijable ovisi o arhitekturi sustava. Na 64-bitnom sustavu pokazivačka varijabla tipično zauzima **8 bajtova**, neovisno o tome pokazuje li na `int`, `double` ili neki drugi tip.

To možemo provjeriti operatorom `sizeof`:

```cpp
cout << sizeof(int*) << '\n';
cout << sizeof(double*) << '\n';
```

Na 64-bitnom sustavu očekivani ispis je:

```text
8
8
```

Tip podatka na koji pokazivač pokazuje ne određuje veličinu same pokazivačke varijable. Tip pokazivača određuje kako kompajler interpretira podatak kojem se pristupa preko te adrese.

---

## 2. Operator adrese `&`

Operator `&`, kada se koristi ispred varijable, daje adresu te varijable:

```cpp
int currentFloor{3};

cout << &currentFloor << '\n';
```

Adresu možemo spremiti u pokazivačku varijablu odgovarajućeg tipa:

```cpp
int* ptrCurrentFloor{&currentFloor};
```

Vrijednosti:

```cpp
&currentFloor
ptrCurrentFloor
```

predstavljaju istu adresu.

Ako je adresa varijable `currentFloor` u nekom izvođenju programa `0x1000`, tada vrijedi:

```text
&currentFloor     -> 0x1000
ptrCurrentFloor   -> 0x1000
```

To ne znači da su `currentFloor` i `ptrCurrentFloor` ista varijabla. `currentFloor` sadrži broj kata, dok `ptrCurrentFloor` sadrži adresu varijable `currentFloor`.

---

## 3. Operator dereferenciranja `*`

Kada se `*` koristi u izrazu ispred pokazivača, pristupamo podatku na adresi koju pokazivač sadrži:

```cpp
int currentFloor{3};
int* ptrCurrentFloor{&currentFloor};

cout << *ptrCurrentFloor << '\n';
```

Ispisuje se:

```text
3
```

Izraz:

```cpp
*ptrCurrentFloor
```

možemo čitati kao: vrijednost na adresi na koju pokazuje `ptrCurrentFloor`

U ovom primjeru `ptrCurrentFloor` sadrži adresu `currentFloor`, pa dereferenciranjem dobivamo vrijednost `3`.

```text
+------------------------+          +------------------------+
| ptrCurrentFloor        |  ----->  | currentFloor           |
| vrijednost: 0x1000     |          | vrijednost: 3          |
+------------------------+          +------------------------+
          *ptrCurrentFloor  ------------------->  3
```

Važno je razlikovati dvije uporabe znaka `*`.

U deklaraciji:

```cpp
int* ptrCurrentFloor{&currentFloor};
```

`*` je dio deklaracije tipa pokazivača.

U izrazu:

```cpp
cout << *ptrCurrentFloor << '\n';
```

`*` je operator dereferenciranja.

---

## 4. Promjena varijable preko pokazivača

Dereferenciranjem pokazivača možemo pristupiti i promijeniti vrijednost varijable na koju pokazuje.

```cpp
int currentFloor{3};
int* ptrCurrentFloor{&currentFloor};

*ptrCurrentFloor = 5;
```

Prije promjene odnos možemo prikazati ovako:

```text
+------------------------+          +------------------------+
| ptrCurrentFloor        |  ----->  | currentFloor           |
| vrijednost: 0x1000     |          | vrijednost: 3          |
+------------------------+          +------------------------+
```

Naredba:

```cpp
*ptrCurrentFloor = 5;
```

mijenja vrijednost na adresi `0x1000`:

```text
+------------------------+          +------------------------+
| ptrCurrentFloor        |  ----->  | currentFloor           |
| vrijednost: 0x1000     |          | vrijednost: 5          |
+------------------------+          +------------------------+
```

Vrijednost pokazivačke varijable nije se promijenila. Ona i dalje sadrži adresu `currentFloor`.

Nije stvorena nova varijabla tipa `int`. Promijenjena je postojeća varijabla kojoj smo pristupili indirektno preko njezine adrese.

Ovo je jedan od najvažnijih temelja za kasniji rad s podacima preko pokazivača.

---

## 5. `nullptr`

Pokazivač ne mora uvijek sadržavati adresu valjane varijable ili drugog podatka.

Ako trenutačno ne pokazuje ni na što, treba ga inicijalizirati vrijednošću `nullptr`:

```cpp
int* ptrCurrentFloor{nullptr};
```

`nullptr` označava null pointer vrijednost.

Takvo stanje možemo prikazati ovako:

```text
+------------------------+
| ptrCurrentFloor        |  ----->  ne pokazuje na valjan podatak
| vrijednost: nullptr    |
+------------------------+
```

Takav pokazivač ne smijemo dereferencirati:

```cpp
int* ptrCurrentFloor{nullptr};

// Pogrešno: pokazivač ne sadrži adresu valjanog int podatka
cout << *ptrCurrentFloor << '\n';
```

Dereferenciranje null pokazivača uzrokuje nedefinirano ponašanje (*undefined behavior*).

Prije dereferenciranja pokazivača koji možda može biti `nullptr`, provjeravamo ga:

```cpp
if (ptrCurrentFloor != nullptr)
{
    cout << *ptrCurrentFloor << '\n';
}
```

Pokazivač se može provjeriti i kraće:

```cpp
if (ptrCurrentFloor)
{
    cout << *ptrCurrentFloor << '\n';
}
```

U početnim primjerima češće ćemo koristiti eksplicitnu usporedbu s `nullptr` jer jasnije pokazuje što provjeravamo.

---

## 6. Automatski i dinamički životni vijek

Lokalna varijabla poput:

```cpp
int currentFloor{3};
```

ima automatski životni vijek. Njezin životni vijek završava automatski kada izvođenje napusti opseg u kojem je definirana.

U svakodnevnom objašnjavanju često ćemo reći da se takve lokalne varijable nalaze na **stacku**.

Objekt stvoren izrazom `new` ima dinamički životni vijek:

```cpp
int* ptrTargetFloor{new int{7}};
```

Za memoriju iz koje se dinamički objekti stvaraju često koristimo izraz **heap**.

Tipičan odnos lokalne pokazivačke varijable i dinamički stvorenog objekta možemo zamisliti ovako:

```text
STACK                                   HEAP

+------------------------+          +------------------------+
| ptrTargetFloor         |  ----->  | dinamički int objekt   |
| adresa:    0x2000      |          | adresa:    0x5000      |
| vrijednost: 0x5000     |          | vrijednost: 7          |
+------------------------+          +------------------------+
```

Pokazivačka varijabla `ptrTargetFloor` ima automatski životni vijek, dok `int` objekt stvoren pomoću `new` ima dinamički životni vijek.

Zbog toga njihovi životni vijekovi nisu automatski povezani.

Ako lokalna pokazivačka varijabla nestane, dinamički objekt neće zbog toga automatski biti oslobođen.

---

## 7. Dinamička alokacija operatorom `new`

Operator `new` koristimo za dinamičko stvaranje **jednog objekta osnovnog ili korisnički definiranog tipa**, primjerice `int`, `double` ili `FloorSensorData`.

Izraz:

```cpp
new int{7}
```

stvara objekt tipa `int` s dinamičkim životnim vijekom i vraća njegovu adresu.

Ako pretpostavimo da je vraćena adresa `0x5000`, možemo to prikazati ovako:

```text
new int{7}
    |
    +---------------------------------> 0x5000
```

Tu adresu spremamo u pokazivačku varijablu:

```cpp
int* ptrTargetFloor{new int{7}};
```

Nakon toga odnos izgleda ovako:

```text
+------------------------+          +------------------------+
| ptrTargetFloor         |  ----->  | dinamički int objekt   |
| vrijednost: 0x5000     |          | adresa:    0x5000      |
+------------------------+          | vrijednost: 7          |
                                    +------------------------+
```

Dinamički stvorenom objektu pristupamo dereferenciranjem:

```cpp
cout << *ptrTargetFloor << '\n';
```

Njegovu vrijednost možemo i promijeniti:

```cpp
*ptrTargetFloor = 9;
```

Nakon promjene:

```text
+------------------------+          +------------------------+
| ptrTargetFloor         |  ----->  | dinamički int objekt   |
| vrijednost: 0x5000     |          | adresa:    0x5000      |
+------------------------+          | vrijednost: 9          |
                                    +------------------------+
```

Pokazivačka varijabla `ptrTargetFloor` lokalna je varijabla, dok objekt stvoren pomoću `new` ima zaseban dinamički životni vijek.

---

## 8. Oslobađanje memorije operatorom `delete`

Objekt stvoren pomoću `new` treba osloboditi pomoću odgovarajućeg `delete`:

```cpp
int* ptrTargetFloor{new int{7}};

cout << *ptrTargetFloor << '\n';

delete ptrTargetFloor;
ptrTargetFloor = nullptr;
```

Prije `delete` imamo:

```text
+------------------------+          +------------------------+
| ptrTargetFloor         |  ----->  | dinamički int objekt   |
| vrijednost: 0x5000     |          | adresa:    0x5000      |
+------------------------+          | vrijednost: 7          |
                                    +------------------------+
```

Naredba:

```cpp
delete ptrTargetFloor;
```

završava životni vijek dinamički stvorenog objekta i njegovu memoriju vraća sustavu za upravljanje dinamičkom memorijom.

Odmah nakon `delete`, prije postavljanja pokazivača na `nullptr`, situaciju možemo zamisliti ovako:

```text
+------------------------+          +---------------------------------+
| ptrTargetFloor         |  ----->  | adresa 0x5000                   |
| vrijednost: 0x5000     |          | dinamički objekt više ne postoji|
+------------------------+          +---------------------------------+
       viseći pokazivač
```

Pokazivačka varijabla još uvijek sadrži staru adresu, ali na toj adresi više nema dinamičkog objekta kojem smijemo pristupati preko tog pokazivača.

Zato ćemo u početnim primjerima nakon `delete` često odmah napisati:

```cpp
ptrTargetFloor = nullptr;
```

Nakon toga:

```text
+------------------------+
| ptrTargetFloor         |  ----->  ne pokazuje na valjan objekt
| vrijednost: nullptr    |
+------------------------+
```

Postavljanje pokazivača na `nullptr` ne oslobađa memoriju — to je već napravio `delete`. Ono samo jasno označava da pokazivačka varijabla više ne sadrži adresu valjanog dinamičkog objekta.

**Napomena**: Postoje još operatori `new[]` i `delete[]`, koji se koriste za dinamička polja. Oni će biti obrađeni u temi 03-02-dinamicka-polja.

---

## 9. Curenje memorije (*memory leak*)

Ako izgubimo posljednju adresu dinamički alociranog objekta prije nego što pozovemo `delete`, više ne možemo pravilno osloboditi njegovu memoriju.

Primjer:

```cpp
int* ptrTargetFloor{new int{7}};

ptrTargetFloor = nullptr;
```

Prije postavljanja pokazivača na `nullptr`:

```text
+------------------------+          +------------------------+
| ptrTargetFloor         |  ----->  | dinamički int objekt   |
| vrijednost: 0x5000     |          | adresa:    0x5000      |
+------------------------+          | vrijednost: 7          |
                                    +------------------------+
```

Nakon:

```cpp
ptrTargetFloor = nullptr;
```

dobivamo:

```text
+------------------------+             +------------------------+
| ptrTargetFloor         |    X ---->  | dinamički int objekt   |
| vrijednost: nullptr    |             | adresa:    0x5000      |
+------------------------+             | vrijednost: 7          |
                                       +------------------------+
                                        memorija nije oslobođena
```

Dinamički objekt i dalje postoji, ali adresa `0x5000` više nije spremljena u `ptrTargetFloor`. Ako nemamo drugi pokazivač koji sadrži tu adresu, više nemamo način da adresu tog objekta predamo operatoru `delete`. To je **curenje memorije** (*memory leak*).

Ispravno je najprije osloboditi dinamički objekt:

```cpp
delete ptrTargetFloor;
ptrTargetFloor = nullptr;
```

Kod većih programa curenja memorije mogu postupno trošiti raspoloživu memoriju. U embedded sustavima s ograničenom količinom memorije taj problem može biti posebno ozbiljan.

---

## 10. Viseći pokazivač (*dangling pointer*)

**Viseći pokazivač** (*dangling pointer*) sadrži adresu dinamičkog objekta čiji je životni vijek već završio.

Primjer:

```cpp
int* ptrTargetFloor{new int{7}};

delete ptrTargetFloor;
```

Nakon `delete`:

```text
+------------------------+          +---------------------------------+
| ptrTargetFloor         |  ----->  | adresa 0x5000                   |
| vrijednost: 0x5000     |          | dinamički objekt više ne postoji|
+------------------------+          +---------------------------------+
       viseći pokazivač
```

Pokazivačka varijabla još uvijek može sadržavati staru memorijsku adresu, ali na toj adresi više nema dinamičkog objekta kojem smijemo pristupati preko tog pokazivača.

Pogrešno je (takav pristup uzrokuje nedefinirano ponašanje):

```cpp
cout << *ptrTargetFloor << '\n';
```

U ovoj fazi koristit ćemo jednostavno pravilo:

```cpp
delete ptrTargetFloor;
ptrTargetFloor = nullptr;
```

Nakon toga pokazivačka varijabla više nije viseći pokazivač:

```text
+------------------------+
| ptrTargetFloor         |  ----->  ne pokazuje na valjan objekt
| vrijednost: nullptr    |
+------------------------+
```

Kasnije ćemo detaljnije učiti kako C++ klase i RAII omogućuju sigurnije upravljanje životnim vijekom resursa.

---

## 11. Pokazivači na korisnički definirane tipove

Pokazivač može pokazivati i na varijablu korisnički definiranog tipa.

Za sada možemo koristiti jednostavan `struct` samo kao spremnik povezanih podataka:

```cpp
struct FloorSensorData
{
    int mFloor;
    bool mIsActive;
};
```

Varijablu tog tipa možemo stvoriti ovako:

```cpp
FloorSensorData objSensorData{4, true};
```

i zatim napraviti pokazivač na nju:

```cpp
FloorSensorData* ptrSensorData{&objSensorData};
```

Odnos možemo prikazati ovako:

```text
+------------------------+          +------------------------+
| ptrSensorData          |  ----->  | objSensorData          |
| vrijednost: 0x3000     |          | adresa:    0x3000      |
+------------------------+          | mFloor:     4          |
                                    | mIsActive:  true       |
                                    +------------------------+
```

Kada članovima pristupamo izravno preko varijable, koristimo operator `.`:

```cpp
cout << objSensorData.mFloor << '\n';
```

Kada im pristupamo preko pokazivača, možemo pisati:

```cpp
cout << (*ptrSensorData).mFloor << '\n';
```

Zbog čitljivosti C++ za ovu čestu operaciju ima operator `->`:

```cpp
cout << ptrSensorData->mFloor << '\n';
```

Dakle:

```cpp
ptrSensorData->mFloor
```

praktično je ekvivalentno izrazu:

```cpp
(*ptrSensorData).mFloor
```

Operator `->` kasnije ćemo vrlo često koristiti s pokazivačima na instance klasa.

---

## 12. Pokazivačka varijabla također ima adresu

Važno je ne poistovjetiti pokazivačku varijablu s varijablom na koju pokazuje.

```cpp
int currentFloor{3};
int* ptrCurrentFloor{&currentFloor};
```

Ovdje postoje dvije zasebne varijable:

1. `currentFloor`
2. `ptrCurrentFloor`

Njihov odnos možemo ponovno prikazati, ovaj put s naglaskom na njihove vlastite adrese:

```text
+------------------------+          +------------------------+
| ptrCurrentFloor        |  ----->  | currentFloor           |
| adresa:    0x2000      |          | adresa:    0x1000      |
| vrijednost: 0x1000     |          | vrijednost: 3           |
+------------------------+          +------------------------+
```

Zato izrazi:

```cpp
&ptrCurrentFloor
```

i:

```cpp
&currentFloor
```

ne daju istu adresu.

U našem zamišljenom primjeru:

```text
&ptrCurrentFloor  -> 0x2000
ptrCurrentFloor   -> 0x1000
&currentFloor     -> 0x1000
*ptrCurrentFloor  -> 3
```

Ta razlika postat će posebno važna kada kasnije budemo radili s pokazivačima na pokazivače.

---

## 13. Pametni pokazivači

Ručno korištenje `new` i `delete` daje programeru potpunu kontrolu, ali i odgovornost da svaki dinamički stvoren objekt bude pravilno oslobođen.

Moderni C++ ima **pametne pokazivače** kao što su:

- `std::unique_ptr`
- `std::shared_ptr`
- `std::weak_ptr`

Oni pomažu povezati upravljanje resursom sa životnim vijekom dinamički stvorenih podataka. Njihova prava svrha postaje jasna tek nakon što obradimo klase, konstruktore, destruktore, vlasništvo (*ownership*) i RAII. Zato ih ovdje samo spominjemo, bez praktične demonstracije.

---

## 14. GDB demonstracija

GDB možemo koristiti za izravno promatranje vrijednosti varijabli, njihovih adresa i sadržaja pokazivačkih varijabli.

Program je prethodno kompajliran s uključenim debug informacijama:

```text
g++ -std=c++17 -g -O0 -Wall -Wextra -Wconversion -Werror main.cpp -o prog
```

Debugger pokrećemo naredbom:

```text
gdb prog.exe
```

Najprije postavljamo breakpointove u dvije demonstracijske funkcije, a zatim pokrećemo program uz preusmjeravanje `cout` ispisa u `NUL`:

```text
(gdb) break demonstrate_address_and_pointer
Breakpoint 1 at 0x140001718: file main.cpp, line 18.
(gdb) break demonstrate_dynamic_allocation
Breakpoint 2 at 0x14000197b: file main.cpp, line 72.
(gdb) run > NUL

Thread 1 hit Breakpoint 1, demonstrate_address_and_pointer () at main.cpp:18
18          int currentFloor{3};
(gdb) n
19          int* ptrCurrentFloor{&currentFloor};
(gdb) n
21          cout << "Trenutni kat: " << currentFloor << '\n';
(gdb) p currentFloor
$1 = 3
(gdb) p &currentFloor
$2 = (int *) 0x5ffe04
(gdb) p ptrCurrentFloor
$3 = (int *) 0x5ffe04
(gdb) p *ptrCurrentFloor
$4 = 3
(gdb) p &ptrCurrentFloor
$5 = (int **) 0x5ffe08
(gdb) c
Continuing.

Thread 1 hit Breakpoint 2, demonstrate_dynamic_allocation () at main.cpp:72
72          int* ptrTargetFloor{new int{7}};
(gdb) n
74          cout << "Odredisni kat: " << *ptrTargetFloor << '\n';
(gdb) p ptrTargetFloor
$6 = (int *) 0x7935c0
(gdb) p *ptrTargetFloor
$7 = 7
(gdb) n
[New Thread 8224.0x700]
76          *ptrTargetFloor = 9;
(gdb) n
77          cout << "Promijenjeni odredisni kat: " << *ptrTargetFloor << '\n';
(gdb) p *ptrTargetFloor
$8 = 9
(gdb) n
[New Thread 8224.0x1e8c]
79          delete ptrTargetFloor;
(gdb) n
80          ptrTargetFloor = nullptr;
(gdb) p ptrTargetFloor
$9 = (int *) 0x7935c0
(gdb) p *ptrTargetFloor
$10 = 8083040
(gdb) n
82          cout << "Vrijednost pokazivaca: " << ptrTargetFloor << '\n';
(gdb) p ptrTargetFloor
$11 = (int *) 0x0
(gdb) p *ptrTargetFloor
Cannot access memory at address 0x0
(gdb) q
```

U prvom dijelu treba primijetiti da `&currentFloor` i `ptrCurrentFloor` imaju istu vrijednost `0x5ffe04`. Pokazivačka varijabla `ptrCurrentFloor` sadrži adresu varijable `currentFloor`.

Dereferenciranjem:

```text
p *ptrCurrentFloor
```

dobivamo vrijednost `3`, odnosno vrijednost spremljenu u varijabli `currentFloor`.

Naredba:

```text
p &ptrCurrentFloor
```

daje adresu same pokazivačke varijable. Ona je u ovom izvođenju `0x5ffe08`, što pokazuje da su `currentFloor` i `ptrCurrentFloor` dvije zasebne varijable u memoriji.

U drugom dijelu programa izraz:

```cpp
new int{7}
```

stvara dinamički objekt tipa `int`, a njegova adresa sprema se u `ptrTargetFloor`.

GDB prikazuje:

```text
ptrTargetFloor   -> 0x7935c0
*ptrTargetFloor  -> 7
```

Nakon naredbe:

```cpp
*ptrTargetFloor = 9;
```

dereferenciranjem pokazivača dobivamo novu vrijednost:

```text
$8 = 9
```

Posebno je važno promotriti stanje neposredno nakon:

```cpp
delete ptrTargetFloor;
```

Pokazivačka varijabla još uvijek sadrži staru adresu:

```text
$9 = (int *) 0x7935c0
```

ali dinamički objekt na toj adresi više ne postoji. `ptrTargetFloor` je tada viseći pokazivač (*dangling pointer*).

GDB je u ovom izvođenju za:

```text
p *ptrTargetFloor
```

ispisao:

```text
$10 = 8083040
```

Ta vrijednost više nema valjano značenje za naš program. Nakon `delete` objekt više ne postoji i pokazivač se ne smije dereferencirati. Rezultat takvog pristupa nije nešto na što se program smije oslanjati.

Nakon izvršavanja:

```cpp
ptrTargetFloor = nullptr;
```

GDB prikazuje:

```text
$11 = (int *) 0x0
```

Pokazivačka varijabla više ne sadrži adresu prethodno dinamički alociranog objekta.

Pokušaj dereferenciranja takvog pokazivača:

```text
p *ptrTargetFloor
```

završava porukom:

```text
Cannot access memory at address 0x0
```

Ova demonstracija jasno pokazuje razliku između adrese varijable, vrijednosti pokazivačke varijable, dereferencirane vrijednosti, te stanja pokazivača prije i nakon `delete` i postavljanja na `nullptr`.

---

## 15. Sažetak

Osnovni obrazac rada s pokazivačem na postojeću varijablu:

```cpp
int currentFloor{3};
int* ptrCurrentFloor{&currentFloor};

cout << *ptrCurrentFloor << '\n';
```

Odnos možemo zapamtiti ovako:

```text
+------------------------+          +------------------------+
| ptrCurrentFloor        |  ----->  | currentFloor           |
| vrijednost: adresa     |          | vrijednost: 3          |
+------------------------+          +------------------------+
```

Promjena varijable preko pokazivača:

```cpp
*ptrCurrentFloor = 5;
```

Pokazivač koji trenutačno ne sadrži valjanu adresu:

```cpp
int* ptrCurrentFloor{nullptr};
```

Osnovni obrazac ručne dinamičke alokacije:

```cpp
int* ptrTargetFloor{new int{7}};

// Rad s dinamički stvorenim objektom
cout << *ptrTargetFloor << '\n';

delete ptrTargetFloor;
ptrTargetFloor = nullptr;
```

Pokazivač na varijablu korisnički definiranog tipa:

```cpp
FloorSensorData objSensorData{4, true};
FloorSensorData* ptrSensorData{&objSensorData};

cout << ptrSensorData->mFloor << '\n';
```

Najvažnije je razlikovati:

- varijablu i njezinu vrijednost
- adresu varijable
- pokazivačku varijablu koja tu adresu čuva
- vrijednost dobivenu dereferenciranjem pokazivača
- adresu same pokazivačke varijable
- kod dinamičke alokacije, pokazivačku varijablu od dinamički stvorenog objekta
- životni vijek lokalne pokazivačke varijable od životnog vijeka dinamički stvorenog objekta
