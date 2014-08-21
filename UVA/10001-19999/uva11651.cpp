#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;
const int maxn = 155;
const ll MOD = 1ll<<32;

struct Mat {
	int r, c;
	ll arr[maxn][maxn];

	Mat (int r = 0, int c = 0) { set(r, c); }

	void set(int r, int c) {
		this->r = r;
		this->c = c;
		memset(arr, 0, sizeof(arr));
	}

	Mat operator * (const Mat& u) {
		Mat ret(r, u.c);
		for (int k = 0; k < c; k++) {
			for (int i = 0; i < r; i++) {
				if (arr[i][k] == 0)
					continue;

				for (int j = 0; j < u.c; j++)
					ret.arr[i][j] = (ret.arr[i][j] + arr[i][k] * u.arr[k][j]) % MOD;
			}
		}
		return ret;
	}
};

int base, N;
ll dp[maxn][maxn], score;

void init () {
	scanf("%d%llu", &base, &score);

	N = (base-1) * (base-1);
	memset(dp, 0, sizeof(dp));
	for (int i = 0; i <= N; i++)
		dp[0][i] = 1;

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < base; j++) {
			for (int k = 0; k < base; k++) {
				int f = (j - k) * (j - k);

				if (i + f > N || f == 0)
					continue;

				dp[i+f][j] = (dp[i+f][j] + dp[i][k]) % MOD;
			}
		}
	}
}

Mat change () {
	Mat ret(N*base, 1);

	for (int i = 1; i <= N; i++)
		for (int j = 0; j < base; j++)
			ret.arr[(i-1)*base+j][0] = dp[i][j];
	return ret;
}

Mat build () {
	int n = N * base;
	Mat x(n, n);

	for (int i = base; i < n; i++)
		x.arr[i-base][i] = 1;

	for (int i = 0; i < base; i++) {
		for (int j = 0; j < base; j++) {
			if (i == j)
				continue;
			int k = N - (i-j) * (i-j);
			x.arr[(N-1)*base+i][k*base+j] = 1;
		}
	}
	return x;
}

Mat pow_mat (Mat ret, int n) {
	Mat x = build();
	while (n) {
		if (n&1)
			ret = x * ret;
		x = x * x;
		n >>= 1;
	}
	return ret;
}

ll solve () {

	ll ans = 0;
	if (score <= N) {
		for (int i = 1; i < base; i++)
			ans = (ans + dp[score][i]) % MOD;
		return ans;
	}

	Mat ret = change();
	ret = pow_mat(ret, score-N);

	for (int i = 1; i < base; i++)
		ans = (ans + ret.arr[(N-1)*base+i][0]) % MOD;
	return ans;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		init();
		printf("Case %d: %llu\n", kcas, solve());
	}
	return 0;
}
