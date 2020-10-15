typedef enum {
    PlusZero      = 0x00,
    MinusZero     = 0x01,
    PlusInf       = 0xF0,
    MinusInf      = 0xF1,
    PlusRegular   = 0x10,
    MinusRegular  = 0x11,
    PlusDenormal  = 0x20,
    MinusDenormal = 0x21,
    SignalingNaN  = 0x30,
    QuietNaN      = 0x31
} float_class_t;

#include <stdio.h>

extern float_class_t classify(double *value_ptr) {
    unsigned long long x = (unsigned long long) (*value_ptr);

    unsigned long long n;
    

    n = 0;
    n = ~n;

    printf("%llu, %llu", n, x);

    if ((x | 0ULL) == 0Ull) {
        printf("PlusZero");
        return PlusZero;
    }

    n = 1ULL << 62;
    if (x & n) {
        printf("%llu, %llu, %llu", n, (unsigned long long) x, ((unsigned long long) x | n));
        printf("MinusZero");
        return MinusZero;
    }
    
return PlusRegular;



}

int main() {
    unsigned long long n = (1ULL << 62);

    double *x = (double*) (&n);

    classify(x);
    return 0;
}
      