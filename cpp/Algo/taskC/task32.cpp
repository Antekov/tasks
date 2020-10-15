#include <iostream>
using namespace std;

bool checkSub(string &s, string &t, long l, long r, long i) {
    if (l > r)
        return true;

    if (l == r && (s[l] == '?' || s[l] == t[i + l]))
        return true;

    long mid = (l + r) / 2;
    long mid1 = (l + mid) / 2;
    long mid2 = (r + mid) / 2;
    if ((s[l] == '?' || s[l] == t[i + l]) && (s[r] == '?' || s[r] == t[i + r]) 
        && (s[mid] == '?' || s[mid] == t[i + mid])
        && (s[mid1] == '?' || s[mid1] == t[i + mid1])
        && (s[mid2] == '?' || s[mid2] == t[i + mid2]))
        if (checkSub(s, t, l + 1, mid1 - 1, i)) {
            if (checkSub(s, t, mid1 + 1, mid - 1, i)) {
                if (checkSub(s, t, mid + 1, mid2 - 1, i)) {
                    if (checkSub(s, t, mid2 + 1, r - 1, i)) {
                        return true;
                    }
                }    
            }
        }
    
    return false;
}
    
void printMatches(string &s, string &t) {
    long m = s.length();
    long n = t.length();

    long i = 0;
    
    while (i <= n - m) {
        long l = 0;
        long r = m - 1;

        if (checkSub(s, t, l, r, i)) {
            cout << i << ' ';
        }
        i += 1;
    }
}

int main() {
    string s, t;
    cin.sync_with_stdio(false);
    cin.tie(NULL);
    cin >> s >> t;
    printMatches(s, t);
}