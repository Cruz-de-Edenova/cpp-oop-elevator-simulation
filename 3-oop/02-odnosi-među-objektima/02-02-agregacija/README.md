# Agregacija

Agregacija (*aggregation*) je odnos među objektima u kojem jedan objekt povezuje druge, samostalno postojeće objekte bez preuzimanja vlasništva nad njima. U primjerima se odnos ostvaruje referencama ili pokazivačima.

**Ključni pojmovi:**

- agregacija (*aggregation*)
- nevlasnički odnos (*non-owning relationship*)
- neovisan životni vijek objekata
- referenca i pokazivač kao podatkovni članovi
- viseća referenca i viseći pokazivač (*dangling reference*, *dangling pointer*)

---

## 1. Agregacija

### 1.1. Što je agregacija?

- **Odnos:** jedan objekt okuplja ili povezuje objekte koji mogu postojati samostalno.
- **Vlasništvo:** objekt koji uspostavlja vezu nije odgovoran za uništavanje povezanih objekata.
- **Životni vijek:** povezani objekti mogu postojati prije njegova stvaranja i nakon njegova uništavanja.
- **C++ mehanizam:** reference ili pokazivači mogu ostvariti takav odnos, ali sami po sebi ne znače agregaciju.

### 1.2. Usporedba kompozicije i agregacije

| Svojstvo | Kompozicija | Agregacija |
| --- | --- | --- |
| Vlasništvo | Objekt posjeduje svoje objekte kao podatkovne članove. | Objekt ne posjeduje povezane objekte. |
| Životni vijek | Objekti koji su podatkovni članovi uništavaju se s objektom koji ih sadrži. | Povezani objekti mogu postojati neovisno o objektu koji ih koristi. |
| Mehanizam u primjerima | Podatkovni članovi objektnog tipa. | Reference ili pokazivači na zasebne objekte. |

- Samo pohranjivanje reference ili pokazivača ne dokazuje agregaciju; važni su odnos i odgovornost za životni vijek.

### 1.3. Primjeri agregacije

Mogući primjeri agregacije, pod uvjetom da povezani objekti imaju neovisno vlasništvo:

- **Mobilni robot — baterija:** objekt robota koristi zasebno stvoren objekt zamjenjive baterije.
- **Upravljački sustav — senzorski moduli:** objekt sustava povezuje zasebne objekte modula.
- **Skladište — rezervni dijelovi:** objekt skladišta povezuje se s objektima koji predstavljaju rezervne dijelove, koji postoje neovisno o skladištu.

---

## 2. Konstrukcija i prednosti agregacije

**Postupak:** odrediti odnos → provjeriti samostalnost objekata → utvrditi vlasništvo → odabrati referencu ili pokazivač → osigurati da povezani objekti postoje tijekom korištenja.
- **Referenca:** prikladna za obaveznu vezu koja se nakon inicijalizacije ne preusmjerava.
- **Pokazivač:** omogućuje praznu (`nullptr`) ili promjenjivu vezu; ne podrazumijeva vlasništvo.
- **Sigurnost:** ni referenca ni pokazivač ne mogu automatski prepoznati da je povezani objekt uništen. Program mora osigurati da se uništenom objektu ne pristupa.
- Primjeri `a` prikazuju jednostavnu implementaciju agregacije, dok primjeri `b` proširuju demonstraciju i prikazuju njezine prednosti.

### 2.1. Primjer 1a — Agregacija pomoću reference

Datoteka: [1a_agregacija_reference.cpp](1a_agregacija_reference.cpp) — obavezna veza s postojećim objektom.

| Ključni koncepti i mehanizmi | Mjesto u kodu |
| --- | --- |
| Referenca kao podatkovni član | `cpp: 35` |
| Inicijalizacija reference u konstruktoru | `cpp: 39-42` |
| Stvaranje zasebnih objekata i njihovo povezivanje | `cpp: 59, 60` |

- `MobileRobot` pristupa postojećem objektu `Battery`, ali nije odgovoran za njegovo uništavanje.

### 2.2. Primjer 1b — Dvije grupe sa zajedničkim objektom (reference)

Datoteka: [1b_agregacija_reference.cpp](1b_agregacija_reference.cpp) — dvije grupe sa zajedničkim objektom.

| Ključni koncepti i mehanizmi | Mjesto u kodu |
| --- | --- |
| Reference kao podatkovni članovi | `cpp: 41, 42` |
| Inicijalizacija referenci i pristup objektima | `cpp: 46-50; 53-57` |
| Dvije različite grupe sa zajedničkim objektom | `cpp: 67-73` |
| Promjena zajedničkog objekta i ponovno očitavanje | `cpp: 82-87` |
| Pristup objektu nakon uništavanja grupa  | `cpp: 92` |

**Prednosti prikazane primjerom:**

- **Bez kopiranja:** grupe koriste već stvorene objekte `TemperatureSensor`.
- **Dijeljenje objekta:** `objMotorSensor` povezan je s obje grupe, uz različite druge objekte.
- **Aktualno stanje:** promjena temperature motora s `58` na `55` mijenja prosjek prve grupe s `52.5` na `51`, a druge sa `60` na `58.5`.
- **Neovisan životni vijek:** izlaskom iz bloka uništavaju se oba objekta klase `SensorGroup`, dok sva tri objekta klase `TemperatureSensor` nastavljaju postojati.

`const TemperatureSensor&` ne dopušta promjenu objekta preko te reference, ali se njegovo stanje može mijenjati drugim nekonstantnim pristupom.

### 2.3. Primjer 2a — Agregacija pomoću pokazivača

Datoteka: [2a_agregacija_pokazivaci.cpp](2a_agregacija_pokazivači.cpp) — naknadno povezivanje objekata.

| Ključni koncepti i mehanizmi | Mjesto u kodu |
| --- | --- |
| Pokazivač kao podatkovni član | `cpp: 35` |
| Početna prazna veza i naknadno povezivanje | `cpp: 39-48` |
| Provjera `nullptr` prije pristupa | `cpp: 53` |
| Prosljeđivanje adrese postojećeg objekta | `cpp: 77` |

### 2.4. Primjer 2b — Dvije grupe sa zajedničkim objektom (pokazivači)

Datoteka: [2b_agregacija_pokazivaci.cpp](2b_agregacija_pokazivači.cpp) — isti odnos kao u primjeru 1b, pomoću pokazivača.

| Ključni koncepti i mehanizmi | Mjesto u kodu |
| --- | --- |
| Pokazivači kao podatkovni članovi | `cpp: 41, 42` |
| Inicijalizacija pokazivača i pristup objektima | `cpp: 46-50; 53-57` |
| Dvije različite grupe sa zajedničkim objektom | `cpp: 67-73` |
| Promjena zajedničkog objekta i ponovno očitavanje | `cpp: 82-87` |
| Pristup objektu nakon uništavanja grupa | `cpp: 92` |

- Oba proširena primjera imaju jednak rezultat. Razlikuje se **način povezivanja**, ne prednosti agregacije.
- `get_average_temperature()` u primjeru 2b pretpostavlja dva valjana pokazivača; ne provjerava `nullptr`.

---

## 3. Primjer 3 — Neovisan životni vijek objekata

Datoteka: [3_sensor_lifetime.cpp](3_sensor_lifetime.cpp) — tablični prikaz adresa objekata tijekom konstrukcije, povezivanja i uništavanja.

Tablični ispis omogućuje praćenje istih objekata tijekom njihova životnog vijeka i pokazuje da uništavanje grupe ne uzrokuje uništavanje povezanih senzora.

- **Identitet objekata:** adrese senzora ispisane u njihovim konstruktorima jednake su adresama dobivenima preko referenci u objektu `SensorGroup`. Time se potvrđuje da grupa koristi postojeće objekte, a ne njihove kopije.
- **Životni vijek grupe:** izlaskom iz unutarnjeg bloka uništava se `objSensorGroup`, dok `objMotorSensor` i `objBearingSensor` nastavljaju postojati.
- **Životni vijek senzora:** pri izlasku iz funkcije `main()` uništavaju se oba senzora, obrnutim redoslijedom konstrukcije — prvo `lezaj`, zatim `motor`.
- **Usporedba adresa:** pokazivač `this` u konstruktorima i destruktorima označava adresu pripadajućeg objekta, a ne adresu konstruktora ili destruktora kao funkcije (adrese njihovih strojnih instrukcija mogu se pregledati pomoću GDB-a, ali nisu relevantne za razumijevanje agregacije).

---

## 4. Tipične greške

- **Viseća referenca:** objekt na koji se referenca odnosi više ne postoji, ali drugi objekt i dalje sadrži referencu na njega.
- **Viseći pokazivač:** objekt na koji pokazivač upućuje je uništen, ali pokazivač i dalje sadrži njegovu adresu.

**Prateći primjeri viseće reference i visećeg pokazivača:**

- [Viseća referenca](dodatak/viseća_referenca.cpp) — privremeni objekt `Battery` uništava se nakon završetka naredbe kojom se stvara objekt `MobileRobot`, čime nastaje viseća referenca.
- [Viseći pokazivač](dodatak/viseći_pokazivač.cpp) — objekt `Battery` uništava se izlaskom iz bloka, dok `MobileRobot` i dalje čuva njegovu adresu.

| Dio demonstracije | `viseca_referenca.cpp` | `viseci_pokazivac.cpp` |
| --- | --- | --- |
| Povezivanje s objektom `Battery` | `cpp: 70; 74` | `cpp: 85` |
| Ispis adrese pri povezivanju | `cpp: 49, 50` | `cpp: 55, 56` |
| Ispis adrese u destruktoru `Battery` | `cpp: 25` | `cpp: 25` |
| Pristup objektu nakon njegova uništavanja (namjerni UB) | `cpp: 78` | `cpp: 93` |

### 4.1. Privremeni objekt i viseća referenca

```cpp
MobileRobot objRobot{Battery{85}};
```

- `Battery{85}` stvara privremeni objekt (*temporary object*) koji se prosljeđuje konstruktoru `MobileRobot(const Battery&)`.
- Privremeni objekt povezan s referencom koja je parametar konstruktora postoji do kraja **punog izraza** (*full-expression*), odnosno do završetka naredbe na znaku `;`.
- Inicijalizacija podatkovnog člana `mBattery` ne produljuje životni vijek privremenog objekta `Battery`. Objekt `MobileRobot` nastavlja postojati, ali njegov podatkovni član `mBattery` postaje viseća referenca.
- Ispisi adresa u konstruktoru `MobileRobot` i destruktoru `Battery` potvrđuju da je riječ o istom objektu `Battery`. Nakon njegova uništavanja podatkovni član `mBattery` ostaje viseća referenca.
- **Ispravno:** najprije stvoriti objekt `Battery objBattery{85};`, a zatim objekt `MobileRobot objRobot{objBattery};`.

### 4.2. Viseći pokazivač

- Pokazivač nakon uništavanja povezanog objekta ne postaje automatski `nullptr`. Nevaljana veza može se ukloniti izričitim postavljanjem pokazivača na `nullptr`. Sama provjera `!= nullptr` ne potvrđuje da objekt na koji pokazivač upućuje još postoji.
- U sigurnoj varijanti nakon izlaska iz bloka uklanja se nevaljana veza naredbom `set_battery(nullptr)` prije sljedećeg pristupa.
- Pristup uništenom objektu preko viseće reference ili pokazivača uzrokuje **nedefinirano ponašanje** (*undefined behavior*). Program se može srušiti, ispisati pogrešne podatke ili naizgled raditi ispravno.

### 4.3. Kompajliranje sigurnih i opasnih varijanti

Bez `DEMONSTRATE_UB` nevaljani se pristupi izbjegavaju; opcija `-DDEMONSTRATE_UB` uključuje namjernu demonstraciju nedefiniranog ponašanja:

```text
g++ -std=c++17 -g -O0 -Wall -Wextra -Wconversion -Werror viseca_referenca.cpp -o referenca_sigurno.exe
g++ -std=c++17 -g -O0 -Wall -Wextra -Wconversion -Werror -DDEMONSTRATE_UB viseca_referenca.cpp -o referenca_ub.exe
g++ -std=c++17 -g -O0 -Wall -Wextra -Wconversion -Werror viseci_pokazivac.cpp -o pokazivac_sigurno.exe
g++ -std=c++17 -g -O0 -Wall -Wextra -Wconversion -Werror -DDEMONSTRATE_UB viseci_pokazivac.cpp -o pokazivac_ub.exe
```
