# 3c — Spremnik ADC uzoraka: više kanala

## Zadatak

1. Proširi klasu `SampleBuffer` iz zadatka 3b tako da jedan spremnik može pohranjivati uzorke više simuliranih 10-bitnih ADC kanala. Konstruktor neka prima broj kanala i kapacitet svakog kanala. Uzorke pohrani u dinamički alocirano dvodimenzionalno polje, s posebnim retkom i zasebnim brojem spremljenih uzoraka za svaki kanal. Svi kanali imaju jednak kapacitet.
2. Prilagodi funkcije za dodavanje i čitanje uzoraka tako da primaju i indeks kanala. Dodavanje u puni kanal mora se odbiti bez utjecaja na ostale kanale. Omogući i čitanje broja kanala; pri čitanju uzoraka pretpostavi valjane indekse kanala i spremljenih uzoraka, kao u prethodnom zadatku.
3. Prilagodi konstruktor kopije i destruktor radu s više dinamički alociranih polja. Kopija mora imati vlastito polje uzoraka za svaki kanal te isti kapacitet, broj kanala, brojeve spremljenih uzoraka i njihove vrijednosti kao izvorni spremnik. Pri uništavanju objekta mora se osloboditi sva memorija koju je alocirao.
4. U `main()` zadrži jedan zasebni blok. Stvori `objBuffer1` s dva kanala kapaciteta 5. U kanal 0 spremi postojeći popis `{120, 512, 890}`, a u kanal 1 uzorke 250 i 750. Zatim stvori `objBuffer2` konstruktorom kopije. U kanal 0 prvog spremnika dodaj 222, a drugog 111; u kanal 1 prvog spremnika dodaj 333, a drugog 444. Prilagodi tablični ispis tako da prikazuje oba kanala svakog spremnika i njihove uzorke. Provjeri da su početne vrijednosti kopirane, a naknadno dodane vrijednosti različite.
5. Program organiziraj u tri izvorne datoteke: `sample_buffer.h` s deklaracijom klase i zaštitom od višestrukog uključivanja, `sample_buffer.cpp` s definicijama njezinih članskih funkcija te `main.cpp` sa stvaranjem objekata, provjerama i konzolnim ispisom.

## Kratke upute kako riješiti zadatak

### Redoslijed rješavanja zadatka

1. **Modularizacija programa:** postojeći kod iz zadatka 3b podijeli u datoteke `sample_buffer.h`, `sample_buffer.cpp` i `main.cpp`. U zaglavlju deklariraj klasu, u pripadajućoj `.cpp` datoteci definiraj njezine članske funkcije, a u `main.cpp` zadrži stvaranje objekata, provjere i konzolni ispis.
2. **Prilagodba podatkovnih članova:** promijeni tip člana `mPtrSamples` u `int**`, ukloni `mSampleCount` te dodaj `mPtrSampleCounts` i `mChannelCount`. Zadrži `mCapacity` kao zajednički kapacitet svih kanala.
3. **Prilagodba običnog konstruktora:** omogući zadavanje broja kanala i njihova kapaciteta. Alociraj polje pokazivača, zatim zasebno polje uzoraka za svaki kanal te polje za broj spremljenih uzoraka. Sve početne vrijednosti broja spremljenih uzoraka postavi na nulu.
4. **Prilagodba destruktora:** oslobodi dinamički alocirano polje uzoraka svakog kanala, zatim polje pokazivača i polje broja spremljenih uzoraka.
5. **Prilagodba članskih funkcija:** prilagodi funkcije `add_sample()`, `get_sample()` i `get_sample_count()` tako da primaju indeks kanala. Dodaj funkciju `get_channel_count()` za dohvat broja kanala.
6. **Prilagodba konstruktora kopije:** osiguraj duboko kopiranje svih kanala, uključujući njihov kapacitet, broj spremljenih uzoraka i vrijednosti uzoraka. Svaki kopirani objekt mora posjedovati vlastitu dinamički alociranu memoriju.
7. **Prilagodba funkcije `main()` i provjera programa:** stvori spremnik s dva ADC kanala, dodaj predviđene uzorke i napravi njegovu kopiju. Zatim dodaj različite uzorke u odgovarajuće kanale obaju spremnika. Prilagodi tablični ispis i provjeri da su sadržaji kopirani, ali međusobno neovisni.

### Organizacija dinamičke memorije

Za pohranu uzoraka više ADC kanala koriste se **dva odvojena polja podataka**:

- **Dvodimenzionalno polje uzoraka**, kojem se pristupa preko `int** mPtrSamples`. Najprije se alocira polje pokazivača, a zatim za svaki kanal zasebno jednodimenzionalno polje tipa `int`. Svaki redak predstavlja jedan ADC kanal, a svaki element retka mjesto za jedan uzorak.
- **Jednodimenzionalno polje brojeva spremljenih uzoraka**, kojem se pristupa preko `int* mPtrSampleCounts`. Svaki element sadrži broj uzoraka koji su trenutačno spremljeni u odgovarajućem kanalu.

Oba polja pripadaju istom objektu `SampleBuffer`, ali zauzimaju odvojene dijelove dinamički alocirane memorije. Povezana su **indeksom ADC kanala**.

Primjer spremnika s dva kanala, svaki kapaciteta pet uzoraka:

```text
1. Dvodimenzionalno polje uzoraka (mPtrSamples)

                         mPtrSamples
                              |
                              v
                      +-------+-------+
                      | ptr[0]| ptr[1]|  Polje pokazivača
                      +---|---+---|---+
                          |       |
             +------------+       +------------+
             |                                 |
             v                                 v
     +-----+-----+-----+-----+-----+   +-----+-----+-----+-----+-----+
     | 120 | 512 | 890 |  ?  |  ?  |   | 250 | 750 |  ?  |  ?  |  ?  |
     +-----+-----+-----+-----+-----+   +-----+-----+-----+-----+-----+
                   Kanal 0                           Kanal 1


2. Jednodimenzionalno polje brojeva spremljenih uzoraka (mPtrSampleCounts)

                       mPtrSampleCounts
                              |
                              v
                          +-----+-----+
                          |  3  |  2  |
                          +-----+-----+
                            [0]   [1]
                          Kanal Kanal
                            0     1
```

Znak `?` označava mjesto na koje uzorak još nije spremljen. Polje uzoraka pojedinog kanala i polje brojeva spremljenih uzoraka alociraju se odvojeno. Također, redci dvodimenzionalnog polja ne moraju biti jedan do drugoga u memoriji.

### Pristup uzorcima i njihovom broju

Za pristup vrijednosti uzorka koriste se dva indeksa:

```cpp
mPtrSamples[channel][index]
```

Prvi indeks određuje ADC kanal, a drugi mjesto uzorka unutar tog kanala. Broj spremljenih uzoraka odgovarajućeg kanala dobiva se izrazom:

```cpp
mPtrSampleCounts[channel]
```

Primjerice:

```cpp
mPtrSamples[0][2]     // Treci uzorak kanala 0: 890
mPtrSampleCounts[0]   // Broj spremljenih uzoraka kanala 0: 3

mPtrSamples[1][0]     // Prvi uzorak kanala 1: 250
mPtrSampleCounts[1]   // Broj spremljenih uzoraka kanala 1: 2
```

Član `mChannelCount` sadrži broj kanala, ujedno i broj elemenata polja `mPtrSampleCounts`, dok `mCapacity` određuje maksimalan broj uzoraka po kanalu. Vrijednosti u `mPtrSampleCounts` na početku su nula, a nakon uspješnog dodavanja uzorka povećava se samo vrijednost pripadajućeg kanala.

### Alokacija, kopiranje i oslobađanje memorije

Konstruktor najprije treba alocirati polje pokazivača na kanale, zatim zasebno polje uzoraka za svaki kanal te odvojeno polje brojeva spremljenih uzoraka, čije početne vrijednosti trebaju biti nula.

Konstruktor kopije mora alocirati vlastita polja, preuzeti podatke o kapacitetu i broju kanala te kopirati broj spremljenih uzoraka i njihove vrijednosti za svaki kanal. Kopirani spremnik ne smije dijeliti dinamički alociranu memoriju s izvornim.

Destruktor treba osloboditi polja uzoraka svih kanala, zatim polje pokazivača i zasebno polje brojeva spremljenih uzoraka. Za svako polje alocirano pomoću `new[]` koristi se `delete[]`.
