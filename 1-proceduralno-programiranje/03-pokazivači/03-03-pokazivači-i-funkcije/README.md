# Pokazivači i funkcije

U prethodnim temama pokazivače smo koristili za pristup postojećim varijablama, dinamički stvorenim objektima i elementima polja. U ovoj temi povezujemo pokazivače s funkcijama i promatramo kako funkcija može preko adrese pristupiti podacima koje posjeduje njezin pozivatelj.

Najprije uspoređujemo običan parametar proslijeđen po vrijednosti s pokazivačem kao parametrom funkcije. Zatim isti princip primjenjujemo na polja i strukture, pokazujemo pokazivač kao povratnu vrijednost te koristimo pokazivačke izlazne parametre kada funkcija treba proizvesti više rezultata.

Na kraju uvodimo pokazivače na funkcije (*function pointers*). Time pokazivač više ne koristimo samo za adresu podatka, nego i za odabir funkcije koju ćemo pozvati.

## Sadržaj

1. Argumenti i parametri funkcije
2. Pokazivač kao parametar funkcije
3. Pokazivač kao povratna vrijednost funkcije
4. Polje kao parametar funkcije
5. Struktura kao parametar funkcije
6. Struktura kao povratna vrijednost funkcije
7. Više rezultata preko izlaznih parametara
8. Struktura kao pregledniji povrat više rezultata
9. Pokazivači na funkcije
10. Pokazivač na funkciju kao parametar druge funkcije
11. GDB demonstracija
12. Sažetak

Prateći primjeri:

- `01_pointer_parameters.cpp`
- `02_arrays_and_structs.cpp`
- `03_function_pointers.cpp`
- `04_output_parameters.cpp`

---

## 1. Argumenti i parametri funkcije

Kod poziva funkcije važno je razlikovati **argument** od **parametra**.

U pozivu:

```cpp
change_copy(value);
```

`value` je argument koji pozivatelj predaje funkciji.

U definiciji:

```cpp
void change_copy(int value)
{
    value = 20;
}
```

`value` je parametar funkcije. 

Kod prosljeđivanja po vrijednosti parametar dobiva kopiju vrijednosti argumenta.

Ako pozivatelj ima:

```cpp
int value{10};
change_copy(value);
```

funkcija mijenja svoju lokalnu kopiju na `20`, ali varijabla pozivatelja nakon povratka iz funkcije i dalje sadrži `10`.

```text
pozivatelj                     change_copy()
                              
value                          value
+----+                         +----+
| 10 |  ---- kopiranje ---->   | 10 |
+----+                         +----+
                                  ↓
                               +----+
                               | 20 |
                               +----+
```

Promjena parametra zato ne mijenja izvornu varijablu pozivatelja.

---

## 2. Pokazivač kao parametar funkcije

Ako funkciji želimo omogućiti pristup varijabli pozivatelja, možemo joj proslijediti adresu te varijable:

```cpp
void change_original(int* ptrValue)
{
    if (ptrValue == nullptr)
    {
        return;
    }

    *ptrValue = 20;
}
```

Poziv izgleda ovako:

```cpp
int value{10};
change_original(&value);
```

Argument `&value` je adresa varijable `value`. Parametar `ptrValue` prima kopiju te adrese.

```text
pozivatelj                         change_original()

value                              ptrValue
+----+                             +----------+
| 10 | <-------------------------- | &value   |
+----+          *ptrValue          +----------+
```

Sam pokazivač kao parametar također se prosljeđuje po vrijednosti: funkcija dobiva kopiju adrese. Međutim, dereferenciranjem te kopirane adrese pristupa istoj varijabli `value` koju posjeduje pozivatelj.

Zato naredba:

```cpp
*ptrValue = 20;
```

mijenja varijablu pozivatelja.

Ovdje treba razlikovati dvije promjene:

```cpp
ptrValue = nullptr;  // Mijenja samo lokalnu kopiju pokazivača
*ptrValue = 20;      // Mijenja vrijednost na adresi pokazivača
```

Drugi izraz smije se koristiti samo kada pokazivač sadrži valjanu adresu.

---

## 3. Pokazivač kao povratna vrijednost funkcije

Pokazivač može biti i povratna vrijednost funkcije:

```cpp
int* find_larger(int* ptrFirst, int* ptrSecond)
{
    if (*ptrFirst > *ptrSecond)
    {
        return ptrFirst;
    }

    return ptrSecond;
}
```

Funkcija prima dvije adrese, uspoređuje vrijednosti na tim adresama i vraća jedan od pokazivača koje je već primila.

```cpp
int firstValue{12};
int secondValue{27};

int* ptrLarger{find_larger(&firstValue, &secondValue)};

cout << *ptrLarger << '\n';
```

U ovom primjeru funkcija ne stvara novi objekt i ne koristi dinamičku alokaciju. Povratna vrijednost samo je jedna od adresa koje su joj proslijeđene.

```text
ptrFirst  ----> firstValue  = 12
ptrSecond ----> secondValue = 27
                    |
                    +---- vraća se ptrSecond
```

Pozivatelj zatim preko vraćenog pokazivača može pristupiti većoj vrijednosti.

---

## 4. Polje kao parametar funkcije

Polje možemo proslijediti funkciji:

```cpp
void print_values(int values[], int elementCount)
{
    for (int index{0}; index < elementCount; ++index)
    {
        cout << values[index] << '\n';
    }
}
```

Poziv:

```cpp
constexpr int elementCount{4};
int values[elementCount]{2, 4, 6, 8};

print_values(values, elementCount);
```

Za razliku od običnog parametra proslijeđenog po vrijednosti, ovdje se **ne stvara kopija cijelog polja**.

Kod parametra funkcije zapis:

```cpp
int values[]
```

je ekvivalentan zapisu:

```cpp
int* values
```

Pri pozivu funkcije funkcija preko pokazivačkog parametra pristupa elementima izvornog polja.

Odnos možemo pojednostavljeno prikazati ovako:

```text
pozivatelj                              print_values()

values                                  values
+-----+-----+-----+-----+               +---------+
|  2  |  4  |  6  |  8  | <------------ | adresa  |
+-----+-----+-----+-----+               +---------+
  [0]   [1]   [2]   [3]
   ^
   |
   +------ pokazivač vodi do prvog elementa

Elementi polja nisu kopirani.
Funkcija pristupa elementima izvornog polja.
```

Zato ova dva oblika parametra predstavljaju isti osnovni mehanizam:

```cpp
void print_values(int values[], int elementCount);
void set_first_value(int* ptrValues, int newValue);
```

U prvom zapisu sintaksa `[]` naglašava da funkciju koristimo za obradu elemenata polja. U drugom zapisu `int*` izravno pokazuje da funkcija prima pokazivač.

Budući da funkcija pristupa izvornim elementima, može ih i promijeniti:

```cpp
void set_first_value(int* ptrValues, int newValue)
{
    ptrValues[0] = newValue;
}
```

Poziv:

```cpp
set_first_value(values, 10);
```

mijenja prvi element izvornog polja:

```text
prije poziva:

values
+-----+-----+-----+-----+
|  2  |  4  |  6  |  8  |
+-----+-----+-----+-----+

nakon poziva:

values
+-----+-----+-----+-----+
| 10  |  4  |  6  |  8  |
+-----+-----+-----+-----+
```

Pokazivač ne sadrži informaciju o broju elemenata polja, pa se `elementCount` funkciji prosljeđuje zasebno kada joj je potreban za prolazak kroz polje.

Važno je razlikovati običan parametar od parametra koji predstavlja polje:

```cpp
void function(int value);      // Stvara se kopija int vrijednosti
void function(int values[]);   // Ne stvara se kopija cijelog polja
```

U drugom slučaju funkcija preko pokazivača pristupa elementima izvornog polja.

---

## 5. Struktura kao parametar funkcije

Strukturu možemo funkciji proslijediti po vrijednosti:

```cpp
struct ElevatorState
{
    int mCurrentFloor;
    bool mDoorOpen;
};
```

```cpp
void change_floor_copy(ElevatorState objState, int newFloor)
{
    objState.mCurrentFloor = newFloor;
}
```

Poziv:

```cpp
ElevatorState objState{2, false};
change_floor_copy(objState, 5);
```

stvara kopiju cijele strukture u parametru `objState`. Promjena člana te kopije ne mijenja strukturu pozivatelja.

Ako želimo mijenjati strukturu pozivatelja, funkciji možemo proslijediti njezinu adresu:

```cpp
void change_floor(ElevatorState* ptrState, int newFloor)
{
    ptrState->mCurrentFloor = newFloor;
}
```

Poziv:

```cpp
change_floor(&objState, 5);
```

omogućuje funkciji da preko pokazivača promijeni član izvorne strukture.

```text
po vrijednosti                         preko pokazivača

objState                               ptrState
+------------------+                   +---------+
| kopija strukture |                   | adresa  | ----+
+------------------+                   +---------+     |
                                                       v
                                                +---------------+
                                                | objState      |
                                                | mCurrentFloor |
                                                +---------------+
```

---

## 6. Struktura kao povratna vrijednost funkcije

Funkcija može vratiti cijelu strukturu po vrijednosti:

```cpp
ElevatorState create_initial_state()
{
    ElevatorState objState{0, false};
    return objState;
}
```

Pozivatelj prima vraćenu vrijednost u vlastiti objekt:

```cpp
ElevatorState objState{create_initial_state()};
```

Nakon povratka iz funkcije `objState` sadrži:

```text
mCurrentFloor = 0
mDoorOpen     = false
```

Ovaj pristup ne zahtijeva pokazivač ni dinamičku alokaciju. Funkcija jednostavno vraća vrijednost korisnički definiranog tipa.

---

## 7. Više rezultata preko izlaznih parametara

Funkcija povratnog tipa `void` ne vraća vrijednost pomoću naredbe `return`, ali preko pokazivača može zapisati rezultate u više varijabli pozivatelja.

Takve parametre možemo koristiti kao **izlazne parametre** (*output parameters*):

```cpp
void calculate(
    int firstValue,      // Prva ulazna vrijednost
    int secondValue,     // Druga ulazna vrijednost
    int* ptrSum,         // Adresa varijable za rezultat zbrajanja
    int* ptrDifference)  // Adresa varijable za rezultat oduzimanja
{
    *ptrSum = firstValue + secondValue;
    *ptrDifference = firstValue - secondValue;
}
```

Pozivatelj priprema varijable u koje želi primiti rezultate:

```cpp
int sum{};
int difference{};

calculate(10, 4, &sum, &difference);
```

Odnos možemo pojednostavljeno prikazati ovako:

```text
calculate()

ptrSum        --------------------> sum
ptrDifference --------------------> difference

*ptrSum        = 14
*ptrDifference = 6
```

Funkcija tako preko dva pokazivača mijenja dvije različite varijable pozivatelja.

---

## 8. Struktura kao pregledniji povrat više rezultata

Ako više rezultata zajedno predstavlja jednu logičku cjelinu, možemo ih grupirati u strukturu:

```cpp
struct CalculationResult
{
    int mSum;
    int mDifference;
};
```

Funkcija tada može vratiti jednu vrijednost tipa `CalculationResult`:

```cpp
CalculationResult calculate_result(int firstValue, int secondValue)
{
    CalculationResult objResult{
        firstValue + secondValue,  // mSum
        firstValue - secondValue   // mDifference
    };

    return objResult;
}
```

Poziv postaje:

```cpp
CalculationResult objResult{calculate_result(10, 4)};
```

Oba pristupa daju ista dva rezultata:

```cpp
calculate(10, 4, &sum, &difference);   // Primjer iz prošlog poglavlja
```

i:

```cpp
CalculationResult objResult{calculate_result(10, 4)};
```

Pokazivački izlazni parametri važni su za razumijevanje načina na koji funkcija može mijenjati više varijabli pozivatelja. Međutim, kada rezultati prirodno pripadaju zajedno, struktura često daje pregledniji potpis funkcije i jasnije grupira podatke koji predstavljaju jedan rezultat.

---

## 9. Pokazivači na funkcije

Pokazivač može sadržavati i adresu funkcije.

Promotrimo dvije funkcije:

```cpp
int add(int firstValue, int secondValue)
{
    return firstValue + secondValue;
}

int subtract(int firstValue, int secondValue)
{
    return firstValue - secondValue;
}
```

Obje funkcije:

* vraćaju vrijednost tipa `int`
* primaju dva parametra tipa `int`

Kod određivanja tipa pokazivača na funkciju dovoljni su **tipovi parametara**. Njihove nazive nije potrebno navoditi.

Pokazivač koji može pokazivati na takvu funkciju definiramo ovako:

```cpp
int (*ptrOperation)(int, int){add};
```

ili

```cpp
int (*ptrOperation)(int, int){subtract};
```

Ovaj zapis možemo čitati počevši od naziva `ptrOperation`:

```text
ptrOperation
    |
    +-- *ptrOperation       -> pokazivač
    |
    +-- (int, int)          -> na funkciju koja prima dva int parametra
    |
    +-- int                 -> ta funkcija vraća int
```

Dakle:

```cpp
int (*ptrOperation)(int, int);
```

čitamo kao:

```text
ptrOperation je pokazivač na funkciju 
koja prima dva int parametra 
i vraća vrijednost tipa int
```

Tipovi parametara moraju odgovarati funkciji na koju pokazivač pokazuje. Njihova imena nisu dio ovog zapisa:

```cpp
int (*ptrOperation)(int, int);
```

nije potrebno pisati kao:

```cpp
int (*ptrOperation)(int firstValue, int secondValue);
```

Inicijalizator:

```cpp
{add}
```

postavlja `ptrOperation` tako da pokazuje na funkciju `add()`.

Odnos možemo pojednostavljeno prikazati ovako:

```text
ptrOperation
+------------------+
| adresa funkcije  |
+--------+---------+
         ↓
      add()
+--------------------------+
| int add(int, int)        |
| vraća int                |
+--------------------------+
```

Cijelu definiciju:

```cpp
int (*ptrOperation)(int, int){add};
```

zato možemo čitati kao:

`ptrOperation` je pokazivač na funkciju koja prima dva parametra tipa `int` i vraća `int`, a početno (inicijalno) pokazuje na funkciju `add()`.

Funkciju možemo pozvati preko pokazivača:

```cpp
cout << ptrOperation(8, 3) << '\n';
```

Budući da `ptrOperation` sada pokazuje na `add()`, rezultat je:

```text
11
```

Pokazivaču zatim možemo dodijeliti drugu funkciju istog tipa:

```cpp
ptrOperation = subtract;
```

Sada odnos izgleda ovako:

```text
ptrOperation
+------------------+
| adresa funkcije  |
+--------+---------+
         ↓
    subtract()
+--------------------------+
| int subtract(int, int)   |
| vraća int                |
+--------------------------+
```

Ponovni poziv:

```cpp
cout << ptrOperation(8, 3) << '\n';
```

sada poziva `subtract()` i daje rezultat:

```text
5
```

Naziv funkcije `add` dovoljan je za inicijalizaciju pokazivača:

```cpp
int (*ptrOperation)(int, int){add};
```

Može se napisati i:

```cpp
int (*ptrOperation)(int, int){&add};
```

Oba zapisa ovdje daju pokazivač na istu funkciju.

### 9.1. Terminologija zapisa pokazivača na funkcije

Kod pokazivača na funkcije korisno je razlikovati nekoliko povezanih izraza:

* **Definicija pokazivača na funkciju**

  ```cpp
  int (*ptrOperation)(int, int){add};
  ```

  Ovim zapisom definiramo varijablu `ptrOperation`, koja je pokazivač na funkciju i početno pokazuje na `add()`.

* **Tip pokazivača na funkciju**

  ```cpp
  int (*)(int, int)
  ```

  To je tip pokazivača koji može pokazivati na funkciju koja prima dva parametra tipa `int` i vraća `int`.
  Imenovani pokazivač `*ptrOperation` piše se unutar zagrada kako bi deklaracija imala značenje pokazivača na funkciju. Bez tih zagrada zapis bi opisivao potpuno drugačiji slučaj: funkciju koja prima dva `int` parametra i vraća `int*`:
  ```cpp
  int* ptrOperation(int, int);
  ```

* **Tip funkcije**

  ```cpp
  int(int, int)
  ```

  To je tip same funkcije: funkcija prima dva parametra tipa `int` i vraća `int`.

---

## 10. Pokazivač na funkciju kao parametar druge funkcije

Pokazivač na funkciju možemo proslijediti drugoj funkciji kao parametar:

```cpp
int calculate(int firstValue,
              int secondValue,
              int (*ptrOperation)(int, int))
{
    return ptrOperation(firstValue, secondValue);
}
```

Funkcija `calculate()` prima tri parametra:

```text
firstValue     -> prva ulazna vrijednost
secondValue    -> druga ulazna vrijednost
ptrOperation   -> pokazivač na funkciju koju treba pozvati
```

Treći parametar `ptrOperation` također je **ulazni parametar**. Preko njega funkcija `calculate()` dobiva informaciju koju operaciju treba izvršiti.

Unutar funkcije:

```cpp
ptrOperation(firstValue, secondValue)
```

poziva se funkcija na koju `ptrOperation` pokazuje, a njezin rezultat zatim se vraća pomoću `return`:

```cpp
return ptrOperation(firstValue, secondValue);
```

Funkciju `calculate()` možemo zato pozvati s različitim funkcijama:

```cpp
int additionResult{calculate(10, 4, add)};
int subtractionResult{calculate(10, 4, subtract)};
```

Kod prvog poziva:

```text
calculate(10, 4, add)
          ↓
   ptrOperation
          ↓
        add()
          ↓
          14
```

Parametar `ptrOperation` pokazuje na `add()`, pa se unutar `calculate()` zapravo izvršava:

```cpp
add(10, 4)
```

Kod drugog poziva:

```text
calculate(10, 4, subtract)
          ↓
   ptrOperation
          ↓
      subtract()
          ↓
          6
```

Parametar `ptrOperation` sada pokazuje na `subtract()`, pa se izvršava:

```cpp
subtract(10, 4)
```

Funkcija `calculate()` tako ne mora unaprijed znati koju će konkretnu operaciju izvršiti. Potrebnu funkciju dobiva preko pokazivača kao argument prilikom poziva.

Važno je da funkcija proslijeđena preko pokazivača odgovara tipu pokazivača:

```cpp
int (*ptrOperation)(int, int)
```

U ovom slučaju mora primati dva parametra tipa `int` i vraćati vrijednost tipa `int`.

### 10.1. Kraći zapis tipa pokazivača na funkciju

Puni zapis tipa pokazivača na funkciju:

```cpp
int (*)(int, int)
```

možemo zapisati preglednije pomoću već poznatog `using`:

```cpp
using Operation = int (*)(int, int);
```

Tada funkciju `calculate()` možemo deklarirati ovako:

```cpp
int calculate(int firstValue,
              int secondValue,
              Operation ptrOperation);
```

Umjesto:

```cpp
int calculate(int firstValue,
              int secondValue,
              int (*ptrOperation)(int, int));
```

Isto vrijedi i za običnu pokazivačku varijablu. Umjesto:

```cpp
int (*ptrOperation)(int, int){add};
```

možemo napisati:

```cpp
Operation ptrOperation{add};
```

Oba zapisa predstavljaju isti tip pokazivača na funkciju. `using` ovdje samo čini složeniji zapis kraćim i preglednijim.

---

## 11. GDB demonstracija

Tema pokazivača i funkcija prikladna je za upoznavanje s GDB naredbama koje omogućuju pregled funkcija, argumenata, lokalnih varijabli i međusobnih poziva funkcija.

Za demonstraciju koristimo `01_pointer_parameters.cpp`, a posebno funkciju:

```cpp
void change_original(int* ptrValue)
{
    if (ptrValue == nullptr)
    {
        return;
    }

    *ptrValue = 20;
}
```

### 11.1. Function call stack i stack frame

Svaki aktivni poziv funkcije u GDB-u predstavljen je vlastitim **stack frameom**. Stack frame sadrži podatke povezane s određenim pozivom funkcije, između ostaloga njezine argumente i lokalne varijable.

Ako je izvođenje programa zaustavljeno unutar `change_original()`, stog poziva funkcija (**function call stack** ili skraćeno **call stack**) možemo pojednostavljeno prikazati ovako:

```text
CALL STACK

#0  change_original()              <- aktivna funkcija
      ↑
#1  demonstrate_pointer_parameter()
      ↑
#2  main()
```

Frame `#0` predstavlja funkciju u kojoj je izvođenje zaustavljeno. Frame `#1` predstavlja funkciju koja ju je pozvala, a `#2` funkciju koja je pozvala frame `#1`.

Kada se funkcija završi, njezin stack frame nestaje i izvođenje se nastavlja u prethodnom frameu.

### 11.2. Korisne GDB naredbe za rad s funkcijama

#### `info functions`

Naredba:

```text
(gdb) info functions
```

prikazuje funkcije koje su poznate GDB-u zajedno s njihovim tipovima. Međutim, može prikazati i dodatne funkcije povezane s runtimeom, standardnom bibliotekom, MinGW-om i drugim dijelovima izvršne datoteke. Zato je često praktičnije koristiti naredbu:

```text
(gdb) info functions -n
```

Opcija `-n` iz rezultata izostavlja funkcijske simbole koji ne dolaze iz debug informacija. Budući da naš program kompajliramo s opcijom `-g`, GDB za funkcije iz izvornog koda ima takve debug informacije.

U našem primjeru time dobivamo znatno pregledniju listu funkcija definiranih u `01_pointer_parameters.cpp`.

Lista se može dodatno ograničiti navođenjem dijela naziva funkcije:

```text
(gdb) info functions demonstrate_
```

ili:

```text
(gdb) info functions change_
```

To je praktično kada želimo pronaći naziv funkcije prije postavljanja breakpointa.

#### `info args`

Naredba:

```text
(gdb) info args
```

prikazuje argumente odabranog stack framea.

Ako smo zaustavljeni u:

```cpp
void change_original(int* ptrValue)
```

možemo očekivati prikaz parametra `ptrValue` i adrese koju je funkcija primila.

To možemo dodatno provjeriti naredbama:

```text
(gdb) p ptrValue
(gdb) p *ptrValue
```

Prva naredba prikazuje adresu spremljenu u pokazivaču, a druga vrijednost na toj adresi.

#### `info locals`

Naredba:

```text
(gdb) info locals
```

prikazuje lokalne varijable odabranog stack framea.

Primjerice, funkcija:

```cpp
void demonstrate_pointer_parameter()
{
    int value{10};

    change_original(&value);
}
```

ima lokalnu varijablu `value`.

Ako je odabran frame te funkcije:

```text
(gdb) info locals
```

omogućuje nam da pregledamo njezine lokalne varijable.

#### `backtrace`

Naredba:

```text
(gdb) backtrace
```

ili kraće:

```text
(gdb) bt
```

prikazuje stog poziva funkcija (**function call stack**).

U našem primjeru očekujemo odnos:

```text
#0  change_original()
#1  demonstrate_pointer_parameter()
#2  main()
```

Logički:

```text
#0  change_original()              <- funkcija u kojoj je izvođenje zaustavljeno
        ↑
#1  demonstrate_pointer_parameter()
        ↑
#2  main()
```

`backtrace` je posebno koristan kada se program zaustavi duboko unutar više međusobno pozvanih funkcija i želimo saznati kojim je redoslijedom program došao do konkretne funkcije.

#### `frame`

Naredba:

```text
(gdb) frame
```

prikazuje podatke o odabranom frameu.

Možemo izravno odabrati određeni frame:

```text
(gdb) frame 1
```

ili:

```text
(gdb) frame 2
```

Ako imamo:

```text
#2  main()
#1  demonstrate_pointer_parameter()
#0  change_original()
```

onda:

```text
(gdb) frame 1
```

odabire `demonstrate_pointer_parameter()`.

Važno je razlikovati **aktivnu funkciju u kojoj je izvođenje zaustavljeno** od **odabranog framea u GDB-u**. Promjenom odabranog framea ne nastavljamo izvođenje programa, nego samo mijenjamo funkcijski kontekst koji pregledavamo.

#### `up`

Naredba:

```text
(gdb) up
```

pomiče odabrani frame za jednu razinu prema funkciji pozivatelja, odnosno prema većem broju framea.

Ako `backtrace` prikazuje:

```text
#0  change_original()
#1  demonstrate_pointer_parameter()
#2  main()
```

i odabran je frame `#0`, nakon:

```text
(gdb) up
```

odabran postaje frame `#1`:

```text
#0  change_original()
#1  demonstrate_pointer_parameter()  <- odabran frame
#2  main()
```

Još jedan `up` odabrao bi frame `#2`, odnosno `main()`.

Možemo navesti i broj frameova za pomak:

```text
(gdb) up 2
```

što od odabranog framea `#0` prelazi izravno na frame `#2`.

#### `down`

Naredba:

```text
(gdb) down
```

pomiče odabrani frame za jednu razinu prema pozvanoj funkciji, odnosno prema manjem broju framea.

Ako je odabran frame `#2`:

```text
#0  change_original()
#1  demonstrate_pointer_parameter()
#2  main()                           <- odabran frame
```

nakon:

```text
(gdb) down
```

odabran postaje frame `#1`:

```text
#0  change_original()
#1  demonstrate_pointer_parameter()  <- odabran frame
#2  main()
```

Još jedan `down` odabrao bi frame `#0`, odnosno `change_original()`.

I ovdje možemo navesti broj frameova za pomak:

```text
(gdb) down 2
```

Odnos naredbi možemo zapamtiti ovako:

```text
veći broj framea
        ↑
       up
        |
#2  main()
#1  demonstrate_pointer_parameter()
#0  change_original()
        |
      down
        ↓
manji broj framea
```

`up` i `down` mijenjaju samo odabrani frame koji pregledavamo u GDB-u. Ne nastavljaju izvođenje programa.


### 11.3. Sažeti pregled naredbi

| Naredba                | Namjena                                      |
| ---------------------- | -------------------------------------------- |
| `info functions`       | prikazuje funkcije poznate GDB-u             |
| `info functions naziv` | traži funkcije prema dijelu naziva           |
| `info functions -n`    | prikazuje funkcije dostupne kroz debug informacije |
| `info args`            | prikazuje argumente odabranog framea         |
| `info locals`          | prikazuje lokalne varijable odabranog framea |
| `backtrace` / `bt`     | prikazuje stog poziva funkcija               |
| `frame`                | prikazuje odabrani frame                     |
| `frame n`              | odabire frame s brojem `n`                   |
| `up`                   | prelazi prema funkciji pozivatelja           |
| `down`                 | prelazi prema pozvanoj funkciji              |

### 11.4. GDB demonstracije s funkcijom `change_original()`

```text
E:\Files\G++\OOP\03-pokazivaci\03-03-pokazivaci-i-funkcije>gdb -silent 01_pointer_parameters.exe
Reading symbols from 01_pointer_parameters.exe...
(gdb) info functions -n
All defined functions:

File 01_pointer_parameters.cpp:
10:     void change_copy(int);
18:     void change_original(int*);
57:     void demonstrate_pointer_parameter();
69:     void demonstrate_pointer_return();
45:     void demonstrate_value_parameter();
30:     int *find_larger(int*, int*);
83:     int main();
(gdb) break change_original
Breakpoint 1 at 0x140001761: file 01_pointer_parameters.cpp, line 20.
(gdb) run > NUL
Starting program: E:\Files\G++\OOP\03-pokazivaci\03-03-pokazivaci-i-funkcije\01_pointer_parameters.exe > NUL
[New Thread 9004.0x1d30]
[New Thread 9004.0x2e8]
[New Thread 9004.0x148c]

Thread 1 hit Breakpoint 1, change_original (ptrValue=0x5ffe0c) at 01_pointer_parameters.cpp:20
20          if (ptrValue == nullptr)
(gdb) info args
ptrValue = 0x5ffe0c
(gdb) p ptrValue
$1 = (int *) 0x5ffe0c
(gdb) p *ptrValue
$2 = 10
(gdb) bt
#0  change_original (ptrValue=0x5ffe0c) at 01_pointer_parameters.cpp:20
#1  0x00007ff70fde1880 in demonstrate_pointer_parameter () at 01_pointer_parameters.cpp:62
#2  0x00007ff70fde1948 in main () at 01_pointer_parameters.cpp:86
(gdb) up
#1  0x00007ff70fde1880 in demonstrate_pointer_parameter () at 01_pointer_parameters.cpp:62
62          change_original(&value);
(gdb) info locals
value = 10
(gdb) p value
$3 = 10
(gdb) p &value
$4 = (int *) 0x5ffe0c
(gdb) down
#0  change_original (ptrValue=0x5ffe0c) at 01_pointer_parameters.cpp:20
20          if (ptrValue == nullptr)
(gdb) n
[New Thread 9004.0x1024]
25          *ptrValue = 20;
(gdb) n
26      }
(gdb) up
#1  0x00007ff70fde1880 in demonstrate_pointer_parameter () at 01_pointer_parameters.cpp:62
62          change_original(&value);
(gdb) p value
$5 = 20
(gdb) q
```

Demonstracija potvrđuje da `ptrValue` sadrži adresu varijable `value` iz funkcije pozivatelja te da promjena preko `*ptrValue` mijenja upravo tu varijablu.

---

## 12. Sažetak

### 1. Prosljeđivanje po vrijednosti

Kod prosljeđivanja po vrijednosti funkcija dobiva kopiju vrijednosti argumenta:

```cpp
void change_copy(int value);
```

Promjena tog parametra ne mijenja varijablu pozivatelja.

### 2. Pokazivač kao parametar funkcije

Pokazivač kao parametar prima kopiju vrijednosti pokazivača, odnosno kopiju adrese:

```cpp
void change_original(int* ptrValue);
```

Dereferenciranjem te adrese funkcija može pristupiti i promijeniti varijablu pozivatelja:

```cpp
*ptrValue = 20;
```

Ako pokazivač može biti `nullptr`, prije dereferenciranja treba ga provjeriti.

### 3. Pokazivač kao povratna vrijednost funkcije

Pokazivač može biti i povratna vrijednost funkcije:

```cpp
int* find_larger(int* ptrFirst, int* ptrSecond);
```

Funkcija može vratiti jedan od pokazivača koje je primila, a pozivatelj zatim preko vraćenog pokazivača pristupa podatku na odgovarajućoj adresi.

### 4. Polje kao parametar funkcije

Polje proslijeđeno funkciji preko parametra zapisanog kao:

```cpp
int values[]
```

u parametarskoj listi znači isto što i:

```cpp
int* values
```

Ne stvara se kopija cijelog polja. Funkcija preko pokazivača pristupa elementima izvornog polja.

Budući da pokazivač ne sadrži informaciju o broju elemenata, broj elemenata funkciji prosljeđujemo zasebno.

### 5. Struktura u funkcijama

Strukturu možemo:

* proslijediti po vrijednosti
* mijenjati preko pokazivača
* vratiti iz funkcije po vrijednosti

Kod prosljeđivanja strukture po vrijednosti funkcija dobiva kopiju strukture:

```cpp
void change_floor_copy(ElevatorState objState, int newFloor);
```

Promjene napravljene nad `objState` ne mijenjaju strukturu pozivatelja.

Kod prosljeđivanja pokazivača na strukturu, funkcija može pristupiti i promijeniti strukturu pozivatelja:

```cpp
void change_floor(ElevatorState* ptrState, int newFloor);
```

Struktura se može koristiti i kao povratni tip:

```cpp
ElevatorState create_initial_state();
```

### 6. Više rezultata iz funkcije

Više rezultata možemo zapisati u varijable pozivatelja pomoću izlaznih pokazivačkih parametara:

```cpp
void calculate(
    int firstValue,
    int secondValue,
    int* ptrSum,             // Izlazni parametar
    int* ptrDifference);     // Izlazni parametar
```

Ako rezultati predstavljaju jednu logičku cjelinu, struktura kao povratni tip često daje pregledniji potpis funkcije:

```cpp
CalculationResult calculate_result(int firstValue, int secondValue);
```

### 7. Pokazivači na funkcije

Pokazivač na funkciju s povratnim tipom `int` i dva parametra tipa `int` zapisujemo:

```cpp
int (*ptrOperation)(int, int);
```

Takav pokazivač može pokazivati na bilo koju kompatibilnu funkciju:

```cpp
ptrOperation = add;
ptrOperation = subtract;
```

Pokazivač na funkciju možemo proslijediti i drugoj funkciji, čime funkcija može dobiti operaciju koju treba pozvati kao argument.

Kraći zapis istog tipa možemo napraviti pomoću već poznatog aliasa:

```cpp
using Operation = int (*)(int, int);
```
---