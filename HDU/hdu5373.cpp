#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

const int mod = 11;
int s;

int solve (int k, int n) {
	int a[105], ca = 0;
	while (n) {
		a[ca++] = n % 10;
		n /= 10;
	}

	for (int i = ca-1; i >= 0; i--) {
		s += a[i];
		k = (k * 10 + a[i]) % mod;
	}
	return k;
}

bool judge (int n, int t) {
	if (t == 0)
		return n % mod == 0;

	s = 0;
	int ret = solve(0, n);

	for (int i = 1; i <= t; i++)
		ret = solve(ret, s);
	return ret == 0;
}

int main () {
	int n, t, cas = 1;
	while (scanf("%d%d", &n, &t) == 2) {
		if (n == -1 || t == -1)
			break;
		printf("Case #%d: %s\n", cas++, judge(n, t) ? "Yes" : "No");
	}
	return 0;
}
