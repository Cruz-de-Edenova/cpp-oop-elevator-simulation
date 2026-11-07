# 1d — Senzor tlaka: usporedba triju senzora

## Zadatak

1. Proširi klasu `PressureSensor` iz zadatka 1c konstruktorom bez argumenata koji postavlja donji prag na 60 bar, a gornji na 95 bar. Zadrži postojeći konstruktor s dva parametra i provjeru valjanosti pragova.
2. U `main()` zadrži senzore A i B te njihove provjere iz zadatka 1c. Dodaj senzor C stvoren bez argumenata, ispiši njegove početne pragove, zatim ih promijeni na 30 i 120 bar. Ispiši ishod promjene i nove pragove koristeći postojeće pomoćne funkcije.
3. Usporedi stanja svih triju senzora za isti skup vrijednosti tlaka kao u zadatku 1c. Rezultate prikaži u četiri poravnata stupca: tlak, senzor A, senzor B i senzor C.
4. Podijeli program u datoteke `pressure_sensor.h`, `pressure_sensor.cpp` i `main.cpp`. U zaglavlju deklariraj klasu i dodaj zaštitu od višestrukog uključivanja, u pripadnoj `.cpp` datoteci definiraj članske funkcije, a u `main.cpp` zadrži pomoćne funkcije, stvaranje objekata i konzolni ispis.

## Kratke upute kako riješiti zadatak

### Redoslijed rješavanja zadatka

1. **Podjela programa:** iz postojećeg `main.cpp` izdvoji deklaraciju klase `PressureSensor` u `pressure_sensor.h`, a definicije njezinih članskih funkcija u `pressure_sensor.cpp`. U `main.cpp` zadrži pomoćne funkcije i ispitivanje senzora.
2. **Konstruktor bez argumenata:** u klasu dodaj `PressureSensor()` koji inicijalizira `mLowPressure` na 60, a `mHighPressure` na 95. Postojeći konstruktor s parametrima ostavi nepromijenjen.
3. **Treći senzor:** u `main()` stvori `objSensorC{}`, ispiši njegove pragove te postojećom pomoćnom funkcijom pokušaj promijeniti pragove na 30 i 120 bar. Ponovno ispiši spremljene pragove.
4. **Tablični prikaz:** u postojećoj petlji postavljaj isti tlak svim trima senzorima i prilagodi ispis tako da se u zasebnim stupcima vidi stanje svakog senzora.
5. **Provjera programa:** kompajliraj oba `.cpp` izvora te provjeri da senzori A i B zadržavaju ponašanje iz zadatka 1c, senzor C prihvaća nove pragove i tablica prikazuje sva tri senzora.

### Konstruktor bez argumenata

Poziv `PressureSensor objSensorC{};` koristi konstruktor bez argumenata, koji postavlja početne pragove na 60 i 95 bar. Postojeći konstruktor s parametrima i dalje omogućuje zadavanje drukčijih pragova te, kao u zadatku 1c, postavlja iste zadane vrijednosti ako primi nevaljan par.
