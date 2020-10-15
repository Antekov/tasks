#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

typedef pair<long long, pair<int, int> > Edge;

const int N = 200100;

int p[N];
long long a[N];

int get_leader(int a)
{
	return (a == p[a] ? a : (p[a] = get_leader(p[a])));
}

bool merge(int a, int b)
{
	a = get_leader(a);
	b = get_leader(b);
	if (a == b) return false;
	p[a] = b;
	return true;
}

int main()
{
	int n, m;
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
		
	vector<Edge> edges(m);

	for (int i = 0; i < m; i++) {
		cin >> edges[i].second.first >> edges[i].second.second >> edges[i].first;
		edges[i].second.first--;
		edges[i].second.second--;
	}

	int min_edge = min_element(a, a + n) - a;

	for (int i = 0; i < n; i++) {
		if (i != min_edge) {
			edges.push_back({a[i] + a[min_edge], {i, min_edge}});
        }
    }

	sort(edges.begin(), edges.end());
	
    long long res = 0;

	for (int i = 0; i < n; i++) {
		p[i] = i;
    }

	for (auto e : edges) {
		if (merge(e.second.first, e.second.second)) {
			res += e.first;
        }
    }
	
    cout << res;

	return 0;		
}