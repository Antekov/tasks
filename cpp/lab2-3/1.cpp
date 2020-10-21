#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("C:\\Temp\\data.txt"); 
    ofstream fout("C:\\Temp\\positive.txt");

    if (fin && fout) {
        int x;

        while (true) {
            fin >> x;

            if (fin.eof()) {
                break;
            }

            // cout << x << endl;
            if (x > 0) {
                fout << x << endl;
            }
        }

        fin.close();
        fout.close();   
    } else {
        cout << "Error opening file(s)" << endl;
    }
    
    return 0;
}