#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>

#define pii pair<int,int>
using namespace std;

const int N = 1500000;
const int M = 30;
const int INF = 0x3f3f3f3f;

struct state {
	int u;
	int d;
};

struct cmp {
	bool operator () (const pii& a, const pii& b) {
		return a.first < b.first;
	}
};

int n, m, tmp;
char s[M], b[M];
int cur, t[M], d, vis[N];
vector<state> v[N];

void add(int x, int y) {
	state cur;
	cur.u = y, cur.d = d;
	v[x].push_back(cur);
}

void dfs(int c, int *t) {
	
	if (c >= n) {
		int far = 0, son = 0, k;
		for (int i = 0; i < n; i++) {

			if (b[i] == '-')		k = 0;
			else if (b[i] == '+')	k = 1;
			else					k = t[i];

			far = far * 2 + t[i];
			son = son * 2 + k;
		}
		add(far, son);
		return;
	}

	if (s[c] == '0') {

		for (t[c] = 0; t[c] < 2; t[c]++)
			dfs(c + 1, t);
	} else {

		if (s[c] == '+')
			t[c] = 1;
		else
			t[c] = 0;
		dfs(c + 1, t);
	}
}

void init() {

	int t[N];
	tmp = 1 << n;
	for (int i = 0; i < tmp; i++)	v[i].clear();

	for (int i = 0; i < m; i++) {
		scanf("%d%s%s", &d, s, b);

		memset(t, 0, sizeof(t));
		dfs(0, t);
	}	
}

void solve() {
	int a[N], Min, c;
	priority_queue< pii, vector<pii>, greater<pii> > que;

	memset(a, INF, sizeof(a));
	memset(vis, 0, sizeof(vis));
	a[tmp - 1] = 0;

	que.push(make_pair(a[tmp - 1], tmp - 1) );

	while ( !que.empty() ) {

		pii cur = que.top(); que.pop();
		int x = cur.second;
		if (vis[x]) continue;
		vis[x] = 1;

		int f = v[x].size();
		for (int j = 0; j < f; j++) {
			int y = v[x][j].u;
			if ( a[y] > a[x] + v[x][j].d ) {
				a[y] = a[x] + v[x][j].d;
				que.push( make_pair(a[y], y) );
			}
		}
	}
	if (a[0] == INF)
		printf("Bugs cannot be fixed.\n\n");
	else
		printf("Fastest sequence takes %d seconds.\n\n", a[0]);
}

int main () {
	int cas = 1;
	while (scanf("%d%d", &n, &m), n + m) {
		init();
		printf("Product %d\n", cas++);
		solve();
	}
	return 0;
}
