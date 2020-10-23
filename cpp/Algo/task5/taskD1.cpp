#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;
    
    s += '\0';

    size_t n = s.length();

    vector<size_t> perm(n);

    vector<size_t> count(256, 0);
    for (char i : s) {
        count[i]++;
    }
    for (size_t i = 1; i < 256; i++) {
        count[i] += count[i - 1];
    }
    for (size_t i = 0; i < n; i++) {
        perm[--count[s[i]]] = i;
    }

    vector<vector<size_t>> eq_cls(1, vector<size_t>(n));
    eq_cls[0][perm[0]] = 0;
    size_t eq_cls_num = 1;
    for (size_t i = 1; i < n; i++) {
        if (s[perm[i]] != s[perm[i - 1]]) ++eq_cls_num;
        eq_cls[0][perm[i]] = eq_cls_num - 1;
    }

    vector<long> new_perm(n);
    int j;
    for (j = 0; (1 << j) < n; j++) {
        for (size_t i = 0; i < n; i++) {
            new_perm[i] = perm[i] - (1 << j);
            if (new_perm[i] < 0) {
                new_perm[i] += n;
            }
        }
        count.assign(eq_cls_num, 0);
        for (size_t i = 0; i < n; i++) {
            count[eq_cls[j][new_perm[i]]]++;
        }
        for (size_t i = 1; i < eq_cls_num; i++) {
            count[i] += count[i - 1];
        }
        for (long i = n - 1; i >= 0; i--) {
            perm[--count[eq_cls[j][new_perm[i]]]] = new_perm[i];
        }

        eq_cls.emplace_back(n);
        eq_cls[j + 1][perm[0]] = 0;
        eq_cls_num = 1;
        for (size_t i = 1; i < n; i++) {
            size_t mid1 = (perm[i] + (1 << j)) % n;
            size_t mid2 = (perm[i - 1] + (1 << j)) % n;
            if (eq_cls[j][perm[i]] != eq_cls[j][perm[i - 1]] || eq_cls[j][mid1] != eq_cls[j][mid2]) {
                eq_cls_num++;
            }
            eq_cls[j + 1][perm[i]] = eq_cls_num - 1;
        }
    }

    vector<size_t> longest_common_prefix(n - 2, 0);

    for (size_t i = 1; i < n - 1; i++) {
        size_t x = perm[i];
        size_t y = perm[i + 1];
        for (int k = j - 1; k >= 0; k--)
            if (eq_cls[k][x] == eq_cls[k][y]) {
                longest_common_prefix[i - 1] += 1 << k;
                x += 1 << k;
                y += 1 << k;
            }
    }

    size_t res = 0;
    for (int i = 1; i < n; i++) {
        res += (n - 1) - perm[i];
    }
    for (int i = 0; i < n - 2; i++) {
        res -= longest_common_prefix[i];
    }

    cout << res;

    return 0;
}
