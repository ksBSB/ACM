#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;

int n = 0, bit[30], num[30], ans[30];

bool judge(int* a, int* b, int n) {
	for (int i = n - 1; i >= 0; i--) {
		if (a[i] != b[i])
			return a[i] > b[i];
	}
	return false;
}

bool cmp (int* a, int* b, int d) {
	for (int i = 1; i <= d; i++) {
		if (a[n-i] != b[n-i])
			return a[n-i] > b[n-i];
	}
	return false;
}

void dfs (int d, int p, bool flag) {
	if (d < p) {
		if (judge(bit, num, n) && judge(num, ans, n))
			memcpy(ans, num, sizeof(num));
		return;
	}

	int end = (flag ? bit[d] : 9);

	for (int i = end; i >= 0; i--) {
		int v = p;

		if (cmp(ans, num, n - d - 1))
			return;

		num[d] = i;
		if (num[d] != num[d+1]) {
			while (v <= d) {
				num[v++] = num[d];
				dfs(d - 1, v, flag && i == end);
			}
		} else
			dfs(d - 1, p, flag && i == end);
	}
}

ll solve () {
	ll a;
	scanf("%llu", &a);

	memset(ans, 0, sizeof(ans));
	memset(bit, 0, sizeof(bit));
	memset(num, 0, sizeof(num));

	n = 0;
	while (a) {
		bit[n++] = a % 10;
		a /= 10;
	}

	num[n] = 0;
	dfs(n-1, 0, 1);

	ll ret = 0;
	for (int i = n - 1; i >= 0; i--)
		ret = ret * 10 + ans[i];
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		printf("%llu\n", solve());
	}
	return 0;
}
