# 3a — Spremnik ADC uzoraka

## Zadatak

1. Izradi konzolni program za pohranu cjelobrojnih uzoraka jednog simuliranog 10-bitnog ADC kanala (vrijednosti od 0 do 1023). Definiraj klasu `SampleBuffer` čiji se kapacitet određuje pri stvaranju objekta.
2. Spremnik neka posjeduje dinamički alocirano polje uzoraka tipa `int`. Konstruktor treba alocirati polje pomoću `new[]`, a destruktor ga osloboditi pomoću `delete[]`. Broj spremljenih uzoraka na početku je nula.
3. Omogući dodavanje uzorka samo dok u spremniku ima mjesta. Funkcija za dodavanje treba vratiti informaciju o uspjehu. Javnim `const` članskim funkcijama omogući čitanje kapaciteta, broja spremljenih uzoraka i pojedinog uzorka prema njegovu indeksu. Za ovaj zadatak nije potrebno provjeravati raspon vrijednosti uzoraka ni valjanost indeksa pri čitanju.
4. U `main()` unutar zasebnog bloka stvori spremnik kapaciteta 5 i redom pokušaj dodati uzorke `{120, 512, 890, 0, 1023, 700}`. Za svaki pokušaj ispiši ishod, a za uspješno dodavanje i indeks te vrijednost spremljenog uzorka. Na kraju ispiši kapacitet i broj spremljenih uzoraka. Prvih pet uzoraka mora biti spremljeno, a šesti odbijen.
5. Pri izlasku iz bloka objekt se mora automatski uništiti i osloboditi svoju dinamičku memoriju. U `main()` nemoj ručno oslobađati memoriju spremnika. Program zadrži u jednoj datoteci `main.cpp`.

## Kratke upute kako riješiti zadatak

### Redoslijed rješavanja zadatka

1. **Definicija klase:** deklariraj `SampleBuffer` s privatnim članovima `int* mPtrSamples`, `int mCapacity` i `int mSampleCount`. Broj spremljenih uzoraka inicijaliziraj na nulu.
2. **Konstruktor i destruktor:** u konstruktoru s parametrom `capacity` pripremi dinamičko polje odgovarajuće veličine. U destruktoru oslobodi upravo to polje.
3. **Članske funkcije:** implementiraj `add_sample(int sample)` s povratnim tipom `bool` te funkcije `get_capacity()`, `get_sample_count()` i `get_sample(int index)`. Funkcije koje samo čitaju podatke označi s `const`.
4. **Provjera programa:** u `main()` pripremi zadano polje uzoraka i prođi kroz njega petljom. Provjeri odbijanje šestog uzorka i završni broj spremljenih uzoraka. Smjesti objekt u zaseban blok kako bi njegov destruktor bio pozvan pri izlasku iz bloka.

### Dinamičko polje i životni vijek objekta

Pokazivač `mPtrSamples` upućuje na dinamički alocirano polje uzoraka. Član `mCapacity` određuje ukupan broj mjesta u tom polju, dok `mSampleCount` označava koliko ih je popunjeno. Dok spremnik nije pun, `mSampleCount` ujedno je indeks sljedećeg slobodnog mjesta.

Memorija alocirana pomoću `new[]` mora se osloboditi odgovarajućim pozivom `delete[]`. Budući da spremnik posjeduje to polje, njegovo oslobađanje pripada destruktoru. Pri izlasku iz bloka destruktor lokalnog objekta poziva se automatski, bez posebnog poziva iz `main()`.
