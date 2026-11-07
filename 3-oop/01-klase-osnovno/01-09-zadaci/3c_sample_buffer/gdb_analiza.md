# GDB analiza zadatka 3c — životni vijek i kopiranje objekata

Analiza se izvodi na dovršenom programu `SampleBuffer` iz zadatka 3c, bez izmjena izvornog koda. Naglasak je na adresama objekata, njihovih dinamički alociranih polja i redoslijedu pozivanja konstruktora i destruktora. Vrijednosti ADC uzoraka već prikazuje sam program pa ih u GDB-u nije potrebno ponovno ispisivati.

## Zadatak

1. Kompajliraj program s informacijama za debugiranje (`-g -O0`) i pokreni ga u GDB-u. Isključi poruke o dretvama i preusmjeri standardni izlaz programa na `NUL` kako bi GDB ispis ostao pregledan.
2. Postavi prekidne točke na obični konstruktor, konstruktor kopije, destruktor i prvu naredbu u `main()` nakon stvaranja objekta `objBuffer2`. Pri zaustavljanju u konstruktorima zabilježi `this` iz GDB-ove poruke i naredbom `bt` provjeri odakle su pozvani. U konstruktoru kopije ispiši adresu `&refSource`.
3. Nakon stvaranja obaju objekata usporedi adrese njihovih polja `mPtrSamples`, adrese polja uzoraka za kanale 0 i 1 te adrese polja `mPtrSampleCounts`. Provjeri da objekti ne dijele nijedno od tih dinamički alociranih polja.
4. Nastavi do pozivanja destruktora. Prema adresi `this` utvrdi koji se objekt prvi uništava, a naredbom `bt` provjeri mjesto poziva. Naredbom `next` (`n`) prati oslobađanje polja pomoću `delete[]`. Pri drugom pozivu destruktora ponovno usporedi `this` s ranije zabilježenom adresom i nastavi do završetka programa.

Kompajliranje i pokretanje:
```text
g++ -std=c++17 -g -O0 -Wall -Wextra -Wconversion -Werror main.cpp sample_buffer.cpp -o prog.exe
gdb -silent prog.exe
```

---

## GDB ispis

```text
E:\Files\G++\Lift\3-oop\01-klase-osnovno\01-09-zadaci\3c_sample_buffer>gdb -silent prog.exe
Reading symbols from prog.exe...
(gdb) set print thread-events off
(gdb) break sample_buffer.cpp:8
Breakpoint 1 at 0x140001c38: file sample_buffer.cpp, line 9.
(gdb) break sample_buffer.cpp:24
Breakpoint 2 at 0x140001d9d: file sample_buffer.cpp, line 25.
(gdb) break sample_buffer.cpp:47
Breakpoint 3 at 0x140001f50: file sample_buffer.cpp, line 49.
(gdb) break main.cpp:70
Breakpoint 4 at 0x140001a13: file main.cpp, line 70.
(gdb) run > NUL
Starting program: E:\Files\G++\Lift\3-oop\01-klase-osnovno\01-09-zadaci\3c_sample_buffer\prog.exe > NUL

Thread 1 hit Breakpoint 1, SampleBuffer::SampleBuffer (this=0x5ffdf0, channelCount=2, capacity=5) at sample_buffer.cpp:9
9           : mChannelCount{channelCount},
(gdb) bt
#0  SampleBuffer::SampleBuffer (this=0x5ffdf0, channelCount=2, capacity=5) at sample_buffer.cpp:9
#1  0x00007ff6444f18ab in main () at main.cpp:38
(gdb) c
Continuing.

Thread 1 hit Breakpoint 2, SampleBuffer::SampleBuffer (this=0x5ffdc0, refSource=...) at sample_buffer.cpp:25
25          : mPtrSamples{new int*[refSource.mChannelCount]},
(gdb) p &refSource
$1 = (const SampleBuffer *) 0x5ffdf0
(gdb) bt
#0  SampleBuffer::SampleBuffer (this=0x5ffdc0, refSource=...) at sample_buffer.cpp:25
#1  0x00007ff6444f1a13 in main () at main.cpp:67
(gdb) c
Continuing.

Thread 1 hit Breakpoint 4, main () at main.cpp:70
70              objBuffer1.add_sample(0, 222);
(gdb) p objBuffer1.mPtrSamples
$2 = (int **) 0x778440
(gdb) p objBuffer2.mPtrSamples
$3 = (int **) 0x77bca0
(gdb) p *objBuffer1.mPtrSamples@2
$4 = {0x773620, 0x77bc50}
(gdb) p *objBuffer2.mPtrSamples@2
$5 = {0x7765e0, 0x776630}
(gdb) p objBuffer1.mPtrSampleCounts
$6 = (int *) 0x773670
(gdb) p objBuffer2.mPtrSampleCounts
$7 = (int *) 0x7765a0
(gdb) c
Continuing.

Thread 1 hit Breakpoint 3, SampleBuffer::~SampleBuffer (this=0x5ffdc0) at sample_buffer.cpp:49
49          for (int i{0}; i < mChannelCount; ++i)
(gdb) bt
#0  SampleBuffer::~SampleBuffer (this=0x5ffdc0) at sample_buffer.cpp:49
#1  0x00007ff6444f1bd5 in main () at main.cpp:87
(gdb) list sample_buffer.cpp:47,56
47      SampleBuffer::~SampleBuffer()
48      {
49          for (int i{0}; i < mChannelCount; ++i)
50          {
51              delete[] mPtrSamples[i];
52          }
53
54          delete[] mPtrSamples;
55          delete[] mPtrSampleCounts;
56      }
(gdb) n
51              delete[] mPtrSamples[i];
(gdb) n
49          for (int i{0}; i < mChannelCount; ++i)
(gdb) n
51              delete[] mPtrSamples[i];
(gdb) n
49          for (int i{0}; i < mChannelCount; ++i)
(gdb) n
54          delete[] mPtrSamples;
(gdb) n
55          delete[] mPtrSampleCounts;
(gdb) n
56      }
(gdb) n

Thread 1 hit Breakpoint 3, SampleBuffer::~SampleBuffer (this=0x5ffdf0) at sample_buffer.cpp:49
49          for (int i{0}; i < mChannelCount; ++i)
(gdb) bt
#0  SampleBuffer::~SampleBuffer (this=0x5ffdf0) at sample_buffer.cpp:49
#1  0x00007ff6444f1be1 in main () at main.cpp:87
(gdb) c
Continuing.
[Inferior 1 (process 10200) exited normally]
(gdb)
```

---

## Kratko objašnjenje GDB ispisa

**Stvaranje objekata.** Obični konstruktor pozvan je iz `main.cpp:38` i za `objBuffer1` prikazuje `this=0x5ffdf0`. Konstruktor kopije pozvan je iz `main.cpp:67`; njegov `this=0x5ffdc0` označava novi objekt `objBuffer2`, dok `&refSource=0x5ffdf0` pokazuje na izvorni `objBuffer1`. Naredba `bt` potvrđuje oba mjesta poziva.

**Dinamički alocirana polja.** Na prekidnoj točki `main.cpp:70`, nakon dovršetka kopiranja, GDB prikazuje sljedeće adrese:

| Dinamički alocirano polje | `objBuffer1` | `objBuffer2` |
| --- | --- | --- |
| Polje pokazivača `mPtrSamples` | `0x778440` | `0x77bca0` |
| Polje uzoraka kanala 0 | `0x773620` | `0x7765e0` |
| Polje uzoraka kanala 1 | `0x77bc50` | `0x776630` |
| Polje `mPtrSampleCounts` | `0x773670` | `0x7765a0` |

Svaki odgovarajući par adresa razlikuje se. Tako se potvrđuje da konstruktor kopije za drugi objekt alocira vlastita polja.

**Uništavanje objekata.** Pri izlasku iz bloka u `main.cpp:87` prvo se poziva destruktor s `this=0x5ffdc0` (`objBuffer2`), a zatim s `this=0x5ffdf0` (`objBuffer1`). Naredba `bt` pokazuje da oba poziva dolaze iz `main()`. Praćenjem naredbe `n` u prvom destruktoru vidi se izvršavanje `delete[]` za polja kanala 0 i 1, zatim za `mPtrSamples` i `mPtrSampleCounts`. Nakon drugog poziva destruktora program normalno završava.

---

## Ključni zaključci

1. Pokazivač `this` identificira objekt čiji se konstruktor ili destruktor trenutačno izvršava. Konstruktor kopije stvara novi objekt, a `refSource` označava postojeći izvorni objekt.
2. Objekti `objBuffer1` i `objBuffer2` imaju različite adrese i vlastita dinamički alocirana polja. To potvrđuje ispravno razdvajanje memorije pri dubokom kopiranju.
3. Destruktori lokalnih objekata automatski se pozivaju pri izlasku iz bloka, obrnutim redoslijedom konstruiranja: prvo `objBuffer2`, zatim `objBuffer1`.
4. Destruktor svakog objekta odgovoran je za oslobađanje njegovih polja. 
