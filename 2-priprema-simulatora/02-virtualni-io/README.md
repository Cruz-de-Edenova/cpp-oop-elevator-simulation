# Virtualni I/O

Virtualni I/O predstavlja jednostavan komunikacijski sloj između budućeg upravljačkog programa i simulacije lifta. Njegova je zadaća omogućiti razmjenu logičkih stanja ulaznih i izlaznih signala bez simuliranja stvarnog mikrokontrolera, GPIO priključaka ili detalja stvarnog električnog upravljačkog kruga.

Ulazi i izlazi promatraju se iz perspektive upravljačkog programa: upravljački program čita ulaze i postavlja izlaze, dok simulacija lifta radi suprotno.

## Sadržaj

1. Uloga virtualnog I/O-a
2. Smjer signala
3. Ulazi upravljačkog programa
4. Izlazi upravljačkog programa
5. Organizacija programskog koda
6. Granice virtualnog I/O-a

**Prateći primjeri:**

- `virtual_io.h`
- `virtual_io.cpp`
- `main.cpp`

---

## 1. Uloga virtualnog I/O-a

Virtualni I/O odvaja upravljački program od simulacije lifta.

Pojednostavljeni odnos izgleda ovako:
```text
upravljački program <-> virtualni I/O <-> simulacija lifta
```

Virtualni I/O predstavlja zajedničko mjesto preko kojeg simulacija lifta i upravljački program razmjenjuju signale. Virtualni I/O samo čuva stanja signala.

Ulazi i izlazi nazivaju se iz **perspektive upravljačkog programa**:

- simulacija lifta postavlja ulazne signale u virtualnom I/O-u, a upravljački program ih čita
```text
simulacija lifta postavlja ulaze
      ↓
virtualni I/O
      ↓
upravljački program čita ulaze
```

- upravljački program postavlja izlazne signale u virtualnom I/O-u, a simulacija lifta ih čita
```text
upravljački program postavlja izlaze
      ↓
virtualni I/O
      ↓
simulacija lifta čita izlaze
```

---

## 2. Smjer signala

Smjerovi se određuju iz perspektive upravljačkog programa:
```text
simulacija lifta              |       upravljački program
                              |
UP tipka ---------------------|-----> ulaz
DOWN tipka -------------------|-----> ulaz
gornji granični prekidač -----|-----> ulaz
                              |
starter motora <--------------|------ izlaz
DOWN solenoid  <--------------|------ izlaz
```

Zbog toga isti signal ima različitu ulogu ovisno o strani s koje se promatra. Primjerice, stanje *UP* tipke simulacija postavlja, a upravljački program ga čita.

---

## 3. Ulazi upravljačkog programa

Predviđena su tri ulazna signala:

| Signal | Značenje |
| --- | --- |
| *UP* tipka | Zahtjev za podizanje platforme |
| *DOWN* tipka | Zahtjev za spuštanje platforme |
| Gornji granični prekidač | Platforma je dosegla podešenu maksimalno dopuštenu gornju visinu |

Upravljački program ta stanja samo čita. Njihove vrijednosti postavlja simulacija lifta.

---

## 4. Izlazi upravljačkog programa

Predviđena su dva izlazna signala:

| Signal | Značenje |
| --- | --- |
| Starter motora | Uključivanje pogona hidraulične pumpe |
| *DOWN* solenoid | Aktiviranje *DOWN* ventila za spuštanje platforme |

Vrijednosti tih signala postavlja upravljački program, a simulacija lifta ih čita i prema njima mijenja ponašanje simuliranog sustava.

---

## 5. Organizacija programskog koda

Virtualni I/O ostaje jednostavan proceduralni dio programa. Nema potrebe uvoditi klase samo radi predstavljanja pojedinačnih ulaza i izlaza.

Struktura koda je:
```text
virtual_io.h
virtual_io.cpp
main.cpp
```

`virtual_io.h` i `virtual_io.cpp` čine zajednički virtualni I/O sloj. **Datoteka `main.cpp` u ovoj temi služi samo kao demonstracijski i testni program kojim se provjerava rad virtualnog I/O-a u oba smjera.** Kasniji upravljački program i OOP simulacija koristit će isti `virtual_io.h` i `virtual_io.cpp`, ali će imati vlastitu programsku strukturu.

## 5.1. `virtual_io.h` i `virtual_io.cpp`

Datoteka `virtual_io.h` sadrži javno sučelje virtualnog I/O-a, odnosno deklaracije funkcija preko kojih upravljački program i simulacija razmjenjuju stanja signala (stanja signala nisu dosupna u H, već u CPP datoteci).

Datoteka `virtual_io.cpp` sadrži definicije tih funkcija i stanja signala. Stanja signala spremljena su u anonimnom *namespaceu* kako bi bila ograničena na tu jedinicu kompajliranja i kako im drugi dijelovi programa ne bi pristupali izravno.

Sve funkcije pripadaju glavnom *namespaceu* `ns_virtual_io`. Time se imena koja pripadaju virtualnom I/O-u grupiraju u zaseban opseg i izbjegava se njihovo miješanje s imenima iz drugih dijelova programa.

*Namespace* `ns_virtual_io` podijeljen je na dva ugniježđena *namespacea*:
```text
ns_virtual_io
├── ns_controller
└── ns_simulation
```

`ns_controller` sadrži funkcije koje koristi upravljački program:
```cpp
bool read_up_button();
bool read_down_button();
bool read_up_limit_switch();

void set_motor_starter(bool active);
void set_down_solenoid(bool active);
```

`ns_simulation` sadrži funkcije koje koristi simulacija lifta:
```cpp
void set_up_button(bool pressed);
void set_down_button(bool pressed);
void set_up_limit_switch(bool active);

bool read_motor_starter();
bool read_down_solenoid();
```

Ovakva podjela ne određuje je li signal ulaz ili izlaz prema nazivu *namespacea*, nego jasno pokazuje **koja strana koristi određenu funkciju**. Upravljački program čita svoje ulaze i postavlja svoje izlaze, dok simulacija postavlja ulaze upravljačkog programa i čita njegove izlaze.

U `.cpp` datotekama koje koriste virtualni I/O mogu se po potrebi definirati kraći *namespace aliasi*:
```cpp
namespace controller = ns_virtual_io::ns_controller;
namespace simulation = ns_virtual_io::ns_simulation;
```

Time se pozivi mogu pisati preglednije:
```cpp
controller::read_up_button();
simulation::set_up_button(true);
```

---

## 6. Granice virtualnog I/O-a

Virtualni I/O sadrži samo signale koji predstavljaju komunikaciju između upravljačkog programa i simuliranog lifta.

Fizička stanja koja nisu dostupna upravljačkom programu preko odgovarajućeg senzora ne pripadaju virtualnom I/O-u. Primjer je kontinuirana visina platforme: simulacija je mora poznavati kako bi izračunala položaj platforme, ali upravljački program za nju nema zaseban ulazni signal.

Također, u virtualni I/O zato se ne uključuju tlak, razina ulja, stanje HVF-a, stanje filtra ni drugi unutarnji podaci simulacije. Takvi će se podaci kasnije, prema potrebi, modelirati unutar OOP dijela simulatora kao dio unutarnjeg stanja odgovarajućih komponenti.
