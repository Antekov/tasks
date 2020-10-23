#include <map>
#include <queue>
#include <iostream>
#include <sstream>
#include <cstdio>

using namespace std;
const int MAXN = 1000000;

string s;
int szt, szs;
string s1;
int len1, len2;
int k1;

struct node {
	int l, r, par, link, mark0, mark1;
	map<int,int> next;
 
	node (int l=0, int r=0, int par=-1)
		: l(l), r(r), par(par), link(-1), mark0(0), mark1(0) {}
	int len()  {  return r - l;  }
	int &get (int c) {
		if (!next.count(c))  next[c] = -1;
		return next[c];
	}
};
node t[MAXN];
node t1[MAXN];
int m2[MAXN];

 
struct position {
	int v, pos;
	position (int v, int pos) : v(v), pos(pos)  {}
};
position ptr (0, 0);
 
position go (position st, int l, int r) {
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
 
int split (position st) {
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
 
int get_link (int v) {
	if (t[v].link != -1)  return t[v].link;
	if (t[v].par == -1)  return 0;
	int to = get_link (t[v].par);
	return t[v].link = split (go (position(to,t[to].len()), t[v].l + (t[v].par==0), t[v].r));
}
 
void tree_extend (int pos) {
	while(true) {
		position nptr = go (ptr, pos, pos+1);
		if (nptr.v != -1) {
			ptr = nptr;
			return;
		}
 
		int mid = split (ptr);
		int leaf = szt++;
		t[leaf] = node (pos, szs, mid);
		t[mid].get( s[pos] ) = leaf;
 
		ptr.v = get_link (mid);
		ptr.pos = t[ptr.v].len();
		if (!mid)  break;
	}
}
  
void build_tree() {
	szt = 1;
    szs = s.length();
	for (int i=0; i<szs; ++i)
		tree_extend (i);
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

void dfs_mark0(int i = 0) {
	//cout << "dfs0(" << i <<")" << endl;
	//cout << t1[i].l << ' ' << t1[i].r << endl;
	for (int j = t1[i].l; j < t1[i].r; j++) {
		//cout << s[j] ;
        if (s[j] == '$') {
			t1[m2[t1[i].par]].mark0 = 1;
			
		}
    }
	//cout << endl;
    if (t1[m2[t1[i].par]].mark0 == 1) {
		//cout << "t[" << m2[t1[i].par] << "].mark0 = 1" << endl;
	}    
    
    for (auto next_node : t1[i].next) {
		int j = m2[next_node.second];
        dfs_mark0(j);
		if (t1[j].mark0 == 1) {
			t1[i].mark0 = 1;
		}
    } 
}

void dfs_mark1(int i = 0) {
	//cout << "dfs1(" << i <<")" << endl;
	//cout << t1[i].l << ' ' << t1[i].r << endl;
	bool found = false;
	for (int j = t1[i].l; j < t1[i].r; j++) {
		//cout << s[j] ;
		if (s[j] == '$') {
			found = true;
		}
	}
	//cout << endl;
    if (!found && t1[i].r > 0 && s[t1[i].r-1] == '#') {
		t1[m2[t1[i].par]].mark1 = 1;
		//cout << "t[" << m2[t1[i].par] << "].mark1 = 1" << endl;
	}
	
    
    for (auto next_node : t1[i].next) {
		int j = m2[next_node.second];
		dfs_mark1(j);
		if (t1[j].mark1 == 1) {
			t1[i].mark1 = 1;
		}
    } 
}

queue<int> q;
int k = 0;
int last = -1;

void dfs_mark2(int i = 0) {
	cout << "dfs2(" << i << ")" << endl;
	if (t1[i].mark0 == 1 && t1[i].mark1 == 1 && i > 0) {
		k++;
		cout << "Added t[" << i << "], k = " << k << endl;
		if (k == k1) {
			cout << t1[i].l << " - " << t1[i].r << endl;
			last = i;
		}
	}	
	
	for (auto next_node : t1[i].next) {
		int j = m2[next_node.second];
		dfs_mark2(j);
	} 
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    freopen("input.txt", "r", stdin);

    std::ostringstream out;

    
    cin >> s;
    len1 = s.length();
    cin >> s1;
    len2 = s1.length();
    s = s + '$' + s1 + '#';
	

	cin >> k1;

    build_tree();
    dfs_index();
	dfs_mark0();
	dfs_mark1();
	dfs_mark2();

    out << szt << "\n";

    for (int k = 1; k < szt; k++) {
        node &node = t1[k];
        out << k << ": " << m2[node.par];

		/*
        if (node.l >= len1) {
            out << " 1 " << node.l - len1 << ' ' << node.r - len1;
        } else {
            out << " 0 " << node.l << ' ' << (node.r > len1 ? node.r - len2 : node.r);
        }
		*/
		if (node.l >= len1) {
            out << " 1 " << node.l << ' ' << node.r;
        } else {
            out << " 0 " << node.l << ' ' << node.r;
        }
		out << " mark = " << node.mark0 << node.mark1;

		
        out << " | ";

        for (int j = node.l; j < node.r; j++) {
            out << s[j];
        }
        
        
        out << "\n";
    }
    
    printf("%s", out.str().c_str());

	string ans = "";
	int i = last;

	while (i != 0) {
		//cout << i << endl;
		ans = s.substr(t1[i].l, t1[i].r - t1[i].l) + ans;
		i = m2[t1[i].par];
		
	}
	if (ans.length() == 0) {
		cout << -1 << endl;
	} else {
		cout << ans << endl;
	}
    return 0;
}