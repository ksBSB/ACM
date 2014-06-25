#include <cstdio>
#include <cstring>

typedef long long ll;
const ll MOD = 20140518;
const int N = 20;

struct mat {
	int r, c;
	ll s[N][N];

	void init (int k, int sign) {

		memset(s, 0, sizeof(s));
		if (sign) {
			r = c = k;
			for (int i = 1; i <= r; i++) {
				for (int j = i; j <= r; j++)
					s[i][j] = 1;
				if (i == r)
					continue;
				s[i+1][i] = k+1-i;
			}
		} else {
			r = k;
			c = 1;
			s[1][1] = k+1;
		}
	}

	void put() {
		for (int i = 1; i <= r; i++) {
			for (int j = 1; j <= c; j++)
				printf("%lld ", s[i][j]);
			printf("\n");
		}
	}
};

mat mul(mat a, mat b) {
	mat ans;
	memset(ans.s, 0, sizeof(ans.s));

	for (int i = 1; i <= a.r; i++) {
		for (int j = 1; j <= b.c; j++) {

			for (int x = 1; x <= a.c; x++)
				ans.s[i][j] = (ans.s[i][j] + a.s[i][x] * b.s[x][j])%MOD;
		}
	}
	ans.r = a.r;
	ans.c = b.c;
	return ans;
}

ll n;
int k;

ll solve (ll x) {
	if (x == 1)
		return k+1;
	x--;
	mat ans, cur;
	ans.init(k, 0);
	cur.init(k, 1);

	while (x) {
		if (x&1)
			ans = mul(cur, ans);

		cur = mul(cur, cur);
		x /= 2;
	}

	int sum = 0;
	for (int i = 1; i <= k; i++)
		sum = (sum + ans.s[i][1]) % MOD;
	return sum;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%lld%d", &n, &k);
		printf("Case #%d: %lld\n", i, solve(n));
	}
	return 0;
}
