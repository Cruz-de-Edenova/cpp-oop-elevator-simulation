# 1c — Senzor tlaka: provjera i promjena pragova

## Zadatak

1. Proširi zadatak 1b provjerom valjanosti pragova: donji prag mora biti nenegativan i strogo manji od gornjeg.
2. Ako konstruktor primi nevaljane pragove, senzor mora dobiti zadane vrijednosti 60–95 bar. Omogući i naknadnu promjenu pragova uz povratnu informaciju o uspjehu. Nevaljana promjena ne smije mijenjati postojeće vrijednosti.
3. U `main()` stvori senzor A s nevaljanim pragovima 120–30 bar i senzor B s pragovima 50–100 bar. Senzoru B pokušaj postaviti najprije 110–40 bar, a zatim 40–110 bar. Ispiši ishod obaju pokušaja i stvarne pragove senzora nakon stvaranja odnosno promjena.
4. Za oba senzora provjeri stanje tlaka za svih 12 vrijednosti iz zadatka 1b. Rezultate prikaži u tri poravnata stupca: tlak, senzor A i senzor B.
5. Izdvoji samostalne funkcije za promjenu pragova i ispis ishoda, prikaz spremljenih pragova te prikaz stanja tlaka. Funkcije koje samo čitaju podatke senzora neka ga primaju putem `const` reference.
