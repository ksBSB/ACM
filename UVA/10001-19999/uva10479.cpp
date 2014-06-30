#include <stdio.h>
#include <string.h>

typedef unsigned long long ll;
const ll tmp = 1;
ll n;

int dfs(ll m, int d) {
	int c = 1;
	for (int i = d - 2; i >= 0; i--) {
		ll k = i ? tmp << (i-1) : tmp;
		for (int j = 0; j < c; j++) {
			if (k < m) m -= k;
			else return dfs(m, i);
		}
		c++;
	}
	return d;
}

int solve() {
	if (n == 1) return 0;
	n--;
	
	for (int i = 1; ; i++) {
		ll k = tmp << (i-1);
		if (k < n) n -= k;
		else return dfs(n, i);
	}
}

int main() {
	while (scanf("%llu", &n) == 1 && n) {
		printf("%d\n", solve());
	}
	return 0;
}
