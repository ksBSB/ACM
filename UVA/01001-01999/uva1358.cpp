#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

const int maxn = 20;

int len, jump[maxn];

void get_jump(char* s) {
	int p = 0;
	len = strlen(s+1);
	for (int i = 2; i <= len; i++) {
		while (p && s[p+1] != s[i])
			p = jump[p];

		if (s[p+1] == s[i])
			p++;
		jump[i] = p;
	}
}

ll solve () {
	int n;
	ll dp[maxn];
	char s[maxn];

	scanf("%d%s", &n, s+1);

	get_jump(s);
	dp[0] = 0;

	for (int i = 1; i <= len; i++) {

		ll& ans = dp[i];
		ans = dp[i-1] + n;

		for (int j = 0; j < n; j++) {
			if (s[i] == 'A' + j)
				continue;

			int p = i-1;
			while (p && s[p+1] != j + 'A')
				p = jump[p];

			if (s[p+1] == j + 'A')
				p++;

			ans += dp[i-1] - dp[p];
		}
	}

	return dp[len];
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		printf("Case %d:\n%lld\n", kcas, solve());

		if (kcas < cas)
			printf("\n");
	}
	return 0;
}
