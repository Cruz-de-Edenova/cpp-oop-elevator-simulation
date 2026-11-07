# 3b — Spremnik ADC uzoraka: kopiranje spremnika

## Zadatak

1. Proširi klasu `SampleBuffer` iz zadatka 3a konstruktorom kopije. Novi spremnik mora imati vlastito dinamički alocirano polje uzoraka te isti kapacitet, broj spremljenih uzoraka i njihove vrijednosti kao izvorni spremnik.
2. U `main()` zadrži postojeći zasebni blok i spremnik kapaciteta 5, ali početni popis uzoraka promijeni u `{120, 512, 890}`. Nakon njihova dodavanja stvori drugi spremnik kopiranjem prvoga.
3. U prvi spremnik zatim dodaj uzorak 222, a u drugi 111. Ispiši kapacitet, broj spremljenih uzoraka i njihove vrijednosti za oba spremnika u tablici. Početna tri uzorka trebaju biti jednaka, a posljednji različiti.
4. Oba spremnika moraju se automatski uništiti pri izlasku iz istog bloka. Svaki objekt mora osloboditi vlastito dinamički alocirano polje, bez ručnog oslobađanja memorije u `main()`.

## Kratke upute kako riješiti zadatak

### Redoslijed rješavanja zadatka

1. **Konstruktor kopije:** u klasu `SampleBuffer` dodaj konstruktor koji prima `const SampleBuffer& refSource`. Za novi objekt osiguraj zasebno dinamičko polje uzoraka.
2. **Kopiranje podataka:** preuzmi `mCapacity` i `mSampleCount` iz izvornog objekta te kopiraj vrijednosti svih spremljenih uzoraka u novo polje.
3. **Provjera u `main()`:** skrati početni popis na tri uzorka, konstruiraj `objBuffer2` iz objekta `objBuffer1` i zatim u svaki spremnik dodaj drukčiji četvrti uzorak.
4. **Tablični ispis:** izdvoji zajednički ispis podataka u funkciju `print_samples(const SampleBuffer& refBuffer, char bufferNumber)` i pozovi je za oba spremnika.
5. **Životni vijek objekata:** zadrži oba objekta u istom bloku. Postojeći destruktor ne treba mijenjati jer svaki objekt sada posjeduje vlastito polje koje oslobađa pri uništavanju.

### Konstruktor kopije i duboko kopiranje

Konstruktor kopije stvara novi objekt na temelju postojećega. Parametar `refSource` referenca je na izvorni spremnik, pa se njegovim podacima može pristupiti bez dodatnog kopiranja objekta.

Nije dovoljno kopirati vrijednost pokazivača `mPtrSamples`: tada bi oba objekta upućivala na isto dinamičko polje. Umjesto toga, konstruktor kopije treba alocirati novo polje kapaciteta `mCapacity` i u njega kopirati `mSampleCount` spremljenih uzoraka. Takav se postupak naziva **duboko kopiranje**.

Nakon kopiranja dva spremnika imaju jednake početne podatke, ali zasebnu memoriju. Zato naknadno dodavanje uzorka u jedan spremnik ne mijenja sadržaj drugoga.
