#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>

using namespace std;
typedef long long ll;
const int D = 12 * 60;
const int lit[3] = {4, 11, 12};
const int maxn = 7005;

int N, pos[maxn], v[maxn];

ll gcd (ll a, ll b) {
	return b == 0 ? a : gcd(b , a % b);
}

ll lcm (ll a, ll b) {
	return a / gcd(a, b) * b;
}

void init () {
	queue<int> que;
	int c[3], s[3][20];

	memset(v, 0, sizeof(v));
	for (int i = 1; i <= N; i++)
		que.push(i);

	for (int k = 0; k < 2; k++) {
		memset(c, 0, sizeof(c));
		for (int i = 0; i < D; i++) {
			int p = 0;

			while (true) {
				if (c[p] == lit[p]) {
					while (c[p])
						que.push(s[p][--c[p]]);
					p++;
				} else {
					s[p][c[p]++] = que.front();
					que.pop();
					break;
				}
			}
		}

		for (int j = 10; j >= 0; j--)
			que.push(s[2][j]);
		que.push(s[2][11]);
	}

	int mv = 1;
	while (!que.empty()) {
		pos[mv++] = que.front();
		que.pop();
	}
}

ll solve () {
	init();

	ll ret = 1;

	for (int i = 1; i <= N; i++) {
		if (v[i])
			continue;

		int mv = i;
		ll cnt = 0;

		while (v[mv] == 0) {
			v[mv] = 1;
			cnt++;
			mv = pos[mv];
		}
		ret = lcm(ret, cnt);
	}
	return ret;
}

int main () {
	while (scanf("%d", &N) == 1 && N) {
		printf("%d balls cycle after %lld days.\n", N, solve());
	}
	return 0;
}
