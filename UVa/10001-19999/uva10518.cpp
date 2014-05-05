#include <stdio.h>
#include <string.h>
long long n;
int b;

struct state {
	int s[2][2];
	state(int a = 0, int b = 0, int c = 0, int d = 0) {
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
	int cas = 1;
	while (scanf("%lld%d", &n, &b), n || b) {
		state ans = solve(n);
		printf("Case %d: %lld %d %d\n", cas++, n, b,(2 * ans.s[0][0] - 1 + b) % b);
	}
	return 0;
}
