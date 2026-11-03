# 2a — Evidencija paketa

## Zadatak

1. Izradi program koji na jednoj pokretnoj traci evidentira pakete prema njihovoj visini u milimetrima. Nije potrebno simulirati gibanje trake ni mjerenje visine.
2. Definiraj klasu `PackageCounter` s privatnim brojačima malih i velikih paketa, početno postavljenima na nulu. Granična visina određuje najveću dopuštenu visinu paketa koji se smatra malim. Zadaje se konstruktorom i pohranjuje u privatni `const` podatkovni član klase. U ovom zadatku granična visina iznosi 120 mm. U `main()` stvori jedan objekt s graničnom visinom od 120 mm.
3. Omogući evidentiranje pojedinog paketa: paket je mali ako je njegova visina manja ili jednaka granici, a veliki ako je veća. Javnim članskim funkcijama omogući čitanje broja malih, velikih i ukupnog broja paketa. Funkcije koje samo čitaju stanje označi s `const`.
4.  U polju pripremi i redom obradi visine 90, 160, 110, 140, 85 i 120 mm.
5. Ispiši broj malih, velikih i ukupno evidentiranih paketa. Program organiziraj u jednoj datoteci `main.cpp`.
