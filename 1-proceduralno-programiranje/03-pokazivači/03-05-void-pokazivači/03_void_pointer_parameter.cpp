#include <iostream>

using std::cout;

enum class ValueType
{
    Integer,
    Double
};

// Ispisuje vrijednost prema tipu podatka na koji ptrData pokazuje
void print_value(const void* ptrData, ValueType type)
{
    if (ptrData == nullptr)
    {
        return;
    }

    if (type == ValueType::Integer)
    {
        const int* ptrValue{static_cast<const int*>(ptrData)};
        cout << "int vrijednost: " << *ptrValue << '\n';
    }
    else if (type == ValueType::Double)
    {
        const double* ptrValue{static_cast<const double*>(ptrData)};
        cout << "double vrijednost: " << *ptrValue << '\n';
    }
}

int main()
{
    int intValue{20};
    double doubleValue{7.5};

    print_value(&intValue, ValueType::Integer);
    print_value(&doubleValue, ValueType::Double);

    return 0;
}
/* ============================================================
int vrijednost: 20
double vrijednost: 7.5
*/