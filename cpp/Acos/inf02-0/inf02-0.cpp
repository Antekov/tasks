#include <iostream>
#include <iomanip>

const int N = 27;

int main(int argc, char** argv) {
    std::string z_str;
    double x;
    long long y;

    if (argc > 1) {
        std::cout << argc << std::endl;
        z_str = argv[1];

        long long z = 0;
        long long p = 1;

        for (int i = z_str.length()-1; i >=0; i--) {
            char c = z_str[i];
            if (c > '9') {
                c = c - 'A' + 10;
            } else {
                c = c - '0';
            }
            std::cout << (unsigned int) c << ' ' << z << ' ' << p * (int)c << ' ' << p << std::endl;
            z += p * c;
            p *= N; 
        }

        std::cin >> x >> std::hex >> y >> std::dec;
        // std::cout << z_str << std::endl;
        // std::cout << x << std::endl;
        // std::cout << y << std::endl;
        // std::cout << z << std::endl;
        std::cout << std::fixed << std::setprecision(3) << x + y + z << std::endl;
    }  

    return 0;
}