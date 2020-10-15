#include <iostream>
#include <vector>

using namespace std;

vector<int> prefix(string s) {
    vector<int> v(s.length());
    for (int i = 0; i < v.size(); i++) { v[i] = 0; }
    int k;

    for (int i = 1; i < s.length(); i++) {
        k = v[i - 1];
        while (k > 0 && s[k] != s[i]) {
            k = v[k - 1];
        }
        
        if (s[k] == s[i]) {
            k = k + 1;
        }
        v[i] = k;
    }

    return v;
}

int search_kmp(string s, string t, int start = 0) {
    int index = -1;
    vector<int> f = prefix(s);
    
    int i = start;
    int k = 0;
    int m = s.length();
    int n = t.length();

    while (k < m && i + m - 1 < n) {
        // cout << "k=" << k << " i=" << i << endl;
        if (s[k] == t[i + k]) {
            k++;
        } else {
            if (k == 0) {
                i++;
            } else {
                i += k - f[k-1];
            }
        }
    }
    // cout << "k = " << k << endl;
    if (k == m) {
        index = i;
    }

    return index;
}

int main() {
    string s, t;
    cin >> s >> t;
    
    int i = -1;
    while (true) {
        //i = search_kmp("abcdab", "baabcdabcabcdabcdab", i+1);
        i = search_kmp(s, t, i+1);
        if (i != -1) {
            cout << i << ' ';
        } else {
            break;
        }
    }
    
    return 0;
}