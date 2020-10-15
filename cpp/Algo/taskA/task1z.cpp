#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

vector<size_t> calc_z(string s) {
    size_t z_value;
    size_t k = s.length();

    vector<size_t> z(k);

	for (size_t i=1, l=0, r=0; i<k; ++i) {
		if (i <= r) {
			z_value = min(r-i+1, z[i-l]);
        }
		while (i+z_value < k && s[z_value] == s[i+z_value]) {
			z_value++;
        }
		if (i+z_value-1 > r) {
			l = i;
            r = i+z_value-1;
        }

        z[i] = z_value;
	}

    return z;
}

vector<size_t> search_z(string p, string t, int start = 0) {
    vector<size_t> entries;
    int index = -1;
    int m = p.length();
    int n = t.length();

    string s = p + '\0' + t;
    //string s = p + t;
    
    int i = start;
    int k = n + m + 1;
    
    vector<int> z(k);
	for (int i=1, l=0, r=0; i<k; ++i) {
		if (i <= r) {
			z[i] = min(r-i+1, z[i-l]);
        } else {
            z[i] = 0;
        }
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

vector<size_t> search_z1(string p, string t, int start = 0) {
    vector<size_t> entries;
    int index = -1;
    int m = p.length();
    int n = t.length();

    string s = p + t;
    
    int i = start;
    int k = n + m;
    
    vector<int> z(k);
	for (int i=1, l=0, r=0; i<k; ++i) {
        std::cout << "pos | left | right = " << i << " | " << l << " | " << r << std::endl; 
		if (i <= r) {
			z[i] = min(r-i+1, z[i-l]);
        } else {
            z[i] = 0;
        }
		while (i+z[i] < k && s[z[i]] == s[i+z[i]] && z[i] < m) {
			++z[i];
        }
        std::cout << "z[" << i << "]=" << z[i] << std::endl;
		if (i+z[i]-1 > r) {
			l = i;
            r = i+z[i]-1;
        }
        if (i >= m && z[i] == m) {
            entries.push_back(i - m);
        }
	}

    return entries;
}

int main() {
    string p, t;
    freopen("input.txt", "r", stdin);
    cin >> p >> t;
 
    vector<size_t> entries = search_z(p, t);
    
    entries = search_z1(p, t);
    
    for (auto i : entries) {
        cout << i << ' ';
    }
    return 0;
}