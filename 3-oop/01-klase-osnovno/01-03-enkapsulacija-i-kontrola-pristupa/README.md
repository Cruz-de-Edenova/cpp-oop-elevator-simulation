# Enkapsulacija i kontrola pristupa

Ova tema objašnjava zašto kontrola pristupa postoji i kako njome oblikujemo granicu između javnog sučelja klase i njezine privatne implementacije. Time dolazimo do jednog od temeljnih OOP koncepata: **enkapsulacije**.

Prvi primjer koristi klasu `ControlButton` kako bi pokazao da i podatkovni članovi i članske funkcije mogu biti privatni. Drugi primjer koristi visinu hidraulične platforme Autoquip Titan kako bi pokazao da klasa može kontrolirati promjenu vlastitog stanja i odbiti nedopuštenu vrijednost.

## Sadržaj

1. Enkapsulacija
2. Kontrola pristupa članovima klase
3. Javno sučelje i privatna implementacija
4. Privatni podatkovni članovi i privatne članske funkcije
5. Kontrolirana promjena stanja objekta
6. Sažetak

**Prateći primjeri:**
- `01_access_control.cpp`
- `02_encapsulation.cpp`

---

## 1. Enkapsulacija

U prethodnim temama već smo napravili prvi korak prema enkapsulaciji: podatke i funkcije koje nad njima rade smjestili smo u istu klasu.

Primjer:
```cpp
class ControlButton
{
private:
    bool mPressed;

public:
    void press();
    void release();
    bool is_pressed();
};
```
Objekt klase `ControlButton` sadrži vlastito stanje:
```cpp
bool mPressed;
```
i ponašanja povezana s tim stanjem:
```cpp
void press();
void release();
bool is_pressed();
```
**Enkapsulacija** (*encapsulation*) povezuje stanje objekta i ponašanja koja nad tim stanjem djeluju u jednu programsku cjelinu te omogućuje da klasa kontrolira način pristupa svojoj unutarnjoj implementaciji.

Važno je razlikovati OOP koncept od C++ mehanizma:
```text
OOP koncept:
    enkapsulacija
        |
        +-- stanje i ponašanje promatramo kao jednu cjelinu
        +-- objekt kontrolira način korištenja svojeg stanja

C++ mehanizmi:
    class
    podatkovni članovi
    članske funkcije
    private / public
```
Sama ključna riječ `private` nije enkapsulacija. Ona je jedan od C++ mehanizama kojima možemo podržati enkapsulirani dizajn klase.

S enkapsulacijom je usko povezano i **skrivanje informacija** (*information hiding*). Vanjski kod ne mora poznavati nepotrebne detalje o tome kako klasa interno sprema ili obrađuje svoje stanje. Korisnik klase treba poznavati način njezina korištenja, a ne svaki detalj implementacije.

---

## 2. Kontrola pristupa članovima klase

C++ koristi specifikatore pristupa:
```cpp
private:
public:
protected:
```
Njima određujemo iz kojih se dijelova programa pojedinom članu klase smije pristupiti. U ovoj temi koristimo `private` i `public`. Specifikator `protected` prvenstveno je važan kod **nasljeđivanja**, pa će njegovo značenje detaljnije biti obrađeno u kasnijim temama.

Specifikator vrijedi za članove koji se nalaze iza njega, sve do sljedećeg specifikatora pristupa ili kraja definicije klase:
```cpp
class ControlButton
{
private:
    bool mPressed;
    void set_pressed(bool pressed);

public:
    void press();
    void release();
    bool is_pressed();
};
```

Članske funkcije klase `ControlButton` smiju pristupati njezinim privatnim članovima:
```cpp
void ControlButton::set_pressed(bool pressed)
{
    mPressed = pressed;
}
```
Javna funkcija `press()` također može pozvati privatnu člansku funkciju:
```cpp
void ControlButton::press()
{
    set_pressed(true);
}
```
Programski kod izvan klase ne može izravno koristiti privatni podatkovni član:
```cpp
// objUpButton.mPressed = true; // Pogreška pri kompajliranju
```
niti može pozvati privatnu člansku funkciju:
```cpp
// objUpButton.set_pressed(true); // Pogreška pri kompajliranju
```
Takav pristup ne prolazi provjeru pristupa pri kompajliranju.

Za sada privatnim članovima pristupamo iz članskih funkcija iste klase. C++ ima i mehanizam `friend` kojim se pristup može posebno dopustiti drugim funkcijama ili klasama, ali on će biti objašnjen u kasnijim temama.

Kod klase definirane ključnom riječi `class` zadani pristup je `private`. U ovom projektu ipak pišemo `private:` eksplicitno kako bi organizacija klase bila jasnija.

---

## 3. Javno sučelje i privatna implementacija

Članovi koje korisnik klase smije koristiti čine njezino **javno sučelje** (*public interface*).

U prvom primjeru javno sučelje klase `ControlButton` čine:
```cpp
public:
    void press();
    void release();
    bool is_pressed();
```
Vanjski kod zato radi s objektom ovako:
```cpp
ControlButton objUpButton;

objUpButton.press();

if (objUpButton.is_pressed())
{
    // ...
}

objUpButton.release();
```
Korisnik klase ne mora znati da se stanje interno sprema kao:
```cpp
bool mPressed;
```
niti da `press()` i `release()` koriste pomoćnu funkciju:
```cpp
void set_pressed(bool pressed);
```
Ti detalji pripadaju privatnoj implementaciji:
```cpp
private:
    bool mPressed;
    void set_pressed(bool pressed);
```
Odnos možemo prikazati ovako:
```text
kod izvan klase
        ↓  koristi
+----------------------------+
|       javno sučelje        |
|                            |
| press()                    |
| release()                  |
| is_pressed()               |
+----------------------------+
              ↓ koristi
+----------------------------+
|   privatna implementacija  |
|                            |
| mPressed                   |
| set_pressed()              |
+----------------------------+
```
Ovakva podjela ima važnu praktičnu posljedicu: unutarnja implementacija klase može se mijenjati bez potrebe da vanjski kod mijenja način korištenja klase, sve dok javno sučelje ostane isto.

Primjerice, korisnik klase i dalje može pisati:
```cpp
objUpButton.press();
```
neovisno o tome kako će klasa kasnije interno predstavljati stanje tipke.

Javno sučelje zato nije samo popis svega što možemo staviti pod `public:`. Ono treba izlagati operacije koje imaju smisla za korisnika klase, dok detalji potrebni samo implementaciji ostaju privatni.

---

## 4. Privatni podatkovni članovi i privatne članske funkcije

Datoteka `01_access_control.cpp` pokazuje da `private` nije namijenjen samo podatkovnim članovima.

Klasa sadrži privatni podatkovni član:
```cpp
private:
    bool mPressed;
```
ali i privatnu člansku funkciju:
```cpp
void set_pressed(bool pressed);
```
Funkcija `set_pressed()` predstavlja pomoćni detalj koji je potreban samoj klasi:
```cpp
void ControlButton::set_pressed(bool pressed)
{
    mPressed = pressed;
}
```
Vanjski kod ne treba poznavati tu funkciju. Umjesto nje koristi smislenije javne operacije:
```cpp
void ControlButton::press()
{
    set_pressed(true);
}

void ControlButton::release()
{
    set_pressed(false);
}
```
Time klasa sama odlučuje kako će izvesti operacije `press()` i `release()`.

Funkcija `is_pressed()` omogućuje čitanje privatnog stanja bez izravnog pristupa podatkovnom članu:
```cpp
bool ControlButton::is_pressed()
{
    return mPressed;
}
```
U `main()` zato koristimo samo javno sučelje:
```cpp
ControlButton objUpButton;

objUpButton.press();

cout << "UP tipka: "
     << (objUpButton.is_pressed() ? "pritisnuta" : "otpustena") << '\n';

objUpButton.release();
```
Ispis:
```text
UP tipka: pritisnuta
UP tipka: otpustena
```
Objekt prije čitanja njegova stanja najprije dovodimo u poznato stanje pozivom `press()` ili `release()`. U sljedećoj temi konstruktor će omogućiti da početno stanje objekta odredimo već pri njegovu stvaranju.

---

## 5. Kontrolirana promjena stanja objekta

Drugi primjer pokazuje važniju praktičnu korist enkapsulacije: objekt može kontrolirati koje će promjene svojeg stanja prihvatiti.

Za model Autoquip Titan 42C8F80 koristimo:
```text
minimalna visina: 30 cm
maksimalna visina: 137 cm
```
Klasa `PlatformPosition` sprema visinu kao privatni podatkovni član:
```cpp
class PlatformPosition
{
private:
    double mHeightCm;

    bool is_height_valid(double heightCm);

public:
    bool set_height(double heightCm);
    double get_height();
};
```
Vanjski kod zato ne može izravno zapisati:
```cpp
// objPlatformPosition.mHeightCm = 150.0;
```
Umjesto toga promjena visine prolazi kroz javnu funkciju:
```cpp
bool set_height(double heightCm);
```
Klasa sadrži privatnu pomoćnu funkciju koja provjerava je li vrijednost u dopuštenom rasponu:
```cpp
bool PlatformPosition::is_height_valid(double heightCm)
{
    const double minHeightCm{30.0};
    const double maxHeightCm{137.0};

    return (heightCm >= minHeightCm) && (heightCm <= maxHeightCm);
}
```
Dvije usporedbe daju `bool` rezultate koje operator `&&` povezuje u jedan konačni rezultat:
```text
heightCm >= minHeightCm
        &&
heightCm <= maxHeightCm
```
Funkcija vraća `true` samo kada su zadovoljene obje granice.

Javni setter koristi privatnu provjeru:
```cpp
bool PlatformPosition::set_height(double heightCm)
{
    if (!is_height_valid(heightCm))
    {
        return false;
    }

    mHeightCm = heightCm;
    return true;
}
```

Za vrijednost `100.0 cm` funkcija sprema novu vrijednost i vraća `true`.

Za vrijednost `150.0 cm` funkcija završava prije promjene člana `mHeightCm` i vraća `false`. Zbog toga prethodno valjano stanje ostaje sačuvano.

U demonstraciji najprije postavljamo početnu vrijednost:
```cpp
objPlatformPosition.set_height(30.0);
```
zatim pokušavamo postaviti dopuštenu vrijednost:
```cpp
if (objPlatformPosition.set_height(100.0))
{
    cout << "Nova visina: " << objPlatformPosition.get_height() << " cm\n";
}
```

Bit enkapsulacije u ovom primjeru jest da neispravna promjena nije narušila prethodno valjano stanje objekta.

Visina platforme ovdje je unutarnje stanje OOP modela simulatora. Ne dodajemo je u `virtual_io`, jer upravljački program odabrane izvedbe ne prima kontinuiranu vrijednost visine platforme preko odgovarajućeg ulaznog signala.

### 5.1. Getter i setter funkcije

Funkcije kojima se pristupa privatnim podacima često se nazivaju **getter** i **setter** funkcijama.

U klasi `PlatformPosition`:
```cpp
bool set_height(double heightCm);
double get_height();
```
`set_height()` je *setter* jer postavlja ili mijenja vrijednost privatnog člana `mHeightCm`, pri čemu prije promjene provjerava je li nova vrijednost dopuštena.

*Getter* i *setter* ne treba automatski dodavati svakom podatkovnom članu. Javno sučelje klase treba sadržavati samo operacije koje imaju smisla za korištenje klase.

---

## 6. Sažetak

**Enkapsulacija**

Enkapsulacija povezuje stanje objekta i ponašanja koja nad tim stanjem djeluju te omogućuje da klasa kontrolira način korištenja svoje unutarnje implementacije.

Enkapsulaciju omogućujemo klasama, članskim funkcijama i kontrolom pristupa članovima klase.

**Kontrola pristupa**

Javne članove možemo koristiti i izvan klase.
Privatnim članovima ne može se izravno pristupati izvan klase.
Članske funkcije iste klase mogu pristupati privatnim podatkovnim članovima i pozivati privatne članske funkcije.

**Javno sučelje**

Javno sučelje (*public interface*) predstavlja način na koji vanjski kod koristi klasu.

Privatni članovi predstavljaju unutarnje detalje klase koji nisu namijenjeni izravnom korištenju izvan klase.

**Kontrola stanja**

*Setter* može provjeriti novu vrijednost prije promjene privatnog stanja. Primjer:
```cpp
if (!is_height_valid(heightCm))
{
    return false;
}

mHeightCm = heightCm;
return true;
```
Time klasa može odbiti nedopuštenu promjenu i sačuvati prethodno valjano stanje.

***Getter*** **i** ***setter***

*Getter* je članska funkcija koja omogućuje čitanje vrijednosti privatnog podatkovnog člana.

*Setter* je članska funkcija kojom se postavlja ili mijenja vrijednost privatnog podatkovnog člana. *Setter* može prije promjene vrijednosti provjeriti je li nova vrijednost dopuštena.

*Getter* i *setter* ne dodaju se automatski svakom podatkovnom članu. Javno sučelje treba izložiti samo operacije koje imaju smisla za korisnika klase.
