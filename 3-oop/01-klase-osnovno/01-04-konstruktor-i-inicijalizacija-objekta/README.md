# Konstruktor i inicijalizacija objekta

U prethodnim primjerima stanje objekta postavljalo se naknadnim pozivima članskih funkcija. Konstruktor omogućuje da se početno stanje objekta odredi automatski pri njegovu stvaranju.

Ova tema uvodi osnovne oblike konstruktora, listu inicijalizatora članova, preopterećenje konstruktora i razliku između inicijalizacije člana i kasnijeg pridruživanja nove vrijednosti.

**Ključni pojmovi:**

- konstruktor (*constructor*)
- defaultni konstruktor (*default constructor*)
- konstruktor s parametrima (*constructor with parameters*)
- preopterećenje konstruktora (*constructor overloading*)
- preopterećeni konstruktor (*overloaded constructor*)
- delegirajući konstruktor (*delegating constructor*)
- lista inicijalizatora članova (*member initializer list*)
- defaultni argument konstruktora (*default argument*)

## Sadržaj

1. Konstruktor
2. Lista inicijalizatora članova
3. Inicijalizacija i pridruživanje
4. Primjer 1 — Konstruktor i početno stanje objekta
5. Primjer 2 — Preopterećenje konstruktora
6. Primjer 3 — Provjera argumenata konstruktora
7. Primjer 4 — Delegirajući konstruktor
8. GDB analiza preopterećenih konstruktora

**Prateći primjeri:**

**Primjer 1:** `1_constructor.cpp`

**Primjer 2:** `2_constructor_overloading.cpp`

**Primjer 3:**
- `3_constructor_argument_validation.cpp`
- `3_platform_position.cpp`
- `3_platform_position.h`

**Primjer 4:** `4_delegating_constructor.cpp`

---

## 1. Konstruktor

**Konstruktor** je posebna članska funkcija koja se poziva pri stvaranju objekta i služi njegovoj inicijalizaciji. Ima isto ime kao klasa i ne navodi mu se povratni tip. U ovom primjeru prikazan je **korisnički deklariran defaultni konstruktor**:
```cpp
class ControlButton
{
public:
    ControlButton();   // Korisnički deklariran defaultni konstruktor 
};                     // Poziva se bez argumenata   
```

**Defaultni konstruktor** je konstruktor koji se može pozvati bez argumenata:
```cpp
ControlButton objButton{};
```

Konstruktor može imati i parametre. Primjer **konstruktora s parametrom**:
```cpp
ControlButton(bool pressed);
```

Tada početno stanje objekta možemo zadati pri samom stvaranju:
```cpp
ControlButton objButton{true};
```

Ako klasa nema nijedan korisnički deklariran konstruktor, **kompajler implicitno deklarira defaultni konstruktor**. Ako sami deklariramo bilo koji konstruktor, kompajler više neće automatski deklarirati takav defaultni konstruktor.

Konstruktori se mogu preopteretiti. Klasa tada ima više konstruktora s različitim popisima parametara, a pri stvaranju objekta odabire se konstruktor koji odgovara proslijeđenim argumentima.

---

## 2. Lista inicijalizatora članova

Članovi objekta mogu se inicijalizirati u **listi inicijalizatora članova** koja se nalazi između zaglavlja konstruktora i njegova tijela:
```cpp
ControlButton::ControlButton(bool pressed)
    : mPressed{pressed}
{
}
```

U ovom primjeru `mPressed` se inicijalizira vrijednošću parametra `pressed` prije početka izvođenja tijela konstruktora.

Broj stavki u listi inicijalizatora ne mora odgovarati broju parametara konstruktora. Primjerice, konstruktor može imati dva parametra, a inicijalizirati tri podatkovna člana:

```cpp
PlatformPositionStatus::PlatformPositionStatus(
    double requestedHeightCm,
    double defaultHeightCm)
    : mRequestedHeightCm{requestedHeightCm},
      mHeightCm{minHeightCm},
      mInputAccepted{false}
{
}
```

`mRequestedHeightCm` dobiva vrijednost iz prvog parametra, `mHeightCm` iz konstante, a `mInputAccepted` iz literala `false`.

Podatkovni članovi stvarno se inicijaliziraju redoslijedom kojim su deklarirani u klasi, ne redoslijedom kojim su napisani u listi inicijalizatora. Zato u primjerima redoslijed stavki u listi inicijalizatora prati redoslijed deklaracije članova.

**Defaultni argument konstruktora** nije isto što i inicijalizacija podatkovnog člana. U deklaraciji:
```cpp
PlatformPositionStatus(
    double requestedHeightCm,
    double defaultHeightCm = minHeightCm);  // Parametar konstruktora s defaultnim argumentom
```

`minHeightCm` je defaultni argument parametra `defaultHeightCm` koji se koristi kada pozivatelj ne proslijedi drugi argument. Taj parametar sam po sebi ne inicijalizira `mHeightCm`.

Parametri bez defaultnog argumenta moraju prethoditi parametrima koji imaju defaultni argument. Zato je `requestedHeightCm` naveden prije `defaultHeightCm`.

---

## 3. Inicijalizacija i pridruživanje

Inicijalizacija i pridruživanje nisu ista operacija.

```cpp
: mHeightCm{minHeightCm}
```
inicijalizira član `mHeightCm` prije ulaska u tijelo konstruktora.

Ako se poslije u tijelu izvrši:
```cpp
mHeightCm = defaultHeightCm;
```

član već postoji i već je inicijaliziran. Ovim izrazom samo mu se pridružuje nova vrijednost.

To se jasno vidi u trećem primjeru. `mHeightCm` se najprije inicijalizira valjanom minimalnom visinom. Nakon toga konstruktor provjerava argumente i po potrebi mijenja već inicijaliziranu vrijednost.

Takav redoslijed omogućuje da `mHeightCm` ima poznatu početnu vrijednost i prije izvršavanja provjera u tijelu konstruktora.

---

## 4. Primjer 1 — Konstruktor i početno stanje objekta

Datoteka: `1_constructor.cpp`

| Novi koncept | Mjesto u kodu |
| --- | --- |
| deklaracija defaultnog konstruktora | `1_constructor.cpp: 19` |
| definicija defaultnog konstruktora | `1_constructor.cpp: 30-33` |
| lista inicijalizatora članova | `1_constructor.cpp: 31` |
| automatski poziv konstruktora pri stvaranju objekta | `1_constructor.cpp: 71` |

U `1_constructor.cpp: 30-33` nalazi se definicija defaultnog konstruktora. U retku 31 član `mHeightCm` inicijalizira se na minimalnu visinu platforme pomoću liste inicijalizatora članova. Za razliku od ranijeg pristupa, nije potreban naknadni poziv `set_height()` samo radi postavljanja početnog stanja.

U `1_constructor.cpp: 71` stvara se objekt izrazom `PlatformPosition objPlatformPosition{};`, čime se automatski poziva defaultni konstruktor. Nakon završetka konstruktora objekt zato već ima poznatu početnu visinu od 30 cm.

Poziv `set_height()` u `1_constructor.cpp: 76` predstavlja kasniju promjenu već postojećeg stanja objekta. Sama nova vrijednost pridružuje se članu `mHeightCm` u `1_constructor.cpp: 54`. Time se jasno razlikuju inicijalizacija člana u konstruktoru i kasnije pridruživanje nove vrijednosti.

---

## 5. Primjer 2 — Preopterećenje konstruktora

Datoteka: `2_constructor_overloading.cpp`

| Novi koncept | Mjesto u kodu |
| --- | --- |
| deklaracije preopterećenih konstruktora | `2_constructor_overloading.cpp: 16 i 19` |
| definicija defaultnog konstruktora | `2_constructor_overloading.cpp: 27-30` |
| definicija konstruktora s parametrom | `2_constructor_overloading.cpp: 34-37` |
| odabir konstruktora prema argumentima | `2_constructor_overloading.cpp: 52-53` |

Klasa `ControlButton` ima dva konstruktora. 

U `2_constructor_overloading.cpp: 16` deklariran je defaultni konstruktor, a u `2_constructor_overloading.cpp: 19` konstruktor s parametrom `bool`. Budući da konstruktori imaju isto ime, ali različite popise parametara, riječ je o preopterećenju konstruktora.

U `2_constructor_overloading.cpp: 27-30` defaultni konstruktor inicijalizira `mPressed` na `false`, dok konstruktor s parametrom u `2_constructor_overloading.cpp: 34-37` inicijalizira isti član proslijeđenom vrijednošću.

U `2_constructor_overloading.cpp: 52-53` stvaraju se dva objekta. Izraz `objUpButton{}` poziva defaultni konstruktor, dok `objDownButton{true}` poziva konstruktor s parametrom. Odgovarajući konstruktor odabire se prema argumentima navedenima pri stvaranju objekta.

---

## 6. Primjer 3 — Provjera argumenata konstruktora

Datoteke:

- `3_constructor_argument_validation.cpp`
- `3_platform_position.cpp`
- `3_platform_position.h`

**Novi koncepti:**
| Novi koncept | Mjesto u kodu |
| --- | --- |
| parametar konstruktora s defaultnim argumentom | `3_platform_position.h: 25` |
| korištenje defaultnog argumenta pri pozivu konstruktora | `3_constructor_argument_validation.cpp: 14` |
| inicijalizacija više članova iz različitih izvora | `3_platform_position.cpp: 11-13` |

**Važni dijelovi koda:**
| Dio programa | Mjesto u kodu |
| --- | --- |
| provjera vrijednosti `defaultHeightCm` | `3_platform_position.cpp: 15-18` |
| provjera zatražene visine i spremanje rezultata | `3_platform_position.cpp: 20-24` |
| ograničavanje vrijednosti na dopušteni raspon | `3_platform_position.cpp: 63-70` |

U `3_platform_position.h: 23-25` konstruktor ima dva parametra. `requestedHeightCm` nema defaultni argument, dok parametar `defaultHeightCm` ima defaultni argument `minHeightCm`. Parametar s defaultnim argumentom nalazi se nakon parametra bez defaultnog argumenta. **Nakon parametra kojem je zadan defaultni argument, svi sljedeći parametri također moraju imati defaultni argument.**

U `3_constructor_argument_validation.cpp: 14` konstruktor se poziva samo s jednim argumentom. Vrijednost `150.0` prosljeđuje se parametru `requestedHeightCm`, dok se za izostavljeni drugi argument koristi defaultni argument `minHeightCm`. Parametar `defaultHeightCm` zato pri ovom pozivu dobiva vrijednost `30.0`.

U `3_platform_position.cpp: 11-13` lista inicijalizatora članova sadrži tri stavke iako konstruktor ima samo dva parametra. **Broj stavki u listi inicijalizatora članova ne mora odgovarati broju parametara konstruktora.** `mRequestedHeightCm` inicijalizira se vrijednošću parametra, `mHeightCm` konstantom `minHeightCm`, a `mInputAccepted` literalom `false`.

Redoslijed tih stavki prati redoslijed deklaracije podatkovnih članova u `3_platform_position.h: 14-16`. **Članovi se stvarno inicijaliziraju redoslijedom deklaracije u klasi, ne redoslijedom kojim su navedeni u listi inicijalizatora članova.**

Član `mHeightCm` zato prije ulaska u tijelo konstruktora već ima valjanu vrijednost `minHeightCm`. U `3_platform_position.cpp: 15-18` provjerava se vrijednost parametra `defaultHeightCm`. Ako je dopuštena, pridružuje se članu `mHeightCm`.

Važno je razlikovati parametar `defaultHeightCm` od defaultnog argumenta `minHeightCm`. Ako pozivatelj navede drugi argument, primjerice `200.0`, defaultni argument se uopće ne koristi. Parametar `defaultHeightCm` tada ima vrijednost `200.0`, koja je izvan dopuštenog raspona, pa `mHeightCm` ostaje na početnih `30.0`.

U `3_platform_position.cpp: 20-24` zatim se provjerava zatražena visina. Ako je dopuštena, pridružuje se članu `mHeightCm`, a `mInputAccepted` postavlja se na `true`. Time zatražena valjana visina ima prednost pred prethodno određenom početnom vrijednošću.

Klasa `PlatformPositionClamp` pokazuje drugi način postupanja s vrijednošću izvan dopuštenog raspona. U `3_platform_position.cpp: 63-70` preniska vrijednost ograničava se na `minHeightCm`, a previsoka na `maxHeightCm`. Zato se u demonstraciji vrijednost `150.0` ograničava na `137.0`.

Ova dva pristupa pokazuju da konstruktor može provjeriti podatke dobivene pri stvaranju objekta i osigurati da objekt nakon konstrukcije sadrži dopušteno početno stanje.

---

## 7. Primjer 4 — Delegirajući konstruktor

Datoteka: `4_delegating_constructor.cpp`

**Delegirajući konstruktor** (*delegating constructor*) u listi inicijalizatora poziva drugi konstruktor iste klase. Pozvani konstruktor naziva se **ciljni konstruktor** (*target constructor*). Ciljni konstruktor inicijalizira objekt, a zatim se izvršava tijelo delegirajućeg konstruktora. Delegiranjem se ne stvara dodatni objekt.

| Novi koncept | Mjesto u kodu |
| --- | --- |
| Delegiranje iz korisnički deklariranog defaultnog konstruktora | `cpp: 37-41` |
| Delegiranje iz konstruktora s jednim parametrom | `cpp: 45-51` |
| Izravna inicijalizacija članova u ciljnom konstruktoru | `cpp: 55-59` |
| Različiti načini stvaranja objekata | `cpp: 95, 101, 107` |
| Redoslijed izvršavanja tijela konstruktora | `cpp: 40, 50, 58` |

Klasa `PressureRange` ima tri preopterećena konstruktora. Defaultni konstruktor `PressureRange()` delegira konstruktoru `PressureRange(int, int)` i prosljeđuje mu dvije konstante s defaultnim pragovima tlaka (`cpp: 5-6, 37-38`). Konstruktor `PressureRange(int)` istom ciljnom konstruktoru prosljeđuje vrijednost parametra `lowPressure` kao prvi argument, a `kDefaultHighPressure` kao drugi (`cpp: 45-46`).

**Broj parametara delegirajućeg konstruktora ne mora odgovarati broju argumenata proslijeđenih ciljnom konstruktoru.** Argumenti se povezuju s parametrima ciljnog konstruktora prema redoslijedu. Ovdje se oba argumenta uvijek izričito prosljeđuju; konstante s nazivom `kDefault...` nisu defaultni argumenti konstruktora u C++ značenju.

Konstruktor `PressureRange(int, int)` ne delegira, nego izravno inicijalizira članove `mLowPressure` i `mHighPressure` (`cpp: 55-59`). Zato je zajednička inicijalizacija obaju pragova tlaka zapisana samo na jednom mjestu. Kada se taj konstruktor izravno pozove pri stvaranju objekta `objCustom`, nema delegiranja (`cpp: 107`).

U `main()` stvaraju se objekti s nula, jednim i dva argumenta (`cpp: 95, 101, 107`). Ispis iz tijela konstruktora pokazuje da se pri delegiranju najprije izvršava tijelo ciljnog konstruktora, a zatim tijelo delegirajućeg (`cpp: 40, 50, 58`). Dobiveni rasponi tlaka redom su 60–95, 50–95 i 40–110 bar.

**Važno:** lista inicijalizatora delegirajućeg konstruktora smije sadržavati samo poziv ciljnog konstruktora. Nije dopušteno u istoj listi dodatno inicijalizirati nijedan podatkovni član. Zakomentirani izraz `, mLowPressure{lowPressure}` uz konstruktor s jednim parametrom pokazuje nedopušten pokušaj; njegovim otkomentiranjem nastaje pogreška pri kompajliranju. Nakon što ciljni konstruktor završi, podatkovni članovi mogu se mijenjati u tijelu delegirajućeg konstruktora, ali u ovom primjeru to nije potrebno jer se odgovarajuće vrijednosti odmah prosljeđuju ciljnom konstruktoru.

**Kada koristiti delegirajući konstruktor?** Kada klasa nudi više načina stvaranja objekta, a ti konstruktori dijele istu inicijalizaciju, delegiranje izbjegava ponavljanje koda. Posebno je korisno ako se kasnije promijeni zajednički postupak inicijalizacije ili mu se doda provjera vrijednosti: tada ga je dovoljno održavati u jednom ciljnom konstruktoru. Ako konstruktori imaju sasvim različitu inicijalizaciju ili bi delegiranje samo zakompliciralo jednostavan kod, nije ga potrebno koristiti.

---

## 8. GDB analiza preopterećenih konstruktora

Demonstracija koristi `2_constructor_overloading.cpp` za praćenje poziva preopterećenih konstruktora. Cilj je provjeriti da se pri stvaranju različitih objekata poziva odgovarajući konstruktor te promotriti parametar konstruktora i inicijalizirano stanje objekta.

```text
E:\Files\G++\Lift\3-oop\01-klase-osnovno\01-04-konstruktor-i-inicijalizacija-objekta>gdb -silent 2_constructor_overloading.exe
Reading symbols from 2_constructor_overloading.exe...
(gdb) info functions ControlButton
All functions matching regular expression "ControlButton":

File 2_constructor_overloading.cpp:
27:     void ControlButton::ControlButton();
34:     void ControlButton::ControlButton(bool);
41:     bool ControlButton::is_pressed();
(gdb) break ControlButton::ControlButton()
Breakpoint 1 at 0x140001718: file 2_constructor_overloading.cpp, line 28.
(gdb) break ControlButton::ControlButton(bool)
Breakpoint 2 at 0x14000172f: file 2_constructor_overloading.cpp, line 35.
(gdb) run > NUL
Starting program: E:\Files\G++\Lift\3-oop\01-klase-osnovno\01-04-konstruktor-i-inicijalizacija-objekta\2_constructor_overloading.exe > NUL
[New Thread 1240.0x20d4]
[New Thread 1240.0x1554]
[New Thread 1240.0x2118]

Thread 1 hit Breakpoint 1, ControlButton::ControlButton (this=0x5ffe2f) at 2_constructor_overloading.cpp:28
28          : mPressed{false}
(gdb) bt
#0  ControlButton::ControlButton (this=0x5ffe2f) at 2_constructor_overloading.cpp:28
#1  0x00007ff723ca1769 in main () at 2_constructor_overloading.cpp:52
(gdb) p this
$1 = (ControlButton * const) 0x5ffe2f
(gdb) p mPressed
$2 = false
(gdb) n
30      }
(gdb) p mPressed
$3 = false
(gdb) c
Continuing.

Thread 1 hit Breakpoint 2, ControlButton::ControlButton (this=0x5ffe2e, pressed=true) at 2_constructor_overloading.cpp:35
35          : mPressed{pressed}
(gdb) bt
#0  ControlButton::ControlButton (this=0x5ffe2e, pressed=true) at 2_constructor_overloading.cpp:35
#1  0x00007ff723ca177a in main () at 2_constructor_overloading.cpp:53
(gdb) p pressed
$4 = true
(gdb) p this
$5 = (ControlButton * const) 0x5ffe2e
(gdb) p mPressed
$6 = false
(gdb) n
[New Thread 1240.0x19a0]
37      }
(gdb) p mPressed
$7 = true
(gdb) q
```

`info functions ControlButton` pokazuje obje verzije konstruktora. GDB ih prikazuje s oznakom `void`, iako C++ konstruktori nemaju povratni tip (to je način na koji GDB prikazuje konstruktore u ovom popisu).

Točke prekida su postavljene na:
```text
ControlButton::ControlButton()
ControlButton::ControlButton(bool)
```

Prva točka prekida pokazuje da `objUpButton{}` poziva defaultni konstruktor. Naredba `bt` potvrđuje da je konstruktor pozvan iz `main()` pri stvaranju objekta u retku 52. GDB se zaustavlja na `mPressed{false}` i prije izvršenja inicijalizacije člana `mPressed` prikazuje vrijednost `false`. Ta vrijednost još ne predstavlja valjano stanje člana, nego samo trenutačni sadržaj memorije. Nakon naredbe `n`, `mPressed` i dalje ima vrijednost `false`, ali je tada ta vrijednost rezultat inicijalizacije u defaultnom konstruktoru, kojim je objekt (tipka) postavljen u otpušteno stanje.

Druga točka prekida pokazuje da `objDownButton{true}` poziva konstruktor s parametrom `bool`. Prije izvršenja inicijalizacije `mPressed{pressed}` član još nije inicijaliziran vrijednošću parametra, pa tada prikazanu vrijednost `false` ne treba tumačiti kao njegovo valjano početno stanje. Nakon naredbe `n`, `mPressed` poprima vrijednost `true`, čime se vidi učinak liste inicijalizatora članova.