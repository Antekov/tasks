#include <iostream>
#include <vector>
#include <set>
#include <stack>
#include <algorithm>
#include <map>
#include <cassert>
// #include <string>

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

void dfs_properties(Node *root) {
    if (root->left != nullptr) {
        dfs_properties(root->left);
    }
    if (root->right != nullptr) {
        dfs_properties(root->right);
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
    bool is_error = false;
    string re, u;

    // Массив символов алфавита, встречающичхся на разных позициях в РВ 
    vector<char> symbols;
    
    freopen("input.txt", "r", stdin);
    
    // Стек для разбора РВ в обратной польской записи
    stack<Node *> st;

    // Занимаем элемент с индексом 0 произвольным символом,
    // чтобы остальные добавлялись начиная с индекса 1
    symbols.push_back('$');

    cin >> re >> u;

    // Дополняем РВ завершающим символом и конкатенацией с ним
    re = re + "#.";

    // Индекс последнего добавленного символа алфавита языка в symbols
    size_t index = 0;

    Node *right = nullptr;
    Node *left = nullptr;

    cerr << "Parse RE:" << endl;
    for (int i = 0; i < re.length(); i++) {
        // Очердной символ из строки РВ
        char c = re[i];
        cerr << ' ' << c << endl; 

        if (c == 'a' || c == 'b' || c == 'c' || c == '#') {
            // Если это символ алфавита или завршающий,
            index++;
            // Создаем узел с этим символом и очередым индексом
            // и помещаем его в стек
            st.push(new Node(c, index));

            // А сам символ помещаем еще в массив символов
            symbols.push_back(c);
            
        } else if (c == '*') {
            // Если это символ замыкания...
            if (st.size() < 1) {
                // Если в стеке нет узлов, то это ошибка
                is_error = true;
                break;
            }
            // Правый узел - пустой
            right = nullptr;
            // Левый узел берем с вершины стека
            left = st.top();
            // и удаляем его из стека
            st.pop();
            // Создаем новый узел с операцией * и пустым индексом (0) и
            // левым и правым потомками, определенными выше
            st.push(new Node(c, 0, left, right));
        } else if (c == '1') {
            // Если это символ 1
            if (st.size() < 1) {
                // Если в стеке нет узлов, то это ошибка
                is_error = true;
                break;
            }
            // Создаем копию верхнего узла в стеке: a -> a, a
            st.push(new Node(*st.top()));

            // Добавляем узел с операцией *: a, a -> a, a*
            right = nullptr;
            left = st.top();
            st.pop();
            st.push(new Node('*', 0, left, right));

            // Добавляем узел с конкатенацией: a, a* -> aa*
            right = st.top();
            st.pop();
            left = st.top();
            st.pop();
            st.push(new Node('.', 0, left, right));
        } else if (c == '+' || c == '.') {
            // Если это операция сложения или конкатенации
            if (st.size() < 2) {
                // Если в стеке менее двух узлов, то это ошибка
                is_error = true;
                break;
            }
            // Правый узел берем с вершины стека и удаляем его из стека
            right = st.top();
            st.pop();
            // Левый узел берем с вершины стека и удаляем его из стека
            left = st.top();
            st.pop();
            // Создаем новый узел с операцией + или ., пустым индексом (0) и
            // левым и правым потомками, определенными выше
            st.push(new Node(c, 0, left, right));
        } else {
            // Если попался символ не из обрабатываемых, то это ошибка
            is_error = true;
            break;
        }
    }

    // Если зафиксирована ошибка или в стеке осталось не одна вершина, то выводим ошибку
    if (is_error || st.size() != 1) {
        std::cout << "ERROR" << endl;
        return 0;
    }

    // Запоминаем узел на вершине стека как корень синтаксического дерева
    Node *root = st.top();
    
    // Обходим дерево узлов начиная с корня, рассчитывая свойства nullable, firstpos и lastpos
    dfs_properties(root);

    // Массив для хранения значений followpos для всех символов из массива symbols 
    vector<set<size_t>> followpos(symbols.size()); 

    // Обходим дерево узлов начиная с корня, рассчитывая followpos
    dfs_followpos(root, followpos);

    std::cout << "folowpos(v):" << endl;
    for (size_t index = 1; index < followpos.size(); index++) {
        std::cout << index << " | " << symbols[index] << " : ";
        for (auto x : followpos[index]) {
            std::cout << x << ' ';
        }
        std::cout << endl;
    }

    // Построение ДКА по рассчитанным значениям followpos

    // Каждое состояние ДКА будет определяться множеством индексов символов из
    // массива symbols

    // Массив состояний ДКА
    vector<set<size_t>> Q;
    
    // Вспомогательное множество для хранения необработанных состояний
    set<set<size_t>> unmarked;

    // Словарь для хранения функции переходов D[Q, A] -> Q
    map<pair<set<size_t>, char>, set<size_t>> D;

    // В качестве начального состояния устанавливаем множество индексов,
    // которое находится в свойстве firstpos для корня дерева
    Q.push_back(root->firstpos);

    // Добавляем это состояние в список необработанных
    unmarked.insert(root->firstpos);

    // Пока есть необработанные состояния
    while (unmarked.size() > 0) {
        // Берем первое из них
        set<size_t> R = *unmarked.begin();
        // Удаляем из необработанных, так как сейчас мы его обработаем
        unmarked.erase(unmarked.begin());

        // Создаем вспомогательный словарь для хранения индексов символов, на которые 
        // можно попасть из состояния R по заданному символу
        map<char, set<size_t>> symbol_sets;

        for (auto index : R) {
            char ch = symbols[index];
            if (symbol_sets.count(ch)) {
                symbol_sets[ch].insert(index);
            } else {
                symbol_sets[ch] = set<size_t>{index};
            }
        }

        // Перебираем все символы из словаря symbol_sets
        for (auto key_val : symbol_sets) {
            // Символ
            char ch = key_val.first;

            // Множество индексов, соответсвующих этому символу, входящих в состояние R
            auto W = key_val.second;

            // Строим объединение множеств из followpos для инексов из W
            set<size_t> S;

            for (auto index : W) {
                for (auto i : followpos[index]) {
                    S.insert(i);
                }
            }

            // Если множество S получилось не пустое
            if (S.size() > 0) {
                // Если среди состояний ДКА еще нет состояния, совпадающего с множеством S,
                if (std::count(Q.begin(), Q.end(), S) == 0) {
                    // то добавляем S как новое состояние в множество состояний Q
                    Q.push_back(S);
                    // и добавляем его в список необработанных
                    unmarked.insert(S);
                }
                // Добавляем переход в состояение S из состояния R по символу ch
                D[{R, ch}] = S;
            }
        }
    }

    // Индекс последнего символа в массиве symbols для определения конечных состояний
    size_t last_index = symbols.size() - 1;

    std::cout << "DFA has states:" << endl;
    for (size_t i = 0; i < Q.size(); i++) {
        std::cout << "State Q[" << i << "] = {";
        for (auto s : Q[i]) {
            std::cout << s << ' ';
        }
        std::cout << "}, is final=";
        std::cout << is_final_state(Q[i], last_index) << endl;
    }

    // Опредляем, какой максималный префикс строки u является префиксом слова из языка
    // задаваемого заданным РВ 
    
    // Максималная длина префикса
    size_t max_prefix_len = 0;
   
    // Устанавливаем текущее состояние ДКА равным начальному
    set<size_t> q = Q[0];

    // Признак, что ДКА есть куда совершить переход по очередному символу (ДКА "не умер")
    bool is_alive = true;
    
    std::cout << endl <<"DFA start:" << endl;
    std::cout << "$ -> ";
    print_state(q);
    std::cout << endl;

    // Берем по одному символы из строки u, и если ДКА сможет совершить переход,
    // то увеличиваем max_prefix_len
    for (size_t k = 0; k < u.size(); k++, max_prefix_len++) {
        char ch = u[k];
        // Вычисляем новое состояние ДКА, в которое он переходит из текущего q по символу ch
        q = D[{q, ch}];
            
        std::cout << ch << " -> ";
        print_state(q);
        std::cout << endl;

        // Если текущее состояние - пустое множество, то ДКА умер.
        // Прерываем цикл, так как дальнейшие символы из строки u 
        // не будут соответствовать никакому продолжению слова из языка РВ
        if (q.size() == 0) {
            is_alive = false;
            break;
        }        
    }

    std::cout << "Max prefix len: ";
    std::cout << max_prefix_len << endl;

    return 0;
}