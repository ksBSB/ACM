#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 50;
const int MOD = 10;

struct Mat {
	int r, c, arr[maxn][maxn];
	Mat () { memset(arr, 0, sizeof(arr)); }
	Mat (int r = 0, int c = 0) { set(r, c); }
	void set (int r, int c) {
		this->r = r;
		this->c = c;
		memset(arr, 0, sizeof(arr));
	}

	Mat operator * (const Mat& u) {
		Mat ret(r, u.c);
		for (int k = 0; k < c; k++) {
			for (int i = 0; i < r; i++)
				for (int j = 0; j < u.c; j++)
					ret.arr[i][j] = (ret.arr[i][j] + arr[i][k] * u.arr[k][j]) % MOD;
		}
		return ret;
	}

	Mat operator + (const Mat& u) {
		Mat ret(r, c);
		for (int i = 0; i < r; i++)
			for (int j = 0; j < c; j++)
				ret.arr[i][j] = (arr[i][j] + u.arr[i][j]) % MOD;
		return ret;
	}
};

int N, K;

Mat pow_mat (Mat x, int n) {
	Mat ret(N, N);
	for (int i = 0; i < N; i++)
		ret.arr[i][i] = 1;

	while (n) {
		if (n&1)
			ret = ret * x;
		x = x * x;
		n >>= 1;
	}
	return ret;
}

Mat solve (Mat x, int n) {
	if (n == 1)
		return x;

	Mat ret(N, N);
	for (int i = 0; i < N; i++)
		ret.arr[i][i] = 1;

	if (n == 0)
		return ret;
	ret = (ret + pow_mat(x, n>>1)) * solve(x, n>>1);

	if (n&1)
		ret = ret + pow_mat(x, n);
	return ret;
}

void put (Mat u) {
	for (int i = 0; i < u.r; i++) {
		printf("%d", u.arr[i][0]);
		for (int j = 1; j < u.c; j++)
			printf(" %d", u.arr[i][j]);
		printf("\n");
	}
}

int main () {
	while (scanf("%d%d", &N, &K) == 2 && N) {
		Mat ans(N, N);
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				scanf("%d", &ans.arr[i][j]);
				ans.arr[i][j] %= MOD;
			}
		}

		ans = solve(ans, K);
		put(ans);
		printf("\n");
	}
	return 0;
}
