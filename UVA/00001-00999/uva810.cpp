#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 105;
const int dir[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1} };

char s[maxn];
int N, M, Sx, Sy, U, F, G[maxn][maxn], vis[maxn][maxn][10][10];
int to[10][10];
vector<pii> ans;

struct State {
	int x, y, u, f, pre;
	State(int x = 0, int y = 0, int u = 0, int f = 0, int pre = 0): x(x), y(y), u(u), f(f), pre(pre) {}
}Q[maxn * maxn * maxn];

void rotate(int& u, int& f, int d) {
	if (d == 0) {int tmp = f; f = 7 - u; u = tmp;}  
	if (d == 1) {int tmp = u; u = 7 - f; f = tmp;}  
	if (d == 2) u = 7 - to[u][f];  
	if (d == 3) u = to[u][f];  
}

void init () {
	scanf("%d%d%d%d%d%d", &N, &M, &Sx, &Sy, &U, &F);
	memset(vis, 0, sizeof(vis));
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= M; j++)
			scanf("%d", &G[i][j]);
}

void put (int p) {
	if (p == -1) return;
	put(Q[p].pre);
	ans.push_back(make_pair(Q[p].x, Q[p].y));
}

bool solve () {
	ans.clear();
	int head = 0, rear = 0;
	Q[rear++] = State(Sx, Sy, U, F, -1);
	vis[Sx][Sy][U][F] = 1;

	while (head < rear) {
		State cur = Q[head++];

		for (int i = 0; i < 4; i++) {
			int p = cur.x + dir[i][0];
			int q = cur.y + dir[i][1];
			int u = cur.u, f = cur.f;

			if (p <= 0 || p > N || q <= 0 || q > M) continue;
			if (G[p][q] != -1 && G[p][q] != cur.u) continue;
			
			if (p == Sx && q == Sy) {
				put(head-1);
				ans.push_back(make_pair(p, q));
				for (int i = 0; i < ans.size(); i++) {
					if (i % 9 == 0) printf("\n  ");
					printf("(%d,%d)%c", ans[i].first, ans[i].second, i == ans.size()-1 ? '\n' : ',');
				}
				return true;
			}
			rotate(u, f, i);
			if (vis[p][q][u][f]) continue;
			vis[p][q][u][f] = 1;
			Q[rear++] = State(p, q, u, f, head-1);
		}
	}
	return false;
}

int main () {
	to[1][2] = 4; to[1][3] = 2; to[1][4] = 5; to[1][5] = 3;  
	to[2][1] = 3; to[2][3] = 6; to[2][4] = 1; to[2][6] = 4;  
	to[3][1] = 5; to[3][2] = 1; to[3][5] = 6; to[3][6] = 2;  
	to[4][1] = 2; to[4][2] = 6; to[4][5] = 1; to[4][6] = 5;  
	to[5][1] = 4; to[5][3] = 1; to[5][4] = 6; to[5][6] = 3;  
	to[6][2] = 3; to[6][3] = 5; to[6][4] = 2; to[6][5] = 4; 
	while (scanf("%s", s) == 1 && strcmp(s, "END")) {
		init ();
		printf("%s", s);
		if (!solve()) printf("\n  No Solution Possible\n");
	}
	return 0;
}
