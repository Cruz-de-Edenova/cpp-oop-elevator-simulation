# Članska funkcija i pokazivač `this`

U prethodnoj temi uvedeni su klasa, objekt, podatkovni član i članska funkcija. Ova tema nastavlja na te pojmove i detaljnije objašnjava kako se članske funkcije deklariraju, definiraju i povezuju s konkretnim objektom nad kojim rade.

Prvi primjer koristi klase `ControlPanel` i `ControllerOutputs`. Drugi primjer koristi klasu `ControllerSignalSnapshot` kako bi pokazao vezu između poziva članske funkcije i pokazivača `this`.

## Sadržaj

1. Članska funkcija klase
2. Deklaracija i definicija članske funkcije
3. Operator `::`
4. Poziv članske funkcije preko objekta
5. Pokazivač `this`
6. Promatranje pokazivača `this` u GDB-u
7. Sažetak

**Prateći primjeri:**
- `01_member_function.cpp`
- `02_this_pointer.cpp`

---

## 1. Članska funkcija klase

U prethodnoj temi člansku funkciju upoznali smo kao C++ mehanizam kojim implementiramo ponašanje objekta. Ovdje nas prvenstveno zanima kako je članska funkcija povezana s klasom i objektom nad kojim je pozvana.

Klasa `ControlPanel` iz prvog primjera sadrži tri članske funkcije:
```cpp
class ControlPanel
{
private:
    bool mUpButtonPressed;
    bool mDownButtonPressed;

public:
    void set_up_button(bool pressed);
    void set_down_button(bool pressed);
    void print_state();
};
```
Druga klasa ima drukčije podatke i ponašanja:
```cpp
class ControllerOutputs
{
private:
    bool mMotorStarter;
    bool mDownSolenoid;

public:
    void set_motor_starter(bool energized);
    void set_down_solenoid(bool energized);
    void print_state();
};
```
Obje klase imaju člansku funkciju naziva `print_state()`. To nije problem jer svaka funkcija pripada svojoj klasi:
```text
ControlPanel::print_state()
ControllerOutputs::print_state()
```

---

## 2. Deklaracija i definicija članske funkcije

U prethodnim jednostavnim primjerima tijelo članske funkcije nalazilo se izravno unutar definicije klase. U ovoj temi odvajamo **deklaraciju** članske funkcije od njezine **definicije**.

Deklaracija se nalazi unutar klase:
```cpp
void set_up_button(bool pressed);
```
Ona navodi naziv funkcije, povratni tip i parametre, ali ne sadrži tijelo funkcije.

Definicija se nalazi izvan definicije klase:
```cpp
void ControlPanel::set_up_button(bool pressed)
{
    mUpButtonPressed = pressed;
}
```
Na isti način definirane su i ostale članske funkcije:
```cpp
void ControlPanel::set_down_button(bool pressed)
{
    mDownButtonPressed = pressed;
}

void ControlPanel::print_state()
{
    cout << "UP tipka:   "
         << (mUpButtonPressed ? "pritisnuta" : "otpustena") << '\n';
    cout << "DOWN tipka: "
         << (mDownButtonPressed ? "pritisnuta" : "otpustena") << '\n';
}
```
Takvo odvajanje deklaracije od definicije postaje posebno važno kada se klasa kasnije podijeli između `.h` i `.cpp` datoteka. U ovom jednostavnom primjeru sve se još nalazi u jednoj datoteci kako bi fokus ostao na članskim funkcijama.

---

## 3. Operator `::`

Kada člansku funkciju definiramo izvan definicije klase, potrebno je navesti kojoj klasi funkcija pripada.

U izrazu:
```cpp
void ControlPanel::set_up_button(bool pressed)
```
dio:
```cpp
ControlPanel::
```
povezuje definiciju funkcije s klasom `ControlPanel`.

Operator `::` (*scope resolution operator*) služi za kvalificiranje imena navođenjem njegova opsega, primjerice *namespacea* ili klase.

Njegovu ulogu posebno dobro pokazuje funkcija `print_state()`, jer obje klase iz prvog primjera imaju funkciju istog imena:
```cpp
void ControlPanel::print_state()
{
    // ...
}

void ControllerOutputs::print_state()
{
    // ...
}
```
Kvalificirani nazivi:
```text
ControlPanel::print_state
ControllerOutputs::print_state
```
jasno određuju kojoj klasi pojedina funkcija pripada.

---

## 4. Poziv članske funkcije preko objekta

Člansku funkciju pozivamo preko konkretnog objekta pomoću operatora `.`:
```cpp
ControlPanel objControlPanel;

objControlPanel.set_up_button(true);
objControlPanel.set_down_button(false);
objControlPanel.print_state();
```
Klasa određuje koje su članske funkcije dostupne, a objekt određuje nad čijim se stanjem funkcija izvršava.

U prvom primjeru `main()` sadrži dvije odvojene demonstracijske cjeline:
```cpp
// Demonstracija članskih funkcija klase ControlPanel
{
    ControlPanel objControlPanel;

    objControlPanel.set_up_button(true);
    objControlPanel.set_down_button(false);
    objControlPanel.print_state();
}
```
Vitičaste zagrade stvaraju zaseban lokalni opseg i istodobno vizualno odvajaju demonstraciju od sljedeće cjeline.

Druga cjelina koristi objekt klase `ControllerOutputs`:
```cpp
// Demonstracija članskih funkcija klase ControllerOutputs
{
    ControllerOutputs objControllerOutputs;

    objControllerOutputs.set_motor_starter(true);
    objControllerOutputs.set_down_solenoid(false);
    objControllerOutputs.print_state();
}
```
Ispis programa:
```text
UP tipka:   pritisnuta
DOWN tipka: otpustena
------------------------------
Motor starter: ukljucen
DOWN solenoid: iskljucen
```
Budući da konstruktore još ne obrađujemo, prije ispisa postavljamo sva stanja koja će pripadajuća funkcija čitati.

---

## 5. Pokazivač `this`

Nestatička članska funkcija izvršava se nad konkretnim objektom. Unutar takve funkcije skriveni pokazivač `this` pokazuje na objekt nad kojim je funkcija pozvana.

Primjer:
```cpp
objRaiseSnapshot.set_outputs(true, false);
```
Unutar `set_outputs()` pokazivač `this` pokazuje na `objRaiseSnapshot`.

```text
objRaiseSnapshot.set_outputs(...)
        |
        +-- this pokazuje na objRaiseSnapshot
```

### 5.1. Implicitno i eksplicitno korištenje `this`

Članovima objekta nad kojim je članska funkcija pozvana najčešće pristupamo implicitno:
```cpp
void ControllerSignalSnapshot::set_inputs(
    bool upPressed,
    bool downPressed,
    bool limitActive)
{
    mUpButtonPressed = upPressed;
    mDownButtonPressed = downPressed;
    mUpLimitSwitchActive = limitActive;
}
```
Kompajler zna da se `mUpButtonPressed`, `mDownButtonPressed` i `mUpLimitSwitchActive` odnose na objekt nad kojim je funkcija pozvana.

Isti se pristup može napisati eksplicitno pomoću `this->`. U drugom primjeru to koristimo kada su nazivi članova i parametara vrlo slični:
```cpp
void ControllerSignalSnapshot::set_outputs(
    bool motorStarter,
    bool downSolenoid)
{
    this->mMotorStarter = motorStarter;
    this->mDownSolenoid = downSolenoid;
}
```
Ovdje `this->mMotorStarter` jasno označava podatkovni član objekta, dok je `motorStarter` parametar funkcije.

Preko `this->` može se pozvati i nestatička članska funkcija:
```cpp
void ControllerSignalSnapshot::print_snapshot()
{
    this->print_state();
}
```
Poziv:
```cpp
objRaiseSnapshot.print_snapshot();
```
znači da `this` unutar `print_snapshot()` pokazuje na `objRaiseSnapshot`, pa se `this->print_state()` također izvršava nad tim objektom.

Eksplicitni `this->` najčešće nije potreban. Koristan je kada razjašnjava na koji se objekt ili član izraz odnosi.

### 5.2. Razlikovanje istoimenog podatkovnog člana i parametra

U ovom projektu prefiks `m` već sprječava da podatkovni član i parametar imaju potpuno isto ime. Bez takve konvencije moguća je situacija u kojoj parametar sakrije istoimeni podatkovni član.

Primjer:
```cpp
class Counter
{
private:
    int value;

public:
    void set_value(int value)
    {
        value = value;
    }
};
```
Ovaj kod je sintaktički ispravan, ali oba pojavljivanja imena `value` odnose se na parametar funkcije. Podatkovni član objekta zato se ne mijenja.

Najčešći i najjasniji način pristupa istoimenom podatkovnom članu jest eksplicitni `this->`:
```cpp
void set_value(int value)
{
    this->value = value;
}
```
Odnos možemo prikazati ovako:
```text
this->value = value;
      |         |
    član     parametar
```
U ovom slučaju `this->value` označava podatkovni član objekta, dok nekvalificirano ime `value` označava parametar funkcije.

### 5.3. Gdje se `this` ne može koristiti

Pokazivač `this` nije dostupan u **statičkoj** članskoj funkciji jer statička funkcija nije povezana s konkretnim objektom:
```cpp
class ControllerSignalSnapshot
{
public:
    static void print_address()
    {
        cout << this << '\n'; // Pogreška pri kompajliranju
    }
};
```
Statička članska funkcija zato nema pokazivač `this`.

`this` nije dostupan ni u običnoj funkciji koja nije nestatička članska funkcija:
```cpp
void print_address()
{
    cout << this << '\n'; // Pogreška pri kompajliranju
}
```
Sama činjenica da se neki zapis nalazi unutar definicije klase također ne znači da je `this` dopušten u svakom takvom kontekstu. Primjerice, ne može se koristiti kao zadani argument članske funkcije:
```cpp
class ControlPanel
{
private:
    bool mUpButtonPressed;

public:
    void set_up_button(bool pressed = this->mUpButtonPressed);
    //                              ^ Pogreška pri kompajliranju
};
```
Za ovu temu dovoljno je povezati `this` s konkretnim objektom i njegovim nestatičkim članskim funkcijama. C++ dopušta `this` i u nekim posebnim kontekstima povezanim s inicijalizacijom članova, koji će se obrađivati kasnije.

### 5.4. Vrijednost pokazivača `this`

Vrijednost pokazivača `this` jednaka je adresi objekta nad kojim je članska funkcija pozvana.

U drugom primjeru:
```cpp
cout << "&objRaiseSnapshot: " << &objRaiseSnapshot << '\n';
objRaiseSnapshot.print_this_address();
```
članska funkcija ispisuje:
```cpp
void ControllerSignalSnapshot::print_this_address()
{
    cout << "this:              " << this << '\n';
}
```
Tipičan rezultat:
```text
&objRaiseSnapshot: 0x...
this:              0x...
```
Za drugi objekt dobiva se druga adresa:
```text
&objLowerSnapshot: 0x...
this:              0x...
```
Dakle, ista definicija članske funkcije može raditi nad različitim objektima jer `this` pri svakom pozivu pokazuje na odgovarajući objekt.

---

## 6. Promatranje pokazivača `this` u GDB-u

Pokazivač `this` možemo neposredno promatrati tijekom izvođenja programa.

Program kompajliramo s informacijama za debugging:
```text
g++ -std=c++17 -g -O0 -Wall -Wextra -Wconversion -Werror 02_this_pointer.cpp -o 02_this_pointer.exe
```

```text
E:\Files\G++\Lift\3-oop\01-klase-osnovno\01-02-clanska-funkcija-i-pokazivac-this>gdb -silent 02_this_pointer.exe
Reading symbols from 02_this_pointer.exe...
(gdb) break ControllerSignalSnapshot::print_this_address
Breakpoint 1 at 0x14000192e: file 02_this_pointer.cpp, line 75.
(gdb) run > NUL
Starting program: E:\Files\G++\Lift\3-oop\01-klase-osnovno\01-02-clanska-funkcija-i-pokazivac-this\02_this_pointer.exe > NUL
[New Thread 1652.0x1ce0]
[New Thread 1652.0x2acc]
[New Thread 1652.0x68c]

Thread 1 hit Breakpoint 1, ControllerSignalSnapshot::print_this_address (this=0x5ffe0b) at 02_this_pointer.cpp:75
75          cout << "this:              " << this << '\n';
(gdb) list 72,76
72      // Ispisuje adresu objekta na koji pokazuje this
73      void ControllerSignalSnapshot::print_this_address()
74      {
75          cout << "this:              " << this << '\n';
76      }
(gdb) print this
$1 = (ControllerSignalSnapshot * const) 0x5ffe0b
(gdb) up
#1  0x00007ff659a41a7e in demonstrate_this_address () at 02_this_pointer.cpp:111
111         objRaiseSnapshot.print_this_address();
(gdb) print &objRaiseSnapshot
$2 = (ControllerSignalSnapshot *) 0x5ffe0b
(gdb) c
Continuing.

Thread 1 hit Breakpoint 1, ControllerSignalSnapshot::print_this_address (this=0x5ffe06) at 02_this_pointer.cpp:75
75          cout << "this:              " << this << '\n';
(gdb) print this
$3 = (ControllerSignalSnapshot * const) 0x5ffe06
(gdb) up
#1  0x00007ff659a41abc in demonstrate_this_address () at 02_this_pointer.cpp:114
114         objLowerSnapshot.print_this_address();
(gdb) print &objLowerSnapshot
$4 = (ControllerSignalSnapshot *) 0x5ffe06
(gdb) q
```

### 6.1. Kratka objašnjenja *debugginga*

Postavljanje prekidne točke na funkciju koja ispisuje `this`:
```text
(gdb) break ControllerSignalSnapshot::print_this_address
```

Kada se izvođenje zaustavi unutar članske funkcije:
```text
(gdb) print this
```
GDB ispisuje adresu trenutnog objekta, primjerice:
```text
$1 = 0x...
```
Za pregled pozivatelja pomaknemo se jedan "okvir" funkcije prema gore na stogu poziva funkcija:
```text
(gdb) up
```
U funkciji `demonstrate_this_address()` možemo provjeriti adresu objekta koji je pozvao člansku funkciju:
```text
(gdb) print &objRaiseSnapshot
```
Ta adresa odgovara prethodno ispisanoj vrijednosti `this`.

Nastavimo izvođenje:
```text
(gdb) continue
```
Program se ponovno zaustavlja pri pozivu `print_this_address()` za drugi objekt. Ovdje možemo ponoviti postupak analogno kao kod prethodnog objekta.

Time GDB izravno pokazuje:
```text
isti kod članske funkcije
        |
        +-- prvi poziv  -> this pokazuje na prvi objekt
        |
        +-- drugi poziv -> this pokazuje na drugi objekt
```

---

## 7. Sažetak

### 1. Deklaracija i definicija članske funkcije

Članska funkcija može biti deklarirana unutar klase:
```cpp
void set_up_button(bool pressed);
```
a definirana izvan klase:
```cpp
void ControlPanel::set_up_button(bool pressed)
{
    mUpButtonPressed = pressed;
}
```

### 2. Operator `::`

Operator `::` koristi se za kvalificiranje imena. Pri definiranju članske funkcije izvan klase njime navodimo kojoj klasi funkcija pripada:
```text
ControlPanel::print_state()
ControllerOutputs::print_state()
```

### 3. Objekt i članska funkcija

Istu člansku funkciju mogu pozvati različiti objekti:
```cpp
objRaiseSnapshot.set_outputs(true, false);
objLowerSnapshot.set_outputs(false, true);
```
Svaki poziv radi nad stanjem pripadajućeg objekta.

### 4. Pokazivač `this`

Unutar nestatičke članske funkcije `this` pokazuje na objekt nad kojim je funkcija pozvana.

Preko `this->` možemo pristupiti podatkovnom članu:
```cpp
this->mMotorStarter = motorStarter;
```
ali i pozvati drugu nestatičku člansku funkciju istog objekta:
```cpp
this->print_state();
```
U ovom primjeru eksplicitni zapis `this->` služi prvenstveno za jasno pokazivanje veze između članske funkcije i konkretnog objekta nad kojim se izvršava.
