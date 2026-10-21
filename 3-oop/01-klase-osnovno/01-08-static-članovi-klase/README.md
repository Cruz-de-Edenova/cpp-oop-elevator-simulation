# `static` članovi klase

Ova tema obrađuje `static` podatkovne članove i `static` članske funkcije. Nestatički podatkovni članovi pripadaju pojedinom objektu, dok `static` podatkovni član nije vezan uz pojedini objekt klase.

Primjeri koriste pojednostavljeni embedded model PWM kanala. Pretpostavlja se da dva prikazana kanala koriste isti hardverski PWM timer, pa imaju zajedničku PWM frekvenciju, dok svaki kanal može imati vlastiti radni ciklus. 

**Ključni pojmovi:**
- `static` podatkovni član (*static data member*)
- `static` članska funkcija (*static member function*)
- statičko trajanje pohrane (*static storage duration*)

---

## Sadržaj

1. `static` podatkovni član
   - 1.1. Deklaracija i definicija
   - 1.2. Zajedničko i pojedinačno stanje
2. `static` članska funkcija
   - 2.1. Funkcija bez pokazivača `this`
   - 2.2. Poziv preko imena klase
3. Primjer 1 — `static` podatkovni član
4. Primjer 2 — `static` članska funkcija
5. GDB analiza `static` člana i članske funkcije
   - 5.1. Ispis GDB-a
   - 5.2. Objašnjenje ispisa GDB-a

**Prateći primjeri:**
- **Primjer 1:** `1_static_data_member.cpp`
- **Primjer 2:** `2_static_member_function.cpp`

---

## 1. `static` podatkovni član

Nestatički podatkovni član pripada svakom objektu zasebno. U klasi `PwmChannel` to su:
```cpp
int mChannel;
int mDutyCyclePercent;
```
Svaki objekt zato može predstavljati drugi PWM kanal i imati vlastiti radni ciklus.

`static` podatkovni član nije vezan uz pojedini objekt. U primjerima je deklariran član:
```cpp
static int mFrequencyHz;
```
`mFrequencyHz` je jedan `static` podatkovni član zajednički svim objektima klase `PwmChannel`. U pojednostavljenom modelu ona predstavlja frekvenciju hardverskog PWM timera koju koriste oba kanala.

Odnos se može prikazati ovako:
```text
objChannel1
    mChannel           -> 1
    mDutyCyclePercent  -> 25 %

objChannel2
    mChannel           -> 2
    mDutyCyclePercent  -> 75 %

PwmChannel
    mFrequencyHz       -> 1000 Hz
```
`mFrequencyHz` ima statičko trajanje pohrane, pa njegova pohrana **traje tijekom cijelog izvođenja programa** i nije vezana uz životni vijek pojedinog objekta klase `PwmChannel`.

### 1.1. Deklaracija i definicija

Unutar definicije klase `static` podatkovni član deklarira se pomoću ključne riječi `static`:
```cpp
static int mFrequencyHz;
```

U primjerima se zatim zasebno definira i inicijalizira izvan definicije klase:
```cpp
int PwmChannel::mFrequencyHz{1000};
```

Pri toj definiciji ključna riječ `static` ne ponavlja se. Operator `::` kvalificira ime člana imenom klase `PwmChannel`.

U C++17 `static` podatkovni član može se deklarirati kao `inline static` i tada se može definirati i inicijalizirati unutar definicije klase. U ovoj temi koristi se zasebna definicija izvan klase kako bi razlika između deklaracije i definicije ostala jasno vidljiva.

### 1.2. Zajedničko i pojedinačno stanje

Članovi `mChannel` i `mDutyCyclePercent` opisuju pojedini objekt. Zato dva objekta mogu imati različite vrijednosti:
```cpp
PwmChannel objChannel1{1, 25};
PwmChannel objChannel2{2, 75};
```

Oba objekta istodobno koriste isti `mFrequencyHz`. Primjer namjerno modelira dva kanala istog PWM timera.

---

## 2. `static` članska funkcija

`static` članska funkcija također nije vezana uz pojedini objekt klase. U drugom primjeru deklarirane su dvije takve funkcije:
```cpp
static int get_frequency_hz();
static void set_frequency_hz(int frequencyHz);
```
Prva čita zajedničku frekvenciju, a druga je mijenja.

Definicije izvan klase više ne sadrže ključnu riječ `static`:
```cpp
int PwmChannel::get_frequency_hz()
{
    return mFrequencyHz;
}
```

```cpp
void PwmChannel::set_frequency_hz(int frequencyHz)
{
    mFrequencyHz = frequencyHz;
}
```
Obje funkcije mogu izravno pristupiti `static` podatkovnom članu `mFrequencyHz`.

### 2.1. Funkcija bez pokazivača `this`

Nestatička članska funkcija izvršava se nad konkretnim objektom i ima pokazivač `this`.
`static` članska funkcija nije povezana s konkretnim objektom pa nema pokazivač `this`.

U drugom primjeru zato nije dopušteno:
```cpp
// cout << this << '\n';
```

Bez konkretnog objekta `static` članska funkcija također ne može izravno pristupiti nestatičkom podatkovnom članu:
```cpp
// return mDutyCyclePercent;
```

Član `mDutyCyclePercent` pripada pojedinom objektu, a `get_frequency_hz()` nije pozvan nad određenim objektom.

S druge strane, `mFrequencyHz` je `static` podatkovni član pa mu `static` članska funkcija može izravno pristupiti:
```cpp
return mFrequencyHz;
```

`static` članska funkcija ne može se `const`-kvalificirati. `const` kvalifikacija nestatičke članske funkcije odnosi se na objekt nad kojim je funkcija pozvana, a `static` članska funkcija nije povezana s takvim objektom.

### 2.2. Poziv preko imena klase

Budući da za poziv `static` članske funkcije nije potreban objekt, prirodno ju je pozvati preko imena klase:
```cpp
PwmChannel::get_frequency_hz();
PwmChannel::set_frequency_hz(2000);
```

C++ dopušta poziv `static` članske funkcije i preko objekta, ali zapis s imenom klase jasnije pokazuje da funkcija nije vezana uz konkretnu instancu:
```cpp
objChannel1.get_frequency_hz();  // Dopušteno, ali manje jasno
PwmChannel::get_frequency_hz();  // Preporučeno korištenje
```

U drugom primjeru promjena:
```cpp
PwmChannel::set_frequency_hz(2000);
```
mijenja jednu zajedničku vrijednost. Nakon toga oba postojeća objekta pri ispisu koriste frekvenciju `2000 Hz`, dok njihovi pojedinačni radni ciklusi ostaju `25 %` i `75 %`.

---

## 3. Primjer 1 — `static` podatkovni član

Datoteka: `1_static_data_member.cpp`

| Novi koncept | Mjesto u kodu |
| --- | --- |
| nestatički i `static` podatkovni članovi | `cpp: 12-14` |
| definicija i inicijalizacija `static` člana | `cpp: 26` |
| pristup zajedničkom `static` podatkovnom članu iz članske funkcije | `cpp: 41` |
| dva objekta koriste isti `static` podatkovni član | `cpp: 50-54` |

U `cpp: 12-14` jasno su odvojene dvije vrste podataka. `mChannel` i `mDutyCyclePercent` pripadaju pojedinom objektu, dok je `mFrequencyHz` zajednički `static` podatkovni član.

U `cpp: 26` `mFrequencyHz` se definira izvan klase i inicijalizira vrijednošću `1000`.

Objekti u `cpp: 50-51` imaju različite brojeve kanala i različite radne cikluse:
```text
kanal 1 -> 25 %
kanal 2 -> 75 %
```
Ispis u `cpp: 53-54` pokazuje da oba objekta koriste istu frekvenciju `1000 Hz`.

Glavna svrha ovoga primjera je razlikovati **stanje pojedinog objekta** od **podatka zajedničkog svim objektima klase**.

---

## 4. Primjer 2 — `static` članska funkcija

Datoteka: `2_static_member_function.cpp`

| Novi koncept | Mjesto u kodu |
| --- | --- |
| deklaracije `static` članskih funkcija | `cpp: 21, 24` |
| definicija i inicijalizacija `static` podatkovnog člana | `cpp: 32` |
| definicije `static` članskih funkcija | `cpp: 43-52, 56-59` |
| nedostupan pokazivač `this` | `cpp: 46` |
| nedopušten pristup nestatičkom članu bez objekta | `cpp: 49` |
| pozivi `static` funkcija preko imena klase | `cpp: 80, 85, 88` |

Drugi primjer zadržava isti odnos između pojedinačnog i zajedničkog stanja, ali dodaje kontrolirani pristup zajedničkoj frekvenciji preko `static` članskih funkcija.

Početna frekvencija čita se pozivom:
```cpp
PwmChannel::get_frequency_hz()
```

Nakon ispisa početnog stanja zajednička se frekvencija mijenja:
```cpp
PwmChannel::set_frequency_hz(2000);
```

Promjena nije izvršena nad `objChannel1` ili `objChannel2`, nego nad zajedničkim stanjem klase. Zato oba objekta u `cpp: 90-91` prikazuju novu frekvenciju `2000 Hz`.

Radni ciklusi ostaju nepromijenjeni jer su `mDutyCyclePercent` nestatički podatkovni članovi i svaki objekt ima vlastitu vrijednost.

---

## 5. GDB analiza `static` člana i članske funkcije

Za ovu temu korisna je kratka GDB analiza drugog primjera. Njome se mogu povezati dvije važne osobine `static` članova:
- `mFrequencyHz` predstavlja jedan zajednički podatak
- `get_frequency_hz()` kao `static` članska funkcija nema pokazivač `this`

Program se kompajlira pomoću G++ kompajlera i pokreće u GDB-u:
```text
g++ -std=c++17 -g -O0 -Wall -Wextra -Wconversion -Werror 2_static_member_function.cpp -o 2_static_member_function.exe
gdb -silent 2_static_member_function.exe
```

### 5.1. Ispis GDB-a

```text
E:\Files\G++\Lift\3-oop\01-klase-osnovno\01-08-static-clanovi-klase>gdb -silent 2_static_member_function.exe
Reading symbols from 2_static_member_function.exe...
(gdb) break PwmChannel::get_frequency_hz
Breakpoint 1 at 0x14000173a: file 2_static_member_function.cpp, line 51.
(gdb) run > NUL
Starting program: E:\Files\G++\Lift\3-oop\01-klase-osnovno\01-08-static-clanovi-klase\2_static_member_function.exe > NUL
[New Thread 5152.0x1d78]
[New Thread 5152.0x1adc]
[New Thread 5152.0x2578]

Thread 1 hit Breakpoint 1, PwmChannel::get_frequency_hz () at 2_static_member_function.cpp:51
51          return mFrequencyHz;
(gdb) bt
#0  PwmChannel::get_frequency_hz () at 2_static_member_function.cpp:51
#1  0x00007ff618af1854 in main () at 2_static_member_function.cpp:80
(gdb) p mFrequencyHz
$1 = 1000
(gdb) p &mFrequencyHz
$2 = (int *) 0x7ff618af4010 <PwmChannel::mFrequencyHz>
(gdb) c
Continuing.

Thread 1 hit Breakpoint 1, PwmChannel::get_frequency_hz () at 2_static_member_function.cpp:51
51          return mFrequencyHz;
(gdb) bt
#0  PwmChannel::get_frequency_hz () at 2_static_member_function.cpp:51
#1  0x00007ff618af18b0 in main () at 2_static_member_function.cpp:88
(gdb) p mFrequencyHz
$3 = 2000
(gdb) p &mFrequencyHz
$4 = (int *) 0x7ff618af4010 <PwmChannel::mFrequencyHz>
(gdb) p this
No symbol "this" in current context.
(gdb) c
Continuing.
[New Thread 5152.0x52c]
[New Thread 5152.0x28b0]
[Thread 5152.0x1d78 exited with code 0]
[Thread 5152.0x52c exited with code 0]
[Thread 5152.0x28b0 exited with code 0]
[Thread 5152.0x2578 exited with code 0]
[Thread 5152.0x1adc exited with code 0]
[Inferior 1 (process 5152) exited normally]
```

### 5.2. Objašnjenje ispisa GDB-a

Točka prekida postavlja se na `static` člansku funkciju:
```text
(gdb) break PwmChannel::get_frequency_hz
(gdb) run > NUL
```

Naredba:
```text
(gdb) bt
```
prikazuje stog poziva funkcija. `Frame #0` predstavlja aktivnu funkciju `PwmChannel::get_frequency_hz()`, dok `frame #1` pokazuje da je funkcija pozvana iz `main()` i navodi redak na kojem se nalazi poziv.

Pri prvom zaustavljanju zajednička frekvencija još ima početnu vrijednost 1000:
```text
(gdb) p mFrequencyHz
```

Provjera adrese `static` podatkovnog člana:
```text
(gdb) p &mFrequencyHz
```

Nakon nastavka izvođenja:
```text
(gdb) c
```
program poziva `set_frequency_hz(2000)`, a zatim ponovno ulazi u `get_frequency_hz()`.

Tada:
```text
(gdb) p mFrequencyHz
```
pokazuje vrijednost 2000.

Ponovljena naredba:
```text
(gdb) p &mFrequencyHz
```
pokazuje istu adresu kao pri prvom zaustavljanju. Konkretna vrijednost adrese ovisi o izvođenju programa; važna je činjenica da se radi o istom `static` podatkovnom članu prije i nakon promjene njegove vrijednosti.

Kada se unutar `get_frequency_hz()` pokrene naredba:
```text
(gdb) p this
```
GDB je ispisao poruku `No symbol "this" in current context.`
To je zato što `static` članska funkcija nema pokazivač `this`, pa u tom kontekstu ne postoji objekt na koji bi `this` pokazivao.

**Sažetak analize**

U ovoj analizi koriste se tri korisne GDB provjere:
- `bt` — prikazuje stog poziva funkcija i redak iz kojeg je `get_frequency_hz()` pozvana
- `p mFrequencyHz` i `p &mFrequencyHz` — prikazuju vrijednost i adresu zajedničkog `static` podatkovnog člana
- `p this` — pokazuje da u `static` članskoj funkciji nema pokazivača `this`