#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<size_t> search_z(string p, string t, int start = 0) {
    vector<size_t> entries;
    int index = -1;
    int m = p.length();
    int n = t.length();

    string s = p + '\0' + t;
    
    int i = start;
    int k = n + m + 1;
    
    vector<int> z(k);
	for (int i=1, l=0, r=0; i<k; ++i) {
		if (i <= r)
			z[i] = min(r-i+1, z[i-l]);
		while (i+z[i] < k && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
        if (i > m && z[i] == m) {
            entries.push_back(i - m - 1);
        }
	}

    return entries;
}

int main() {
    string p, t;
    cin >> p >> t;
    
    vector<size_t> entries = search_z(p, t);
    
    for (auto i : entries) {
        cout << i << ' ';
    }
    
    return 0;
}