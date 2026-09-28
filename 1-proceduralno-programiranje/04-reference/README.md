# Tema 04 - Reference

Tema 04 sastoji se od četiri podteme koje postupno obrađuju osnove referenci, njihovu primjenu u funkcijama, korištenje referenci uz `const` te praktične razlike između referenci i pokazivača.

## 04-01 - Osnove referenci

Objašnjava osnovno značenje reference kao drugog imena za postojeću varijablu ili objekt. Obrađuje deklaraciju i inicijalizaciju reference, pristup i promjenu vrijednosti pomoću reference, odnos varijable i reference, vezivanje reference, reference na korisnički definirane tipove te osnovna ograničenja referenci.

### Sadržaj

1. Što je referenca?
2. Deklaracija i inicijalizacija reference
3. Pristup vrijednosti preko reference
4. Promjena vrijednosti varijable preko reference
5. Odnos varijable i reference
6. Više referenci na istu varijablu
7. Referenca se ne može preusmjeriti
8. Referenca na objekt korisnički definiranog tipa
9. Osnovna ograničenja referenci
10. Usporedba reference i pokazivača
11. GDB demonstracija
12. Sažetak

---

## 04-02 - Reference i funkcije

Objašnjava korištenje referenci kao parametara i povratnih vrijednosti funkcija. Obrađuje razliku između prosljeđivanja po vrijednosti i pomoću reference, rad s objektima korisnički definiranih tipova te važnost životnog vijeka objekta kada funkcija vraća referencu.

### Sadržaj

1. Prosljeđivanje po vrijednosti
2. Referenca kao parametar funkcije
3. Prosljeđivanje po vrijednosti i pomoću reference
4. Objekt korisnički definiranog tipa kao referentni parametar
5. Referenca kao povratni tip funkcije
6. Promjena objekta pomoću vraćene reference
7. Životni vijek objekta i vraćena referenca
8. GDB demonstracija
9. Sažetak

---

## 04-03 - `const` i reference

Objašnjava reference na `const` objekte i način na koji `const` ograničava promjenu vrijednosti pomoću reference. Obrađuje vezivanje reference na `const` uz `const` i obične varijable te korištenje takvih referenci kao parametara i povratnih vrijednosti funkcija.

### Sadržaj

1. Referenca na `const int` vezana uz `const` varijablu
2. Referenca na `const int` vezana uz običnu varijablu
3. Referenca na `const` objekt kao parametar funkcije
4. Referenca na `const int` kao povratna vrijednost funkcije
5. Sažetak

---

## 04-04 - Reference i pokazivači: razlike i ograničenja

Objašnjava praktične razlike između referenci i pokazivača pri radu s postojećim objektima. Poseban naglasak je na izboru reference ili pokazivača kao parametra funkcije, korištenju `nullptr` te potrebi provjere pokazivača prije dereferenciranja.

### Sadržaj

1. Referenca ili pokazivač kao parametar funkcije
2. Pokazivač kao parametar i `nullptr`
3. Zašto je provjera `nullptr` važna?
4. Kada koristiti referencu, a kada pokazivač?
5. Sažetak
