#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;
typedef pair<int,int> pii;
const int maxn = 1005;
const int dir[4][2] = { {0, 1}, {1, 0}, {-1, 0}, {0, -1} };

int N, M, D[maxn * 2], R[maxn][maxn], V[maxn][maxn];
char G[maxn][maxn], A[maxn * 2];
vector<pii> T;

void bfs () {
	T.clear();
	T.push_back(make_pair(1, 1));
	queue<pii> que;
	que.push(make_pair(1, 1));
	V[1][1] = 1;

	int ans = 2;

	while (!que.empty()) {
		int x = que.front().first;
		int y = que.front().second;
		que.pop();

		for (int i = 0; i < 4; i++) {
			int p = x + dir[i][0];
			int q = y + dir[i][1];
			if (p <= 0 || p > N || q <= 0 || q > M || G[p][q] == '1' || V[p][q])
				continue;
			V[p][q] = 1;
			que.push(make_pair(p, q));

			if (p + q > ans) {
				ans = p + q;
				T.clear();
			}
			if (p + q == ans)
				T.push_back(make_pair(p, q));
		}
	}
}

void solve () {
	queue<pii> Q;
	if (G[1][1] == '1')
		Q.push(make_pair(1, 1));
	else {
		bfs();
		for (int i = 0; i < T.size(); i++)
			Q.push(T[i]);
	}

	while (!Q.empty()) {
		int x = Q.front().first;
		int y = Q.front().second;
		Q.pop();

		if (D[x + y] && G[x][y] == '1')
			continue;

		for (int i = 0; i < 2; i++) {
			int p = x + dir[i][0];
			int q = y + dir[i][1];

			if (p <= 0 || p > N || q <= 0 || q > M)
				continue;

			R[p][q] = 3 - i;
			if (G[p][q] == '0')
				D[p+q] = 1;
			if (V[p][q] == 0) {
				V[p][q] = 1;
				Q.push(make_pair(p, q));
			}
		}
	}
}

void put () {
	int x = N, y = M, c = 0;
	while (true) {
		A[c++] = G[x][y];
		int t = R[x][y];
		if (t == -1)
			break;
		x = x + dir[t][0];
		y = y + dir[t][1];
	}

	while (c && A[c-1] == '0')
		c--;

	if (c == 0) {
		printf("0\n");
		return;
	}

	for (int i = c-1; i >= 0; i--)
		printf("%c", A[i]);
	printf("\n");
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &N, &M);
		memset(D, 0, sizeof(D));
		memset(R, -1, sizeof(R));
		memset(V, 0, sizeof(V));
		for (int i = 1; i <= N; i++)
			scanf("%s", G[i] + 1);
		solve();
		put();
	}
	return 0;
}
