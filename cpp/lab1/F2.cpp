#include <iostream>
#include <vector>

using namespace std;

int main() {
    int n;
    
    cin >> n;

    vector<vector<int>> A(n, vector<int>(n));

    for (int i = 0; i < n; i++) {
        char c;
        for (int j = 0; j < n; j++) {
            cin >> c;
            if (c == '1') {
                A[i][j] = 1;
            }
        }
    }

    int minAc = -1;
    vector<int> bestCut;

    vector< vector<int> > v(n);
    for (int i = 0; i < n; ++i) {
        v[i].assign(1, i);
    }
    vector<int> weight(n);
    vector<bool> exist(n, true);
    vector<int> inLeft(n);

    for (int phase = 0; phase < n - 1; phase++) {
        inLeft.assign(n, false);
        weight.assign(n, 0);
        for (int it = 0, prev = 0; it < n - phase; it++) {
            int sel = -1;
            for (int i = 0; i < n; ++i) {
                if (exist[i] && !inLeft[i] && (sel == -1 || weight[i] > weight[sel]))
                    sel = i;
            }
            if (it == n - phase - 1) {
                if (weight[sel] < minAc || minAc == -1){
                    minAc = weight[sel];
                    bestCut = v[sel];
                }
                v[prev].insert(v[prev].end(), v[sel].begin(), v[sel].end());
                for (int i = 0; i < n; ++i) {
                    A[prev][i] = A[i][prev] += A[sel][i];
                }
                exist[sel] = false;
            } else {
                inLeft[sel] = true;
                for (int i = 0; i < n; i++) {
                    weight[i] += A[sel][i];
                }
                prev = sel;
            }
        }
    }

    inLeft.assign(n, false);

    for (auto i : bestCut) {
        cout << i + 1<< " ";
        inLeft[i] = true;
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        if (!inLeft[i]) {
            cout << i + 1 << " ";
        }
    }
    
    return 0;
}
