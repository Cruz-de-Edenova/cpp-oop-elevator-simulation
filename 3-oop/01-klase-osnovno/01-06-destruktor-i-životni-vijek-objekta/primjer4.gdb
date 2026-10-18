# GDB pomocne naredbe za 4_resource_cleanup.exe

# Postavlja tocke prekida potrebne za analizu dinamicke memorije
define setup
    tbreak 4_resource_cleanup.cpp:98
    break SampleStorage::~SampleStorage
end

# Prikazuje objekte i njihove zasebne dinamicki alocirane podatke
define objects
    printf "objOriginal:\n"
    printf "  object    = %p\n", &objOriginal
    printf "  mPtrValue = %p\n", objOriginal.mPtrValue
    printf "  value     = %d\n", *objOriginal.mPtrValue

    printf "objCopy:\n"
    printf "  object    = %p\n", &objCopy
    printf "  mPtrValue = %p\n", objCopy.mPtrValue
    printf "  value     = %d\n", *objCopy.mPtrValue
end

# Prikazuje objekt ciji se destruktor izvrsava i njegov alocirani podatak
define destructor
    printf "this      = %p\n", this
    printf "mPtrValue = %p\n", mPtrValue
    printf "value     = %d\n", *mPtrValue
end
