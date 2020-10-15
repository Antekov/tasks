#include <stdio.h>
#include <stdlib.h>

const int N = 27;

int main(int argc, char** argv) {
    char *p;
    double x;
    int y;

    if (argc > 1) {
        long z = strtol(argv[1], &p, N);
        
        scanf("%lf %x", &x, &y);
        printf("%.3lf\n", x + y + z);
    }  

    return 0;
}