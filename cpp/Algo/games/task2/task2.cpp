#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

const int N = 8;

std::set<std::pair<int, int>> walls;

struct Position {
    int r, t;
    bool isRunnerStep;

    bool operator<(const Position& p) const {
        return r < p.r ? true : (t < p.t ? true : (isRunnerStep < p.isRunnerStep));
    }
};

std::ostream & operator<<(std::ostream &out, const Position& pos) {
    out << "{" << pos.r << ", " << pos.t << "} " << pos.isRunnerStep;
    return out;
}

struct Node {
    int id;
    int IsWin;
    bool IsTerminal = false;
    Position pos;

    Node *parent;
    std::set<Node *> children;

    Node(const Position& pos) : pos(pos) {
        id = 0;
        parent = nullptr;
        IsWin = -1; 
        IsTerminal = isTerminal();   
    }

    ~Node() {
        for (auto c : children) {
            delete c;
        }
    }

    bool isRunnerWin() {
        if (isTermyWin()) return false;

        int x1, y1;

        x1 = pos.r % N;
        y1 = pos.r / N;

        if (y1 == N-1) {
            return true;
        }

        return false;
    }

    bool isTermyWin() {
        int x1, y1, x2, y2;

        x1 = pos.r % N;
        y1 = pos.r / N;

        x2 = pos.t % N;
        y2 = pos.t / N;

        if (x1 == x2 && y1 == y2) {
            return true;
        }

        if (x1 - x2 == 0 || y1 - y2 == 0 || abs(x1 - x2) == abs(y1 - y2)) {
            // check walls
            if (x1 == x2) {
                for (int y = std::min(y1, y2) + 1; y < std::max(y1, y2); y++) {
                    if (walls.count({x1, y}) != 0) {
                        return false;
                    }
                }
            } else if (y1 == y2) {
                for (int x = std::min(x1, x2) + 1; x < std::max(x1, x2); x++) {
                    if (walls.count({x, y1}) != 0) {
                        return false;
                    }
                }
            } else {
                int stepx = x2 > x1 ? 1 : -1;
                int stepy = y2 > y1 ? 1 : -1;
                for (int x = x1 + stepx, y = y1 + stepy; 
                    x < x2; x += stepx, y += stepy) {
                    if (walls.count({x, y}) != 0) {
                        return false;
                    }
                }
            }
            return true;
        }
        return false;
    }

    bool isTerminal() {
        if (pos.isRunnerStep && isRunnerWin()) {
            IsWin = 1;
            return true;
        }
        
        if (isTermyWin()) {
            IsWin = 0;
            return true;
        }

        return false;
    }

    

};

class Game {
    std::map<Position, Node*> positions;
    Node *root;
public:
    Game(Node *root) : root(root) {

    }

    int solve() {
        std::vector<Node *> q;
       

        if (!root->isTerminal()) {
            q.push_back(root);
        }

        while (q.size() > 0) {
            Node *current = q[0];
            std::cerr << "Get from queue: " << current->pos << std::endl;
            q.erase(q.begin());
            makeStep(current);

            for (auto &node : current->children) {
                if (positions.count(node->pos) == 0 && find(q.begin(), q.end(), node) == q.end()) {
                    std::cerr << "Add to queue: " << node->pos << std::endl;
                    q.push_back(node);
                }
            }
        }

        return root->IsWin;
    }

    void makeStep(Node *current) {
        auto pos = current->pos;
        const int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
        const int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

        int x, y, px, py;

        if (pos.isRunnerStep) {
            x = pos.r % N;
            y = pos.r / N;
        } else {
            x = pos.t % N;
            y = pos.t / N;
        }

        for (int i = 0; i < 8; i++) {
            px = x + dx[i];
            py = y + dy[i];

            if (px < 0 || px >= N || py < 0 || py >= N) continue;

            int idx = py * N + px;

            if (pos.isRunnerStep) {
                if (positions.count({idx, pos.t, false}) == 0) {
                    Node *node = new Node({idx, pos.t, false});
                    node->parent = current;

                    current->children.insert(node);
                } else {
                    current->children.insert(positions[{idx, pos.t, false}]);
                }
            } else {
                if (positions.count({pos.r, idx, true}) == 0) {
                    Node *node = new Node({idx, pos.t, true});
                    node->parent = current;

                    current->children.insert(node);
                } else {
                    current->children.insert(positions[{pos.r, idx, true}]);
                }
            }

        }

        positions[current->pos] = current;
    }
};



int main() {
    freopen("input.txt", "r", stdin);
    
    int runner;
    int termy;

    for (int i = 0; i < 8; i++) {
        std::string s;
        std::cin >> s;
        std::cerr << s << std::endl;
        for (int j = 0; j < 8; j++) {
            if (s[j] == '1') {
                walls.insert({i, j});
                // std::cerr << "Wall at " << i << ", " << j << std::endl;
            } else if (s[j] == '2') {
                runner = i*N + j;
            } else if (s[j] == '3') {
                termy = i*N + j;
            }
        }
    }

    Node *root = new Node({runner, termy, true});

    Game game(root);

    int ans = game.solve();

    std::cout << ans << std::endl;


    return 0;
}