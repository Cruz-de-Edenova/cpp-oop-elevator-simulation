# GDB pomocne naredbe za 2_object_lifetime.exe

# Postavlja tocke prekida potrebne za analizu zivotnog vijeka objekata
define setup
    tbreak 2_object_lifetime.cpp:54
    break Peripheral::~Peripheral
end
# ————————————————————————————————————————————————————————————

# Ispisuje vrijednosti sva cetiri objekta prije izlaska iz unutarnjeg bloka
define objects
    print objFirst
    print objSecond
    print objThird
    print objFourth
end
# ————————————————————————————————————————————————————————————

# Ispisuje adrese objekata i sprema ih u GDB pomocne varijable
define addresses
    print &objFirst
    print &objSecond
    print &objThird
    print &objFourth

    set $first = &objFirst
    set $second = &objSecond
    set $third = &objThird
    set $fourth = &objFourth
end
# ————————————————————————————————————————————————————————————

# Ispisuje "mId" i "this" objekta ciji se destruktor trenutno izvrsava
define destructor
    printf "mId = %d\n", mId
    printf "this = %p\n", this
end
# ————————————————————————————————————————————————————————————

# Prikazuje sadrzaj memorije na ranije spremljenim adresama objekata
# x   -> pregledaj memoriju na zadanoj adresi
# d   -> prikazi procitanu vrijednost kao decimalni cijeli broj
define memory
    x/d $first 
    x/d $second
    x/d $third 
    x/d $fourth
end
