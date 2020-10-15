#include <stdio.h>
#include <string.h>

const int N = 27;

int main(int argc, char** argv) {
    char *z_str;
    double x;
    int y;

    if (argc > 1) {
        z_str = argv[1];

        long long z = 0;
        long long p = 1;

        //printf("%d\n", strlen(z_str));

        for (int i = strlen(z_str) - 1; i >=0; i--) {
            char c = z_str[i];
            if (c > '9') {
                c = c - 'A' + 10;
            } else {
                c = c - '0';
            }
            //printf("%d\n",  c);
            z += p * c;
            p *= N; 
        }

        scanf("%lf", &x);
        scanf("%x", &y);
        printf("%.3f\n", x + y + z);
    }  

    return 0;
}