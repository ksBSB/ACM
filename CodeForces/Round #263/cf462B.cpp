#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e5+5;
typedef long long ll;

int N, K, c[50];
char s[maxn];

int main () {
	scanf("%d%d%s", &N, &K, s);
	for (int i = 0; i < N; i++)
		c[s[i] - 'A']++;

	sort(c, c + 26);

	ll ans = 0;
	for (int i = 25; i >= 0; i--) {
		int cnt = min(K, c[i]);
		K -= cnt;
		ans += 1LL * cnt * cnt;
	}
	printf("%lld\n", ans);
	return 0;
}
