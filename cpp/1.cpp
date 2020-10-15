#include <iostream>
#include <vector>
#include <set>
using namespace std;

int main() {
    int a, b, M, x, y, start, end;
    
    cin >> a >> b >> M >> x >> y;

    vector<int> d(M);
    set<int> inf_d;
    bool path_from_a = false, path_from_b = false;


    const int INF = 200000000;

    for (int i = 0; i < M; i++)
    {
        d[i] = INF;
        inf_d.insert(i);
    }

    d[x] = 0;
    inf_d.erase(x);

    for (auto c : d) {
        // cout << c << ' ';
    }

    // cout << endl;

    set<int> vertexes, next_vertexes;

    
    vertexes.insert(x);

    for (long long i = 0; i < M; i++) {
        bool is_changed = false;

        // cout << "Vertexes: ";
        for (auto c : vertexes)
        {
            // cout << c << ' ';
        }
        // cout << endl;

        next_vertexes.clear();

        for (auto start : vertexes)
        {
            // cout << "Handle start = " << start << endl;
            end = (start + 1) % M;
            if (d[end] > d[start] + a) {
                d[end] = d[start] + a;
                inf_d.erase(end);
                is_changed = true;
                if (end == y) {
                    path_from_a = true;
                }
            }

            // cout << "Add (z+1) % M = "<< (start + 1) << " % M = " << end << " to next" << endl;
            next_vertexes.insert(end);

            end = (start * start + 1) % M;
            if (d[end] > d[start] + b) {
                d[end] = d[start] + b;
                inf_d.erase(end);
                is_changed = true;
                if (end == y) {
                    path_from_b = true;
                }
            }

            // cout << "Add (z^2+1) % M = "<< (start * start + 1) << " % M = " << end << " to next" << endl;
            next_vertexes.insert(end);

            for (auto c : d)
            {
                // cout << c << ' ';
            }
            // cout << endl;

            // cout << "Next vertexes: ";
            for (auto c : next_vertexes)
            {
                // cout << c << ' ';
            }
            // cout << endl << endl;

            // cout << "Count of Inf d: " << inf_d.size() << endl;
            // cout << "Is changed: " << is_changed << endl;
            if (inf_d.size() == 0 && !is_changed) {
                break;        
            }

            if (path_from_a && path_from_b) {
                break;
            }
        }

        if (inf_d.size() == 0 && !is_changed) {
            break;        
        }

        if (path_from_a && path_from_b) {
            break;
        }

        vertexes = next_vertexes;
    }
    cout << d[y] << endl;
    return 0;
}