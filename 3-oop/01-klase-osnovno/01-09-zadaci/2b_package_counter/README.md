# 2b — Evidencija paketa: usporedba dviju traka

## Zadatak

1. Proširi zadatak 2a tako da program vodi odvojenu evidenciju paketa na dvije pokretne trake, A i B. U `main()` stvori dva objekta klase `PackageCounter`, s graničnim visinama od 120 mm za traku A i 140 mm za traku B. Na objema trakama obradi isti niz visina paketa iz zadatka 2a.
2. Omogući čitanje granične visine pojedinog objekta putem javne `const` članske funkcije. Pravilo razvrstavanja ostaje nepromijenjeno: paket čija je visina jednaka granici smatra se malim.
3. Izdvoji ispis rezultata pojedine trake u zajedničku pomoćnu funkciju koja objekt brojača prima putem `const` reference. Za svaku traku ispiši njezinu oznaku, graničnu visinu te broj malih, velikih i ukupno evidentiranih paketa.
