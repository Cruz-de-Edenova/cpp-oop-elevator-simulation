# Kompozicija

U prethodnim temama obrađene su klase, objekti, enkapsulacija, konstruktori i destruktori. U ovoj temi se obrađuje povezivanje više objekata u jednu cjelinu pomoću **kompozicije** (*composition*). To je prvi odnos među objektima koji se obrađuje u ovoj cjelini.

Prateći primjeri koriste upravljačku ploču s tipkama *UP* i *DOWN* podizne platforme Autoquip Titan. Objašnjavaju odnose među objektima, a ne upravljačku logiku ili rad virtualnog I/O-a simulatora. 

**Ključni pojmovi:**
- kompozicija (*composition*)
- odnos cjeline i dijelova (*whole-part relationship*)
- objekt kao podatkovni član (*member object*)
- životni vijek objekta kao podatkovnog člana
- redoslijed konstrukcije i uništavanja objekata

## Sadržaj

1. Kompozicija kao odnos cjeline i dijelova
2. Implementacija kompozicije u C++-u
   2.1. Kada je eksplicitna inicijalizacija potrebna?
3. Redoslijed konstrukcije i uništavanja objekata
4. Primjer 1 — Upravljačka ploča i dvije tipke
5. Primjer 2 — Životni vijek upravljačke ploče i tipki
6. GDB analiza
   6.1. GDB ispis
   6.2. Sažeto objašnjenje GDB ispisa

**Prateći primjeri:**
- **Primjer 1:** `1_control_panel.cpp`
  Prikazuje kompoziciju i upravljanje stanjem dviju tipki.
- **Primjer 2:** `2_object_lifetime.cpp`
  Prikazuje redoslijed konstrukcije i uništavanja objekata koji su podatkovni članovi klase `ControlPanel`.

---

## 1. Kompozicija kao odnos cjeline i dijelova

Kompozicija je OOP odnos u kojem objekt predstavlja **cjelinu** sastavljenu od drugih objekata, odnosno **dijelova**. Takav odnos nazivamo odnosom cjeline i dijelova (*whole-part relationship*), a često se opisuje i izrazom *has-a* (ima).

Primjer upravljačke ploče koja sadrži dvije upravljačke tipke:
```text
ControlPanel
    |
    +-- ControlButton mUpButton
    +-- ControlButton mDownButton
```
Objekt klase `ControlPanel` predstavlja cjelinu, a objekti `mUpButton` i `mDownButton` njezine dijelove. Svaki od tih objekata ima vlastito stanje, ali je njihov životni vijek vezan uz životni vijek ploče koja ih sadrži.

Kompozicija ovdje opisuje **programski model**, a ne tvrdnju da se fizička tipka nikada ne može zamijeniti. To ne znači da se objekti klase `ControlButton` ne mogu stvarati zasebno. U ovom primjeru kompozicija se odnosi na `mUpButton` i `mDownButton`, koji su podatkovni članovi klase `ControlPanel` i čiji je životni vijek vezan uz objekt te klase.

---

## 2. Implementacija kompozicije u C++-u

C++ nema posebnu ključnu riječ za kompoziciju. Njezin uobičajeni mehanizam jest **objekt kao nestatički podatkovni član druge klase**. U klasi `ControlPanel` deklarirani su:
```cpp
ControlButton mUpButton;
ControlButton mDownButton;
```

To nisu pokazivači niti reference, nego objekti deklarirani kao podatkovni članovi klase `ControlPanel`. Njihova inicijalizacija i životni vijek vezani su uz objekt klase `ControlPanel`.

Konstruktor klase `ControlPanel` može inicijalizirati objekte koji su njezini podatkovni članovi pomoću liste inicijalizatora članova:
```cpp
ControlPanel()
    : mUpButton{}, mDownButton{}
{
}
```
U ovom primjeru za inicijalizaciju oba podatkovna člana poziva se defaultni konstruktor klase `ControlButton`. Lista inicijalizatora članova napisana je eksplicitno kako bi se pokazalo kako se objekti koji su podatkovni članovi inicijaliziraju tijekom konstrukcije objekta klase `ControlPanel`.

U ovom slučaju inicijalizatori `mUpButton{}` i `mDownButton{}` mogli bi se izostaviti:
```cpp
ControlPanel()
{
}
```
Rezultat je isti. Tijekom konstrukcije objekta klase `ControlPanel` automatski se poziva defaultni konstruktor klase `ControlButton` za svaki od dvaju podatkovnih članova. Obje tipke tako dobivaju početno otpušteno stanje. 

**Korist za dizajn:** `ControlPanel` upravlja svojim tipkama preko njihovih javnih članskih funkcija. Vanjski kod ne mora znati kako ploča interno čuva tipke. Uz to, nije potrebno ručno upravljati životnim vijekom tih objekata.

### 2.1. Kada je eksplicitna inicijalizacija potrebna?

Ako klasa `ControlButton` nema defaultni konstruktor, primjerice zato što je definiran samo konstruktor s parametrom:
```cpp
ControlButton(bool pressed)
    : mPressed{pressed}
{
}
```
tada u konstruktoru klase `ControlPanel` potrebno je osigurati inicijalizaciju oba podatkovna člana, primjerice pomoću liste inicijalizatora članova:
```cpp
ControlPanel()
    : mUpButton{false}, mDownButton{false}
{
}
```
U ovom slučaju inicijalizatori `mUpButton{false}` i `mDownButton{false}` ne mogu se izostaviti jer klasa `ControlButton` nema konstruktor koji se može pozvati bez argumenata. Bez odgovarajuće inicijalizacije program se ne bi mogao kompajlirati.

Alternativno, inicijalizatori se mogu navesti izravno pri deklaraciji podatkovnih članova klase `ControlPanel`:
```cpp
class ControlPanel
{
private:
    ControlButton mUpButton{false};   // Tipka za podizanje
    ControlButton mDownButton{false}; // Tipka za spuštanje

public:
    // Inicijalizira obje tipke u otpuštenom stanju
    ControlPanel();
};
```
Tada konstruktor klase `ControlPanel` može ostati bez liste inicijalizatora članova:
```cpp
ControlPanel()
{
}
```
Oba objekta klase `ControlButton` inicijaliziraju se vrijednošću `false` navedenom pri deklaraciji njihovih podatkovnih članova.

---

## 3. Redoslijed konstrukcije i uništavanja objekata

Pri stvaranju objekta klase `ControlPanel` njegovi se podatkovni članovi konstruiraju **redoslijedom deklaracije u klasi**, neovisno o redoslijedu navedenom u listi inicijalizatora članova. Tek nakon njihove konstrukcije izvršava se tijelo konstruktora klase `ControlPanel`.

U ovom primjeru redoslijed izvršavanja tijela konstruktora je:
```text
1. ControlButton (mUpButton)   - tijelo konstruktora
2. ControlButton (mDownButton) - tijelo konstruktora
3. ControlPanel                - tijelo konstruktora
```
Kada završi životni vijek objekta klase `ControlPanel`, najprije se izvršava tijelo njegova destruktora. Nakon toga automatski se uništavaju objekti koji su njegovi podatkovni članovi, **obrnutim redoslijedom od njihove konstrukcije**.

Redoslijed izvršavanja tijela destruktora je:
```text
1. ControlPanel                - tijelo destruktora
2. ControlButton (mDownButton) - tijelo destruktora
3. ControlButton (mUpButton)   - tijelo destruktora
```
Takav redoslijed uništavanja vrijedi i kada destruktor klase `ControlPanel` nije eksplicitno definiran. Kompajler osigurava automatsko uništavanje njezinih podatkovnih članova.

Redoslijed konstrukcije i uništavanja objekata detaljnije je prikazan u 6. poglavlju (**GDB analiza**) na primjeru programa `2_object_lifetime.cpp`. U tom su primjeru destruktori klasa `ControlButton` i `ControlPanel` eksplicitno definirani kako bi se moglo pratiti njihovo izvršavanje. Za pravilno uništavanje objekata koji su podatkovni članovi nije potrebno eksplicitno definirati destruktore. 

---

## 4. Primjer 1 — Upravljačka ploča i dvije tipke

Datoteka: `1_control_panel.cpp`

Program prikazuje kompoziciju u kojoj klasa `ControlPanel` ima dva objekta klase `ControlButton` kao podatkovne članove. Njihova se stanja mijenjaju i čitaju pomoću javnih članskih funkcija upravljačke ploče.

| Novi koncept | Mjesto u kodu |
| --- | --- |
| Objekti kao podatkovni članovi | `cpp: 41-42` |
| Inicijalizacija tih objekata u konstruktoru | `cpp: 46-49` |
| Pozivanje funkcija objekata koji su podatkovni članovi | `cpp: 52-55; 58-61; 64-67; 70-73` |
| Demonstracija kompozicije | `cpp: 91-107` |

U `cpp: 41-42` deklarirani su `mUpButton` i `mDownButton`, oba tipa `ControlButton`. Konstruktor klase `ControlPanel` u `cpp: 46-49` inicijalizira ih pozivanjem defaultnog konstruktora klase `ControlButton`. Svaka tipka zato na početku ima stanje `false`, odnosno otpuštena je.

Funkcije klase `ControlPanel` u `cpp: 52-55; 58-61; 64-67; 70-73` pozivaju javne funkcije pripadajućih tipki. U `cpp: 91-107` prikazuju se početna stanja, promjena stanja tipke *UP* i njezino ponovno otpuštanje. Stanje tipke *DOWN* pritom se ne mijenja. 

---

## 5. Primjer 2 — Životni vijek upravljačke ploče i tipki

Datoteka: `2_object_lifetime.cpp`

Drugi program prikazuje redoslijed konstrukcije i uništavanja objekata. Za razliku od prvog primjera, klasa `ControlButton` ovdje čuva samo oznaku tipke (`mLabel`), koja služi za razlikovanje objekata tijekom ispisa. Stanje pritisnutosti tipke ne prati se jer nije potrebno za ovu demonstraciju.

| Novi koncept | Mjesto u kodu |
| --- | --- |
| Objekti kao podatkovni članovi | `cpp: 38, 39` |
| Redoslijed konstrukcije i uništavanja objekata | `cpp: 18-53` |
| Životni vijek objekta ograničen blokom | `cpp: 66-69` |

U `cpp: 43-47` konstruktor klase `ControlPanel` inicijalizira `mUpButton` oznakom `"UP"`, a `mDownButton` oznakom `"DOWN"`. Tek nakon konstrukcije obiju tipki izvršava se tijelo konstruktora klase `ControlPanel`.

Objekt `objPanel` stvara se unutar zasebnog bloka (`cpp: 66-69`). Izlaskom iz bloka automatski započinje njegovo uništavanje. Najprije se izvršava tijelo destruktora klase `ControlPanel`, a zatim tijela destruktora tipki obrnutim redoslijedom od njihove konstrukcije.

Ispis programa:
```text
Prije stvaranja kontrolne ploce
ControlButton "UP": tijelo konstruktora
ControlButton "DOWN": tijelo konstruktora
ControlPanel: tijelo konstruktora
------------------------------
ControlPanel: tijelo destruktora
ControlButton "DOWN": tijelo destruktora
ControlButton "UP": tijelo destruktora
Nakon izlaska iz bloka
```

Destruktori su u ovom primjeru eksplicitno definirani radi praćenja njihova izvršavanja. Za automatsko uništavanje objekata koji su podatkovni članovi nije potrebno pisati vlastite destruktore ako nema drugih razloga za njihovu definiciju.

---

## 6. GDB analiza

GDB analiza izvodi se nad programom `2_object_lifetime.cpp`. Cilj je provjeriti redoslijed izvršavanja tijela konstruktora i destruktora, razlikovati dvije tipke prema oznaci `mLabel` i pregledati stog poziva funkcija. 

### 6.1. GDB ispis

```text
E:\Files\G++\Lift\3-oop\02-odnosi-medu-objektima\02-01-kompozicija>gdb -q 2_object_lifetime.exe
Reading symbols from 2_object_lifetime.exe...
(gdb) set print thread-events off
(gdb) break 2_object_lifetime.cpp:21
Breakpoint 1 at 0x1400033a3: file 2_object_lifetime.cpp, line 21.
(gdb) break 2_object_lifetime.cpp:27
Breakpoint 2 at 0x14000340c: file 2_object_lifetime.cpp, line 27.
(gdb) break 2_object_lifetime.cpp:46
Breakpoint 3 at 0x140003289: file 2_object_lifetime.cpp, line 46.
(gdb) break 2_object_lifetime.cpp:52
Breakpoint 4 at 0x14000333c: file 2_object_lifetime.cpp, line 52.
(gdb) info breakpoints
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000001400033a3 in ControlButton::ControlButton(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&)
                                                   at 2_object_lifetime.cpp:21
2       breakpoint     keep y   0x000000014000340c in ControlButton::~ControlButton() at 2_object_lifetime.cpp:27
3       breakpoint     keep y   0x0000000140003289 in ControlPanel::ControlPanel() at 2_object_lifetime.cpp:46
4       breakpoint     keep y   0x000000014000333c in ControlPanel::~ControlPanel() at 2_object_lifetime.cpp:52
(gdb) run
Starting program: E:\Files\G++\Lift\3-oop\02-odnosi-medu-objektima\02-01-kompozicija\2_object_lifetime.exe
Prije stvaranja kontrolne ploce

Thread 1 hit Breakpoint 1, ControlButton::ControlButton (this=0x5ffdf0, label="UP") at 2_object_lifetime.cpp:21
21              cout << "ControlButton \"" << mLabel << "\": tijelo konstruktora\n";
(gdb) p mLabel
$1 = "UP"
(gdb) bt
#0  ControlButton::ControlButton (this=0x5ffdf0, label="UP") at 2_object_lifetime.cpp:21
#1  0x00007ff7ad55321c in ControlPanel::ControlPanel (this=0x5ffdf0) at 2_object_lifetime.cpp:44
#2  0x00007ff7ad551742 in main () at 2_object_lifetime.cpp:67
(gdb) c
Continuing.
ControlButton "UP": tijelo konstruktora

Thread 1 hit Breakpoint 1, ControlButton::ControlButton (this=0x5ffe10, label="DOWN") at 2_object_lifetime.cpp:21
21              cout << "ControlButton \"" << mLabel << "\": tijelo konstruktora\n";
(gdb) p mLabel
$2 = "DOWN"
(gdb) bt
#0  ControlButton::ControlButton (this=0x5ffe10, label="DOWN") at 2_object_lifetime.cpp:21
#1  0x00007ff7ad553270 in ControlPanel::ControlPanel (this=0x5ffdf0) at 2_object_lifetime.cpp:44
#2  0x00007ff7ad551742 in main () at 2_object_lifetime.cpp:67
(gdb) c
Continuing.
ControlButton "DOWN": tijelo konstruktora

Thread 1 hit Breakpoint 3, ControlPanel::ControlPanel (this=0x5ffdf0) at 2_object_lifetime.cpp:46
46              cout << "ControlPanel: tijelo konstruktora\n";
(gdb) set print pretty on
(gdb) p *this
$3 = {
  mUpButton = {
    mLabel = "UP"
  },
  mDownButton = {
    mLabel = "DOWN"
  }
}
(gdb) bt
#0  ControlPanel::ControlPanel (this=0x5ffdf0) at 2_object_lifetime.cpp:46
#1  0x00007ff7ad551742 in main () at 2_object_lifetime.cpp:67
(gdb) c
Continuing.
ControlPanel: tijelo konstruktora
------------------------------

Thread 1 hit Breakpoint 4, ControlPanel::~ControlPanel (this=0x5ffdf0) at 2_object_lifetime.cpp:52
52              cout << "ControlPanel: tijelo destruktora\n";
(gdb) bt
#0  ControlPanel::~ControlPanel (this=0x5ffdf0) at 2_object_lifetime.cpp:52
#1  0x00007ff7ad551764 in main () at 2_object_lifetime.cpp:69
(gdb) c
Continuing.
ControlPanel: tijelo destruktora

Thread 1 hit Breakpoint 2, ControlButton::~ControlButton (this=0x5ffe10) at 2_object_lifetime.cpp:27
27              cout << "ControlButton \"" << mLabel << "\": tijelo destruktora\n";
(gdb) p *this
$4 = {
  mLabel = "DOWN"
}
(gdb) bt
#0  ControlButton::~ControlButton (this=0x5ffe10) at 2_object_lifetime.cpp:27
#1  0x00007ff7ad553362 in ControlPanel::~ControlPanel (this=0x5ffdf0) at 2_object_lifetime.cpp:53
#2  0x00007ff7ad551764 in main () at 2_object_lifetime.cpp:69
(gdb) c
Continuing.
ControlButton "DOWN": tijelo destruktora

Thread 1 hit Breakpoint 2, ControlButton::~ControlButton (this=0x5ffdf0) at 2_object_lifetime.cpp:27
27              cout << "ControlButton \"" << mLabel << "\": tijelo destruktora\n";
(gdb) p *this
$5 = {
  mLabel = "UP"
}
(gdb) bt
#0  ControlButton::~ControlButton (this=0x5ffdf0) at 2_object_lifetime.cpp:27
#1  0x00007ff7ad55336e in ControlPanel::~ControlPanel (this=0x5ffdf0) at 2_object_lifetime.cpp:53
#2  0x00007ff7ad551764 in main () at 2_object_lifetime.cpp:69
(gdb) c
Continuing.
ControlButton "UP": tijelo destruktora
Nakon izlaska iz bloka
[Inferior 1 (process 7636) exited normally]
(gdb)
```

### 6.2. Sažeto objašnjenje GDB ispisa

U GDB-u su postavljene četiri točke prekida, ali program se zaustavlja šest puta jer se konstruktor i destruktor klase `ControlButton` izvršavaju za oba objekta koji su podatkovni članovi klase `ControlPanel`.

**Redoslijed konstrukcije:**

1. `ControlButton::ControlButton(const string&)` — inicijalizacija tipke `UP`
2. `ControlButton::ControlButton(const string&)` — inicijalizacija tipke `DOWN`
3. `ControlPanel::ControlPanel()`                — izvršavanje tijela konstruktora upravljačke ploče

Pri trećem zaustavljanju naredba `p *this` prikazuje objekt `ControlPanel` s oba već inicijalizirana podatkovna člana (`mUpButton` i `mDownButton`). Time se potvrđuje da se objekti koji su podatkovni članovi konstruiraju prije izvršavanja tijela konstruktora klase `ControlPanel`.

**Redoslijed uništavanja:**

1. `ControlPanel::~ControlPanel()`   — izvršavanje tijela destruktora upravljačke ploče
2. `ControlButton::~ControlButton()` — uništavanje tipke `DOWN`
3. `ControlButton::~ControlButton()` — uništavanje tipke `UP`

Naredba `bt` prikazuje stog poziva funkcija i potvrđuje da se konstruktori tipki pozivaju tijekom konstrukcije objekta `ControlPanel`, a njihovi destruktori tijekom njegova uništavanja.

GDB analiza pokazuje da se objekti koji su podatkovni članovi automatski konstruiraju redoslijedom deklaracije u klasi, a uništavaju obrnutim redoslijedom. Njihov životni vijek vezan je uz objekt klase `ControlPanel`.