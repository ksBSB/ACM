#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e4 + 5;

char ans[maxn][maxn];

struct Node {
	int idx, ch[2];
	Node (int idx = 0): idx(idx) { memset(ch, 0, sizeof(ch)); }
};

struct Tree {
	int n;
	Node nd[maxn];

	void init () { n = 0; }

	int newNode (int val) {
		nd[++n] = Node(val);
		return n;
	}

	void insert(int& u, int val) {
		if (u == 0) {
			u = newNode(val);
			return;
		}

		if (val < nd[u].idx)
			insert(nd[u].ch[0], val);
		else
			insert(nd[u].ch[1], val);
	}

	void solve (int u, int d, char* s) {
		if (u == 0) return;
		s[d] = '\0';
		strcpy(ans[nd[u].idx], s);

		if (nd[u].ch[0]) {
			s[d] = 'E';
			solve(nd[u].ch[0], d + 1, s);
		}
		if (nd[u].ch[1]) {
			s[d] = 'W';
			solve(nd[u].ch[1], d + 1, s);
		}
	}
}solver;

int main () {
	int cas, n, x;
	scanf("%d", &cas);
	while (cas--) {
		solver.init();

		scanf("%d", &n);
		if (n == 0) continue;

		scanf("%d", &x);
		int root = solver.newNode(x);
		for (int i = 1; i < n; i++) {
			scanf("%d", &x);
			solver.insert(root, x);
		}

		char s[maxn];
		solver.solve(root, 0, s);

		scanf("%d", &n);
		while (n--) {
			scanf("%d", &x);
			printf("%s\n", ans[x]);
		}
	}
	return 0;
}

