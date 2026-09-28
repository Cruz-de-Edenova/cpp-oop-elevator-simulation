# Reference i pokazivači: razlike i ograničenja

Reference i pokazivači omogućuju pristup postojećim varijablama i objektima bez stvaranja njihove kopije, ali se razlikuju u tome što mogu predstavljati i kako izražavaju namjeru funkcije.

Prva dva primjera ove teme kratko uspoređuju već obrađena svojstva referenci i pokazivača. Glavni novi sadržaj prikazan je u `03_reference_or_pointer_parameter.cpp`, gdje uspoređujemo referencu i pokazivač kao parametre funkcije te mogućnost korištenja `nullptr`.

## Sadržaj

1. Referenca ili pokazivač kao parametar funkcije
2. Pokazivač kao parametar i `nullptr`
3. Zašto je provjera `nullptr` važna?
4. Kada koristiti referencu, a kada pokazivač?
5. Sažetak

Prateći primjeri:

- `01_reference_vs_pointer.cpp`
- `02_binding_and_reassignment.cpp`
- `03_reference_or_pointer_parameter.cpp`

---

## 1. Referenca ili pokazivač kao parametar funkcije

U primjeru `03_reference_or_pointer_parameter.cpp` istu vrstu objekta prosljeđujemo funkciji na dva načina.

Prva funkcija prima referencu:
```cpp
void set_floor(ElevatorState& refState, int newFloor)
{
    refState.mCurrentFloor = newFloor;
}
```

Poziv:
```cpp
ElevatorState objState{2, false};
set_floor(objState, 5);
```
izražava da funkcija očekuje postojeći objekt `ElevatorState`.

Druga funkcija prima pokazivač:
```cpp
bool try_set_floor(ElevatorState* ptrState, int newFloor)
{
    if (ptrState == nullptr)
    {
        return false;
    }

    ptrState->mCurrentFloor = newFloor;
    return true;
}
```
Pokazivač kao parametar omogućuje da funkciji proslijedimo adresu postojećeg objekta, ali i `nullptr`.

---

## 2. Pokazivač kao parametar i `nullptr`

Funkciju koja prima pokazivač možemo pozvati adresom objekta:
```cpp
ElevatorState objState{2, false};

bool success{try_set_floor(&objState, 5)};
```
U tom slučaju `ptrState` pokazuje na `objState`, pa funkcija mijenja njegov član `mCurrentFloor` i vraća `true`.

U našem primjeru dopuštamo i poziv:
```cpp
success = try_set_floor(nullptr, 7);
```
`nullptr` označava da funkciji nije proslijeđena adresa objekta.

Funkcija zato provjerava vrijednost pokazivača:
```cpp
if (ptrState == nullptr)
{
    return false;
}
```
Ako primi `nullptr`, vraća `false` i ne pokušava pristupiti objektu.

U primjeru se zato nakon poziva s `nullptr` dobiva:
```text
Poziv s nullptr:
Uspjeh: ne
Kat: 5
```
Kat ostaje `5` jer se naredba koja bi ga postavila na `7` nije izvršila.

---

## 3. Zašto je provjera `nullptr` važna?

Kada pokazivač kao parametar može imati vrijednost `nullptr`, prije dereferenciranja potrebno je provjeriti njegovu vrijednost.

Ako bismo iz funkcije uklonili:
```cpp
if (ptrState == nullptr)
{
    return false;
}
```
poziv:
```cpp
try_set_floor(nullptr, 7);
```
došao bi do naredbe:
```cpp
ptrState->mCurrentFloor = newFloor;
```
iako `ptrState` ne pokazuje ni na jedan objekt.

Takav pristup zahtijeva dereferenciranje null pokazivača i uzrokuje **nedefinirano ponašanje** (*undefined behavior*).

Važno je razlikovati kompajliranje od izvođenja programa. Funkcija bez provjere može se uspješno kompajlirati, ali problem nastaje kada se tijekom izvođenja pokuša dereferencirati pokazivač čija je vrijednost `nullptr`.

Program se u praksi može srušiti zbog nevaljanog pristupa memoriji, ali kod nedefiniranog ponašanja C++ ne jamči određeni rezultat.

U našem primjeru provjera:
```cpp
if (ptrState == nullptr)
{
    return false;
}
```
sprječava dolazak do dereferenciranja kada objekt nije dostupan.

---

## 4. Kada koristiti referencu, a kada pokazivač?

Na ovoj razini izbor možemo povezati s namjerom funkcije.

| Situacija | Referenca | Pokazivač |
| --- | --- | --- |
| Funkcija očekuje postojeći objekt | prirodan izbor | moguće |
| Potrebno je dopustiti odsutnost objekta | nije moguće pomoću reference | prirodan izbor pomoću `nullptr` |
| Treba promijeniti na koji objekt pristupamo | nije moguće ponovno vezivanje | prirodan izbor |
| Jednostavan pristup postojećem objektu bez kopiranja | prirodan izbor | moguće |
| Funkcija treba provjeravati postoji li objekt | nije potrebno | potrebno je, zbog mogućnosti da pokazivač bude `nullptr` |
| Pristup članovima objekta | operator `.` | operator `->` |
| Rad s dinamički alociranim objektom | ne koristi se za stvaranje dinamički alociranih objekata, ali se može vezati uz već postojeći takav objekt | koristi se za pristup dinamički alociranom objektu |

U našem primjeru:
```cpp
void set_floor(ElevatorState& refState, int newFloor);
```
koristimo kada objekt mora postojati.

Oblik:
```cpp
bool try_set_floor(ElevatorState* ptrState, int newFloor);
```
koristimo kada želimo dopustiti i mogućnost da objekt nije dostupan, te tu situaciju obraditi pomoću `nullptr`.

To nije pravilo da jedna vrsta parametra uvijek mora biti bolja od druge. Izbor ovisi o tome što funkcija treba predstavljati.

---

## 5. Sažetak

- Referenca kao parametar prikladna je kada funkcija očekuje postojeći objekt.
- Pokazivač kao parametar može predstavljati adresu objekta, ali i `nullptr`.
- Ako pokazivač kao parametar može imati vrijednost `nullptr`, prije dereferenciranja potrebno je provjeriti njegovu vrijednost.
- Dereferenciranje null pokazivača uzrokuje nedefinirano ponašanje.
- Kod koji dereferencira `nullptr` može se uspješno kompajlirati; problem nastaje tijekom izvođenja kada se takva naredba izvrši.
- Referencu koristimo kada funkcija očekuje postojeći objekt, a pokazivač kada je potrebno dopustiti i mogućnost `nullptr`.
