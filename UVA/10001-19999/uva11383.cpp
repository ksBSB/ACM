#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 505;
const int inf = 0x3f3f3f3f;

int N, L[maxn];
int Lx[maxn], Ly[maxn], W[maxn][maxn];
bool S[maxn], T[maxn];

int match(int i) {
	S[i] = true;
	for (int j = 1; j <= N; j++) {
		if (Lx[i] + Ly[j] == W[i][j] && !T[j]) {
			T[j] = true;
			if (!L[j] || match(L[j])) {
				L[j] = i;
				return true;
			}
		}
	}
	return false;
}

void update () {
	int a = inf;
	for (int i = 1; i <= N; i++) if (S[i]) {
		for (int j = 1; j <= N; j++) if (!T[j])
			a = min(a, Lx[i]+Ly[j]-W[i][j]);
	}
	for (int i = 1; i <= N; i++) {
		if (S[i]) Lx[i] -= a;
		if (T[i]) Ly[i] += a;
	}
}

void KM () {
	for (int i = 1; i <= N; i++) {
		L[i] = Lx[i] = Ly[i] = 0;
		for (int j = 1; j <= N; j++)
			Lx[i] = max(Lx[i], W[i][j]);
	}
	for (int i = 1; i <= N; i++) {
		while (true) {
			for (int j = 1; j <= N; j++) S[j] = T[j] = 0;
			if (match(i)) break;
			else update();
		}
	}
}

void init () {
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
			scanf("%d", &W[i][j]);
	KM();
}

int main () {
	int cas = 0;
	while (scanf("%d", &N) == 1) {
		init();
		int ans = 0;
		for (int i = 1; i <= N; i++) {
			printf("%d%c", Lx[i], i == N ? '\n' : ' ');
			ans += Lx[i];
		}
		for (int i = 1; i <= N; i++) {
			printf("%d%c", Ly[i], i == N ? '\n' : ' ');
			ans += Ly[i];
		}
		printf("%d\n", ans);
	}
	return 0;
}
