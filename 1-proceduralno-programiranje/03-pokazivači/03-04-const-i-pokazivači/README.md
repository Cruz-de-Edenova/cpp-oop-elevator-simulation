# `const` i pokazivači

U temi 02-01 `const` i `constexpr` već smo upoznali osnovno značenje kvalifikatora `const`: nakon inicijalizacije vrijednost se ne smije mijenjati kroz naziv koji je označen kao `const`. U prethodnim temama zatim smo obradili pokazivače, dereferenciranje i pokazivače kao parametre funkcija.

U ovoj temi povezujemo ta dva područja. Kod pokazivača `const` može ograničiti promjenu podatka kojem pristupamo preko pokazivača, promjenu samog pokazivača ili oboje.

Posebno ćemo razlikovati:

```cpp
const int* ptrValue;
int* const ptrValue;
const int* const ptrValue;
```

Ta tri zapisa imaju različita značenja i omogućuju različite operacije.

## Sadržaj

1. Pokazivač na `const int`
2. `const` pokazivač
3. `const` pokazivač na `const int`
4. `const` i pokazivači kao parametri funkcija
5. Sažetak

Prateći primjeri:

- `01_pointer_to_const.cpp`
- `02_const_pointer.cpp`
- `03_const_pointer_parameters.cpp`

---

## 1. Pokazivač na `const int`

Promotrimo:

```cpp
int value{10};
const int* ptrValue{&value};
```

Varijabla `value` obična je `int` varijabla i može se mijenjati:

```cpp
value = 20;
```

Međutim, preko pokazivača `ptrValue` vrijednost se ne smije mijenjati:

```cpp
// *ptrValue = 20;  // Pogreška pri kompajliranju
```

Pokazivač je tipa:

```cpp
const int*
```

što čitamo kao:

> pokazivač na `const int`

To ne znači da je sama varijabla `value` postala `const`. Ograničenje vrijedi za pristup vrijednosti preko `ptrValue`.

Odnos možemo pojednostavljeno prikazati ovako:

```text
value
+----+
| 10 |
+----+
  ↑
ptrValue
const int*

value = 20;       -> dopušteno
*ptrValue = 20;   -> nije dopušteno
```

### 1.1. Pokazivač na `const` varijablu

Pokazivač na `const int` može pokazivati i na varijablu koja je sama označena s `const`:

```cpp
const int value{30};
const int* ptrValue{&value};
```

Sada vrijednost nije moguće mijenjati ni izravno preko naziva `value`:

```cpp
// value = 40;  // Pogreška pri kompajliranju
```

ni preko pokazivača:

```cpp
// *ptrValue = 40;  // Pogreška pri kompajliranju
```

Za tip pokazivača možemo koristiti i alternativni zapis:

```cpp
int const* ptrAlternative{&value};
```

Zapisi:

```cpp
const int*
int const*
```

predstavljaju isti tip: pokazivač na `const int`.

### 1.2. Preusmjeravanje pokazivača na `const int`

Kod zapisa:

```cpp
const int* ptrValue{&firstValue};
```

`const` se odnosi na podatak kojem pristupamo preko pokazivača, a ne na sam pokazivač.

Zato se `ptrValue` može preusmjeriti na drugu varijablu:

```cpp
int firstValue{10};
int secondValue{20};

const int* ptrValue{&firstValue};

ptrValue = &secondValue;
```

Prije preusmjeravanja:

```text
ptrValue ------> firstValue
                 +----+
                 | 10 |
                 +----+
```

Nakon preusmjeravanja:

```text
ptrValue ------> secondValue
                 +----+
                 | 20 |
                 +----+
```

Dakle, kod `const int*`:

- vrijednost se ne može mijenjati preko pokazivača
- pokazivač se može preusmjeriti

---

## 2. `const` pokazivač

Kod zapisa:

```cpp
int* const ptrValue{&value};
```

`const` se odnosi na sam pokazivač.

Takav pokazivač nakon inicijalizacije ne može promijeniti adresu koju sadrži:

```cpp
// ptrValue = nullptr;  // Pogreška pri kompajliranju
```

Međutim, podatak na koji pokazuje nije `const`, pa ga preko pokazivača možemo mijenjati:

```cpp
*ptrValue = 20;
```

Odnos možemo sažeti ovako:

```text
int* const ptrValue

ptrValue = drugaAdresa;  -> nije dopušteno
*ptrValue = novaVrijednost; -> dopušteno
```

Budući da je sam pokazivač `const`, mora biti inicijaliziran pri definiciji:

```cpp
int value{30};

int* const ptrValue{&value};
```

Ovo nije dopušteno:

```cpp
// int* const ptrValue;  // Pogreška pri kompajliranju
```

Pokazivaču bi se u protivnom adresa morala dodijeliti naknadno, a upravo to `const` zabranjuje.

---

## 3. `const` pokazivač na `const int`

Oba ograničenja možemo spojiti:

```cpp
int value{40};
const int* const ptrValue{&value};
```

Ovaj zapis znači:

> `ptrValue` je `const` pokazivač na `const int`.

Zato nije dopušteno mijenjati vrijednost preko pokazivača:

```cpp
// *ptrValue = 50;  // Pogreška pri kompajliranju
```

niti preusmjeriti sam pokazivač:

```cpp
// ptrValue = nullptr;  // Pogreška pri kompajliranju
```

Sama varijabla `value` u ovom primjeru ipak nije `const`:

```cpp
value = 50;
```

pa se može promijeniti izravno preko svojeg naziva. `ptrValue` će tada pri dereferenciranju vidjeti novu vrijednost.

---

## 4. `const` i pokazivači kao parametri funkcija

U prethodnoj temi vidjeli smo da funkcija može primiti pokazivač na strukturu:

```cpp
void change_floor(ElevatorState* ptrState, int newFloor);
```

Takva funkcija preko pokazivača može mijenjati strukturu pozivatelja:

```cpp
ptrState->mCurrentFloor = newFloor;
```

Ako funkcija treba samo čitati strukturu, parametar možemo zapisati kao pokazivač na `const` strukturu:

```cpp
void print_state(const ElevatorState* ptrState)
{
    if (ptrState == nullptr)
    {
        return;
    }

    cout << "Kat: " << ptrState->mCurrentFloor << '\n';
    cout << "Vrata otvorena: "
         << (ptrState->mDoorOpen ? "da" : "ne") << '\n';

    // ptrState->mCurrentFloor = 5;  // Pogreška pri kompajliranju
}
```

Zapis:

```cpp
const ElevatorState* ptrState
```

znači da funkcija preko `ptrState` može čitati članove strukture, ali ih ne može mijenjati.

Sam pokazivač kao parametar i dalje se prosljeđuje po vrijednosti. `const` u ovom zapisu odnosi se na strukturu kojoj pristupamo preko pokazivača, a ne na lokalnu kopiju pokazivača `ptrState`.

Ovakav potpis funkcije jasno izražava njezinu namjeru:

```cpp
void print_state(const ElevatorState* ptrState);           // Čita strukturu
void change_floor(ElevatorState* ptrState, int newFloor);  // Može je mijenjati
```

### 4.1. Prosljeđivanje obične i `const` strukture

Funkciji koja prima pokazivač na `const` strukturu možemo proslijediti adresu obične strukture:

```cpp
ElevatorState objState{2, false};

print_state(&objState);
```

To je dopušteno. Funkcija samo dobiva ograničen pristup strukturi preko svojeg parametra i ne može je mijenjati preko tog pokazivača.

Možemo joj proslijediti i adresu strukture koja je sama `const`:

```cpp
const ElevatorState objState{7, true};

print_state(&objState);
```

I taj poziv je dopušten jer `print_state()` ne zahtijeva mogućnost promjene strukture.

Suprotan smjer nije dopušten:

```cpp
const ElevatorState objState{7, true};

// change_floor(&objState, 3);  // Pogreška pri kompajliranju
```

Funkcija `change_floor()` prima:

```cpp
ElevatorState* ptrState
```

pa bi preko pokazivača mogla mijenjati strukturu. Davanje adrese `const` strukture takvoj funkciji uklonilo bi zaštitu koju `const` treba osigurati, zato kompajler taj poziv odbija.

---

## 5. Sažetak

### 1. Usporedba oblika

Najvažnija razlika između obrađenih oblika može se prikazati tablicom:

| Deklaracija | Promjena vrijednosti preko pokazivača | Preusmjeravanje pokazivača |
| --- | --- | --- |
| `int* ptrValue` | dopuštena | dopušteno |
| `const int* ptrValue` | nije dopuštena | dopušteno |
| `int* const ptrValue` | dopuštena | nije dopušteno |
| `const int* const ptrValue` | nije dopuštena | nije dopušteno |

Pri čitanju deklaracije korisno je razlikovati što je označeno s `const`.

```cpp
const int* ptrValue;
```

`ptrValue` je pokazivač na `const int`.

```cpp
int* const ptrValue{&value};
```

`ptrValue` je `const` pokazivač na `int`.

```cpp
const int* const ptrValue{&value};
```

`ptrValue` je `const` pokazivač na `const int`.

### 2. `const` uz pokazivač kao parametar funkcije

```cpp
void print_state(const ElevatorState* ptrState);
```

funkciji omogućuje čitanje strukture preko pokazivača, ali ne i njezinu promjenu preko tog pokazivača.

Obična struktura može se proslijediti takvoj funkciji:

```cpp
ElevatorState objState{2, false};
print_state(&objState);
```

a može se proslijediti i `const` struktura:

```cpp
const ElevatorState objState{7, true};
print_state(&objState);
```

### 3. Zaštita koju osigurava kompajler

Pokušaj promjene podatka preko pokazivača na `const`, preusmjeravanja `const` pokazivača ili prosljeđivanja `const` strukture funkciji koja je smije mijenjati uzrokuje pogrešku pri kompajliranju.

Time `const` ne služi samo kao opis namjere programera, nego kompajleru omogućuje provođenje tih ograničenja.

---
