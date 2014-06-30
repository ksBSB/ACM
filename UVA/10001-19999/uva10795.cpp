#include <stdio.h>
#include <string.h>
#include <math.h>

#define ll long long

const int N = 100;

ll T[N];
int n, tmp, now[N], end[N];

void init() {
	memset(T, 0, sizeof(T));
	T[0] = 1;
	for (int i = 1; i <= 63; i++)
		T[i] = T[i - 1] * 2;
}

void input() {
	memset(now, 0, sizeof(now));
	memset(end, 0, sizeof(end));

	for (int i = 1; i <= n; i++)	scanf("%d", &now[i]);
	for (int i = 1; i <= n; i++)	scanf("%d", &end[i]);
}

ll move(int d, int aid) {
	if (d == 0) return 0;
	if (now[d] == aid)
		return move(d - 1, aid);
	else
		return move(d - 1, 6 - now[d] - aid) + T[d - 1];
}

ll solve() {
	int i;
	ll ans = 0;
	for (i = n; i; i--) {
		if (now[i] != end[i]) {
			tmp = 6 - now[i] - end[i];
			ans += move(i - 1, tmp) + 1;
			i--;
			break;
		}
	}

	for (; i; i--) {
		if (end[i] != tmp) {
			tmp = 6 - end[i] - tmp;
			ans += T[i - 1];
		}
	}
	return ans;
}

int main () {
	int cas = 1;
	init();
	while (scanf("%d", &n) == 1 && n) {
		input();
		printf("Case %d: %lld\n", cas++, solve() );
	}
	return 0;
}
