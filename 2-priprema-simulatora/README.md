# Priprema simulatora

Ova cjelina služi kao priprema za kasniju izradu simulatora lifta. Najprije se opisuje stvarna hidraulična podizna platforma i njezin način rada, a zatim se definira virtualni I/O kao komunikacijski sloj između upravljačkog programa i simulacije lifta.

## 1 - Opis lifta

Ova tema sadrži opis konstrukcije i načina rada hidraulične podizne platforme **Autoquip Titan Scissors Lift** koja će poslužiti kao osnova simulatora. Obrađeni su odabrani model platforme, osnovna struktura sustava, električni i hidraulični sustav, podizanje i spuštanje platforme te sigurnosni i zaštitni elementi.

## 2 - Virtualni I/O

Ova tema definira jednostavan proceduralni komunikacijski sloj između budućeg upravljačkog programa i simulacije lifta. Opisani su ulazni i izlazni signali iz perspektive upravljačkog programa, smjer njihove razmjene te organizacija datoteka `virtual_io.h` i `virtual_io.cpp`. Virtualni I/O služi kao zajednička granica preko koje će kasniji OOP dio simulatora komunicirati s upravljačkim programom.
