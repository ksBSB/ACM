#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 20;
const int inf = 0x3f3f3f3f;

int N, L[maxn], Lx[maxn], Ly[maxn], slack[maxn];
int X[maxn], Y[maxn], W[maxn][maxn];
bool S[maxn], T[maxn];

void setCol (int c) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			W[i][j] = -(abs(X[i]-j) + abs(Y[i]-c));
	}
}

void setRow (int r) {
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			W[i][j] = -(abs(X[i]-r) + abs(Y[i]-j));
	}
}

bool match (int u) {
	S[u] = true;
	for (int i = 1; i <= N; i++) {
		if (!T[i]) {
			if (Lx[u] + Ly[i] == W[u][i]) {
				T[i] = true;
				if (!L[i] || match(L[i])) {
					L[i] = u;
					return true;
				}
			} else
				slack[i] = min(slack[i], Lx[u]+Ly[i]-W[u][i]);
		}
	}
	return false;
}

void update () {
	int a = inf;
	for (int i = 1; i <= N; i++) if (!T[i])
		a = min(a, slack[i]);

	for (int i = 1; i <= N; i++) if (S[i]) Lx[i] -= a;
	for (int i = 1; i <= N; i++) if (T[i]) Ly[i] += a;
}

int KM () {
	for (int i = 1; i <= N; i++) {
		Lx[i] = L[i] = Ly[i] = 0;
		for (int j = 1; j <= N; j++) 
			Lx[i] = max(Lx[i], W[i][j]);
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) slack[j] = inf;
		while (true) {
			for (int j = 1; j <= N; j++) S[j] = T[j] = false;
			if (match(i)) break;
			else update();
		}
	}

	int ret = 0;
	for (int i = 1; i <= N; i++)
		ret += (Lx[i] + Ly[i]);
	return -ret;
}

int solve () {
	int ans = inf;
	for (int i = 1; i <= N; i++) {
		setCol(i);
		ans = min(ans, KM());
		setRow(i);
		ans = min(ans, KM());
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			W[i][j] = -(abs(X[i]-j) + abs(Y[i]-j));
	}
	ans = min(ans, KM());

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++)
			W[i][j] = -(abs(X[i]-j) + abs(Y[i]- (N-j+1)));
	}
	ans = min(ans, KM());
	return ans;
}

int main () {
	int cas = 1;
	while (scanf("%d", &N) == 1 && N) {
		for (int i = 1; i <= N; i++) scanf("%d%d", &X[i], &Y[i]);

		int ans = solve();
		printf("Board %d: %d moves required.\n\n", cas++, ans);
	}
	return 0;
}
