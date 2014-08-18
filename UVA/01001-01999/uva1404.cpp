#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int sqrt_inf = 46340;
const int maxn = 2 * 1e9;

int np, pri[sqrt_inf];
bool vis[maxn+5];
vector<int> vec;

void prime_table (int n) {
	np = 0;
	memset(vis, 0, sizeof(vis));

	for (int i = 2; i <= n; i++) {
		if (vis[i])
			continue;

		pri[np++] = i;
		for (int j = i * i; j <= n; j += i)
			vis[j] = 1;
	}
}

int solve () {
	int ret = 0;
	int a, b, s, k;
	vec.clear();
	memset(vis, 0, sizeof(vis));

	scanf("%d%d%d%d", &a, &b, &k, &s);

	for (int i = 0; i < np && pri[i] * pri[i] <= b; i++) {
		int u = pri[i], d = (u - a % u) % u;

		if (u == a + d)
			d += u;

		while (d <= b - a) {
			vis[d] = 1;
			d += u;
		}
	}

	for (int i = 0; i <= b-a; i++) {
		if (vis[i] == 0 && a + i > 1)
			vec.push_back(a+i);
	}


	for (int i = 0; i + k - 1 < vec.size(); i++) {
		if (vec[i+k-1] - vec[i] == s)
			ret++;
	}

	return ret;
}

int main () {
	prime_table(sqrt_inf);

	int cas;
	scanf("%d", &cas);

	while (cas--) {
		printf("%d\n", solve());
	}
	return 0;
}
