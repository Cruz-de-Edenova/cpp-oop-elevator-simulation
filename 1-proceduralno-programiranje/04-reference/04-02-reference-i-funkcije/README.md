# Reference i funkcije

U prethodnoj temi reference smo koristili kao druga imena postojećih objekata. Sada ih koristimo s funkcijama: kao parametre i kao povratni tip funkcije.

Referenca kao parametar omogućuje funkciji pristup postojećem objektu pozivatelja bez stvaranja njegove kopije. Funkcija također može vratiti referencu na objekt koji već postoji, ali tada njegov životni vijek mora biti dovoljno dug.

## Sadržaj

1. Prosljeđivanje po vrijednosti
2. Referenca kao parametar funkcije
3. Prosljeđivanje po vrijednosti i pomoću reference
4. Objekt korisnički definiranog tipa kao referentni parametar
5. Referenca kao povratni tip funkcije
6. Promjena objekta pomoću vraćene reference
7. Životni vijek objekta i vraćena referenca
8. GDB demonstracija
9. Sažetak

Prateći primjeri:

- `01_reference_parameters.cpp`
- `02_struct_reference_parameter.cpp`
- `03_reference_return.cpp`

---

## 1. Prosljeđivanje po vrijednosti

Kod prosljeđivanja po vrijednosti parametar funkcije dobiva vlastitu kopiju vrijednosti argumenta.

U primjeru `01_reference_parameters.cpp` funkcija:
```cpp
void change_floor_copy(int floor)
{
    floor = 5;
    cout << "Vrijednost parametra floor: " << floor << '\n';
}
```
prima `int` po vrijednosti.

Poziv:
```cpp
int currentFloor{2};
change_floor_copy(currentFloor);
```
ne mijenja `currentFloor`. Promijenjena je samo lokalna varijabla `floor` unutar funkcije.

---

## 2. Referenca kao parametar funkcije

Parametar funkcije može biti referenca:
```cpp
void change_floor(int& refFloor)
{
    refFloor = 5;
    cout << "Vrijednost parametra refFloor: " << refFloor << '\n';
}
```
Pri pozivu:
```cpp
int currentFloor{2};
change_floor(currentFloor);
```
referentni parametar `refFloor` veže se uz objekt `currentFloor`.

Zato naredba:
```cpp
refFloor = 5;
```
mijenja `currentFloor` kod pozivatelja.

Poziv funkcije pritom ne koristi operator adrese:
```cpp
change_floor(currentFloor);
```

---

## 3. Prosljeđivanje po vrijednosti i pomoću reference

Osnovna razlika može se prikazati ovako:

| Parametar | Što funkcija dobiva | Promjena parametra mijenja objekt argumenta |
| --- | --- | --- |
| `int floor` | kopiju vrijednosti | ne |
| `int& refFloor` | referencu na postojeći objekt | da |

U primjeru `01_reference_parameters.cpp` nakon:
```cpp
change_floor_copy(currentFloor);
```
`currentFloor` ostaje `2`.

Nakon:
```cpp
change_floor(currentFloor);
```
`currentFloor` postaje `5`.

---

## 4. Objekt korisnički definiranog tipa kao referentni parametar

Referentni parametar može biti i referenca na objekt korisnički definiranog tipa.

U primjeru `02_struct_reference_parameter.cpp` koristimo:
```cpp
struct ElevatorState
{
    int mCurrentFloor;
    bool mDoorOpen;
};
```
Funkcija prima referencu na postojeći objekt:
```cpp
void update_state(ElevatorState& refState, int newFloor, bool doorOpen)
{
    refState.mCurrentFloor = newFloor;
    refState.mDoorOpen = doorOpen;
}
```
Poziv:
```cpp
ElevatorState objState{2, false};
update_state(objState, 5, true);
```
mijenja članove objekta `objState`.

Referentni parametar zato je koristan kada funkcija treba raditi s postojećim objektom, a ne s njegovom kopijom.

---

## 5. Referenca kao povratni tip funkcije

Funkcija može vratiti referencu:
```cpp
int& select_higher_floor(int& refFirstFloor, int& refSecondFloor)
{
    if (refFirstFloor > refSecondFloor)
    {
        return refFirstFloor;
    }

    return refSecondFloor;
}
```
Povratni tip:
```cpp
int&
```
označava da funkcija vraća referencu na postojeći objekt tipa `int`.

U ovom primjeru funkcija vraća jednu od referenci koje je primila kao parametre.

Poziv:
```cpp
int firstFloor{2};
int secondFloor{7};

int& refSelectedFloor{select_higher_floor(firstFloor, secondFloor)};
```
veže `refSelectedFloor` uz objekt koji je funkcija odabrala. U ovom slučaju to je `secondFloor`.

---

## 6. Promjena objekta pomoću vraćene reference

Budući da `refSelectedFloor` označava postojeći objekt, pomoću nje ga možemo mijenjati:
```cpp
refSelectedFloor = 10;
```
Ako je `refSelectedFloor` vezan uz `secondFloor`, nakon te naredbe vrijedi:
```text
firstFloor  = 2
secondFloor = 10
```
Funkcija `select_higher_floor()` nije vratila kopiju vrijednosti `7`, nego referencu na postojeći objekt `secondFloor`.

---

## 7. Životni vijek objekta i vraćena referenca

Funkcija koja vraća referencu mora vratiti referencu na objekt koji i nakon završetka funkcije još postoji.

Ovo je pogrešan obrazac:
```cpp
int& bad_reference()
{
    int value{10};
    return value;
}
```
`value` je lokalna varijabla. Njezin životni vijek završava izlaskom iz funkcije pa bi vraćena referenca ostala bez valjanog objekta.

U primjeru `03_reference_return.cpp` taj problem ne postoji, jer funkcija vraća jednu od referenci primljenih od pozivatelja:
```cpp
return refFirstFloor;
```
ili:
```cpp
return refSecondFloor;
```

---

## 8. GDB demonstracija

Referencu kao parametar možemo promatrati pomoću adresa.

### `01_reference_parameters.cpp`

```text
E:\Files\G++\OOP\04-reference\04-02-reference-i-funkcije>gdb -silent 01_reference_parameters.exe
Reading symbols from 01_reference_parameters.exe...
(gdb) break change_floor
Breakpoint 1 at 0x140001765: file 01_reference_parameters.cpp, line 16.
(gdb) run > NUL
Starting program: E:\Files\G++\OOP\04-reference\04-02-reference-i-funkcije\01_reference_parameters.exe > NUL
[New Thread 8452.0x10e8]
[New Thread 8452.0xba0]
[New Thread 8452.0x2bf4]

Thread 1 hit Breakpoint 1, change_floor (refFloor=@0x5ffe0c: 2) at 01_reference_parameters.cpp:16
16          refFloor = 5;
(gdb) p &refFloor
$1 = (int *) 0x5ffe0c
(gdb) up
#1  0x00007ff72095188a in demonstrate_reference_parameter () at 01_reference_parameters.cpp:40
40          change_floor(currentFloor);
(gdb) p &currentFloor
$2 = (int *) 0x5ffe0c
(gdb) q
``` 

Kada je izvođenje zaustavljeno unutar `change_floor()`, možemo provjeriti adresu objekta označenog parametrom:
```text
(gdb) p &refFloor
```
Zatim prijeđemo u frame funkcije pozivatelja:
```text
(gdb) up
(gdb) p &currentFloor
```
Adrese `&refFloor` i `&currentFloor` jednake su jer referentni parametar označava isti objekt.

### `03_reference_return.cpp`

```text
E:\Files\G++\OOP\04-reference\04-02-reference-i-funkcije>gdb -silent 03_reference_return.exe
Reading symbols from 03_reference_return.exe...
(gdb) break select_higher_floor
Breakpoint 1 at 0x14000171c: file 03_reference_return.cpp, line 8.
(gdb) break 23
Breakpoint 2 at 0x140001767: file 03_reference_return.cpp, line 23.
(gdb) break 29
Breakpoint 3 at 0x140001804: file 03_reference_return.cpp, line 29.
(gdb) run > NUL
Starting program: E:\Files\G++\OOP\04-reference\04-02-reference-i-funkcije\03_reference_return.exe > NUL
[New Thread 4256.0x1ba0]
[New Thread 4256.0x20cc]
[New Thread 4256.0x1590]

Thread 1 hit Breakpoint 1, select_higher_floor (refFirstFloor=@0x5ffe34: 2, refSecondFloor=@0x5ffe30: 7) at 03_reference_return.cpp:8
8           if (refFirstFloor > refSecondFloor)
(gdb) info args
refFirstFloor = @0x5ffe34: 2
refSecondFloor = @0x5ffe30: 7
(gdb) c
Continuing.

Thread 1 hit Breakpoint 2, main () at 03_reference_return.cpp:23
23          cout << "Prvi kat: " << firstFloor << '\n';
(gdb) p &refSelectedFloor
$1 = (int *) 0x5ffe30
(gdb) c
Continuing.

Thread 1 hit Breakpoint 3, main () at 03_reference_return.cpp:29
29          cout << "\nNakon promjene pomocu vracene reference:\n";
(gdb) p &secondFloor
$2 = (int *) 0x5ffe30
(gdb) q
```

---

## 9. Sažetak

### 1. Referenca kao parametar funkcije

Referencu kao parametar deklariramo pomoću `&`:
```cpp
void change_floor(int& refFloor);
```
Pri pozivu se veže uz postojeći objekt argumenta, pa funkcija može mijenjati taj objekt.

### 2. Prosljeđivanje po vrijednosti i pomoću reference

Parametar proslijeđen po vrijednosti dobiva kopiju. Referenca kao parametar označava postojeći objekt pozivatelja.

### 3. Povrat reference

Funkcija može vratiti referencu:
```cpp
int& select_higher_floor(int& refFirstFloor, int& refSecondFloor);
```
Vraćena referenca omogućuje daljnji pristup odabranom objektu bez stvaranja njegove kopije.

### 4. Životni vijek

Ne smije se koristiti vraćena referenca na lokalni objekt čiji je životni vijek završio izlaskom iz funkcije. Objekt na koji vraćena referenca upućuje mora i dalje postojati.

---
