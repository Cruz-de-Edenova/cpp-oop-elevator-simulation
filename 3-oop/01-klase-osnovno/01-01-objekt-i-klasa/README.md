# Objekt i klasa

Ovom temom započinje sustavno proučavanje objektno-orijentiranog programiranja u C++-u. Dosadašnji programi prvenstveno su bili organizirani proceduralno: podaci su se čuvali u varijablama, a nad njima su djelovale zasebne funkcije. Objektno-orijentirani pristup omogućuje da podatke i ponašanja koja im prirodno pripadaju promatramo kao jednu smislenu cjelinu.

U ovoj temi uvode se pojmovi **klasa**, **objekt**, **instanca**, **atribut** i **ponašanje**, a zatim se povezuju s odgovarajućim C++ mehanizmima: korisnički definiranim tipom, podatkovnim članovima i članskim funkcijama.

Primjeri koriste upravljačke tipke *UP* i *DOWN* podizne platforme Autoquip Titan. Svaka tipka može biti pritisnuta ili otpuštena, pa dvije tipke prirodno mogu predstavljati dva objekta iste klase s različitim stanjem. Primjer još nije povezan s virtualnim I/O-om simulatora.

## Sadržaj

1. Od proceduralnog prema objektnom razmišljanju
2. Klasa
3. Objekt klase
4. Atributi, ponašanja i članovi klase
5. Kratka usporedba `class` i `struct`
6. Sažetak

**Prateći primjeri:**
- `01_control_button.cpp`
- `02_class_i_struct.cpp`

---

## 1. Od proceduralnog prema objektnom razmišljanju

U proceduralnom programu podatke i funkcije najčešće promatramo kao zasebne elemente. Primjerice, stanje tipke *UP* možemo spremiti u običnu varijablu:
```cpp
bool upButtonPressed{false};
```
Zasebna funkcija može mijenjati tu vrijednost:
```cpp
void set_button_pressed(bool& pressed, bool newPressed)
{
    pressed = newPressed;
}
```
Takav pristup nije pogrešan. Za mnoge male probleme proceduralno rješenje može biti jednostavnije i potpuno prikladno.

Međutim, upravljačka tipka u modelu sustava nije samo jedna nepovezana vrijednost. Ima vlastito stanje, a nad tim stanjem postoje operacije koje imaju smisla upravo za tipku.

Objektno-orijentirano razmišljanje zato pokušava prepoznati smislene cjeline:
```text
upravljačka tipka
    |
    +-- stanje: pritisnuta ili otpuštena
    |
    +-- ponašanje: promijeni stanje tipke
    |
    +-- ponašanje: ispiši stanje
```
Važna promjena nije samo sintaktička. Prvo razmišljamo što neki objekt predstavlja, koje mu stanje prirodno pripada i koja ponašanja nad tim stanjem imaju smisla. Tek nakon toga biramo C++ mehanizme kojima ćemo takav model implementirati.

To ne znači da svaka varijabla ili svaka funkcija mora postati klasa. Klasa ima smisla kada predstavlja smislenu programsku cjelinu.

---

## 2. Klasa

Klasa opisuje zajedničke karakteristike i ponašanja određene vrste objekata. Ona nije jedna konkretna tipka, nego opis prema kojem se mogu stvarati konkretni objekti.

U C++-u klasa je **korisnički definirani tip**. Osnovna definicija klase koristi ključnu riječ `class`:
```cpp
class ControlButton
{
    // Članovi klase
};
```
Nakon ove definicije naziv `ControlButton` predstavlja novi tip koji možemo koristiti u programu.

Usporedimo:
```cpp
int count{0};
bool upButtonPressed{false};
ControlButton objUpButton;
```
`int` i `bool` su ugrađeni tipovi, dok je `ControlButton` tip koji smo definirali sami.

Definicija klase završava znakom `;` iza zatvorene vitičaste zagrade:
```cpp
class ControlButton
{
    // ...
};
```
Unutar klase navode se njezini članovi. U ovom projektu članove organiziramo pomoću specifikatora pristupa (*access specifiers*) `private:` i `public:`. Njihovo značenje i uloga u enkapsulaciji detaljno će se obrađivati u narednim temama, pa ih ovdje koristimo bez dublje analize.

---

## 3. Objekt klase

Klasa opisuje tip objekta. Objekt klase stvaramo tako da definiramo objekt tipa te klase:
```cpp
ControlButton objUpButton;
```
`ControlButton` je klasa, odnosno korisnički definirani tip.

`objUpButton` je **objekt** te klase. Konkretan objekt neke klase naziva se i **instancom klase**, pa možemo reći da je `objUpButton` instanca klase `ControlButton`.

`objUpButton` je istodobno:
- objekt tipa `ControlButton`
- instanca klase `ControlButton`

Razlika je više u načinu na koji se izraz koristi nego u samom značenju. Objekt je opći C++/OOP izraz za konkretan element određenog tipa u programu, dok instanca klase posebno naglašava odnos tog objekta prema klasi kojoj pripada.

Jedna klasa može imati više zasebnih objekata:
```cpp
ControlButton objUpButton;
ControlButton objDownButton;
```
Odnos možemo prikazati ovako:
```text
klasa ControlButton
        |
        +-- objUpButton
        +-- objDownButton
```
Oba objekta pripadaju istoj klasi i imaju ista dostupna ponašanja, ali svaki objekt ima vlastito stanje.

U primjeru `01_control_button.cpp` tipka *UP* je pritisnuta, a tipka *DOWN* otpuštena:
```cpp
objUpButton.set_pressed(true);
objDownButton.set_pressed(false);
```
Nakon toga svaki objekt pamti vlastitu vrijednost. Promjena stanja jednog objekta ne mijenja stanje drugog objekta.

To je jedna od temeljnih razlika između klase i njezinih instanci:
```text
ControlButton
    opisuje što svaka upravljačka tipka ima i što može raditi

objUpButton
    jedna instanca klase s vlastitim stanjem

objDownButton
    druga instanca iste klase s vlastitim stanjem
```
Odabrani Titan ima zasebne komande *UP* i *DOWN*. U ovom primjeru još ne modeliramo njihov utjecaj na motor, *DOWN* solenoid ili ostatak sustava. Trenutačni cilj je samo pokazati da iz jedne klase možemo stvoriti više zasebnih objekata.

---

## 4. Atributi, ponašanja i članovi klase

Objektno-orijentirana terminologija razlikuje **atribute** i **ponašanja** (*behavior*) objekta. U C++ klasi te ideje najčešće implementiramo pomoću **podatkovnih članova** (*data members*) i **članskih funkcija** (*member functions*).
```text
OOP pojam                              C++ mehanizam

atribut (attribute)                 -> podatkovni član (data member)
ponašanje (behavior)                -> članska funkcija (member function)
klasa (class)                       -> korisnički definirani tip (user-defined type)
instanca klase (class instance)     -> objekt toga tipa (object of that type)
```
### 4.1. Atributi i podatkovni članovi

Atribut opisuje neku karakteristiku ili dio stanja objekta.

Za upravljačku tipku koristimo atribut:
```text
stanje tipke: pritisnuta ili otpuštena
```
U C++ klasi taj atribut predstavljamo podatkovnim članom:
```cpp
bool mPressed;
```
Podatkovni član pripada svakom objektu klase. Zato `objUpButton` i `objDownButton` mogu imati različite vrijednosti člana `mPressed`.

U ovom primjeru `mPressed` predstavlja stanje pojedinog objekta klase `ControlButton`. Povezivanje tog objekta s postojećim proceduralnim virtualnim I/O-om simulatora zasad ne uvodimo.

### 4.2. Ponašanja i članske funkcije

Ponašanje predstavlja operaciju koja ima smisla za objekt.

U primjeru koristimo dvije jednostavne članske funkcije:
```cpp
void set_pressed(bool pressed);
void print_state();
```
`set_pressed()` mijenja stanje tipke, a `print_state()` ispisuje trenutačno stanje objekta.

### 4.3. Specifikatori pristupa `private` i `public`

`private` i `public` su **specifikatori pristupa** (*access specifiers*). Oni određuju iz kojih se dijelova programa može pristupati članovima klase.

Članovi navedeni iza `public:` dostupni su i izvan klase, primjerice preko objekta:
```cpp
class ControlButton
{
private:
    bool mPressed;

public:
    void set_pressed(bool pressed);
    void print_state();
};
```
Funkcije `set_pressed()` i `print_state()` su javni članovi pa ih možemo pozvati preko objekta:
```cpp
objUpButton.set_pressed(true);
objUpButton.print_state();
```
Članovi navedeni iza `private:` nisu izravno dostupni kodu izvan klase. Podatkovnom članu `mPressed` zato ne možemo pristupiti na ovaj način:
```cpp
objUpButton.mPressed = true; // Pogreška pri kompajliranju
```
Članske funkcije iste klase mogu pristupati privatnim članovima, pa `set_pressed()` može mijenjati vrijednost člana `mPressed`.

Specifikator pristupa vrijedi za sve članove koji slijede iza njega, sve do sljedećeg specifikatora pristupa ili kraja definicije klase.

Ako u definiciji pomoću ključne riječi `class` ne navedemo specifikator pristupa, podrazumijeva se `private`:
```cpp
class ControlButton
{
    bool mPressed; // private
};
```
Kod `struct` vrijedi suprotno: ako specifikator pristupa nije naveden, podrazumijeva se `public`:
```cpp
struct ButtonState
{
    bool mPressed; // public
};
```
U ovom projektu `private:` pišemo eksplicitno iako je kod `class` to zadani pristup. Time je namjera klase jasnije vidljiva u kodu.

Detaljnije značenje kontrole pristupa i njezina uloga u enkapsulaciji obrađivat će se u zasebnoj temi.

### 4.4. Pristup članovima klase preko objekta

Za pristup dostupnom članu klase preko konkretnog objekta koristi se operator `.`.

Poziv članske funkcije izgleda ovako:
```cpp
objUpButton.set_pressed(true);
objUpButton.print_state();
```
Lijevo od operatora `.` nalazi se objekt, a desno član kojem pristupamo.

Budući da su `set_pressed` i `print_state` funkcije, nakon njihovih naziva slijedi `()`:
```text
objUpButton . set_pressed(true)
     |              |
   objekt       članska funkcija
```
Operator `.` koristi se i za pristup dostupnom podatkovnom članu. Drugi primjer to pokazuje pomoću strukture `ButtonState`:
```cpp
ButtonState objState{false};
objState.mPressed = true;
```
Ovdje se operatorom `.` pristupa podatkovnom članu `mPressed`.

Kod klase `ControlButton` podatkovni član `mPressed` nalazi se u `private` dijelu, pa mu vanjski kod ne pristupa izravno. Pravila za specifikatore pristupa `private` i `public` te razlog za skrivanje podataka bit će obrađeni u narednim temama.

### 4.5. `01_control_button.cpp`

Datoteka `01_control_button.cpp` sadrži dvije demonstracije.

`demonstrate_single_object()` pokazuje stanje jednog objekta:
```cpp
ControlButton objUpButton;
objUpButton.set_pressed(true);

cout << "UP tipka: ";
objUpButton.print_state();
```

`demonstrate_multiple_objects()` zatim stvara dva objekta iste klase i svakom postavlja zasebno stanje:
```cpp
ControlButton objUpButton;
ControlButton objDownButton;

objUpButton.set_pressed(true);
objDownButton.set_pressed(false);
```

Ispis:
```text
UP tipka: pritisnuta
------------------------------
UP tipka: pritisnuta
DOWN tipka: otpustena
```
---

## 5. Kratka usporedba `class` i `struct`

C++ dopušta da i `class` i `struct` sadrže podatkovne članove i članske funkcije. Oba definiraju korisnički definirane tipove.

Važna razlika koju sada trebamo znati odnosi se na zadani pristup članovima:
```text
class  -> članovi su private ako nije navedeno drukčije
struct -> članovi su public ako nije navedeno drukčije
```
Nasljeđivanje još ne obrađujemo, pa odgovarajuću razliku u zadanom pristupu baznoj klasi ostavljamo za kasnije.

Jednostavan `struct` može izgledati ovako:
```cpp
struct ButtonState
{
    bool mPressed;
};
```
Njegovom članu možemo pristupiti izravno:
```cpp
ButtonState objState{false};
objState.mPressed = true;
```
Klasa u našem glavnom primjeru podatak `mPressed` drži u `private` dijelu, a ponašanja izlaže kroz `public` članske funkcije. Time već vidimo oblik koji će kasnije biti važan za enkapsulaciju, ali ga u ovoj temi još ne analiziramo detaljno.

Datoteka `02_class_i_struct.cpp` pokazuje oba tipa u istom programu. Klasa `ControlButton` pritom koristi iste članske funkcije `set_pressed()` i `print_state()` kao u prvom primjeru.

Ispis:
```text
Tip:        Stanje tipke:
struct      pritisnuta
class       pritisnuta
```
U OOP primjerima ovog projekta prvenstveno ćemo koristiti klase, ali `struct` je također punopravni C++ mehanizam koji može sadržavati podatke i članske funkcije.

U C++-u `class` i `struct` imaju gotovo iste mogućnosti. Glavna jezična razlika je u zadanom pristupu članovima: kod `class` podrazumijeva se `private`, a kod `struct` `public`. U praksi se `struct` često koristi za jednostavne tipove čiji su podaci namjerno javni, dok se `class` češće koristi za objekte koji skrivaju svoje unutarnje stanje.

---

## 6. Sažetak

### 1. Klasa i objekt

Klasa je korisnički definirani tip koji opisuje zajedničke podatke i ponašanja:
```cpp
class ControlButton
{
    // ...
};
```
Objekt je konkretna instanca te klase:
```cpp
ControlButton objUpButton;
```
Iz iste klase možemo stvoriti više objekata, a svaki od njih može imati vlastito stanje.

### 2. Atributi i ponašanja

OOP atribut u C++ klasi predstavljamo podatkovnim članom:
```cpp
bool mPressed;
```
OOP ponašanje implementiramo članskom funkcijom:
```cpp
void set_pressed(bool pressed);
```

### 3. Pristup članovima

Operator `.` koristi se za pristup dostupnim članovima klase preko objekta.

Pristup podatkovnom članu:
```cpp
objState.mPressed
```
Poziv članske funkcije:
```cpp
objUpButton.print_state();
```

### 4. `class` i `struct`

I `class` i `struct` mogu sadržavati podatkovne članove i članske funkcije.

Uobičajeno se `struct` koristi za jednostavne tipove s javno dostupnim podacima, a `class` za tipove koji skrivaju svoje unutarnje stanje.
