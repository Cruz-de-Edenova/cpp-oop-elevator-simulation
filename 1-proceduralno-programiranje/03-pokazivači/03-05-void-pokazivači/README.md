# `void` pokazivači

U prethodnim temama tip pokazivača određivao je na što pokazivač može pokazivati. Primjerice, `int*` pokazuje na `int`, a `double*` na `double`.

U ovoj temi upoznajemo `void*`, odnosno pokazivač koji može sadržavati adresu objekta različitih tipova bez informacije o njegovu konkretnom tipu. Takav pokazivač daje veću općenitost, ali istodobno gubimo dio tipovne sigurnosti koju obični pokazivači pružaju.

Vidjet ćemo kako se `void*` pretvara natrag u pokazivač odgovarajućeg tipa, kako se uz njega koristi `const` te zašto funkcija koja prima `void*` mora na neki drugi način znati stvarni tip podatka.

## Sadržaj

1. Osnove `void*` pokazivača
2. `const` i `void*`
3. `void*` kao parametar funkcije
4. Ograničenja i praktična primjena
5. Sažetak

Prateći primjeri:

- `01_void_pointer_basics.cpp`
- `02_const_void_pointer.cpp`
- `03_void_pointer_parameter.cpp`

---

## 1. Osnove `void*` pokazivača

Obični pokazivač u svojem tipu sadrži informaciju o tipu podatka na koji pokazuje:
```cpp
int intValue{20};
int* ptrInt{&intValue};
```

Kod `void*` pokazivača ta informacija nije prisutna:
```cpp
int intValue{20};
void* ptrData{&intValue};
```

`ptrData` sadrži adresu varijable `intValue`, ali njegov tip ne govori da se na toj adresi nalazi `int`.
Pokazivač tipa `void*` zato možemo promatrati kao adresu objekta bez informacije o njegovu konkretnom tipu.

### 1.1. `void*` se ne može izravno dereferencirati

Kod običnog pokazivača:
```cpp
int* ptrInt{&intValue};

cout << *ptrInt << '\n';
```
kompajler iz tipa `int*` zna da dereferenciranjem treba pristupiti podatku tipa `int`.

Kod `void*` ta informacija nedostaje:
```cpp
void* ptrData{&intValue};
// cout << *ptrData;  // Pogreška: void* se ne može dereferencirati
```

Prije dereferenciranja pokazivač moramo pretvoriti natrag u pokazivač odgovarajućeg tipa:
```cpp
int* ptrInt{static_cast<int*>(ptrData)};
cout << *ptrInt << '\n';
```

Pretvorbu radimo pomoću `static_cast`:
```cpp
static_cast<int*>(ptrData)
```

Nakon pretvorbe ponovno imamo `int*`, pa kompajler zna kako pristupiti podatku na toj adresi.

### 1.2. Isti `void*` može sadržavati adrese različitih tipova

`void*` nije vezan uz jedan konkretan tip objekta:
```cpp
int intValue{20};
double doubleValue{7.5};
void* ptrData{&intValue};
```

Dok `ptrData` sadrži adresu `intValue`, vraćamo ga u `int*`:
```cpp
int* ptrInt{static_cast<int*>(ptrData)};
cout << "int vrijednost: " << *ptrInt << '\n';
```

Isti pokazivač zatim možemo preusmjeriti na `doubleValue`:
```cpp
ptrData = &doubleValue;
```

Sada ga moramo pretvoriti u `double*`:
```cpp
double* ptrDouble{static_cast<double*>(ptrData)};
cout << "double vrijednost: " << *ptrDouble << '\n';
```

Odnos možemo pojednostavljeno prikazati ovako:
```text
ptrData
   |
   +------> intValue
   |        tip: int
   |
   +------> doubleValue
            tip: double
```
Ovdje treba naglasiti da `ptrData` ne sadrži istodobno obje adrese, nego u različitim trenucima može sadržavati obje adrese, ali sam `void*` ne pamti kojem tipu podatka pripada adresa koju sadrži.
Zato programer mora znati u koji tip pokazivač treba pretvoriti prije dereferenciranja.

---

## 2. `const` i `void*`

Pravila za `const` koja smo upoznali u prethodnoj temi vrijede i uz `void*`.
Važno je razlikovati:
```cpp
const void* ptrData;           // pokazivač na const void
```
i:
```cpp
void* const ptrData{&value};   // const pokazivač na void
```

U prvom slučaju `const` se odnosi na podatak kojem pristupamo preko pokazivača, a u drugom na sam pokazivač.

### 2.1. Pokazivač na `const void`

Promotrimo:
```cpp
int value{30};
const void* ptrData{&value};
```
`ptrData` može sadržavati adresu varijable `value`, ali podatak preko njega ne smijemo mijenjati.

Prilikom pretvorbe natrag u konkretan tip moramo zadržati `const`:
```cpp
const int* ptrValue{static_cast<const int*>(ptrData)};
cout << *ptrValue << '\n';
```

Promjena preko dobivenog pokazivača nije dopuštena:
```cpp
// *ptrValue = 40;  // Pogreška: vrijednost se ne može mijenjati
```

Ne možemo ni pretvorbom jednostavno ukloniti `const`:
```cpp
// int* ptrOther{static_cast<int*>(ptrData)};  // Pogreška: uklanja const
```

Sama varijabla `value` u ovom primjeru nije `const`, pa je i dalje možemo promijeniti izravno:
```cpp
value = 40;
```
`ptrValue` će tada pri dereferenciranju vidjeti novu vrijednost.

Dakle, razlika između `void*` i `const void*` postaje jasna nakon pretvorbe natrag u konkretan tip:
```cpp
int value{30};

void* ptrData{&value};
int* ptrValue{static_cast<int*>(ptrData)};

*ptrValue = 40;  // Dopušteno
```

nasuprot:
```cpp
int value{30};

const void* ptrData{&value};
const int* ptrValue{static_cast<const int*>(ptrData)};

// *ptrValue = 40;  // Pogreška pri kompajliranju
```

`void*` skriva konkretan tip podatka, ali nakon ispravne pretvorbe u `int*` dopušta njegovu promjenu. `const void*` također skriva konkretan tip, ali preko njega ne dopušta promjenu podatka.

### 2.2. `const` pokazivač na `void`

Kod zapisa:
```cpp
int firstValue{50};
void* const ptrData{&firstValue};
```
`const` se odnosi na sam pokazivač.

Podatak se nakon pretvorbe u odgovarajući tip može mijenjati:
```cpp
int* ptrValue{static_cast<int*>(ptrData)};
*ptrValue = 70;
```

Međutim, `ptrData` se više ne može preusmjeriti na drugu adresu:
```cpp
// int secondValue{60};
// ptrData = &secondValue;  // Pogreška: const pokazivač se ne može preusmjeriti
```

---

## 3. `void*` kao parametar funkcije

`void*` se može koristiti kada funkcija treba primiti adresu podatka čiji konkretan tip nije određen samim tipom parametra.

U primjeru koristimo:
```cpp
enum class ValueType
{
    Integer,
    Double
};
```
i funkciju:
```cpp
void print_value(const void* ptrData, ValueType type)
{
    if (ptrData == nullptr)
    {
        return;
    }

    if (type == ValueType::Integer)
    {
        const int* ptrValue{static_cast<const int*>(ptrData)};
        cout << "int vrijednost: " << *ptrValue << '\n';
    }
    else if (type == ValueType::Double)
    {
        const double* ptrValue{static_cast<const double*>(ptrData)};
        cout << "double vrijednost: " << *ptrValue << '\n';
    }
}
```

Funkciju možemo pozvati s podacima različitih tipova:
```cpp
int intValue{20};
double doubleValue{7.5};

print_value(&intValue, ValueType::Integer);
print_value(&doubleValue, ValueType::Double);
```

Parametar:
```cpp
const void* ptrData
```
daje funkciji adresu podatka, ali ne i informaciju o njegovu konkretnom tipu.

Zato drugi parametar:
```cpp
ValueType type
```
govori funkciji kako treba protumačiti podatak na toj adresi.

Za prvi poziv:
```cpp
print_value(&intValue, ValueType::Integer);
```
funkcija dobiva dvije odvojene informacije:
```text
&intValue          -> gdje se podatak nalazi
ValueType::Integer -> kojeg je podatak tipa
```

Tek nakon toga može napraviti odgovarajuću pretvorbu:
```cpp
const int* ptrValue{static_cast<const int*>(ptrData)};
```

### 3.1. Odgovornost za stvarni tip podatka

`void*` sam ne provjerava odgovara li pretvorba stvarnom tipu objekta.

Primjerice, ako bismo pogrešno napisali:
```cpp
double doubleValue{7.5};
print_value(&doubleValue, ValueType::Integer);
```
funkcija bi prema vrijednosti `ValueType::Integer` adresu pretvorila u pokazivač na `int`.
Takva pretvorba može se uredno kompajlirati jer `static_cast` iz `const void*` u `const int*` ne provjerava stvarni tip objekta na toj adresi.

Problem nastaje pri dereferenciranju:
```cpp
const int* ptrValue{static_cast<const int*>(ptrData)};
cout << *ptrValue << '\n';
```
Objekt na toj adresi zapravo je tipa `double`, a pristupa mu se kao objektu tipa `int`. Takav pristup uzrokuje nedefinirano ponašanje.
Zato kod korištenja `void*` programer mora na drugi način sačuvati pouzdanu informaciju o stvarnom tipu podatka.

---

## 4. Ograničenja i praktična primjena

`void*` omogućuje rad s adresama objekata različitih tipova, ali cijena te općenitosti je gubitak informacije o konkretnom tipu.
Iz toga proizlazi nekoliko važnih ograničenja.

### 4.1. Kada se `void*` koristi?

`void*` ima smisla kada dio programa treba primiti, pohraniti ili proslijediti adresu nekog objekta, ali taj dio programa nije vezan uz jedan konkretan tip. Takav primjer je demonstriran u datoteci `03_void_pointer_parameter.cpp`.

Takav se pristup često susreće u niskorazinskim bibliotekama i C sučeljima koja moraju raditi s podacima različitih tipova.

Takva općenitost ima cijenu: `void*` sam ne sadrži informaciju o stvarnom tipu objekta. Ako podatku želimo pristupiti, tu informaciju moramo imati na neki drugi način i pokazivač pretvoriti natrag u odgovarajući tip.

U C++ kodu specifičan tip pokazivača pruža više informacija kompajleru i bolju tipovnu sigurnost, pa `void*` ne treba koristiti kada konkretan tip možemo izraziti izravno.

### 4.2. Nema izravnog dereferenciranja

Ovo nije dopušteno:
```cpp
// cout << *ptrData;
```
Prije dereferenciranja potrebno je dobiti pokazivač konkretnog tipa.

### 4.3. Nema standardne pokazivačke aritmetike nad `void*`

Kod pokazivača poput `int*` kompajler zna veličinu elementa i može izračunati sljedeću adresu:
```cpp
++ptrInt;
```

Kod `void*` nema informacije o veličini konkretnog tipa, pa standardni C++ ne dopušta takvu pokazivačku aritmetiku:
```cpp
// ++ptrData;  // Nije dopušteno u standardnom C++
```

---

## 5. Sažetak

### 1. Osnovno značenje `void*`

```cpp
void* ptrData{&value};
```
`void*` može sadržavati adresu objekta različitih tipova, ali sam ne nosi informaciju o konkretnom tipu podatka.
Zato se ne može izravno dereferencirati.

Prije pristupa podatku vraćamo ga u odgovarajući tip pokazivača:
```cpp
int* ptrValue{static_cast<int*>(ptrData)};
```

### 2. `const` i `void*`

Razliku možemo sažeti ovako:
| Deklaracija | Promjena podatka preko pokazivača | Preusmjeravanje pokazivača |
| --- | --- | --- |
| `void* ptrData` | dopuštena nakon odgovarajuće pretvorbe | dopušteno |
| `const void* ptrData` | nije dopuštena | dopušteno |
| `void* const ptrData` | dopuštena nakon odgovarajuće pretvorbe | nije dopušteno |

Kod `const void*` nakon pretvorbe moramo zadržati `const`:
```cpp
const int* ptrValue{static_cast<const int*>(ptrData)};
```

### 3. `void*` kao parametar funkcije

Funkcija:
```cpp
void print_value(const void* ptrData, ValueType type);
```
preko `ptrData` dobiva adresu, a preko `type` informaciju o stvarnom tipu podatka.
`void*` tu informaciju sam ne sadrži.

### 4. Tipovna sigurnost

Kod pretvorbe `void*` natrag u konkretan tip programer mora znati stvarni tip objekta.

Pogrešna informacija o tipu može dovesti do dereferenciranja pokazivača kao pogrešnog tipa i nedefiniranog ponašanja.

Zato `void*` daje općenitost, ali istodobno prenosi veći dio odgovornosti za tipovnu sigurnost na programera.

---
