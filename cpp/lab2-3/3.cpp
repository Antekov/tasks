#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int m;

    cin >> m;

    ifstream fin("data1.txt"); 
    ofstream fout1("data2.txt"), fout2("data3.txt");

    double x;

    while (true) {
        fin >> x;

        if (fin.eof()) {
            break;
        }

        cout << x << endl;
        if (x <= m) {
            fout1 << x << endl;
        } else {
            fout2 << x << endl;
        }
    }

    fin.close();
    fout1.close();
    fout2.close();
    
    return 0;
}