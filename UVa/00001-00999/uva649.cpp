#include <stdio.h>
#include <string.h>

#define max(a,b) (a)>(b)?(a):(b)
#define cal(a,b) (a&(1<<b))

const int N = 30;
const int INF = 0x3f3f3f3f;

int ans, recAns, n, m, k[N], cnt;

inline void init () {
	cnt = 0;
	m = (n+1)/2;
	ans = INF;
	memset(k, 0, sizeof(k));

	int u, a, t;
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &u, &t);
		u--;
		k[u] |= (1<<u);
		for (int j = 0; j < t; j++) {
			scanf("%d", &a);
			k[u] |= (1<<(a-1));
		}
	}
}

inline int bitcount (int x) {
	return x == 0 ? 0 : (bitcount(x/2) + (x&1));
}

inline int solve (int s) {

	int val = 0, t;
	int c = bitcount(s);
	int ss = ((1<<n) - 1) ^ s;

	for (int i = 0; i < n; i++) {
		if (cal(s, i)) {
			t = bitcount(s&k[i]);
			val = max(val, c - t);
		} else { 
			t = bitcount(ss&k[i]);
			val = max(val, n - c - t);
		}

		if (val > ans) return ans;
	}
	return val;
}

inline void dfs (int d, int s) {

	if (cnt > m || d - cnt > m) return;

	if (d == n) {
		int cost = solve (s);
		if (cost < ans) {
			ans = cost;
			recAns = s;
		}
		return;
	}

	dfs (d + 1, s);

	cnt++;
	dfs (d + 1, s | (1<<d));
	cnt--;
}

inline void put () {
	printf("%d\n", ans);

	int a = 0, b = 0, A[N], B[N];
	for (int i = 0; i < n; i++) {
		(recAns & (1<<i)) == 0 ? A[a++] = i + 1 : B[b++] = i + 1;
	}

	printf("%d", a);
	for (int i = 0; i < a; i++)
		printf(" %d", A[i]);
	printf("\n");

	printf("%d", b);
	for (int i = 0; i < b; i++)
		printf(" %d", B[i]);
	printf("\n");
}

int main () {
	int cas = 0;

	while (scanf("%d", &n) == 1) {
		if (cas++) printf("\n");

		init ();
		dfs (0, 0);
		put ();
	}
	return 0;
}
