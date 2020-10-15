#include <stdint.h>

uint16_t satsum(uint16_t x, uint16_t y) {
    uint16_t z = x + y;
    if (z - x == y) {
        return z;
    } else {
        if (x >= z + 1) {
            return (x - z - 1) + y;
        } else {
            return (y - z - 1) + x;
        }
    }
}



#include <stdio.h>

int main() {
    uint16_t x, y, z;

    x = 65535;
    y = 2;

    z = satsum(x, y);

    printf("%hu + %hu = %hu", x, y, z);
}

