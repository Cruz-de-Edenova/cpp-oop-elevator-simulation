# Osnove referenci

U prethodnoj temi pokazivače smo koristili za indirektan pristup postojećim varijablama preko njihovih memorijskih adresa. Reference omogućuju drugi način pristupa postojećoj varijabli: nakon inicijalizacije referencu možemo koristiti kao drugo ime za tu varijablu.

U ovoj temi obrađujemo osnovno korištenje referenci. Promatramo deklaraciju i inicijalizaciju reference, čitanje i promjenu varijable preko reference, odnos memorijskih adresa te važnu činjenicu da se jednom vezana referenca ne može preusmjeriti na drugu varijablu.

Reference će kasnije biti posebno važne kod prosljeđivanja podataka funkcijama, `const` referenci i rada s korisnički definiranim tipovima.

## Sadržaj

1. Što je referenca?
2. Deklaracija i inicijalizacija reference
3. Pristup vrijednosti preko reference
4. Promjena vrijednosti varijable preko reference
5. Odnos varijable i reference
6. Više referenci na istu varijablu
7. Referenca se ne može preusmjeriti
8. Referenca na objekt korisnički definiranog tipa
9. Osnovna ograničenja referenci
10. Usporedba reference i pokazivača
11. GDB demonstracija
12. Sažetak

Prateći primjeri:

- `01_reference_basics.cpp`
- `02_reference_binding.cpp`
- `03_reference_to_struct.cpp`

---

## 1. Što je referenca?

**Referenca** je drugo ime, odnosno alias, za već postojeći objekt ili funkciju.

U ovoj temi reference najprije vežemo uz obične varijable. Promotrimo:
```cpp
int currentFloor{3};
int& refCurrentFloor{currentFloor};
```
`currentFloor` je varijabla tipa `int`, a `refCurrentFloor` je referenca vezana uz tu varijablu.

Pojednostavljeno:
```text
                ista varijabla
                      |
                      v
                   +-----+
currentFloor ----> |  3  | <---- refCurrentFloor
                   +-----+
```
Stvaranjem reference nije stvorena još jedna `int` varijabla s kopijom vrijednosti `3`. `currentFloor` i `refCurrentFloor` omogućuju pristup istoj varijabli.

To je važna razlika u odnosu na običnu inicijalizaciju nove varijable:
```cpp
int currentFloor{3};
int copiedFloor{currentFloor};
```
Ovdje postoje dvije različite `int` varijable:
```text
currentFloor         copiedFloor
+-----+              +-----+
|  3  |              |  3  |
+-----+              +-----+
```
Njihove početne vrijednosti jesu jednake, ali promjena jedne varijable ne mijenja drugu.

Kod reference:
```cpp
int currentFloor{3};
int& refCurrentFloor{currentFloor};
```
ne postoji takva kopija. Referenca omogućuje pristup izvornoj varijabli.

---

## 2. Deklaracija i inicijalizacija reference

Referencu na `int` deklariramo pomoću znaka `&`:
```cpp
int& refCurrentFloor{currentFloor};
```
Zapis možemo rastaviti ovako:
```text
int&             -> referenca na int
refCurrentFloor  -> naziv reference
currentFloor     -> varijabla uz koju se referenca veže
```
Znak `&` ovdje je dio deklaratora reference. To nije ista uporaba znaka `&` kao kod operatora adrese:
```cpp
int* ptrCurrentFloor{&currentFloor};
```
U izrazu:
```cpp
&currentFloor
```
`&` je operator adrese i daje adresu varijable `currentFloor`.

Kod:
```cpp
int& refCurrentFloor{currentFloor};
```
`&` označava da deklariramo referencu.

### 2.1. Referenca mora biti inicijalizirana

Obična lokalna referenca mora biti vezana uz odgovarajuću varijablu pri svojoj inicijalizaciji:
```cpp
int currentFloor{3};
int& refCurrentFloor{currentFloor};
```
Ne možemo napisati:
```cpp
// int& refCurrentFloor;      // Pogreška: referenca nije inicijalizirana
```
U ovoj temi zato koristimo obrazac:
```cpp
int value{10};
int& refValue{value};
```

---

## 3. Pristup vrijednosti preko reference

Nakon što je referenca vezana uz varijablu, koristimo je poput same varijable:
```cpp
int currentFloor{3};
int& refCurrentFloor{currentFloor};

cout << currentFloor << '\n';
cout << refCurrentFloor << '\n';
```
Oba izraza ispisuju:
```text
3
3
```
Kod pokazivača smo morali razlikovati pokazivačku varijablu od varijable na koju pokazuje:
```cpp
int* ptrCurrentFloor{&currentFloor};

cout << ptrCurrentFloor << '\n';
cout << *ptrCurrentFloor << '\n';
```
Kod reference nije potreban operator dereferenciranja:
```cpp
cout << refCurrentFloor << '\n';
```
`refCurrentFloor` već predstavlja pristup varijabli uz koju je referenca vezana.

---

## 4. Promjena vrijednosti varijable preko reference

Budući da referencu možemo koristiti kao drugo ime za postojeću varijablu, preko reference možemo promijeniti tu varijablu:
```cpp
int currentFloor{3};
int& refCurrentFloor{currentFloor};

refCurrentFloor = 5;
```
Nakon dodjele:
```text
currentFloor    = 5
refCurrentFloor = 5
```
Nije promijenjena neka zasebna vrijednost reference. Promijenjena je varijabla `currentFloor`.

---

## 5. Odnos varijable i reference

Vezu reference i varijable možemo dodatno provjeriti pomoću njihovih adresa.

U primjeru `01_reference_basics.cpp` koristimo:
```cpp
cout << "\nAdresa currentFloor:    " << &currentFloor << '\n';
cout << "Adresa preko reference: " << &refCurrentFloor << '\n';
```
U jednom izvođenju programa dobiven je ispis:
```text
Adresa currentFloor:    0x8d313ffb24
Adresa preko reference: 0x8d313ffb24
```
Stvarna adresa može biti drugačija pri svakom izvođenju programa. Važan je njihov međusobni odnos:
```text
&currentFloor == &refCurrentFloor
```
Izraz `&currentFloor` daje adresu varijable `currentFloor`. Izraz `&refCurrentFloor` daje istu adresu jer `refCurrentFloor` predstavlja drugo ime za `currentFloor`.

---

## 6. Više referenci na istu varijablu

Uz istu varijablu može se vezati više referenci:
```cpp
int currentFloor{3};

int& refFirst{currentFloor};
int& refSecond{currentFloor};
```
Sva tri naziva omogućuju pristup istoj varijabli.

Ako promijenimo varijablu preko jedne reference:
```cpp
refFirst = 6;
```
vrijednost koju vidimo preko svih naziva postaje `6`:
```text
currentFloor = 6
refFirst     = 6
refSecond    = 6
```
Ne postoje tri sinkronizirane vrijednosti. Postoji samo jedna varijabla kojoj pristupamo preko više naziva.

---

## 7. Referenca se ne može preusmjeriti

Jedna od najvažnijih razlika između reference i pokazivača jest da se jednom inicijalizirana referenca ne može naknadno vezati uz drugu varijablu.

Promotrimo primjer `02_reference_binding.cpp`:
```cpp
int firstValue{10};
int secondValue{20};
int& refValue{firstValue};
```
Nakon inicijalizacije vrijedi:
```text
refValue ----> firstValue
               +----+
               | 10 |
               +----+

secondValue
+----+
| 20 |
+----+
```
Sada izvršavamo:
```cpp
refValue = secondValue;
```
Ova naredba **ne preusmjerava** `refValue` na `secondValue`, već vrijednost varijable `secondValue` dodjeljuje varijabli `firstValue`.

Budući da je `refValue` već drugo ime za `firstValue`, naredbu možemo promatrati kao:
```cpp
firstValue = secondValue;
```
Vrijednost `20` zato se kopira iz `secondValue` u `firstValue`.

Nakon dodjele:
```text
firstValue:  20
secondValue: 20
refValue:    20
```
Referenca je i dalje vezana uz `firstValue`.

---

## 8. Referenca na objekt korisnički definiranog tipa

Referenca nije ograničena na osnovne tipove poput `int`. Može biti vezana i uz objekt korisnički definiranog tipa.

U primjeru `03_reference_to_struct.cpp` imamo:
```cpp
struct ElevatorState
{
    int mCurrentFloor;
    bool mDoorOpen;
};
```
Stvaramo objekt tipa `ElevatorState` i referencu na taj objekt:
```cpp
ElevatorState objState{2, false};
ElevatorState& refState{objState};
```
`refState` je referenca na objekt `objState` tipa `ElevatorState`.

Članovima pristupamo preko reference jednako kao preko naziva izvornog objekta:
```cpp
refState.mCurrentFloor = 5;
refState.mDoorOpen = true;
```

---

## 9. Osnovna ograničenja referenci

Reference imaju nekoliko važnih jezičnih ograničenja.

### 9.1. Ne postoji obična `null` referenca

Kod pokazivača možemo jasno predstaviti stanje u kojem pokazivač trenutačno ne pokazuje na valjanu varijablu:
```cpp
int* ptrValue{nullptr};
```
Za običnu pravilno inicijaliziranu referencu ne koristimo odgovarajući oblik s `nullptr`. U primjerima ove teme referenca se pri inicijalizaciji veže uz postojeću varijablu.

### 9.2. Reference nisu objekti

Budući da reference same nisu objekti, određene konstrukcije nisu dopuštene.

Ne postoji polje referenci:
```cpp
// Pogreška
// int& refValues[3];
```
Ne postoji pokazivač na referencu:
```cpp
// Pogreška
// int&* ptrReference;
```
Ne možemo izravno deklarirati ni referencu na referencu:
```cpp
// Pogreška
// int& &refReference;
```

### 9.3. Ne postoji referenca na `void`

Ovo nije valjan tip:
```cpp
// Pogreška
// void& refValue;
```
Pokazivač tipa `void*`, koji smo ranije obradili, dopušten je:
```cpp
void* ptrData{nullptr};
```
ali referenca na `void` nije dopuštena.

---

## 10. Usporedba reference i pokazivača

Reference i pokazivači omogućuju pristup postojećim varijablama bez stvaranja njihove kopije, ali njihov način korištenja nije isti.
Osnovne razlike možemo sažeti tablicom:

| Svojstvo | Referenca | Pokazivač |
| --- | --- | --- |
| Omogućuje pristup postojećoj varijabli | da | da |
| Za osnovni pristup vrijednosti koristi `*` | ne | da |
| Pri inicijalizaciji koristimo adresu varijable | ne | da |
| Može se naknadno preusmjeriti na drugu varijablu | ne | da |
| Može imati vrijednost `nullptr` | ne | da |
| Operator `&` nad nazivom daje adresu ciljne varijable | da | ne; `&ptr` daje adresu pokazivačke varijable |

U kasnijim temama vidjet ćemo situacije u kojima je prirodnija referenca i situacije u kojima nam je potrebna mogućnost koju pruža pokazivač.

---

## 11. GDB demonstracija

Za demonstraciju referenci najkorisnije je u GDB-u promatrati njihove vrijednosti i adrese.

`01_reference_basics.cpp`
```text
E:\Files\G++\OOP\04-reference\04-01-osnove-referenci>gdb -silent 01_reference_basics.exe
Reading symbols from 01_reference_basics.exe...
(gdb) break 12
Breakpoint 1 at 0x140001734: file 01_reference_basics.cpp, line 12.
(gdb) break 18
Breakpoint 2 at 0x1400017d4: file 01_reference_basics.cpp, line 18.
(gdb) break 25
Breakpoint 3 at 0x14000188a: file 01_reference_basics.cpp, line 25.
(gdb) run > NUL
Starting program: E:\Files\G++\OOP\04-reference\04-01-osnove-referenci\01_reference_basics.exe > NUL
[New Thread 5676.0x2158]
[New Thread 5676.0x1b94]
[New Thread 5676.0x1f68]

Thread 1 hit Breakpoint 1, main () at 01_reference_basics.cpp:12
12          cout << "currentFloor:      " << currentFloor << '\n';
(gdb) list 8,10
8           int currentFloor{3};
9           int& refCurrentFloor{currentFloor};
10          int& refSelectedFloor{currentFloor};
(gdb) p currentFloor
$1 = 3
(gdb) p refCurrentFloor
$2 = (int &) @0x5ffe2c: 3
(gdb) p refSelectedFloor
$3 = (int &) @0x5ffe2c: 3
(gdb) p &currentFloor
$4 = (int *) 0x5ffe2c
(gdb) p &refCurrentFloor
$5 = (int *) 0x5ffe2c
(gdb) p &refSelectedFloor
$6 = (int *) 0x5ffe2c
(gdb) c
Continuing.
[New Thread 5676.0x1034]

Thread 1 hit Breakpoint 2, main () at 01_reference_basics.cpp:18
18          cout << "\nNakon promjene preko refCurrentFloor:\n";
(gdb) p currentFloor
$7 = 5
(gdb) p refCurrentFloor
$8 = (int &) @0x5ffe2c: 5
(gdb) p refSelectedFloor
$9 = (int &) @0x5ffe2c: 5
(gdb) c
Continuing.

Thread 1 hit Breakpoint 3, main () at 01_reference_basics.cpp:25
25          cout << "\nNakon promjene preko refSelectedFloor:\n";
(gdb) p currentFloor
$10 = 7
(gdb) p refCurrentFloor
$11 = (int &) @0x5ffe2c: 7
(gdb) p refSelectedFloor
$12 = (int &) @0x5ffe2c: 7
(gdb) q
```

`02_reference_binding.cpp`
```text
E:\Files\G++\OOP\04-reference\04-01-osnove-referenci>gdb -silent 02_reference_binding.exe
Reading symbols from 02_reference_binding.exe...
(gdb) break 19
Breakpoint 1 at 0x1400017e5: file 02_reference_binding.cpp, line 19.
(gdb) list 8,10
8           int firstValue{10};
9           int secondValue{20};
10          int& refValue{firstValue};
(gdb) run > NUL
Starting program: E:\Files\G++\OOP\04-reference\04-01-osnove-referenci\02_reference_binding.exe > NUL
[New Thread 5736.0xe0c]
[New Thread 5736.0x1b48]
[New Thread 5736.0x1a18]

Thread 1 hit Breakpoint 1, main () at 02_reference_binding.cpp:19
19          cout << "\nNakon refValue = secondValue:\n";
(gdb) p &firstValue
$1 = (int *) 0x5ffe34
(gdb) p &secondValue
$2 = (int *) 0x5ffe30
(gdb) p &refValue
$3 = (int *) 0x5ffe34
(gdb) q
```

---

## 12. Sažetak

### 1. Osnovno značenje reference

Referencu deklariramo oblikom:
```cpp
int& refValue{value};
```
`refValue` je drugo ime za postojeću varijablu `value`. Stvaranjem reference ne nastaje kopija te varijable.

### 2. Pristup i promjena

Varijabli preko reference pristupamo bez operatora dereferenciranja:
```cpp
cout << refValue << '\n';
```
Promjena preko reference mijenja izvornu varijablu:
```cpp
refValue = 20;
```

### 3. Adresa preko reference

Za:
```cpp
int value{10};
int& refValue{value};
```
vrijedi:
```text
&value == &refValue
```
Oba izraza daju adresu iste varijable.

### 4. Vezivanje reference

Referenca mora biti inicijalizirana tako da se veže uz odgovarajuću varijablu. Jednom vezana referenca ne može se preusmjeriti:
```cpp
int& refValue{firstValue};
refValue = secondValue;
```
Naredba `refValue = secondValue;` ne veže `refValue` uz `secondValue`. Vrijednost `secondValue` dodjeljuje varijabli `firstValue`.

### 5. Korisnički definirani tipovi

Referenca se može vezati i uz objekt korisnički definiranog tipa:
```cpp
ElevatorState objState{2, false};
ElevatorState& refState{objState};
```
Članovima pristupamo operatorom `.`:
```cpp
refState.mCurrentFloor = 5;
```

### 6. Osnovna ograničenja

Reference same nisu objekti. Ne postoje obična polja referenci, pokazivači na reference ni izravno deklarirane reference na reference. Ne može se formirati ni referenca na `void`.
