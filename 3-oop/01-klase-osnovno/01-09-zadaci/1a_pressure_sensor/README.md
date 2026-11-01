# 1a — Senzor tlaka

## Zadatak

1. Izradi samostalan program koji na primjeru senzora tlaka u hidrauličnom sustavu demonstrira enkapsulaciju.
2. Definiraj klasu `PressureSensor` s privatnim podatkovnim članom za spremljenu vrijednost tlaka u barima, inicijaliziranim na nulu.
3. Javnim članskim funkcijama omogući spremanje i čitanje tlaka te provjeru je li tlak ispod donjeg ili iznad gornjeg praga. Pragove odredi imenovanim konstantama `kLowPressure` (60 bar) i `kHighPressure` (95 bar). Vrijednosti jednake pragovima pripadaju zadanom rasponu.
4. U `main()` stvori jedan objekt senzora i redom obradi vrijednosti 45, 74, 105, 97 i 87 bar.
5. Prikaži tlak i njegovo stanje u dva poravnata stupca. Izvan klase pristupaj spremljenom tlaku samo preko javnih članskih funkcija.
