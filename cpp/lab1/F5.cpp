#include <iostream>
#include <vector>

using namespace std;

class TaskF {
public:
    int minAcquaintance = -1;
    int n;
    vector<vector<int>> matrix;
    string cut1, cut2;

    TaskF(int n, vector<string> symbols) : n(n) {
        matrix.assign(n, vector<int>(n));
        char symbol;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                symbol = symbols[i][j];
                if (symbol == '1') { matrix[i][j] = 1; }
            }
        }
    }
    int run() {
        vector<vector<int>> temp(n);
        for (int i = 0; i < n; ++i) {
            temp[i].assign(1, i);
        }

        vector<int> bestCut;
        vector<bool> existance(n, true);
        vector<int> inLeft(n);
        vector<int> weight(n);

        for (int ph = 0; ph < n - 1; ph++) {
            weight.assign(n, 0);
            inLeft.assign(n, false);
            for (int i = 0, pr; i < n - ph; i++) {
                int sel = -1;
                for (int j = 0; j < n; j++) {
                    if (existance[j] && !inLeft[j] && (sel == -1 || weight[j] > weight[sel]))
                        sel = j;
                }
                if (i == n - ph - 1) {
                    if (weight[sel] < minAcquaintance || minAcquaintance == -1){
                        minAcquaintance = weight[sel];
                        bestCut = temp[sel];
                    }
                    temp[pr].insert(temp[pr].end(), temp[sel].begin(), temp[sel].end());
                    for (int j = 0; j < n; j++) {
                        matrix[pr][j] = matrix[j][pr] += matrix[sel][j];
                    }
                    existance[sel] = false;
                } else {
                    inLeft[sel] = true;
                    for (int j = 0; j < n; j++) {
                        weight[j] += matrix[sel][j];
                    }
                    pr = sel;
                }
            }
        }

        inLeft.assign(n, false);
        
        for (auto i : bestCut) {
            cout << i + 1 << " ";
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
};

int main() {
    int n = 4;

    vector<string> symbols(n);
    symbols[0] = "0111";
    symbols[1] = "1001";
    symbols[2] = "1001";
    symbols[3] = "1110";
    
    TaskF task(n, symbols);
    task.run();
    
}