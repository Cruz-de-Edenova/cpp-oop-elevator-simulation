# `const` članovi klase i `inline` funkcije

Ova tema obrađuje `const` članove klase i `inline` članske funkcije. Temeljna pravila za `const` već su obrađena u temi `1-proceduralno-programiranje/02-razno2/02-01-const`, pa se ovdje ne ponavljaju opća objašnjenja `const` varijabli i kvalifikatora tipa.

Fokus je na dijelovima koji tada još nisu bili potrebni: `const` podatkovnim članovima, `const` članskim funkcijama i pozivanju članskih funkcija nad `const` objektima. Uz to se uvodi `inline` kao C++ specifikator koji se često susreće kod kratkih članskih funkcija.

**Ključni pojmovi:**

- `inline` funkcija (*inline function*)
- `const` podatkovni član (*const data member*)
- `const` članska funkcija (*const-qualified member function*)
- `const` objekt (*const object*)

---

## Sadržaj

1. `inline` članske funkcije
  - 1.1. Značenje `inline` i optimizacija poziva funkcije
2. `const` podatkovni član
3. `const` članska funkcija i `const` objekt
4. Primjer 1 — `inline` članske funkcije
5. Primjer 2 — `const` članovi klase

**Prateći primjeri:**
- **Primjer 1:** `1_inline_member_function.cpp`
- **Primjer 2:** `2_const_members.cpp`

---

## 1. `inline` članske funkcije

Specifikator `inline` može se koristiti uz funkciju. Kod članskih funkcija posebno su važna dva načina zapisa.

Ako je cijela definicija članske funkcije napisana unutar definicije klase, funkcija je implicitno `inline`:
```cpp
class DownSolenoid
{
public:
    void energize()
    {
        // ...
    }
};
```

Drugi je način deklarirati funkciju unutar klase, a pri definiciji izvan klase eksplicitno navesti `inline`:
```cpp
class DownSolenoid
{
public:
    void deenergize();
};

inline void DownSolenoid::deenergize()
{
    // ...
}
```

Riječ `inline` ne predstavlja naredbu kojom se kompajler prisiljava da poziv funkcije zamijeni njezinim tijelom. **Kompajler sam odlučuje hoće li napraviti takvu optimizaciju**, neovisno o tome je li funkcija deklarirana kao `inline`.

Važno je i jezično značenje specifikatora `inline`: dopušta da se identična definicija funkcije s odgovarajućim povezivanjem pojavi u više jedinica kompajliranja. Zbog toga se `inline` funkcije mogu definirati u datoteci zaglavlja koju uključuje više `.cpp` datoteka.

U ovoj temi važnije je prepoznati oba načina definiranja `inline` članske funkcije i razumjeti da `inline` ne jamči optimizaciju poziva.

### 1.1. Značenje `inline` i optimizacija poziva funkcije

Izvorna ideja specifikatora `inline` povezana je s optimizacijom poziva funkcije.

Kod običnog poziva funkcije izvođenje mora prijeći iz koda pozivatelja u tijelo funkcije, proslijediti potrebne argumente i nakon završetka funkcije vratiti se na mjesto poziva. Takav poziv zato zahtijeva dodatne operacije povezane s pozivom i povratkom iz funkcije.

Ako kompajler napravi *inlining*, pojedini poziv funkcije može zamijeniti njezinim tijelom. Ako se takva zamjena napravi na više mjesta poziva, tijelo funkcije ugrađuje se na svako od tih mjesta. Time se mogu izbjeći dodatne operacije potrebne za sam poziv funkcije.

Međutim, specifikator `inline` **ne naređuje kompajleru da napravi tu optimizaciju**. Kompajler smije poziv `inline` funkcije ostaviti kao običan poziv, a smije i funkciju koja nije deklarirana kao `inline` samostalno ugraditi na mjesto poziva.

Zato treba razlikovati ova dva pojma:
- **inline funkcija**, jezično svojstvo funkcije u C++
- **inline substitution**, optimizacija koju kompajler može, ali ne mora napraviti

*Inlining* također nije uvijek povoljan. Ako se tijelo funkcije kopira na mnogo mjesta poziva, količina generiranog strojnog koda može porasti. U sustavima s ograničenom programskom memorijom to može biti jednako važno kao i brzina izvođenja.

Kod embedded programiranja zato nema smisla rutinski dodavati `inline` svim kratkim funkcijama samo radi očekivane brzine. *Inlining* može povećati strojni kod jer se tijelo funkcije u tom slučaju ugrađiva na više mjesta poziva. Ako se veća funkcija ugradi na mnogo mjesta, to može nepotrebno povećati zauzeće Flash memorije. Zato je u embedded sustavima to važan razlog za oprez. Modernom kompajleru u pravilu treba prepustiti odluku o stvarnom *inliningu* prema odabranim optimizacijama.

`inline` ipak ostaje koristan C++ mehanizam. Primjerice, članska funkcija definirana unutar definicije klase implicitno je `inline`, što omogućuje da se takva definicija nalazi u datoteci zaglavlja koju uključuje više jedinica kompajliranja.

---

## 2. `const` podatkovni član

Podatkovni član klase može biti označen s `const`:
```cpp
class AdcChannel
{
private:
    const int mChannel;
};
```
Takav član nakon inicijalizacije ne može dobiti novu vrijednost. U drugom primjeru broj ADC kanala određuje se pri stvaranju objekta i poslije ostaje nepromijenjen.

Budući da vrijednost člana `mChannel` dolazi iz argumenta konstruktora, član se inicijalizira u listi inicijalizatora članova:
```cpp
AdcChannel::AdcChannel(int channel, int rawValue)
    : mChannel{channel}, mRawValue{rawValue}
{
}
```
Do početka izvođenja tijela konstruktora članovi su već inicijalizirani. Naknadno pridruživanje nove vrijednosti članu `mChannel` nije dopušteno.

To je razlika između dva podatkovna člana iz primjera:
```text
mChannel    -> const, određuje se pri inicijalizaciji objekta
mRawValue   -> nije const, može se poslije mijenjati
```
Praktična korist je u tome što sama definicija klase izražava i provodi pravilo da identitet ADC kanala nakon konstrukcije ostaje nepromijenjen.

---

## 3. `const` članska funkcija i `const` objekt

Nestatička članska funkcija može biti `const`-kvalificirana. Kvalifikator `const` piše se iza parametarske liste:
```cpp
int get_channel() const;
```

Ako je funkcija definirana izvan klase, `const` mora biti naveden i u definiciji:
```cpp
int AdcChannel::get_channel() const
{
    return mChannel;
}
```
U `const` članskoj funkciji `this` pokazuje na `const` objekt, pa se obični podatkovni članovi tog objekta ne mogu mijenjati preko `this`:
```cpp
int AdcChannel::get_raw_value() const
{
    // mRawValue = 0; // Pogreška pri kompajliranju

    return mRawValue;
}
```
Iz istog razloga ne može izravno pozvati ne-`const` člansku funkciju nad istim objektom:
```cpp
int AdcChannel::get_raw_value() const
{
    // set_raw_value(0); // Pogreška pri kompajliranju

    return mRawValue;
}
```

`const` objekt definira se tako da se `const` navede uz njegov tip:
```cpp
const AdcChannel objReferenceChannel{7, 1023};
```
Od nestatičkih članskih funkcija takav objekt može pozivati `const` članske funkcije:
```cpp
objReferenceChannel.get_channel();
objReferenceChannel.get_raw_value();
```
Ne može pozvati ne-`const` člansku funkciju:
```cpp
// objReferenceChannel.set_raw_value(900); // Pogreška pri kompajliranju
```

Običan objekt nije tako ograničen. On može pozivati i `const` i ne-`const` članske funkcije.

Ovdje se jasno razlikuju OOP namjera, C++ mehanizam i praktična korist:
- **namjera**: funkcija samo čita stanje objekta
- **C++ mehanizam**: `const` kvalifikator iza parametarske liste članske funkcije
- **praktična korist**: javno sučelje jasno izražava koje operacije ne mijenjaju objekt, a kompajler provodi to ograničenje

---

## 4. Primjer 1 — `inline` članske funkcije

Datoteka: `1_inline_member_function.cpp`

| Novi koncept | Mjesto u kodu |
| --- | --- |
| definicija članske funkcije unutar klase | `cpp: 19-23` |
| deklaracija funkcije definirane izvan klase | `cpp: 26` |
| eksplicitni `inline` uz definiciju izvan klase | `cpp: 38-42` |
| pozivi obje članske funkcije | `cpp: 52-53` |

U `cpp: 19-23` funkcija `energize()` potpuno je definirana unutar definicije klase `DownSolenoid`. U C++17 takva je članska funkcija implicitno `inline`; ključnu riječ `inline` nije potrebno posebno napisati.

Funkcija `deenergize()` u `cpp: 26` unutar klase je samo deklarirana. Njezina definicija nalazi se u `cpp: 38-42`, gdje je prije povratnog tipa eksplicitno naveden specifikator `inline`.

Pozivi u `cpp: 52-53` izgledaju jednako za obje funkcije. Razlika je u načinu njihove definicije, a ne u sintaksi poziva preko objekta.

Primjer namjerno ne pokušava dokazivati je li kompajler stvarno ugradio tijelo funkcije na mjesto poziva. Specifikator `inline` takvu optimizaciju ne jamči.

---

## 5. Primjer 2 — `const` članovi klase

Datoteka: `2_const_members.cpp`

| Novi koncept | Mjesto u kodu |
| --- | --- |
| `const` podatkovni član | `cpp: 12` |
| deklaracije `const` članskih funkcija | `cpp: 20, 23` |
| inicijalizacija `const` podatkovnog člana | `cpp: 31-34` |
| definicije `const` članskih funkcija | `cpp: 38-41, 45-55` |
| pokušaj promjene `const` podatkovnog člana | `cpp: 62` |
| stvaranje `const` objekta | `cpp: 74` |
| nedopušten poziv ne-`const` funkcije preko `const` objekta | `cpp: 88` |

Član `mChannel` u `cpp: 12` označen je s `const`, dok je `mRawValue` običan podatkovni član. Konstruktor u `cpp: 31-34` inicijalizira oba člana, a `mChannel` nakon toga više ne može dobiti novu vrijednost.

Funkcije `get_channel()` i `get_raw_value()` deklarirane su kao `const` u `cpp: 20, 23`, a isti se kvalifikator ponavlja u njihovim definicijama u `cpp: 38-41, 45-55`.

Unutar `get_raw_value()` zakomentirana su dva nedopuštena slučaja. `const` članska funkcija ne može mijenjati obični podatkovni član `mRawValue`, niti može pozvati ne-`const` funkciju `set_raw_value()` nad istim objektom.

Funkcija `set_raw_value()` nije `const`, pa smije promijeniti obični član `mRawValue`. Međutim, zakomentirani pokušaj u `cpp: 62` pokazuje da ni takva funkcija ne smije naknadno mijenjati `const` član `mChannel`.

U `cpp: 73-74` stvaraju se običan i `const` objekt. Običan `objChannel` može pozvati `set_raw_value()`, dok `objReferenceChannel` može koristiti funkcije za čitanje jer su one `const`-kvalificirane. Zakomentirani poziv u `cpp: 88` pokazuje da `const` objekt ne može pozvati ne-`const` člansku funkciju `set_raw_value()`.
