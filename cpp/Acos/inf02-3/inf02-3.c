#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[]) {
    for (int i = 1; i < argc; i++) {
        size_t len = strlen(argv[i]);
        size_t zeros = 0;

        while (argv[i][zeros + 2] == '0') zeros++;
    
        len -= zeros;

        if (len <= 2) len++; 

        printf("%ld ", (len - 1) / 2);
        /*
        if (strstr(argv[i], "ULL") || strstr(argv[i], "ULl") || 
            strstr(argv[i], "UlL") || strstr(argv[i], "Ull") ||
            strstr(argv[i], "uLL") || strstr(argv[i], "uLu") ||
            strstr(argv[i], "ulL") || strstr(argv[i], "ull") ||
            strstr(argv[i], "LL") || strstr(argv[i], "Ll") || 
            strstr(argv[i], "lL") || strstr(argv[i], "ll")) {
            printf("8 ");
        } else if ( strstr(argv[i], "UL") || strstr(argv[i], "Ul") || 
                    strstr(argv[i], "uL") || strstr(argv[i], "ul") ||
                    strstr(argv[i], "L") || strstr(argv[i], "l")) {
            printf("4 ");
        } else {        
            
            printf("%ld ", (len - 1) / 2);
        }
        */
    }

    return 0;
}