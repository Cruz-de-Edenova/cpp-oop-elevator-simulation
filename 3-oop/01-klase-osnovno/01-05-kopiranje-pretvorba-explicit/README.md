# 01-05 Konstruktor kopije, pretvorbeni konstruktor i `explicit`

Ova tema obrađuje kopiranje objekata te konstruktore koji mogu sudjelovati u pretvorbi drugih tipova u objekte klase. Primjeri su razdvojeni u pet malih programa. Posebna pažnja posvećena je razlici između kopiranja član po član, plitkog i dubokog kopiranja te razlici između konstruktora kopije i inicijalizacije kopiranjem.

## Ključni pojmovi

- konstruktor kopije (*copy constructor*)
- kopiranje član po član (*member-wise copy*)
- plitko kopiranje (*shallow copy*)
- duboko kopiranje (*deep copy*)
- pretvorbeni konstruktor (*converting constructor*)
- inicijalizacija kopiranjem (*copy-initialization*)
- izravna inicijalizacija listom (*direct-list-initialization*)
- implicitna pretvorba argumenta (*implicit conversion*)
- specifikator `explicit` (*explicit specifier*)
- eksplicitni konstruktor (*explicit constructor*)

---

## Sadržaj

1. Kopiranje član po član
2. Plitko kopiranje
3. Duboko kopiranje
4. Pretvorbeni konstruktor i inicijalizacija kopiranjem
   - 4.1. Pretvorbeni konstruktor
   - 4.2. Izravna inicijalizacija listom vs. inicijalizacija kopiranjem
   - 4.3. Konstruktor kopije vs. inicijalizacija kopiranjem
   - 4.4. Implicitna pretvorba argumenta
5. Specifikator `explicit`

**Prateći primjeri**

- `1_memberwise_copy.cpp` — kopiranje objekta čiji su članovi obične vrijednosti
- `2_shallow_copy.cpp` — posljedica kopiranja pokazivačkog člana
- `3_deep_copy.cpp` — korisnički deklariran konstruktor kopije za duboko kopiranje
- `4_converting_constructor.cpp` — pretvorbeni konstruktor, inicijalizacija kopiranjem i implicitna pretvorba argumenta
- `5_explicit_constructor.cpp` — sprječavanje neželjenih implicitnih pretvorbi pomoću `explicit`

---

## 1. Kopiranje član po član

Datoteka: `1_memberwise_copy.cpp`

Kada novi objekt inicijaliziramo postojećim objektom istog tipa, poziva se konstruktor kopije (*copy constructor*). U primjeru se to događa pri stvaranju objekta `objCopy`:

```cpp
SensorReading objOriginal{2, 750, true};
SensorReading objCopy{objOriginal};
```

Klasa `SensorReading` nema korisnički deklariran konstruktor kopije (ima obični korisnički konstruktor s parametrima). Kompajler ga zato implicitno deklarira, a kada se koristi za stvaranje objekta `objCopy`, implicitno ga i definira.

U ovom primjeru implicitno definirani konstruktor kopije kopira nestatičke podatkovne članove objekta **član po član** (*member-wise copy*). Klasa sadrži tri obična podatkovna člana:
```cpp
int mChannel;
int mRawValue;
bool mValid;
```

Stvaranje originala i njegove kopije nalazi se u `cpp: 57-58`. Nakon kopiranja oba objekta imaju jednake vrijednosti, što se vidi u ispisu programa.

Zatim se mijenja samo ADC vrijednost kopije (`cpp: 66`). Original zadržava vrijednost `750`, dok kopija dobiva vrijednost `900`. Svaki objekt ima vlastite vrijednosti svojih podatkovnih članova pa je kopiranje član po član u ovom slučaju odgovarajuće.

Važno je znati da **kopiranje član po član nije sinonim za plitko kopiranje**. To će postati vidljivo u sljedećem primjeru, kada podatkovni član više nije fundamentalnog tipa poput `int` ili `bool`, nego je pokazivač.

---

## 2. Plitko kopiranje

Datoteka: `2_shallow_copy.cpp`

Klasa `ShallowCopy` sadrži pokazivač `mPtrValue` koji pokazuje na dinamički alocirani `int`. Konstruktor alocira taj podatak i njegovu adresu sprema u pokazivački član.

U `cpp: 64-65` objekt `objCopy` stvara se kopiranjem objekta `objOriginal`. Klasa `ShallowCopy` nema korisnički deklariran konstruktor kopije, pa se koristi konstruktor kopije koji osigurava kompajler. On obavlja kopiranje član po član (*member-wise copy*). Budući da klasa `ShallowCopy` ima samo jedan podatkovni član, u ovom se primjeru kopira vrijednost pokazivača `mPtrValue`, odnosno adresa.
```text
objOriginal.mPtrValue ─┐
                       ├──> int{10}
objCopy.mPtrValue ─────┘
```

Takav rezultat u ovom primjeru predstavlja **plitko kopiranje** (*shallow copy*).

Nakon naredbe u `cpp: 73` vrijednost se mijenja preko objekta `objCopy`. Ispis u `cpp: 75-79` pokazuje vrijednost `20` kroz oba objekta jer oba pokazivača upućuju na isti `int`.

Zbog zajedničke adrese memorija se u ovom demonstracijskom primjeru oslobađa samo jednom (`cpp: 82`). Nakon toga pokazivač u `objCopy` ostaje viseći pokazivač i više se ne koristi.

Ručni `cleanup()` ovdje služi samo za demonstraciju problema. Oslobađanje dinamički alociranog podatka pomoću destruktora obrađuje se u sljedećoj temi.

---

## 3. Duboko kopiranje

Datoteka: `3_deep_copy.cpp`

Ako kopija treba imati zaseban dinamički alocirani podatak, samo kopiranje vrijednosti pokazivača nije dovoljno. Klasa `DeepCopy` zato deklarira vlastiti konstruktor kopije:
```cpp
DeepCopy(const DeepCopy& refSource);
```

Klasa ima dva konstruktora s različitim ulogama:
```cpp
DeepCopy(int value);
DeepCopy(const DeepCopy& refSource);
```

`DeepCopy(int)` stvara početni objekt iz vrijednosti tipa `int`, dok `DeepCopy(const DeepCopy&)` stvara novi objekt kopiranjem postojećeg objekta `DeepCopy`.

Konstruktor kopije u `cpp: 40-43` alocira novi `int`:
```cpp
DeepCopy::DeepCopy(const DeepCopy& refSource)
    : mPtrValue{new int{*(refSource.mPtrValue)}}
{
}
```

Izraz `*(refSource.mPtrValue)` čita se ovim redoslijedom:
```text
refSource              -> izvorni objekt DeepCopy
refSource.mPtrValue    -> pokazivač spremljen u izvornom objektu
*(refSource.mPtrValue) -> vrijednost na koju taj pokazivač pokazuje 
```

Izraz `*refSource.mPtrValue` dereferencira pokazivač izvornog objekta i dohvaća vrijednost na koju on pokazuje. `new int{...}` zatim alocira novi `int` inicijaliziran tom vrijednošću.

Zato nakon stvaranja kopije u `cpp: 74-75` oba objekta imaju vrijednost `10`, ali njihovi pokazivački članovi sadrže različite adrese:

```text
objOriginal.mPtrValue ─────> int{10}
objCopy.mPtrValue ─────────> int{10}
```

To je **duboko kopiranje** (*deep copy*).

Kada se vrijednost kopije promijeni na `20`, original ostaje nepromijenjen (`cpp: 83-89`). Budući da svaki objekt pokazuje na zaseban dinamički alocirani podatak, oba se podatka na kraju mogu zasebno osloboditi (`cpp: 91-92`).

---

## 4. Pretvorbeni konstruktor i inicijalizacija kopiranjem

Datoteka: `4_converting_constructor.cpp`

Klasa `AdcReading` predstavlja zaseban korisnički definirani tip. Iako sadrži samo jedan član tipa `int`, objekt `AdcReading` nije isto što i vrijednost tipa `int`.

Mogućnost stvaranja objekta `AdcReading` iz vrijednosti tipa `int` daje konstruktor:
```cpp
AdcReading(int rawValue);
```

### 4.1. Pretvorbeni konstruktor

Konstruktor `AdcReading(int)` nije označen specifikatorom `explicit`, pa je u ovom primjeru **pretvorbeni konstruktor** (*converting constructor*). On omogućuje stvaranje objekta `AdcReading` iz vrijednosti tipa `int`, a u odgovarajućim kontekstima može sudjelovati i u implicitnoj pretvorbi `int -> AdcReading`.

Konstruktor `AdcReading(int)` nije konstruktor kopije. Tipičan konstruktor kopije klase `AdcReading` imao bi parametar istog tipa klase, primjerice:
```cpp
AdcReading(const AdcReading& refSource);
```

### 4.2. Izravna inicijalizacija listom vs. inicijalizacija kopiranjem

Primjer u `cpp: 52-53` uspoređuje dva načina stvaranja objekta:
```cpp
AdcReading objDirect{512};
AdcReading objCopyInitialized = 768;
```

Prvi redak koristi **izravnu inicijalizaciju listom** (*direct-list-initialization*). Iz vrijednosti `512` stvara se novi objekt `AdcReading` pozivom konstruktora `AdcReading(int)`. Na ovaj smo način i u dosadašnjim primjerima uobičajeno stvarali nove objekte.

Drugi redak koristi **inicijalizaciju kopiranjem** (*copy-initialization*). Vrijednost `768` tipa `int` služi za inicijalizaciju novog objekta `AdcReading`, pri čemu se također koristi `AdcReading(int)`.

Znak `=` u ovom slučaju ne predstavlja naknadno pridruživanje postojećem objektu. Objekt `objCopyInitialized` upravo se stvara i inicijalizira.

### 4.3. Konstruktor kopije vs. inicijalizacija kopiranjem

Nazivi su slični, ali označavaju različite pojmove.

Kod:
```cpp
AdcReading objCopy{objOriginal};
```
inicijalizira novi objekt postojećim objektom istog tipa, pa se poziva konstruktor kopije.

Nasuprot tome:
```cpp
AdcReading objCopyInitialized = 768;
```
predstavlja inicijalizaciju kopiranjem, ali se ne kopira postojeći objekt `AdcReading`. Iz vrijednosti `768` tipa `int` stvara se novi objekt pomoću pretvorbenog konstruktora `AdcReading(int)`.

Riječ *copy* u izrazu *copy-initialization* zato **ne znači da se nužno poziva konstruktor kopije**.

### 4.4. Implicitna pretvorba argumenta

Funkcija `print_reading()` prima objekt `AdcReading` po vrijednosti. U `cpp: 67` poziva se ovako:
```cpp
print_reading(900);
```

Argument `900` ima tip `int`, dok parametar funkcije ima tip `AdcReading`. Budući da `AdcReading(int)` nije označen s `explicit`, kompajler ga može koristiti za implicitnu pretvorbu argumenta.

Iz vrijednosti `900` tako se stvara objekt `AdcReading` potreban za inicijalizaciju parametra funkcije. Vrijednost `900` pritom se prosljeđuje kao argument konstruktoru `AdcReading(int)` i njome se inicijalizira njegov parametar `rawValue`.

Isti konstruktor zato u ovom programu sudjeluje u tri različita konteksta:
```text
AdcReading objDirect{512};
    -> izravna inicijalizacija listom

AdcReading objCopyInitialized = 768;
    -> inicijalizacija kopiranjem

print_reading(900);
    -> implicitna pretvorba argumenta
```

---

## 5. Specifikator `explicit`

Datoteka: `5_explicit_constructor.cpp`

Pretvorbeni konstruktor iz prethodnog primjera dopušta implicitnu pretvorbu `int -> AdcReading`. Takva pretvorba ponekad može biti korisna, ali također može dopustiti stvaranje objekta na mjestima gdje to nije bila namjera programera.

Specifikator `explicit` sprječava takvu automatsku uporabu konstruktora:
```cpp
explicit AdcReading(int rawValue);
```

Specifikator `explicit` navodi se u deklaraciji konstruktora unutar klase. Ne ponavlja se u definiciji izvan klase.

Izravna inicijalizacija listom i dalje je dopuštena:
```cpp
AdcReading objReading{512};
```

Taj slučaj nalazi se u `cpp: 52`.

Dopušteno je i izričito stvoriti objekt pri pozivu funkcije:
```cpp
print_reading(AdcReading{900});
```

U `cpp: 56` objekt tipa `AdcReading` izričito se stvara izrazom `AdcReading{900}`, pa nije potrebna implicitna pretvorba argumenta `int -> AdcReading`.

Izraz `AdcReading{900}` ne sprema se u zasebnu imenovanu varijablu, nego se odmah koristi kao argument poziva funkcije. Parametar `objReading` postoji tijekom izvođenja funkcije `print_reading()`. Životni vijek objekata detaljnije će se obraditi u sljedećoj temi.

Zakomentirane naredbe u `cpp: 59-60` ne prolaze kompajliranje:
```cpp
// AdcReading objCopyInitialized = 768;
// print_reading(900);
```

Prva zahtijeva da se konstruktor označen s `explicit` koristi pri inicijalizaciji kopiranjem, a druga zahtijeva implicitnu pretvorbu argumenta iz `int` u `AdcReading`. `explicit` sprječava oba slučaja.

Time konstruktor ostaje dostupan kada ga programer izričito odabere za stvaranje objekta, ali se ne koristi automatski za implicitne pretvorbe.
