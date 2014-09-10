#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 100005;

bool flag;
int N, M, C, t[maxn], v[maxn], f[maxn];
vector<int> g[maxn];

inline int getfar(int x) {
	return x == f[x] ? x : f[x] = getfar(f[x]);
}

void init () {
	scanf("%d%d%d", &N, &M, &C);
	int x, a, b, n = N;

	memset(t, 0, sizeof(t));
	memset(v, 0, sizeof(v));
	for (int i = 0; i <= N; i++) {
		f[i] = i;
		g[i].clear();
	}

	for (int i = 0; i < C; i++) {
		scanf("%d", &x);
		t[x] = 1;
	}

	for (int i = 0; i < M; i++) {
		scanf("%d%d", &a, &b);

		g[a].push_back(b);
		g[b].push_back(a);

		int p = getfar(a), q = getfar(b);
		if (p != q) {
			f[p] = q;
			n--;
		}
	}

	flag = (n == 1);
}

void bfs(int s) {
	queue<int> que;
	t[s] = 0; v[s] = 1;
	que.push(s);

	while (!que.empty()) {
		int u = que.front();
		que.pop();

		for (int i = 0; i < g[u].size(); i++) {
			int k = g[u][i];

			if (v[k] || t[k]) {
				v[k] = 1;
				t[k] = 0;
				continue;
			}

			v[k] = 1;
			que.push(k);
		}
	}
}

bool judge () {
	int n, x;
	scanf("%d", &n);

	if (n < C)
		flag = false;

	for (int i = 0; i < n; i++) {
		scanf("%d", &x);
		if (flag == false || (t[x] && i)) {
			flag = false;
			continue;
		}
		bfs(x);
	}
	return flag;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%s\n", judge() ? "Yes" : "No");
	}
	return 0;
}
