#include <stdio.h>
#include <math.h>
long long n, b, k;

struct state {
	long long s[2][2];
	state(long long a = 0, long long b = 0, long long  c = 0, long long d = 0) {
		s[0][0] = a, s[0][1] = b, s[1][0] = c, s[1][1] = d;
	}
}tmp(1, 0, 0, 1), c(1, 1, 1, 0);

state count(const state& p, const state& q) {
	state f;
	for (int i = 0; i < 2; i++)
		for (int j = 0; j < 2; j++)
			f.s[i][j] = (p.s[i][0] * q.s[0][j] + p.s[i][1] * q.s[1][j]) % b;
	return f;
}

state solve(long long k) {
	if (k == 0) return tmp;
	else if (k == 1) return c;

	state a = solve(k / 2);

	a = count(a, a);
	if (k % 2) a = count(a, c);
	return a;
}

int main () {
	int m;
	while (scanf("%lld%d", &n, &m) == 2) {
		b = pow(2, m);
		if (n) {
			state ans = solve(n - 1);
			k = ans.s[0][0];
		} else
			k = 0;
		printf("%lld\n", k);
	}
	return 0;
}
