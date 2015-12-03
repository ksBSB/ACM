#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 30;
typedef long long ll;

int C[maxn][maxn];
char S[maxn];
int N, K, cnt[maxn];

void init () {
	scanf("%s%d", S, &K);
	N = strlen(S);
	memset(cnt, 0, sizeof(cnt));
	for (int i = 0; i < N; i++)
		cnt[S[i]-'a']++;
}

ll count(int n) {
	ll ret = 1;
	for (int i = 0; i < 26; i++) {
		ret *= C[n][cnt[i]];
		n -= cnt[i];
	}
	return ret;
}

void solve (int d, int k) {
	if (d > N) {
		printf("\n");
		return;
	}
	int i;
	for (i = 0; i < 26; i++) if (cnt[i]) {
		cnt[i]--;
		ll t = count(N-d);
		if (t >= k) break;
		else k -= t;
		cnt[i]++;
	}
	printf("%c", 'a' + i);
	solve(d + 1, k);
}

int main () {
	for (int i = 0; i <= 20; i++) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; j++)
			C[i][j] = C[i-1][j] + C[i-1][j-1];
	}

	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case %d: ", kcas);

		if (count(N) < K)
			printf("Impossible\n");
		else
			solve(1, K);
	}
	return 0;
}
