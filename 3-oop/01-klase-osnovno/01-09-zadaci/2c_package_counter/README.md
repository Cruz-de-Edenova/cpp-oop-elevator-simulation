# 2c — Evidencija paketa: odvojene serije

## Zadatak

1. Proširi zadatak 2b tako da klasa `PackageCounter` omogućuje poništavanje broja evidentiranih malih i velikih paketa bez promjene granične visine.
2. Nakon obrade prve serije paketa iz zadatka 2b i ispisa rezultata poništi evidenciju obiju traka. Ponovno ispiši tablicu i provjeri da su oba broja paketa na nuli, a granične visine ostale 120 mm za traku A i 140 mm za traku B.
3. Obradi drugu seriju paketa: na traci A visine 90, 120, 80 i 150 mm, a na traci B visine 140, 160, 130 i 170 mm. Očekivani rezultat je **3 mala i 1 veliki paket na traci A** te **2 mala i 2 velika paketa na traci B**.
4. Izdvoji ponavljajuću obradu niza visina i prikaz usporedne tablice u pomoćne funkcije. Zadrži postojeću funkciju za ispis rezultata pojedine trake.

## Kratke upute kako riješiti zadatak

### Redoslijed rješavanja zadatka

1. **Poništavanje evidencije:** u klasu `PackageCounter` dodaj javnu funkciju `reset_record()` koja postavlja `mSmallCount` i `mLargeCount` na nulu, bez promjene `kmSmallHeight`.
2. **Izdvajanje obrade paketa:** definiraj funkciju `count_packages(PackageCounter& refCounter, const int* ptrPackageList, int packageCount)` koja redom evidentira zadani broj visina u odabranom brojaču.
3. **Izdvajanje ispisa tablice:** definiraj `print_table(const PackageCounter& refCounterA, const PackageCounter& refCounterB)` koja ispisuje zaglavlje i poziva postojeću funkciju `print_results()` za obje trake.
4. **Prva serija i poništavanje:** u `main()` obradi postojeći popis `packageList1` pomoću nove funkcije, ispiši tablicu, pozovi `reset_record()` za oba objekta i ponovno ispiši tablicu.
5. **Druga serija i provjera:** pripremi zasebna polja `packageList2A` i `packageList2B`, evidentiraj po četiri paketa za svaku traku i ispiši rezultate. Provjeri da nova evidencija ne uključuje podatke iz prve serije.

### Poništavanje stanja i pomoćne funkcije

Funkcija `reset_record()` mijenja samo brojeve evidentiranih paketa. Granična visina `kmSmallHeight` ostaje nepromijenjena, pa se isti objekt može ponovno upotrijebiti za novu seriju.

Funkcija `count_packages()` prima `PackageCounter&` jer mijenja stanje zadanog objekta. Pokazivač `const int* ptrPackageList` omogućuje čitanje visina bez njihove izmjene, a `packageCount` određuje koliko elemenata treba obraditi. Funkcija `print_table()` prima oba brojača putem `const` referenci jer samo čita njihovo stanje.
