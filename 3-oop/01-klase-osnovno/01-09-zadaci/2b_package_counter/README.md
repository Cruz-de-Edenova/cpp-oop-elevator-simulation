# 2b — Evidencija paketa: usporedba dviju traka

## Zadatak

1. Proširi zadatak 2a tako da program vodi odvojenu evidenciju paketa za dvije pokretne trake, A i B. Stvori dva objekta klase `PackageCounter`: za traku A s graničnom visinom od 120 mm, a za traku B od 140 mm. Na objema trakama obradi isti popis visina paketa iz zadatka 2a.
2. Dodaj javnu `const` člansku funkciju za čitanje granične visine pojedinog brojača. Pravilo razvrstavanja ostaje nepromijenjeno: paket visine manje ili jednake granici smatra se malim.
3. Izdvoji ispis rezultata u zajedničku pomoćnu funkciju koja brojač prima putem `const` reference. U poravnatoj tablici prikaži oznaku trake, njezinu graničnu visinu te broj malih, velikih i ukupno evidentiranih paketa. Očekivani rezultat je **4 mala i 2 velika paketa za traku A**, odnosno **5 malih i 1 veliki paket za traku B**.

## Kratke upute kako riješiti zadatak

### Redoslijed rješavanja zadatka

1. **Čitanje granice:** u klasu `PackageCounter` dodaj funkciju `get_small_height() const`, koja vraća vrijednost postojećeg člana `kmSmallHeight`.
2. **Dva neovisna objekta:** u `main()` zadrži `objCounterA{120}` i dodaj `objCounterB{140}`. Postojećom petljom proslijedi svaku visinu iz `packageList` objema objektima.
3. **Zajednički ispis:** definiraj pomoćnu funkciju `print_results(const PackageCounter& refCounter, char conveyorName)` koja javnim članskim funkcijama čita podatke zadanog objekta i ispisuje jedan redak tablice.
4. **Provjera programa:** ispiši zaglavlje tablice i pozovi `print_results()` za obje trake. Provjeri da objekti daju različite rezultate razvrstavanja, iako obrađuju jednake visine paketa.

### Neovisno stanje objekata

Svaki objekt `PackageCounter` ima vlastitu graničnu visinu i vlastite brojeve evidentiranih paketa. Zato ista visina, primjerice 140 mm, pripada velikim paketima na traci A, a malima na traci B.

Pomoćna funkcija `print_results()` prima objekt putem `const` reference kako ga ne bi kopirala i kako bi mogla pozivati samo članske funkcije koje ne mijenjaju njegovo stanje.
