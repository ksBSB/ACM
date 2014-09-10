#include <cstdio>
#include <cstring>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <algorithm>

using namespace std;
const int sigma_size = 10;
typedef pair<string, string> pii;

struct Node {
	int val;
	Node* next[sigma_size];

	Node() { 
		val = 0;
		memset(next, 0, sizeof(next));
	}
};

void clear(Node* &p);
void insert (Node* &p, int d, int L, int R, int tig);
void dfs(Node* p, string str);
int pushup(Node* &p, int tig);

map<string, int> g;

int n, m;
string l, r, name[105];
Node* root = NULL;

vector<pii> vec;

void init () {
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
		clear(root);

		printf("%lu\n", vec.size());
		for (int i = 0; i < vec.size(); i++)
			cout << vec[i].first << " " << vec[i].second << endl;
	}
	return 0;
}

int pushup (Node* &p, int tig) {
	if (p == NULL) {
		p = new Node;
		return p->val = tig;
	}

	if (p->val)
		tig = p->val;

	int k = pushup(p->next[0], tig);
	for (int i = 1; i < sigma_size; i++) {
		if (k != pushup(p->next[i], tig))
			k = 0;
	}

	return p->val = k;
}

void dfs (Node* p, string str) {
	if (p != root && p->val) {
		if (p->val <= m && name[p->val] !=  "invalid")
			vec.push_back(make_pair(str, name[p->val]));
		return ;
	}

	for (int i = 0; i < sigma_size; i++) {
		if (p->next[i] != NULL) {
			char ch = '0' + i;
			dfs(p->next[i], str + ch);
		}
	}
}

void insert (Node* &p, int d, int L, int R, int tig) {
	if (p == NULL)
		p = new Node;

	if (p->val)
		tig = p->val;

	if (d >= l.length()) {
		p->val = tig;
		return;
	}

	if (L == 0 && R == 0) {
		p->val = tig;
		return;
	} else if (L == 0) {
		insert(p->next[r[d]-'0'], d + 1, 0, 1, tig);
		for (int i = 0; '0' + i < r[d]; i++)
			insert(p->next[i], d + 1, 0, 0, tig);
	} else if (R == 0) {
		insert(p->next[l[d]-'0'], d + 1, 1, 0, tig);
		for (int i = l[d] - '0' + 1; i < sigma_size; i++)
			insert(p->next[i], d + 1, 0, 0, tig);
	} else if (r[d] == l[d]) {
		insert(p->next[l[d]-'0'], d + 1, 1, 1, tig);
	} else {
		insert(p->next[l[d]-'0'], d + 1, 1, 0, tig);
		insert(p->next[r[d]-'0'], d + 1, 0, 1, tig);
		for (int i = l[d] + 1; i < r[d]; i++)
			insert(p->next[i-'0'], d + 1, 0, 0, tig);
	}
}

void clear(Node* &p) {
	for (int i = 0; i < sigma_size; i++) {
		if (p->next[i] != NULL)
			clear(p->next[i]);
	}
	delete p;
	p = NULL;
}
