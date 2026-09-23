# Tema 03 - Pokazivači

Tema 03 sastoji se od pet podtema koje postupno obrađuju pokazivače, njihov odnos s memorijom, poljima i funkcijama te korištenje kvalifikatora `const` i pokazivača tipa `void*`.

## 03-01 - Osnove pokazivača

Objašnjava osnovni odnos između varijable, njezine adrese i pokazivača. Obrađuje operatore `&` i `*`, `nullptr`, dinamičku alokaciju pomoću `new` i `delete`, životni vijek dinamički stvorenih podataka, viseće pokazivače, curenje memorije te pristup članovima strukture preko pokazivača.

### Sadržaj

1. Varijabla, adresa i pokazivač
2. Operator adrese `&`
3. Operator dereferenciranja `*`
4. Promjena varijable preko pokazivača
5. `nullptr`
6. Automatski i dinamički životni vijek
7. Dinamička alokacija operatorom `new`
8. Oslobađanje memorije operatorom `delete`
9. Curenje memorije (*memory leak*)
10. Viseći pokazivač (*dangling pointer*)
11. Pokazivači na korisnički definirane tipove
12. Pokazivačka varijabla također ima adresu
13. Pametni pokazivači
14. GDB demonstracija
15. Sažetak

---

## 03-02 - Polja fiksne veličine, dinamički alocirana polja i `std::vector`

Objašnjava odnos pokazivača i polja, dinamičku alokaciju pomoću `new[]` i `delete[]`, višedimenzionalna dinamička polja i pokazivačku aritmetiku. Na kraju uspoređuje ručno upravljanje dinamički alociranim poljima sa spremnikom `std::vector`.

### Sadržaj

1. Polje fiksne veličine i dinamički alocirano polje
2. Range-based `for` petlja
3. Kratki osvrt na `auto`
4. Dinamički alocirano jednodimenzionalno polje
5. Prolazak kroz dinamičko polje
6. Oslobađanje dinamičkog polja operatorom `delete[]`
7. Dvodimenzionalno polje s dinamički alociranim redovima
8. Dinamički alocirano dvodimenzionalno polje pomoću pokazivača na pokazivač
9. Dinamički alocirana trodimenzionalna i N-dimenzionalna polja
10. `std::vector` kao alternativa dinamički alociranom polju
11. Aritmetika pokazivača
12. GDB demonstracija
13. Sažetak

---

## 03-03 - Pokazivači i funkcije

Objašnjava korištenje pokazivača kao parametara i povratnih vrijednosti funkcija te razliku između prosljeđivanja po vrijednosti i pristupa podatku preko adrese. Obrađuje polja i strukture u funkcijama, izlazne parametre, pokazivače na funkcije i njihovo prosljeđivanje drugim funkcijama.

### Sadržaj

1. Argumenti i parametri funkcije
2. Pokazivač kao parametar funkcije
3. Pokazivač kao povratna vrijednost funkcije
4. Polje kao parametar funkcije
5. Struktura kao parametar funkcije
6. Struktura kao povratna vrijednost funkcije
7. Više rezultata preko izlaznih parametara
8. Struktura kao pregledniji povrat više rezultata
9. Pokazivači na funkcije
10. Pokazivač na funkciju kao parametar druge funkcije
11. GDB demonstracija
12. Sažetak

---

## 03-04 - `const` i pokazivači

Objašnjava razliku između pokazivača na `const` podatak, `const` pokazivača i `const` pokazivača na `const` podatak. Poseban naglasak je na korištenju `const` uz pokazivače kao parametre funkcija radi ograničavanja promjene podataka preko pokazivača.

### Sadržaj

1. Pokazivač na `const int`
2. `const` pokazivač
3. `const` pokazivač na `const int`
4. `const` i pokazivači kao parametri funkcija
5. Sažetak

---

## 03-05 - `void` pokazivači

Objašnjava pokazivače tipa `void*`, koji mogu sadržavati adrese objekata različitih tipova bez informacije o njihovu konkretnom tipu. Obrađuje pretvorbu natrag u odgovarajući tip pokazivača, `const void*`, `void* const`, korištenje `void*` kao parametra funkcije te ograničenja i odgovornost za tipovnu sigurnost.

### Sadržaj

1. Osnove `void*` pokazivača
2. `const` i `void*`
3. `void*` kao parametar funkcije
4. Ograničenja i praktična primjena
5. Sažetak

---
