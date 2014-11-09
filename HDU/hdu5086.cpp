#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 447005;
const ll mod = 1e9+7;

int N;
ll A[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%I64d", &A[i]);
		ll ans = 0;
		for (int i = 1; i <= N; i++)
			ans = (ans + (A[i] * i) % mod * (N-i+1)) % mod;
		printf("%I64d\n", ans);
	}
	return 0;
}
