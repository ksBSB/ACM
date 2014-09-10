#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;

const int maxn = 8;

struct point {
	ll x[3];

	void input() {
		for (int i = 0; i < 3; i++)
			scanf("%lld", &x[i]);
	}

	void output() {
		printf("%lld %lld %lld\n", x[0], x[1], x[2]);
	}

	point operator - (const point& u) {
		point ret;
		for (int i = 0; i < 3; i++)
			ret.x[i] = x[i] - u.x[i];
		return ret;
	}
}p[maxn+5];

ll dis (point u) {
	ll ret = 0;
	for (int i = 0; i < 3; i++)
		ret += u.x[i] * u.x[i];
	return ret;
}

bool check (int k) {
	int mv = 0;
	ll d[maxn+5];

	for (int i = 0; i < maxn; i++) {
		if (i == k)
			continue;

		d[mv++] = dis(p[k] - p[i]);
	}

	sort(d, d + 7);
	if (d[0] == 0)
		return false;

	if (d[0] != d[1] || d[0] != d[2])
		return false;

	if (d[3] != d[4] || d[3] != d[5])
		return false;

	if (d[0] * 2 != d[3] || d[0] * 3 != d[6])
		return false;
	return true;
}

bool judge () {

	for (int i = 0; i < maxn; i++)
		if (!check(i))
			return false;

	printf("YES\n");
	for (int i = 0; i < maxn; i++)
		p[i].output();
	return true;
}

bool dfs (int d) {

	if (d == maxn)
		return judge();

	sort(p[d].x, p[d].x + 3);
	do {
		if (dfs(d+1))
			return true;
	} while (next_permutation(p[d].x, p[d].x + 3));
	return false;
}

int main () {
	for (int i = 0; i < maxn; i++)
		p[i].input();

	if (!dfs(1))
		printf("NO\n");
	return 0;
}
