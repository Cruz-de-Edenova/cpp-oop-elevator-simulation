# `namespace` i `using namespace`

`namespace` služi za grupiranje povezanih imena i sprječavanje sukoba između funkcija, tipova i varijabli jednakih naziva.
U većem programu različiti dijelovi programa mogu koristiti ista imena. `namespace` omogućuje da ih međusobno razlikujemo.

## 1. Definiranje namespacea

**Primjer 1:**

```cpp
namespace elevator
{
    int currentFloor{1};

    void print_status()
    {
        // ...
    }
}
```

- Namespace se definira ključnom riječi `namespace`, nakon koje slijedi njegovo ime.
U primjeru 1 `currentFloor` i `print_status()` pripadaju namespaceu `elevator`.

## 2. Operator `::`

- Imenima unutar namespacea možemo pristupiti pomoću operatora `::`.

**Primjer 2:**

```cpp
elevator::currentFloor = 3;
elevator::print_status();
```

Zapis:

```text
elevator::print_status
```

znači: koristi `print_status` koji pripada namespaceu `elevator`

- Operator `::` naziva se operator razrješenja opsega (*scope resolution operator*).

## 3. Zašto je namespace koristan?

- Dva namespacea mogu sadržavati funkcije jednakog imena.

**Primjer 3:**

```cpp
namespace elevator
{
    void print_status()
    {
        // ...
    }
}

namespace building
{
    void print_status()
    {
        // ...
    }
}
```

Nema konflikta jer možemo jasno navesti koju funkciju želimo:

```cpp
elevator::print_status();
building::print_status();
```

Namespace tako pomaže organizirati kod i spriječiti sukobe imena.

## 4. `using namespace`

- Ako često koristimo imena iz istog namespacea, možemo napisati:

```cpp
using namespace elevator;
```

Nakon toga imena iz namespacea `elevator` možemo koristiti bez prefiksa `elevator::`.

**Primjer 4:**

```cpp
using namespace elevator;

print_status();
```

umjesto:

```cpp
elevator::print_status();
```

`using namespace` ne premješta niti kopira sadržaj namespacea. Samo omogućuje da se njegova imena u trenutnom opsegu koriste bez navođenja naziva namespacea.

## 5. Oprez kod korištenja `using namespace`

- `using namespace` može ponovno povećati mogućnost sukoba imena.

**Primjer 5:**

```cpp
using namespace elevator;
using namespace building;
```

Ako oba namespacea sadrže:

```cpp
void print_status();
```

onda poziv:

```cpp
print_status();
```

postaje nejasan jer kompajler ne zna koju funkciju želimo.

Zato je često sigurnije koristiti kvalificirano ime:

```cpp
elevator::print_status();
```

- Posebno treba izbjegavati:

```cpp
using namespace std;
```

na globalnoj razini većih programa i u header datotekama.

`std` sadrži velik broj imena iz standardne C++ biblioteke, pa njihovo uvođenje u trenutni opseg može povećati mogućnost konflikta.

Stoga je bolje koristiti puni oblik:

```cpp
std::cout
std::array
std::string
```

## 6. Ograničavanje `using namespace` na manji opseg

- Ako `using namespace` ipak koristimo, bolje ga je ograničiti na manji opseg umjesto da ga postavimo globalno.

**Primjer 6:**

```cpp
void demonstrate_namespace()
{
    using namespace elevator;

    print_status();
}
```

Ovdje se direktiva:

```cpp
using namespace elevator;
```

odnosi samo na opseg funkcije `demonstrate_namespace()`.

Unutar te funkcije možemo koristiti:

```cpp
print_status();
```

bez navođenja:

```cpp
elevator::print_status();
```

Izvan funkcije ponovno moramo koristiti kvalificirano ime:

```cpp
elevator::print_status();
```

Na taj način smanjujemo mogućnost sukoba imena u ostatku programa.

### 6.1. Selektivna `using` deklaracija

- Ne moramo uvijek uvesti cijeli namespace. Možemo u trenutni opseg uvesti samo pojedina imena koja želimo koristiti.

**Primjer 7:**

```cpp
using std::cout;
using std::endl;

cout << "Lift je spreman" << endl;
```

Ovdje su samo `cout` i `endl` dostupni bez prefiksa `std::`.
Ostala imena iz namespacea `std` nisu uvedena u trenutni opseg.
To je preciznije od:

```cpp
using namespace std;
```

jer ne uvodimo sva dostupna imena iz namespacea `std`.

- U praksi je za običan novi red često dovoljno koristiti:

```cpp
using std::cout;

cout << "Lift je spreman\n";
```

ili:

```cpp
using std::cout;

cout << "Lift je spreman" << '\n';
```

`std::endl` osim prijelaza u novi red dodatno prazni izlazni međuspremnik (*flush*), što najčešće nije potrebno.

- Možemo razlikovati 3 načina korištenja imena iz namespacea:

```cpp
std::cout << "Lift je spreman\n";
```

```cpp
using std::cout;

cout << "Lift je spreman\n";
```

```cpp
using namespace std;

cout << "Lift je spreman\n";
```

1. način koristi potpuno kvalificirano ime.
2. način uvodi samo konkretno ime koje želimo koristiti.
3. način omogućuje izravno korištenje svih dostupnih imena iz namespacea `std`, zbog čega postoji veća mogućnost sukoba imena.

## 7. Sažetak

- `namespace` grupira povezana imena
- namespace pomaže spriječiti sukobe jednakih imena
- operatorom `::` pristupamo imenu unutar namespacea
- `using namespace` omogućuje korištenje imena bez prefiksa namespacea
- `using namespace` može povećati mogućnost konflikta imena
- `using namespace std;` ne treba koristiti kao zadanu globalnu praksu
- ako koristimo `using namespace`, bolje ga je ograničiti na mali opseg ili koristiti selektivnu `using` deklaraciju