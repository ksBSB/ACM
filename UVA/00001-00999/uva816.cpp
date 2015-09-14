#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
const int maxn = 30;
const int dir[4][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};
typedef pair<int,int> pii;

struct State {
	int x, y, d, pre;
	State (int x = 0, int y = 0, int d = 0, int pre = 0): x(x), y(y), d(d), pre(pre) {}
}Q[100000];

map<char, int> M;
int Sx, Sy, Ex, Ey, vis[maxn][maxn][5];
char s[maxn], o[maxn], t[maxn];
vector<int> G[maxn][maxn][5];
vector<pii> ans;

void add (int x, int y, char* p) {
	int n = strlen(p);
	int d = M[p[0]];
	for (int i = 1; i < n; i++)
		G[x][y][d].push_back((d + M[p[i]]) % 4);
}

void init () {
	memset(vis, 0, sizeof(vis));
	for (int i = 0; i < maxn; i++) {
		for (int j = 0; j < maxn; j++)
			for (int x = 0; x < 4; x++)
				G[i][j][x].clear();
	}
	scanf("%d%d%s%d%d", &Sx, &Sy, o, &Ex, &Ey);
	int x, y;
	while (scanf("%d", &x) == 1 && x) {
		scanf("%d", &y);
		while (scanf("%s", t) == 1 && t[0] != '*')
			add(x, y, t);
	}
}

void put(int p) {
	if (p == -1) return;
	put(Q[p].pre);
	ans.push_back(make_pair(Q[p].x, Q[p].y));
}

void bfs () {
	int head = 0, rear = 0, Sd = M[o[0]];
	ans.clear();
	G[Sx][Sy][Sd].push_back(Sd);
	Q[rear++] = State(Sx, Sy, Sd, -1);
	vis[Sx][Sy][Sd] = 1;

	while (head < rear) {
		State u = Q[head++];
		int x = u.x, y = u.y, d = u.d;

		if (x == Ex && y == Ey) {
			put(head-1);
			for (int i = 0; i < ans.size(); i++) {
				if (i % 10 == 0) printf("\n ");
				printf(" (%d,%d)", ans[i].first, ans[i].second);
			}
			printf("\n");
			return;
		}

		for (int i = 0; i < G[x][y][d].size(); i++) {
			int v = G[x][y][d][i];
			int p = x + dir[v][0];
			int q = y + dir[v][1];

			if (vis[p][q][v]) continue;
			vis[p][q][v] = 1;
			Q[rear++] = State(p, q, v, head-1);
		}
	}
	printf("\n  No Solution Possible\n");  
}

int main () {
	M['W'] = 0, M['N'] = 1, M['E'] = 2, M['S'] = 3;
	M['R'] = 1, M['F'] = 0, M['L'] = 3;
	while (scanf("%s", s) == 1 && strcmp(s, "END")) {
		init ();
		printf("%s", s);
		bfs();
	}
	return 0;
}
