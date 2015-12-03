#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
const int maxn = 17;
const int maxs = 1<<17;
const int inf = 0x3f3f3f3f;

int N, S[maxn][maxn], X[maxn], Y[maxn], D[maxs];

bool judge (int x1, int y1, int x2, int y2) {
	return x1 * y2 == y1 * x2;
}

void init () {
	scanf("%d", &N);
	for (int i = 0; i < N; i++)
		scanf("%d%d", &X[i], &Y[i]);

	memset(D, -1, sizeof(D));
	memset(S, 0, sizeof(S));
	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			int& s = S[i][j];
			s = 0;
			for (int k = 0; k < N; k++) {
				if (!judge(X[k]-X[i], Y[k]-Y[i], X[j]-X[i], Y[j]-Y[i]))
					s |= (1<<k);
			}
		}
	}
}

int bitcount(int x) { return x == 0 ? 0 : bitcount(x>>1) + (x&1); }

int dfs (int s) {
	if (D[s] != -1) return D[s];
	int c = bitcount(s);
	if (c == 0) return D[s] = 0;
	if (c <= 2) return D[s] = 1;
	int& ans = D[s];
	ans = inf;

	for (int i = 0; i < N; i++) if (s&(1<<i)) {
		for (int j = i+1; j < N; j++) if (s&(1<<j))
			ans = min(ans, dfs(s&S[i][j]) + 1);
		break;
	}
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case %d: %d\n", kcas, dfs((1<<N)-1));
	}
	return 0;
}
