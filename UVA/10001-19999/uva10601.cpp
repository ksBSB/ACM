#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 12;

int u[maxn+5], rod[maxn+5];
ll C[maxn+5][maxn+5];

void init () {
	memset(C, 0, sizeof(C));
	for (int i = 0; i <= maxn; i++) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; j++)
			C[i][j] = C[i-1][j-1] + C[i-1][j];
	}
}

ll solve (ll k) {
	int n = 0;
	ll ret = 1;

	for (int i = 0; i < 6; i++) {
		if (u[i] % k)
			return 0;
		u[i] /= k;
		n += u[i];
	}

	for (int i = 0; i < 6; i++) {
		ret *= C[n][u[i]];
		n -= u[i];
	}
	//printf("%lld %lld!!\n", k, ret);
	return ret;
}

ll still () {
	memcpy(u, rod, sizeof(rod));
	return solve(1);
}

ll rot_point () {
	memcpy(u, rod, sizeof(rod));
	return 4 * 2 * solve(3);
}

ll rot_edge () {
	ll ret = 0;
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6; j++) {
			if (rod[i] && rod[j]) {
				memcpy(u, rod, sizeof(rod));
				u[i]--; u[j]--;
				ret += 6 * solve(2);
			}
		}
	}
	return ret;
}

ll rot_plane () {
	ll ret = 0;
	memcpy(u, rod, sizeof(rod));
	ret += solve(4) * 2 * 3;
	memcpy(u, rod, sizeof(rod));
	ret += solve(2) * 3;
	return ret;
}

inline ll polya () {
	return still() + rot_point() + rot_edge() + rot_plane();
}

int main () {
	init();

	int cas, x;
	scanf("%d", &cas);
	while (cas--) {

		memset(rod, 0, sizeof(rod));
		for (int i = 0; i < maxn; i++) {
			scanf("%d", &x);
			rod[x-1]++;
		}

		printf("%lld\n", polya() / 24);
	}
	return 0;
}
