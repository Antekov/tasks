#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits.h>
#include <cfloat>

using namespace std;

int main() {
    ofstream fout("data_types.txt");

    if (fout) {
        fout << setw(20) << "data type" 
            << setw(8) << "byte" 
            << setw(21) << "minvalue" 
            << setw(21) << "max value" << endl;
        
        fout << setw(20) << "char" 
            << setw(8) << sizeof(char)
            << setw(21) << CHAR_MAX 
            << setw(21) << CHAR_MIN << endl;

        fout << setw(20) << "short int"
            << setw(8) << sizeof(short int)
            << setw(21) << SHRT_MAX 
            << setw(21) << SHRT_MIN << endl;
        
        fout << setw(20) << "unsigned short int" 
            << setw(8) << sizeof(unsigned short int)
            << setw(21) << USHRT_MAX 
            << setw(21) << 0 << endl;

        fout << setw(20) << "int" 
            << setw(8) << sizeof(int)
            << setw(21) << INT_MAX 
            << setw(21) << INT_MIN << endl;

        fout << setw(20) << "unsigned int" 
            << setw(8) << sizeof(unsigned int)
            << setw(21) << UINT_MAX 
            << setw(21) << 0 << endl;

        fout << setw(20) << "long int" 
            << setw(8) << sizeof(long int)
            << setw(21) << LONG_MAX 
            << setw(21) << LONG_MIN << endl;

        fout << setw(20) << "unsigned long int" 
            << setw(8) << sizeof(unsigned long int)
            << setw(21) << ULONG_MAX 
            << setw(21) << 0 << endl;

        fout << setw(20) << "long long" 
            << setw(8) << sizeof(long long)
            << setw(21) << LLONG_MAX 
            << setw(21) << LLONG_MIN << endl;

        fout << setw(20) << "unsigned long long" 
            << setw(8) << sizeof(unsigned long long)
            << setw(21) << ULLONG_MAX 
            << setw(21) << 0 << endl;

        fout << setw(20) << "float" 
            << setw(8) << sizeof(float)
            << setw(21) << FLT_MAX 
            << setw(21) << FLT_MIN << endl;

        fout << setw(20) << "double" 
            << setw(8) << sizeof(double)
            << setw(21) << DBL_MAX 
            << setw(21) << DBL_MIN << endl;
        
        fout.close();   
    } else {
        cout << "Error opening file" << endl;
    }
    
    return 0;
}