# 1b — Senzor tlaka: vlastiti pragovi

## Zadatak

1. Proširi klasu `PressureSensor` iz zadatka 1a tako da svaki objekt ima vlastiti donji i gornji prag tlaka. Umjesto zajedničkih konstanti, pragove spremi u privatne podatkovne članove.
2. Omogući zadavanje obaju pragova konstruktorom i njihovo čitanje javnim `const` članskim funkcijama. Prilagodi funkcije `is_low()` i `is_high()` tako da uspoređuju spremljeni tlak s pragovima pojedinog objekta.
3. U `main()` stvori senzor s donjim pragom 50 bar i gornjim pragom 100 bar te ispiši oba praga.
4. Zadrži tablični prikaz stanja tlaka iz zadatka 1a, ali provjeri vrijednosti `{25, 30, 45, 55, 60, 74, 95, 97, 100, 105, 120, 125}`.

## Kratke upute kako riješiti zadatak

### Redoslijed rješavanja zadatka

1. **Podatkovni članovi:** ukloni konstante `kLowPressure` i `kHighPressure` iz zadatka 1a te dodaj privatne članove `mLowPressure` i `mHighPressure`. Postojeći član `mPressureBar` zadrži.
2. **Konstruktor:** dodaj `PressureSensor(int lowPressure, int highPressure)` i inicijaliziraj pragove pomoću liste inicijalizatora članova.
3. **Članske funkcije:** dodaj `get_low_pressure() const` i `get_high_pressure() const`. Prilagodi `is_low() const` i `is_high() const` za korištenje pragova spremljenih u objektu.
4. **Provjera programa:** u `main()` stvori `objSensor{50, 100}`, ispiši njegove pragove i obradi novi niz vrijednosti u postojećoj petlji. Provjeri da vrijednosti jednake pragovima nisu označene kao preniske ili previsoke.

### Pragovi kao dio stanja objekta

U zadatku 1a pragovi su bili zajedničke konstante. Sada su `mLowPressure` i `mHighPressure` podatkovni članovi klase, pa svaki objekt `PressureSensor` može imati vlastite pragove.

Konstruktor postavlja pragove pri stvaranju objekta pomoću liste inicijalizatora članova. Funkcije `is_low()` i `is_high()` zatim koriste pragove tog objekta, dok ostatak programa i dalje pristupa njegovu stanju preko javnih članskih funkcija.
