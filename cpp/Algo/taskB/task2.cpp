#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int main() {
    string s;
    cin >> s;

    int n = s.length();
    vector<pair<int, int>> p;
    
    int pairs = 0;
    
    for (size_t k = 0; k < n; k++) {
        // cout << "k = " << k << endl;
        int i, j;
        
        i = k;
        j = k + 1;
        while (i >= 0 && j < n) {
            if (s[i] == s[j]) {
                pairs++;
                // p.push_back({i, j});
                // cout << i << ' ' << j << ": " << s.substr(i, j - i + 1) << endl;
            } else {
                break;
            }

            i--; 
            j++;
        }

        i = k - 1;
        j = k + 1;
        while (i >= 0 && j < n) {
            if (s[i] == s[j]) {
                pairs++;
                // p.push_back({i, j});
                // cout << i << ' ' << j << ": " << s.substr(i, j - i + 1) << endl;
            } else {
                break;
            }

            i--; 
            j++;
        }
    }
    cout << pairs << endl;   
    return 0;
}