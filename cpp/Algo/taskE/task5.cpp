#include <map>
#include <iostream>
#include <sstream>
#include <cstdio>
#include <cstring>

using namespace std;
const int N = 1005000;

char s[N];
int szt, szs;
char s1[N];
int len1, len2;

struct node {
	int l, r, par, link;
	map<int,int> next;
 
	node (int l=0, int r=0, int par=-1)
		: l(l), r(r), par(par), link(-1) {}
	int len()  {  return r - l;  }
	int &get (int c) {
		if (!next.count(c))  next[c] = -1;
		return next[c];
	}
};

node t[N];
node t1[N];
int m2[N];

 
struct position {
	int v, pos;
	position (int v, int pos) : v(v), pos(pos)  {}
};
position ptr (0, 0);
 
position go_down(position st, int l, int r) {
	while (l < r)
		if (st.pos == t[st.v].len()) {
			st = position (t[st.v].get( s[l] ), 0);
			if (st.v == -1)  return st;
		}
		else {
			if (s[ t[st.v].l + st.pos ] != s[l])
				return position (-1, -1);
			if (r-l < t[st.v].len() - st.pos)
				return position (st.v, st.pos + r-l);
			l += t[st.v].len() - st.pos;
			st.pos = t[st.v].len();
		}
	return st;
}
 
int split_edge(position st) {
	if (st.pos == t[st.v].len())
		return st.v;
	if (st.pos == 0)
		return t[st.v].par;
	node v = t[st.v];
	int id = szt++;
	t[id] = node (v.l, v.l+st.pos, v.par);
	t[v.par].get( s[v.l] ) = id;
	t[id].get( s[v.l+st.pos] ) = st.v;
	t[st.v].par = id;
	t[st.v].l += st.pos;
	return id;
}
 
int link(int v) {
	if (t[v].link!= -1)  return t[v].link;
	if (t[v].par == -1)  return 0;
	int to = link(t[v].par);
	return t[v].link= split_edge(go_down(position(to,t[to].len()), t[v].l + (t[v].par==0), t[v].r));
}
 
void add_char_to_tree(int pos) {
	while(true) {
		position nptr = go_down(ptr, pos, pos+1);
		if (nptr.v != -1) {
			ptr = nptr;
			return;
		}
 
		int mid = split_edge(ptr);
		int leaf = szt++;
		t[leaf] = node (pos, szs, mid);
		t[mid].get( s[pos] ) = leaf;
 
		ptr.v = link(mid);
		ptr.pos = t[ptr.v].len();
		if (!mid)  break;
	}
}
  
void build_tree() {
	szt = 1;
    szs = strlen(s);
	for (int i = 0; i < szs; i++)
		add_char_to_tree(i);
}

int idx = 0;

void dfs_index(int i = 0) {
    t1[idx] = t[i];
    m2[i] = idx;
    idx++;
    
    for (auto next_node : t[i].next) {
        dfs_index(next_node.second);
    } 
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);
    
    std::ostringstream out;
    

    cin >> s;
    len1 = strlen(s);
    cin >> s1;
    len2 = strlen(s1);
    memcpy(s + len1, s1, len2);
    //s = s + s1;
	out << s << endl;

    build_tree();
    dfs_index();

    out << szt << "\n";

    for (int k = 1; k < szt; k++) {
        node &node = t1[k];
        out << m2[node.par];

        if (node.l >= len1) {
            out << " 1 " << node.l - len1 << ' ' << node.r - len1;
        } else {
            out << " 0 " << node.l << ' ' << (node.r > len1 ? node.r - len2 : node.r);
        }
        
        out << " | ";

        for (int j = node.l; j < node.r; j++) {
            out << s[j];
        }
        
        out << "\n";
    }
    
    
    printf("%s", out.str().c_str());
    return 0;
}