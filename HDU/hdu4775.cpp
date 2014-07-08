#include <cstdio>
#include <cstring>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 1e4;
const int INF = 2*1e9+10;
const int dir[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };
typedef pair<int, int> pii;

int N, Nw, Nb, X[maxn+5], Y[maxn+5], f[maxn+5], c[maxn+5];
map<pii, int> R;

void init () {
	scanf("%d", &N);

	Nw = N / 2;
	Nb = N - Nw;

	R.clear();
	for (int i = 0; i < N; i++) {
		f[i] = i;
		c[i] = 0;
	}
}

inline int bit (int x) {
	return x&1;
}

int getfar (int x) {
	return f[x] == x ? x : f[x] = getfar(f[x]);
}

inline bool isEmpty (int x, int y) {
	if (x <= 0 || y <= 0 || x >= INF || y >= INF)
		return false;
	if (R.count(make_pair(x, y)))
		return false;
	return true;
}

inline int count_empty (pii u) {
	int cnt = 0;
	for (int i = 0; i < 4; i++) {
		int x = u.first + dir[i][0];
		int y = u.second + dir[i][1];
		if (isEmpty(x, y))
			cnt++;
	}
	return cnt;
}

inline void link_board (int x, int y) {
	int fx = getfar(x);
	int fy = getfar(y);

	f[fy] = fx;
	c[fx] += c[fy];
	/**/
	c[fx]--;
}

int del_board (int col, int x, int y) {
	int cnt = 1;
	pii u = make_pair(x, y);
	queue<pii> que;
	que.push(u);

	f[R[u]] = R[u];
	R.erase(u);

	while (!que.empty()) {
		u = que.front();
		que.pop();

		for (int i = 0; i < 4; i++) {
			int p = u.first + dir[i][0];
			int q = u.second + dir[i][1];

			if (p <= 0 || p >= INF || q <= 0 || q >= INF)
				continue;

			pii v = make_pair(p, q);
			if (!R.count(v))
				continue;

			int set = R[v];

			if (bit(set) != col) {
				int k = getfar(set);
				c[k]++;
				continue;
			}

			f[R[v]] = R[v];
			R.erase(v);
			cnt++;
			que.push(v);
		}
	}
	return cnt;
}

 void del_empty (int k) {
	int fk = getfar(k);
	c[fk]--;

	if (c[fk] == 0) {
		int set = bit(fk);
		int cnt = del_board(set, X[fk], Y[fk]);
		if (set)
			Nw -= cnt;
		else
			Nb -= cnt;
	}
}

void solve () {

	for (int i = 0; i < N; i++) {
		scanf("%d%d", &X[i], &Y[i]);
		pii v = make_pair(X[i], Y[i]);
		c[i] = count_empty(v);
		R[v] = i;

		for (int j = 0; j < 4; j++) {
			int p = X[i] + dir[j][0];
			int q = Y[i] + dir[j][1];

			if (p <= 0 || q <= 0 || p >= INF || q >= INF)
				continue;

			pii u = make_pair(p, q);
			if (!R.count(u))
				continue;

			int k = R[u];
			if (bit(i) == bit(k))
				link_board(i, k);
			else
				del_empty(k);
		}

		int fi = getfar(i);
		if (c[fi] == 0) {
			int cnt = del_board(bit(fi), X[fi], Y[fi]);
			if (bit(fi))
				Nw -= cnt;
			else
				Nb -= cnt;
		}
	}
	printf("%d %d\n", Nb, Nw);
}

int main () {
	int cas;	
	scanf("%d", &cas);
	while (cas--) {
		init();
		solve();
	}
	return 0;
}
