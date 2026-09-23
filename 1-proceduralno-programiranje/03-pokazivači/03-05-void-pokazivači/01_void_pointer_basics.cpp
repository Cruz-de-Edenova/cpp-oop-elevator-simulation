#include <iostream>

using std::cout;

// Demonstrira korištenje void pokazivača s različitim tipovima podataka
void demonstrate_void_pointer()
{
    int intValue{20};
    double doubleValue{7.5};

    void* ptrData{&intValue};

    // cout << *ptrData;  // Pogreška: void* se ne može dereferencirati

    int* ptrInt{static_cast<int*>(ptrData)};
    cout << "int vrijednost: " << *ptrInt << '\n';

    ptrData = &doubleValue;

    double* ptrDouble{static_cast<double*>(ptrData)};
    cout << "double vrijednost: " << *ptrDouble << '\n';
}

int main()
{
    demonstrate_void_pointer();
    return 0;
}
/* ============================================================
int vrijednost: 20
double vrijednost: 7.5
*/