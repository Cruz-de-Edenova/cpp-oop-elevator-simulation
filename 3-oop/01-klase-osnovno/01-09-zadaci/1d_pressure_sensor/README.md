# 1d — Senzor tlaka: usporedba triju senzora

## Zadatak

1. Proširi zadatak 1c konstruktorom bez argumenata koji postavlja pragove na 60–95 bar. Zadrži postojeći konstruktor s dva argumenta i provjeru valjanosti pragova.
2. U `main()` zadrži senzore A i B te njihove provjere iz zadatka 1c. Dodaj senzor C stvoren bez argumenata i ispiši njegove početne pragove.
3. Senzoru C promijeni pragove na 30–120 bar. Ispiši ishod promjene i konačne pragove svih triju senzora koristeći postojeće pomoćne funkcije.
4. Usporedi stanja senzora A, B i C za svih 12 vrijednosti tlaka iz zadatka 1c. Rezultate prikaži u četiri poravnata stupca: tlak, senzor A, senzor B i senzor C.
5. Podijeli program na `main.cpp`, `pressure_sensor.h` i `pressure_sensor.cpp`. U zaglavlju deklariraj klasu, u pripadnoj `.cpp` datoteci definiraj njezine članske funkcije, a u `main.cpp` zadrži stvaranje objekata, ispitivanje i konzolni prikaz. Sačuvaj postojeće ponašanje programa.
