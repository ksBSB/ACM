#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;

const ll mod = 1000000007;
const int maxn = 1e5+5;

int N, M, T, P[maxn];

int pow_mod(ll x, int n) {
	ll ret = 1;
	while (n) {
		if (n&1)
			ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

int query(int n, int pos) {
	int c = 1;
	for (int i = n - 1; i; i--) {
		if (P[i] == 1) {
			if (pos <= T)
				pos = pos * 2 - 1;
			else
				pos = (pos - T) * 2;
		} else if (P[i] == 2)
			pos = N - pos + 1;
		else if (P[i] == 3)
			 c = (c + c) % (mod - 1);
	}
	return pow_mod(pos, c);
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int x;
		char op[5];
		memset(P, 0, sizeof(P));

		scanf("%d%d", &N, &M);
		T = (N + 1) / 2;
		for (int i = 1; i <= M; i++) {
			scanf("%s%d", op, &x);
			if (op[0] == 'Q')
				printf("%d\n", query(i, x));
			else
				P[i] = x;
		}
	}
	return 0;
}
