#include <bits/stdc++.h>

using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define forn(i, n) for (int i = 0; i < (int) n; ++i)

const int di[4] = { 1, -1, 0,  0 };
const int dj[4] = { 0,  0, 1, -1 };

vvi g;
vi mt;
int n, m;
vi last_was;
vector<string> s;
int timer;

int num(int i, int j) {
  return i * m + j;
}

void addEdge(int v, int to) {
  g[v].push_back(to);
}

bool isEmpty(int i, int j) {
  return 0 <= i && i < n && 0 <= j && j < m && s[i][j] == '*';
}

bool dfs(int v) {
  if  (last_was[v] == timer) {
    return false;
  }
  last_was[v] = timer;
  for (auto to : g[v]) {
    if  (mt[to] == -1 || dfs(mt[to])) {
      mt[to] = v;
      return true;
    }
  }
  return false;
}

int main() {
//  freopen(".in", "r", stdin);

  int a, b;
  scanf("%d%d%d%d\n", &n, &m, &a, &b);

  g.resize(n * m);
  s.resize(n);
  forn(i, n) {
    getline(cin, s[i]);
    s[i].resize(m);
  }

  int cnt_empty = 0;
  forn(i, n) {
    forn(j, m) {
      if  ((i + j) % 2 && isEmpty(i, j)) {
        forn(k, 4) {
          int ii = i + di[k];
          int jj = j + dj[k];
          if  (isEmpty(ii, jj)) {
            addEdge(num(i, j), num(ii, jj));  
          }
        }
      }
      cnt_empty += isEmpty(i, j);
    }
  }

  if  (2 * b <= a) {
    printf("%d\n", b * cnt_empty);
  } else {
    mt.assign(n * m, -1);
    last_was.assign(n * m, -1);
    timer = 0;
    forn(v, n * m) {
      ++timer;
      dfs(v);    
    }

    int pairs = 0;
    forn(to, n * m) {
      pairs += mt[to] != -1;
    }

    printf("%d\n", pairs * a + (cnt_empty - 2 * pairs) * b);
  }

  return 0;
}