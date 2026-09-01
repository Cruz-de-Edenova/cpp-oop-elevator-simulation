# 02 - Razno2

Ova tema obrađuje nekoliko važnih C++ mehanizama koji će se kasnije koristiti kao temelj za OOP.

## `const` i `constexpr`

Objašnjava razliku između `const` i `constexpr`, njihovu primjenu na varijable i funkcije te razliku između vrijednosti poznatih tijekom kompajliranja i vrijednosti dobivenih tijekom izvođenja programa.

## Funkcije

Obrađuje prototipe funkcija, parametre i argumente, pozive funkcija, defaultne argumente, te pojmove potpisa i tipa funkcije.

## Preopterećenje funkcija

Objašnjava preopterećenje funkcija prema broju i tipovima parametara, odabir odgovarajuće preopterećene funkcije, standardne konverzije te moguće dvosmislenosti pri odabiru funkcije.

## Modularizacija programa

Prikazuje podjelu programa na `.h` datoteku zaglavlja i odgovarajuću `.cpp` datoteku, korištenje direktive `#include`, zaštitu datoteke zaglavlja, jedinicu kompajliranja (*translation unit*), te osnovni proces kompajliranja i povezivanja više `.cpp` datoteka.
Kako program raste, novi parovi `.h/.cpp` datoteka dodaju se postupno za nove, prirodno odvojene cjeline programa.