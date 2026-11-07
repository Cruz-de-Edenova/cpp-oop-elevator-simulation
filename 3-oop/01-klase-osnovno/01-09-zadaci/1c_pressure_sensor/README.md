# 1c — Senzor tlaka: provjera i promjena pragova

## Zadatak

1. Proširi klasu `PressureSensor` iz zadatka 1b provjerom valjanosti pragova: donji prag mora biti nenegativan i strogo manji od gornjeg. Provjeru izdvoji u privatnu člansku funkciju.
2. Ako konstruktor primi nevaljane pragove, postavi zadane vrijednosti 60 i 95 bar. Dodaj javnu funkciju za naknadnu promjenu pragova koja vraća informaciju o uspjehu. Nevaljana promjena mora ostaviti postojeće pragove nepromijenjenima.
3. U `main()` stvori senzor A s pragovima 120 i 30 bar te senzor B s pragovima 50 i 100 bar. Za senzor B pokušaj postaviti najprije pragove 110 i 40 bar, a zatim 40 i 110 bar. Ispiši ishod pokušaja i stvarne pragove nakon stvaranja odnosno promjene senzora.
4. Za oba senzora prikaži stanje tlaka za isti skup vrijednosti kao u zadatku 1b, u tri poravnata stupca: tlak, senzor A i senzor B.
5. Izdvoji pomoćne funkcije za promjenu pragova i ispis ishoda, ispis trenutačnih pragova te ispis stanja tlaka. Pri prosljeđivanju senzora koristi referencu, a za funkcije koje samo čitaju njegovo stanje `const` referencu.

## Kratke upute kako riješiti zadatak

### Redoslijed rješavanja zadatka

1. **Provjera pragova:** dodaj privatnu funkciju `are_thresholds_valid(int lowPressure, int highPressure) const` koja provjerava oba uvjeta valjanosti pragova.
2. **Konstruktor:** iskoristi provjeru pragova i, ako su zadane vrijednosti nevaljane, postavi `mLowPressure` na 60 i `mHighPressure` na 95.
3. **Promjena pragova:** dodaj javnu funkciju `set_thresholds(int lowPressure, int highPressure)` koja vraća `bool`. Oba podatkovna člana mijenjaj samo ako je novi par pragova valjan.
4. **Pomoćne funkcije:** izdvoji `set_thresholds_and_print_status()` za promjenu pragova i ispis ishoda, `print_thresholds()` za ispis spremljenih pragova te `print_pressure_status()` za ispis stanja tlaka. Koristi odgovarajuće reference na `PressureSensor`.
5. **Provjera programa:** u `main()` stvori senzore `objSensorA` i `objSensorB`, provjeri nevaljanu i valjanu promjenu pragova senzora B te prikaži stanja obaju senzora u zajedničkoj tablici.

### Provjera pragova i očuvanje stanja

Privatna funkcija `are_thresholds_valid()` koristi se i u konstruktoru i u funkciji `set_thresholds()`, kako uvjeti valjanosti ne bi bili zapisani na dva mjesta. Konstruktor za nevaljane početne pragove postavlja zadane vrijednosti, dok `set_thresholds()` odbija nevaljan par i zadržava prethodne vrijednosti obaju pragova.

Senzor A zato dobiva pragove 60 i 95 bar, iako je stvoren s argumentima 120 i 30. Senzor B zadržava pragove 50 i 100 nakon neuspjele promjene na 110 i 40, a zatim prihvaća promjenu na 40 i 110 bar.

### Reference u pomoćnim funkcijama

Funkcija `set_thresholds_and_print_status()` prima `PressureSensor&` jer mijenja stanje senzora. Funkcije `print_thresholds()` i `print_pressure_status()` primaju `const PressureSensor&` jer stanje samo čitaju. Tako pomoćne funkcije rade s postojećim objektima bez njihova kopiranja.
