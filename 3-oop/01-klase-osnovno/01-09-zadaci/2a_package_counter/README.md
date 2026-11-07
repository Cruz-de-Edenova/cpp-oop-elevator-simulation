# 2a — Evidencija paketa

## Zadatak

1. Izradi konzolni program koji na jednoj pokretnoj traci evidentira pakete prema njihovoj visini u milimetrima. Nije potrebno simulirati gibanje trake ni mjerenje visine.
2. Definiraj klasu `PackageCounter` koja zasebno prati broj malih i velikih paketa. Oba broja početno postavi na nulu. Graničnu visinu zadaj konstruktorom i pohrani u privatni `const` podatkovni član.
3. Omogući evidentiranje jednog paketa prema njegovoj visini. Paket je mali ako je visina manja ili jednaka graničnoj vrijednosti, a veliki ako je veća. Javnim `const` članskim funkcijama omogući čitanje broja malih, velikih i ukupnog broja evidentiranih paketa.
4. U `main()` stvori jedan objekt s graničnom visinom od 120 mm. Redom obradi visine `{90, 160, 110, 140, 85, 120}` i ispiši broj malih, velikih i ukupno evidentiranih paketa. Očekivani rezultat je **4 mala, 2 velika i 6 paketa ukupno**. Program organiziraj u jednoj datoteci `main.cpp`.

## Kratke upute kako riješiti zadatak

### Redoslijed rješavanja zadatka

1. **Podatkovni članovi:** definiraj klasu `PackageCounter` s privatnim članovima `const int kmSmallHeight`, `int mSmallCount{0}` i `int mLargeCount{0}`.
2. **Konstruktor:** dodaj `PackageCounter(int smallHeight)` i inicijaliziraj `kmSmallHeight` pomoću liste inicijalizatora članova.
3. **Članske funkcije:** implementiraj `record_package(int height)` za evidentiranje paketa te `get_small_count() const`, `get_large_count() const` i `get_total_count() const` za čitanje rezultata. Ukupan broj izračunaj iz postojećih članova.
4. **Provjera programa:** u `main()` stvori `objCounter{120}`, definiraj polje `packageList` i petljom evidentiraj sve pakete. Ispiši rezultate i provjeri da paket visine točno 120 mm pripada malima.
