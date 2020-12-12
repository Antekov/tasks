#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

const int n = 8;

struct Position {
    int r = 0, t = 0;
    bool isRunnerStep = false;

    Position(int r=0, int t=0, bool s=true) : r(r), t(t), isRunnerStep(s) {}

    bool operator<(const Position& p) const {
        if (r < p.r)
            return true;
        if (r > p.r)
            return false;
        if (t < p.t) 
            return true;
        if (t > p.t)
            return false;
        if (!isRunnerStep && p.isRunnerStep)
            return true;
        if (isRunnerStep && p.isRunnerStep)
            return false;
        return false;
        
    }

    bool operator==(const Position& p) const {
        return r == p.r ? (t == p.t ? (isRunnerStep == p.isRunnerStep) : false) : false;
    } 
};

std::ostream & operator<<(std::ostream &out, const Position& pos) {
    out << "{" << pos.r << ", " << pos.t << "} " << pos.isRunnerStep;
    return out;
}

class Game {
    std::map<Position, std::vector<Position>> g;
    Position startPosition;
    std::set<Position> usedPositions;
    std::set<Position> winPositions;
    std::set<Position> losePositions;

    std::set<std::pair<int, int>> walls;
public:
    Game(int runner, int termy, std::set<std::pair<int, int>> &walls) : 
        startPosition(runner, termy, true),
        walls(walls) {        
    }
private:

    bool isRunnerStep(Position &pos) {
        return pos.isRunnerStep;
    }

    bool isTermyWin(Position &pos) {
        int x1 = pos.r % n;
        int y1 = pos.r / n;

        int x2 = pos.t % n;
        int y2 = pos.t / n;

        if (x1 == x2 && y1 == y2) {
            return true;
        }

        if (x1 - x2 == 0 || y1 - y2 == 0 || abs(x1 - x2) == abs(y1 - y2)) {
            // check walls
            if (x1 == x2) {
                for (int y = std::min(y1, y2) + 1; y < std::max(y1, y2); y++) {
                    if (walls.count({y, x1}) != 0) {
                        return false;
                    }
                }
            } else if (y1 == y2) {
                for (int x = std::min(x1, x2) + 1; x < std::max(x1, x2); x++) {
                    if (walls.count({y1, x}) != 0) {
                        return false;
                    }
                }
            } else {
                int stepx = x2 > x1 ? 1 : -1;
                int stepy = y2 > y1 ? 1 : -1;
                for (int x = x1 + stepx, y = y1 + stepy; 
                    x < x2; x += stepx, y += stepy) {
                    if (walls.count({y, x}) != 0) {
                        return false;
                    }
                }
            }
            return true;
        }
        
        return false;
    }

    bool isRunnerWin(Position &pos) {
        if (isTermyWin(pos)) {
            return false;
        }

        if (isRunnerStep(pos)) {
            int y1 = pos.r / n;

            if (y1 == n-1)
                return true;
        }
            
        return false;
    }

    bool isTerminal(Position &pos) {
        if (isRunnerWin(pos))
            return true;
                
        if (isTermyWin(pos))
            return true;
        
        return false;
    }

    std::vector<Position> makeStep(Position &pos) {
        const int dx[] = {-1, -1, -1,  0, 0,  1, 1, 1};
        const int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

        int x, y, px, py, runner, termy;

        std::vector<Position> nextPositions;

        if (isRunnerStep(pos)) {
            x = pos.r % n;
            y = pos.r / n;
        } else {
            x = pos.t % n;
            y = pos.t / n;
        }

        for (int i = 0; i < 8; i++) {
            px = x + dx[i];
            py = y + dy[i];

            if (px < 0 || px >= n || py < 0 || py >= n) continue;

            if (walls.count({y, x}) != 0) {
                continue;
            }

            if (isRunnerStep(pos)) {
                runner = py * n + px;
                termy = pos.t;
            } else {
                runner = pos.r;
                termy = py * n + px;
            }

            bool step = !pos.isRunnerStep;

            nextPositions.push_back({runner, termy, step});
        }

        usedPositions.insert(pos);

        return nextPositions;
    }

public:
int solve() {
        std::vector<Position> q;
       
        q.push_back(startPosition);

        while (q.size() > 0) {
            Position position = q[0];
            std::cerr << "Get from queue: " << q[0] << std::endl;
            q.erase(q.begin());

            int count1 = usedPositions.size();
            /*
            usedPositions.insert(position);
            if (position == Position({20, 17, true})) {
                std::cerr << "Handle " << position << " | usedPositions.count(position) = " << usedPositions.count(position) << std::endl;
                std::cerr << "Handle " << position << " | count(position) = " << std::count(usedPositions.begin(), usedPositions.end(), position) << std::endl;

                for (auto &pos : usedPositions) {
                    if (pos == Position({20, 17, true})) {
                        std::cerr << "Found" << std::endl;
                        break;
                    }
                }

                throw 2;
            }
            */
            
            if (isTerminal(position)) {
                if (isRunnerStep(position)) {
                    if (isRunnerWin(position)) {
                        //std::cerr << "Runner Win - add " << position << " to N" << std::endl;
                        winPositions.insert(position);
                    } else {
                        //std::cerr << "Runner Lose - add " << position << " to P" << std::endl;
                        losePositions.insert(position);
                    }
                } else {
                    if (isTermyWin(position)) {
                        //std::cerr << "Termy Win - add " << position << " to N" << std::endl;
                        winPositions.insert(position);
                    } else {
                        //std::cerr << "Termy Lose - add " << position << " to P" << std::endl;
                        losePositions.insert(position);
                    }
                }
                usedPositions.insert(position);
            } else {
                g[position] = makeStep(position);
                
                for (auto &nextPosition : g[position]) {
                    
                    if (usedPositions.count(nextPosition) == 0 &&
                        std::find(q.begin(), q.end(), nextPosition) == q.end()) {
                        //std::cerr << nextPosition << " - Add to queue" << std::endl;
                        q.push_back(nextPosition);
                    }
                    
                }
                
            }
            int count2 = usedPositions.size();
            std::cerr << "Pos count: " << count2 << " | Q count: " << q.size() << std::endl;
            if (count1 == count2) {
                throw 2;
                break;
            }
        }

        std::set<Position> &N = winPositions;
        std::set<Position> &P = losePositions;
        std::set<Position> U = usedPositions;


        std::set<Position> diff;
        std::set<Position> un;

        std::set_union(N.begin(), N.end(), P.begin(), P.end(), std::inserter(un, un.begin()));
        std::set_difference(U.begin(), U.end(), un.begin(), un.end(), std::inserter(diff, diff.begin()));
        U = diff;

        //print('Start position:', startPosition)
        //print(f'Start: U: {len(U)} | N: {len(N)} | P: {len(P)}')
        
        while (U.size() > 0) {
            std::set<Position> R;
            for (auto &u : U) {
                int c = 0;
                for (auto &v : g[u]) {
                    if (P.count(v) > 0) {
                        // print(u, '- Add to N')
                        N.insert(u); 
                        R.insert(u);
                        break;
                    }
                    if (N.count(v) > 0) {
                        c += 1;
                    }
                } 
                if (c == g[u].size()) {
                    // print(u, '- Add to P')
                    P.insert(u);
                    R.insert(u);
                }
            }
            if (R.size() > 0) {
                diff.clear();
                std::set_difference(U.begin(), U.end(), R.begin(), R.end(), std::inserter(diff, diff.begin()));
                U = diff;
            } else {
                // print(f'Break U: {len(U)} | N: {len(N)} | P: {len(P)}') 
                break;
            }

            // print(f'U: {len(U)} | N: {len(N)} | P: {len(P)}')          

        }

        if (N.count(startPosition) > 0) {
            return 1;
        } 
        return -1;        
    }
};



int main() {
    freopen("input.txt", "r", stdin);
    
    int runner = 0;
    int termy = 0;
    std::set<std::pair<int, int>> walls;

    for (int i = 0; i < n; i++) {
        std::string s;
        std::cin >> s;
        // std::cerr << s << std::endl;
        for (int j = 0; j < n; j++) {
            if (s[j] == '1') {
                walls.insert({i, j});
                // std::cerr << "Wall at " << i << ", " << j << std::endl;
            } else if (s[j] == '2') {
                runner = i*n + j;
            } else if (s[j] == '3') {
                termy = i*n + j;
            }
        }
    }

    Game game(runner, termy, walls);

    int ans = game.solve();

    std::cout << ans << std::endl;


    return 0;
}