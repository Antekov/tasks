#include <iostream>
#include <cstring>
#include <string>
#include <algorithm>
#include <cmath>


int lcp (int i, int j, int **c, int log_n) {
	int res = 0;
	for (int k=log_n; k>=0; --k)
		if (c[k][i] == c[k][j]) {
			res += 1<<k;
			i += 1<<k;
			j += 1<<k;
		}
	return res;
}


int main() {
    std::string s;
    std::cin >> s;

    s.push_back('\0');
    size_t n = s.length(); // длина строки

    size_t log_n = ceil(log2(n));

    // std::cout << n << ' ' << log_n << std::endl;

    const int alphabet = 256; // размер алфавита, <= maxlen

    int *p = new int[n], *cnt = new int[alphabet], **c = new int*[log_n];
    for (int i = 0; i < log_n; i++) {
        c[i] = new int[n];
    }

    for (int i = 0; i < alphabet; cnt[i] = 0, i++);
    
    // Нулевая фаза
    for (int i = 0; i < n; ++i)
        ++cnt[s[i]];
    for (int i=1; i<alphabet; ++i)
        cnt[i] += cnt[i-1];
    for (int i=0; i<n; ++i)
        p[--cnt[s[i]]] = i;
    c[0][p[0]] = 0;
    int classes = 1;
    for (int i=1; i<n; ++i) {
        if (s[p[i]] != s[p[i-1]])  ++classes;
        c[0][p[i]] = classes-1;
    }

    // Следующие фазы построения префиксного массива p[]
    int *pn = new int[n], *cn = new int[n];
    for (int h=0; (1<<h)<n; ++h) {
        for (int i=0; i<n; ++i) {
            pn[i] = p[i] - (1<<h);
            if (pn[i] < 0)  pn[i] += n;
        }
        for (int i = 0; i < classes; cnt[i] = 0, i++);
        //std::cout << "0" << "\n";    
        for (int i=0; i<n; ++i) {
            //std::cout << "h=" << h << ' ' << i << ' ' << pn[i] << "\n"; 
            ++cnt[c[h][pn[i]]];
        }
        //std::cout << "1" << "\n";
        for (int i=1; i<classes; ++i)
            cnt[i] += cnt[i-1];
        //std::cout << "2" << "\n";
        for (int i=n-1; i>=0; --i)
            p[--cnt[c[h][pn[i]]]] = pn[i];
        //std::cout << "3" << "\n";
        cn[p[0]] = 0;
        classes = 1;
        for (int i=1; i<n; ++i) {
            int mid1 = (p[i] + (1<<h)) % n,  mid2 = (p[i-1] + (1<<h)) % n;
            if (c[h][p[i]] != c[h][p[i-1]] || c[h][mid1] != c[h][mid2])
                ++classes;
            cn[p[i]] = classes-1;
            //std::cout << "9" << "\n";
        }
        std::swap(c[h+1], cn);
    }
    /*
    for (int i = 0; i < n; i++) {
        std::cout << p[i] << ' ';
    }

    std::cout << std::endl;
    */
    /*
    int *lcp1 = new int[n-2];

    for (int i = 0; i < n - 2; i++) {
        lcp1[i] = lcp(p[i+1], p[i+2], c, log_n);
        std::cout << lcp1[i] << ' ';
    }
    std::cout << std::endl;
    */

    int res = 0;
    for (int i = 1; i < n; i++) {
        res += (n - 1 - p[i]);
    }

    for (int i = 0; i < n-2; i++) {
        res -= lcp(p[i+1], p[i+2], c, log_n);
    }

    std::cout << res << "\n";

    for (int i = 0; i < log_n; i++) {
        delete[] c[i];
    }

    delete [] p, pn, c, cn, cnt; 
    return 0;

    
}