#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1005;

ll d, k;
int n, c, v[maxn][maxn], arr[maxn];

bool judge () {
	ll ret = 1;
	for (int i = 1; i <= d; i++) {
		ret *= k;
		if (ret >= n)
			return true;
	}
	return false;
}

void solve (int u) {

	if (d == u) {
		memcpy(v[c++], arr, sizeof(arr));
		return;
	}

	int& i = arr[u];
	for (i = 1; i <= k; i++) {
		solve(u+1);
		if (c == n)
			return;
	}
}

int main () {
	scanf("%d%lld%lld", &n, &k, &d);

	if (judge ()) {
		c = 0;
		solve(0);
		for (int i = 0; i < d; i++) {
			printf("%d", v[0][i]);
			for (int j = 1; j < n; j++)
				printf(" %d", v[j][i]);
			printf("\n");
		}
	} else
		printf("-1\n");
	return 0;
}
