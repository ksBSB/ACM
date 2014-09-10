#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;
const int sigma_size = 10;
typedef pair<string, string> pii;

struct Node {
	int val,  next[sigma_size];

	Node() { 
		val = 0;
		memset(next, 0, sizeof(next));
	}
}node[maxn];

void insert (int &p, int d, int L, int R, int tig);
void dfs(int p, string str);
int pushup(int &p, int tig);

map<string, int> g;

int n, m, sz, root;
string l, r, name[105];

vector<pii> vec;

int new_node() {
	++sz;
	node[sz].val = 0;
	memset(node[sz].next, 0, sizeof(node[sz].next));
	return sz;
}

void init () {
	sz = root = 0;
	vec.clear();
	g.clear();
	string tmp;

	for (int i = 1; i <= m; i++) {
		cin >> l >> tmp >> r >> name[i];

		tmp = "";
		int d = l.length() - r.length();

		for (int i = 0; i < d; i++)
			tmp += l[i];
		tmp += r;
		r = tmp;

		if (l > r)
			continue;

		int k = i;
		if (g.count(name[i]))
			k = g[name[i]];
		else
			g[name[i]] = i;

		insert(root, 0, 1, 1, k);
	}
}

int main () {
	int cas = 0;
	while (cin >> m) {
		if (cas++)
			cout << endl;

		init();
		pushup(root, m+1);
		dfs(root, "");

		printf("%lu\n", vec.size());
		for (int i = 0; i < vec.size(); i++)
			cout << vec[i].first << " " << vec[i].second << endl;
	}
	return 0;
}

int pushup (int &p, int tig) {
	if (p == 0) {
		p = new_node();
		return node[p].val = tig;
	}

	if (node[p].val)
		tig = node[p].val;

	int k = pushup(node[p].next[0], tig);
	for (int i = 1; i < sigma_size; i++) {
		if (k != pushup(node[p].next[i], tig))
			k = 0;
	}

	return node[p].val = k;
}

void dfs (int p, string str) {
	if (p != root && node[p].val) {
		if (node[p].val <= m && name[node[p].val] !=  "invalid")
			vec.push_back(make_pair(str, name[node[p].val]));
		return ;
	}

	for (int i = 0; i < sigma_size; i++) {
		if (node[p].next[i] != 0) {
			char ch = '0' + i;
			dfs(node[p].next[i], str + ch);
		}
	}
}

void insert (int &p, int d, int L, int R, int tig) {
	if (p == 0)
		p = new_node();

	if (node[p].val)
		tig = node[p].val;

	if (d >= l.length()) {
		node[p].val = tig;
		return;
	}

	if (L == 0 && R == 0) {
		node[p].val = tig;
		return;
	} else if (L == 0) {
		insert(node[p].next[r[d]-'0'], d + 1, 0, 1, tig);
		for (int i = 0; '0' + i < r[d]; i++)
			insert(node[p].next[i], d + 1, 0, 0, tig);
	} else if (R == 0) {
		insert(node[p].next[l[d]-'0'], d + 1, 1, 0, tig);
		for (int i = l[d] - '0' + 1; i < sigma_size; i++)
			insert(node[p].next[i], d + 1, 0, 0, tig);
	} else if (r[d] == l[d]) {
		insert(node[p].next[l[d]-'0'], d + 1, 1, 1, tig);
	} else {
		insert(node[p].next[l[d]-'0'], d + 1, 1, 0, tig);
		insert(node[p].next[r[d]-'0'], d + 1, 0, 1, tig);
		for (int i = l[d] + 1; i < r[d]; i++)
			insert(node[p].next[i-'0'], d + 1, 0, 0, tig);
	}
}
