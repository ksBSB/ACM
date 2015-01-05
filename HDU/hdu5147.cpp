#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 50005;

int N, arr[maxn], fenw[maxn], lef[maxn], rig[maxn];

#define lowbit(x) ((x)&(-x))
void add(int x, int v) {
	while (x <= N) {
		fenw[x] += v;
		x += lowbit(x);
	}
}

int sum(int x) {
	int ret = 0;
	while (x) {
		ret += fenw[x];
		x -= lowbit(x);
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		memset(fenw, 0, sizeof(fenw));
		for (int i = 1; i <= N; i++)
			scanf("%d", &arr[i]);

		ll ans = 0, tmp = 0;
		for (int i = 1; i <= N; i++) {
			lef[i] = sum(arr[i]);
			rig[i] = N - i - arr[i] + lef[i] + 1;
			add(arr[i], 1);
			tmp += rig[i];
		}

		for (int i = 1; i <= N; i++) {
			tmp -= rig[i];
			ans += tmp * lef[i];
		}
		printf("%I64d\n", ans);
	}
	return 0;
}
