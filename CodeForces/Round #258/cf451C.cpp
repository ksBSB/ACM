#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

ll n, k, d1, d2;

bool check (ll u, ll t) {
	if (u % 3 || u > n)
		return false;

	return u / 3 >= t;
}

bool judge () {
	if (n % 3)
		return false;

	/*
		*/
	if (check(n - k + d1 + d2 * 2, d1 + d2))
		return true;

	if (check(n - k + 2 * d1 + d2, d1 + d2))
		return true;

	if (check(n - k + d1 + d2, max(d1, d2)))
		return true;

	if (check(n - k + 2 * max(d1, d2) - min(d1, d2), max(d1, d2)))
		return true;
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 0; i < cas; i++) {
		scanf("%lld%lld%lld%lld", &n, &k, &d1, &d2);
		printf("%s\n", judge() ? "yes" : "no");
	}
	return 0;
}
