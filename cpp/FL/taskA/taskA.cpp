#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>
#include <map>
#include <cassert>

using namespace std;

void print_state(set<size_t> q) {
    std::cout << "{";
    for (auto i : q) {
        std::cout << i << ' ';
    }
    std::cout << "}";
}

struct Node {
    char symbol;
    size_t index;
    bool nullable;
    set<size_t> firstpos;
    set<size_t> lastpos;

    Node *left;
    Node *right;

    Node(char symbol, size_t index=0, Node *left=nullptr, Node* right=nullptr) : 
        symbol(symbol), index(index), left(left), right(right) {

    }
};

void dfs_nullable(Node *root) {
    if (root->left != nullptr) {
        dfs_nullable(root->left);
    }
    if (root->right != nullptr) {
        dfs_nullable(root->right);
    }

    std::cout << "Node " << root->symbol << "(" << root->index << ")" << endl;
    Node *u = root->left;
    Node *v = root->right;

    if (root->symbol == '+') {
        root->nullable = u->nullable || v->nullable;

        std::set_union(u->firstpos.begin(), u->firstpos.end(),
                       v->firstpos.begin(), v->firstpos.end(),                  
                       std::inserter(root->firstpos, root->firstpos.begin()));
        
        std::set_union(u->lastpos.begin(), u->lastpos.end(),
                       v->lastpos.begin(), v->lastpos.end(),                  
                       std::inserter(root->lastpos, root->lastpos.begin()));

    } else if (root->symbol == '.') {
        root->nullable = u->nullable && v->nullable;

        if (u->nullable) {
            std::set_union(u->firstpos.begin(), u->firstpos.end(),
                       v->firstpos.begin(), v->firstpos.end(),                  
                       std::inserter(root->firstpos, root->firstpos.begin()));
        } else {
            root->firstpos = u->firstpos;
        }

        if (v->nullable) {
            std::set_union(u->lastpos.begin(), u->lastpos.end(),
                       v->lastpos.begin(), v->lastpos.end(),                  
                       std::inserter(root->lastpos, root->lastpos.begin()));
        } else {
            root->lastpos = v->lastpos;
        }
    } else if (root->symbol == '*') {
        root->nullable = true;
        root->firstpos = u->firstpos;
        root->lastpos = u->lastpos;
    } else {
        root->nullable = false;
        root->firstpos = set<size_t>{root->index};
        root->lastpos = set<size_t>{root->index};
    }

    std::cout << root->nullable << " | fp: ";
    for (auto i : root->firstpos) {
        std::cout << i << ' ';
    }
    std::cout << "| lp: ";
    for (auto i : root->lastpos) {
        std::cout << i << ' ';
    }
    std::cout << endl << endl;;
}

void dfs_followpos(Node *root, vector<set<size_t>> &followpos) {
    if (root->left != nullptr) {
        dfs_followpos(root->left, followpos);
    }
    if (root->right != nullptr) {
        dfs_followpos(root->right, followpos);
    }

    std::cout << "Node " << root->symbol << "(" << root->index << ")" << endl;
    Node *u = root->left;
    Node *v = root->right;

    if (root->symbol == '.') {
        for (auto i : u->lastpos) {
            for (auto x : v->firstpos) {
                followpos[i].insert(x);
            }
        }
    } else if (root->symbol == '*') {
        for (auto i : u->lastpos) {
            for (auto x : u->firstpos) {
                followpos[i].insert(x);
            }
        }
    } else {
        return;
    }

    std::cout << root->nullable << " | fp: ";
    for (auto i : root->firstpos) {
        std::cout << i << ' ';
    }
    std::cout << "| lp: ";
    for (auto i : root->lastpos) {
        std::cout << i << ' ';
    }
    std::cout << endl << endl;;
}

bool is_final_state(set<size_t> Q, size_t last_index) {
    return Q.count(last_index) > 0;
}

int main() {
    string re, u;

    vector<char> symbols;
    vector<bool> nullable;

    freopen("input.txt", "r", stdin);
    
    stack<Node *> st;

    symbols.push_back('$');

    cin >> re >> u;

    re = re + "#.";
    size_t index = 0;

    Node *root = nullptr;
    Node *right = nullptr;
    Node *left = nullptr;

    for (int i = 0; i < re.length(); i++) {
        char c = re[i];

        if (isalpha(c) || c == '#') {
            index++;
            st.push(new Node(c, index));
            symbols.push_back(c);
            
        } else if (c == '*') {
            right = nullptr;
            left = st.top();
            st.pop();
            st.push(new Node(c, 0, left, right));
            
        } else if (c == '+' || c == '.') {
            right = st.top();
            st.pop();
            left = st.top();
            st.pop();
            st.push(new Node(c, 0, left, right));
        }
    }

    root = st.top();

    assert(st.size() == 1);

    dfs_nullable(root);

    vector<set<size_t>> followpos(symbols.size()); 

    dfs_followpos(root, followpos);

    std::cout << "folowpos(v):" << endl;
    for (size_t index = 1; index < followpos.size(); index++) {
        std::cout << index << " | " << symbols[index] << " : ";
        for (auto x : followpos[index]) {
            std::cout << x << ' ';
        }
        std::cout << endl;
    }

    vector<set<size_t>> Q;
    set<set<size_t>> unmarked;
    map<pair<set<size_t>, char>, set<size_t>> D;

    Q.push_back(root->firstpos);
    unmarked.insert(root->firstpos);

    while (unmarked.size() > 0) {
        set<size_t> R = *unmarked.begin();
        unmarked.erase(unmarked.begin());

        map<char, set<size_t>> symbol_sets;

        for (auto index : R) {
            char ch = symbols[index];
            if (symbol_sets.count(ch)) {
                symbol_sets[ch].insert(index);
            } else {
                symbol_sets[ch] = set<size_t>{index};
            }
        }

        for (auto key_val : symbol_sets) {
            char ch = key_val.first;
            auto W = key_val.second;

            set<size_t> S;

            for (auto index : W) {
                for (auto i : followpos[index]) {
                    S.insert(i);
                }
            }

            if (S.size() > 0) {
                if (std::count(Q.begin(), Q.end(), S) == 0) {
                    Q.push_back(S);
                    unmarked.insert(S);
                }
                D[pair<set<size_t>, char>(R, ch)] = S;
            }
        }
    }

    size_t last_index = symbols.size() - 1;

    for (size_t i = 0; i < Q.size(); i++) {
        std::cout << "State Q[" << i << "] = {";
        for (auto s : Q[i]) {
            std::cout << s << ' ';
        }
        std::cout << "}, F = ";
        std::cout << is_final_state(Q[i], last_index) << endl;
    }

    size_t max_prefix_len = 0;

    for (size_t right = 0; right < u.size(); right++) {
        set<size_t> q = Q[0];
        bool is_alive = true;
        std::cout << "Prefix " << right + 1 << ": " << endl;

        print_state(q);
        std::cout << endl;
        for (size_t k = 0; k < right + 1; k++) {
            char ch = u[k];
            q = D[{q, ch}];
            
            std::cout << ch << " -> ";
            print_state(q);
            std::cout << endl;

            if (q.size() == 0) {
                is_alive = false;
                break;
            }
        }
        if (is_alive) {
            max_prefix_len = right + 1;
        }
        
    }

    std::cout << "Max prefix len: ";
    std::cout << max_prefix_len << endl;
       

    return 0;
}