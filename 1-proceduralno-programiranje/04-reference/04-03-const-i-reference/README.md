# `const` i reference

U prethodnoj temi reference smo koristili kao parametre i povratne vrijednosti funkcija. U ovoj temi dodajemo `const` kako bismo ograničili promjenu vrijednosti pomoću reference.

Deklaracija `const int&` predstavlja referencu na `const int`. Takva referenca može se vezati uz `const` varijablu, ali i uz običnu varijablu.

## Sadržaj

1. Referenca na `const int` vezana uz `const` varijablu
2. Referenca na `const int` vezana uz običnu varijablu
3. Referenca na `const` objekt kao parametar funkcije
4. Referenca na `const int` kao povratna vrijednost funkcije
5. Sažetak

Prateći primjeri:

- `01_const_references.cpp`
- `02_const_reference_parameter.cpp`
- `03_const_reference_return.cpp`

---

## 1. Referenca na `const int` vezana uz `const` varijablu

Referencu na `const int` možemo vezati uz `const` varijablu:
```cpp
const int lockedFloor{5};
const int& refLockedFloor{lockedFloor};
```

Vrijednost nije dopušteno mijenjati ni izravno pomoću `lockedFloor` ni pomoću `refLockedFloor`:
```cpp
// lockedFloor = 7;    // Nije dopušteno
// refLockedFloor = 7; // Nije dopušteno
```

Obična referenca `int&` ne može se vezati uz `const int` varijablu:
```cpp
// int& refFloor{lockedFloor}; // Nije dopušteno
```
Takav pokušaj vezivanja uzrokuje pogrešku pri kompajliranju jer bi obična referenca omogućila promjenu `const` varijable.

---

## 2. Referenca na `const int` vezana uz običnu varijablu

Referenca na `const int` može se vezati i uz običnu varijablu:
```cpp
int floor{5};
const int& refFloor{floor};
```

Varijabla `floor` i dalje se može mijenjati izravno:
```cpp
floor = 7;
```

Referenca i dalje označava istu varijablu pa će `refFloor` nakon promjene također dati vrijednost `7`.

Promjena vrijednosti pomoću reference nije dopuštena:
```cpp
// refFloor = 9; // Nije dopušteno
```

Dakle, `const int&` ne čini samu varijablu `floor` konstantnom. Ograničenje vrijedi za pristup pomoću te reference.

---

## 3. Referenca na `const` objekt kao parametar funkcije

Referenca na `const` korisna je kada funkcija treba pristupiti postojećem objektu, ali ga ne treba mijenjati.

U primjeru `02_const_reference_parameter.cpp` funkcija prima referencu na `const ElevatorState`:
```cpp
void print_state(const ElevatorState& refState)
{
    cout << "Kat: " << refState.mCurrentFloor << '\n';
    cout << "Vrata otvorena: " << (refState.mDoorOpen ? "da" : "ne") << '\n';

    // refState.mCurrentFloor = 5; // Nije dopušteno
}
```

Takvoj funkciji možemo proslijediti običan objekt:
```cpp
ElevatorState objState{2, false};
print_state(objState);
```

ali i `const` objekt:
```cpp
const ElevatorState objLockedState{7, true};
print_state(objLockedState);
```

Funkcija u oba slučaja pristupa postojećem objektu bez stvaranja njegove kopije, ali ga ne može mijenjati pomoću parametra `refState`.

---

## 4. Referenca na `const int` kao povratna vrijednost funkcije

Funkcija može vratiti referencu na `const int`:
```cpp
const int& select_higher_floor(const int& refFirstFloor, const int& refSecondFloor)
{
    if (refFirstFloor > refSecondFloor)
    {
        return refFirstFloor;
    }

    return refSecondFloor;
}
```
Parametri omogućuju čitanje proslijeđenih varijabli, ali ne i njihovu promjenu pomoću tih referenci.

Vraćenu referencu možemo spremiti ovako:
```cpp
const int& refSelectedFloor{select_higher_floor(firstFloor, secondFloor)};
```

Njome možemo čitati odabranu vrijednost, ali je ne možemo mijenjati:
```cpp
// refSelectedFloor = 10; // Nije dopušteno
```

Ako se izvorna varijabla promijeni izravno, promjena je vidljiva i pomoću reference:
```cpp
secondFloor = 10;
cout << refSelectedFloor; // 10
```

---

## 5. Sažetak

- `const int&` je referenca na `const int`.
- Referenca na `const int` može se vezati uz `const` ili običnu `int` varijablu.
- Obična referenca `int&` ne može se vezati uz `const int` varijablu.
- `const int&` kod obične varijable sprječava promjenu pomoću reference, ali ne sprječava izravnu promjenu same varijable.
- Referenca na `const` kao parametar omogućuje pristup postojećem objektu bez kopiranja i bez mogućnosti njegove promjene pomoću tog parametra.
- Funkcija može vratiti referencu na `const`, čime pozivatelj može pristupati postojećoj vrijednosti bez mogućnosti promjene pomoću vraćene reference.
