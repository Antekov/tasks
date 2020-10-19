#include <map>
#include <vector>
#include <iostream>

using namespace std;
const int MAXN = 1000000;

struct node{
    int l, r, par, link; //s[l..r-1] подстрока, написанная на ведущем в вершину ребре
    std::map<char, int> next;
    node(int l=-1, int r=-1, int par=-1) : l(l), r(r), par(par){ }
};

struct position{
    int V, L;
    position(int V, int L) : V(V), L(L) {}
};

node t[MAXN];
string s;
int szt, szs;

int leng(int v){
    return t[v].r - t[v].l;
}
int add_edge_to_parent(int l, int r, int parent){
    int nidx = szt++;
    t[nidx] = node(l, r, parent);
    return (t[parent].next[s[l]] = nidx);
}

int split_edge(position pos){
    int v = pos.V, up = pos.L, down = leng(v) - up;

    if (up == 0) return v;
    if (down == 0) return t[v].par; 

    int mid = add_edge_to_parent(t[v].l, t[v].l + down, t[v].par);
    t[v].l += down, t[v].par = mid;
    t[mid].next[s[t[v].l]] = v;
    return mid;
}

position read_char(position pos, char c){
    int v = pos.V, up = pos.L;
    if (up > 0)
        return s[t[v].r] == c ? position(v, up - 1) : position(-1, -1);
    else {
        int nextv = t[v].next.count(c) ? t[v].next[c] : -1;
        return nextv != -1 ? position(nextv, leng(nextv) - 1) : position(-1, -1);
    }
}
position fast_go_down(int v, int l, int r){
    if (l == r) return position(v, 0);

    while (true) {
        v = t[v].next[s[l]];
        if (leng(v) >= r - l)
            return position(v, leng(v) - r + l);
        l += leng(v);
    }
    throw;
}


int link(int v) {
    if (t[v].link == -1)
        t[v].link = split_edge(fast_go_down(link(t[v].par), t[v].l + int(t[v].par == 0), t[v].r));
    return t[v].link;
}

position add_char_to_tree(position pos, int i) {
    while(true){
        position npos = read_char(pos, s[i]);
        if (npos.V != -1) return npos;

        int mid = split_edge(pos);

        add_edge_to_parent(i, szs, mid);

        pos = position(link(mid), 0);

        if (mid == 0)
            return pos;
    }
    throw;
}




void make_tree() {
    szt = 0;
    szs = s.length();
    node root(-1, -1, -1); 
    root.link = 0;
    t[szt++] = root;

    position pos(0, 0);
    for(int i = 0; i < szs; ++i) {
        pos = add_char_to_tree(pos, i);
    }
}



vector<pair<node, int>> nodes;

void dfs_index(int i = 0) {
    nodes.push_back({t[i], i});
    for (auto next_node : t[i].next) {
        //if (s[t[next_node.second].r] != '$') {
            dfs_index(next_node.second);
        //}
    } 
}




int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    string s1;
    int len1, len2;
    cin >> s;
    len1 = s.length();
    cin >> s1;
    len2 = s1.length();
    s = s + s1;

    make_tree(); 

    cout << szt << endl;
    dfs_index();

    for (int k = 1; k < nodes.size(); k++) {
        auto node = nodes[k];
        for (int i = 0; i < nodes.size(); i++) {
            if (nodes[i].second == node.first.par) {
                cout << i;
                break;
            }
        }
        if (node.first.l >= len1) {
            cout << " 1 " << node.first.l - len1 << ' ' << node.first.r - len1;
        } else {
            cout << " 0 " << node.first.l << ' ' << (node.first.r > len1 ? node.first.r - len1 : node.first.r);
        }
        
        cout << " | ";

        for (int j = node.first.l; j < node.first.r; j++) {
            cout << s[j];
        }
        
        cout << endl;
    }
    return 0;
}