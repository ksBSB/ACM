#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 10000000;

struct Tire {
	int sz;
	int ans;
	int node[maxn][2];
	int val[maxn];

	void init();
	int idx(char ch);
	void insert(char* s);
}tree;

int main () {
	int cas, n;
	char str[205];
	scanf("%d", &cas);
	while (cas--) {
		tree.init();
		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%s", str);
			tree.insert(str);
		}

		printf("%d\n", tree.ans);
	}
	return 0;
}

void Tire::init() {
	sz = 1;
	ans = 0;
	memset(val, 0, sizeof(val));
	memset(node[0], 0, sizeof(node[0]));
}

int Tire::idx(char ch) {
	return ch - '0';
}

void Tire::insert(char* s) {
	int n = strlen(s), u = 0;
	for (int i = 0; i < n; i++) {
		int v = idx(s[i]);

		if (node[u][v] == 0) {
			memset(node[sz], 0, sizeof(node[sz]));
			node[u][v] = sz++;
		}
		u = node[u][v];
		val[u] += (i + 1);
		ans = max(ans, val[u]);
	}
}
