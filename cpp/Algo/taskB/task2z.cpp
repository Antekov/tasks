#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main() {
    string s;
    cin >> s;

    long long n = s.length();

    vector<long long> d1(n);
    vector<long long> d2(n);

    long long l = 0, r = -1, tm;
    for(long long i = 0; i < s.length(); ++i)
    {
        tm = (i > r ? 0 : min(d1[l + r - i], r - i)) + 1;
        while(i + tm < s.length() && i - tm >= 0 && s[i - tm] == s[i + tm]) {
            ++tm;
        }
        d1[i] = --tm;
        if(i + tm > r) {
            l = i - tm;
            r = i + tm;
        }
    }

    l = 0, r = -1, tm;
    for(long long i = 0; i < s.length(); ++i)
    {
        tm = (i > r ? 0 : min(d2[l + r - i + 1], r - i + 1)) + 1;
        while(i + tm - 1 < s.length() && i - tm >= 0 && s[i - tm] == s[i + tm - 1]) {
            ++tm;
        }
        d2[i] = --tm;
        if(i + tm - 1 > r) {
            l = i - tm;
            r = i + tm - 1;
        }
    }
    
    long long ans = 0;
    for (long long i = 0; i < n; i++) {
        ans += d1[i] + d2[i];
    }
    cout << ans << endl;
    
    return 0;
}