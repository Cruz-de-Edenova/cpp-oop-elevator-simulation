# 1a — Senzor tlaka

## Zadatak

1. Izradi konzolni program koji pomoću klase `PressureSensor` prikazuje stanje tlaka u hidrauličnom sustavu. Klasa treba pohranjivati trenutačnu vrijednost tlaka u barima.
2. Vrijednost tlaka spremi u privatni podatkovni član inicijaliziran na nulu. Javnim članskim funkcijama omogući postavljanje i čitanje tlaka te provjeru je li tlak prenizak ili previsok. Funkcije koje samo čitaju stanje objekta označi s `const`.
3. Donji prag tlaka odredi konstantom `kLowPressure` (60 bar), a gornji konstantom `kHighPressure` (95 bar). Tlak ispod donjeg praga smatra se preniskim, a iznad gornjeg previsokim. Vrijednosti jednake pragovima pripadaju zadanom rasponu.
4. U `main()` stvori jedan objekt senzora i redom obradi vrijednosti `{45, 74, 105, 97, 87}`. Za svaku vrijednost ispiši tlak i njegovo stanje u dva poravnata stupca. Izvan klase pristupaj spremljenom tlaku isključivo preko javnih članskih funkcija.

## Kratke upute kako riješiti zadatak

### Redoslijed rješavanja zadatka

1. **Podaci senzora:** definiraj konstante `kLowPressure` i `kHighPressure` te klasu `PressureSensor` s privatnim članom `int mPressureBar{0}`.
2. **Članske funkcije:** implementiraj `set_pressure(int pressureBar)` za promjenu spremljenog tlaka, `get_pressure() const` za čitanje te `is_low() const` i `is_high() const` za usporedbu s pragovima.
3. **Provjera programa:** u `main()` stvori objekt `objSensor` i polje `pressureValues`. Petljom redom postavljaj tlak i određuj njegovo stanje preko javnih funkcija klase.
4. **Konzolni ispis:** prikaži rezultate u dva poravnata stupca. Provjeri da su vrijednosti 45, 74, 105, 97 i 87 bar redom označene kao prenizak tlak, tlak u zadanom rasponu, previsok tlak, previsok tlak i tlak u zadanom rasponu.

### Enkapsulacija stanja senzora

Enkapsulacija u ovom primjeru znači da klasa `PressureSensor` čuva spremljeni tlak u privatnom članu `mPressureBar`, dok ostatak programa s objektom komunicira preko javnih članskih funkcija. Tako se način pohrane podatka odvaja od načina na koji se senzor koristi.

Funkcija `set_pressure()` mijenja stanje objekta. Funkcije `get_pressure()`, `is_low()` i `is_high()` samo ga čitaju, pa su označene s `const`. Funkcije za provjeru pragova vraćaju logičku vrijednost, a odluku o tekstualnom ispisu donosi `main()`.
