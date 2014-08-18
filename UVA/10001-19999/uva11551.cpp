#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 55;
const int MOD = 1000;

struct Mat {
	int r, c, arr[maxn][maxn];
	Mat (int r = 0, int c = 0) {
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
};

Mat pow_mat (Mat ret, Mat x, int n) {
	while (n) {
		if (n&1)
			ret = x * ret;
		x = x * x;
		n >>= 1;
	}
	return ret;
}

int main () {
	int cas, N, K;
	scanf("%d", &cas);

	while (cas--) {
		scanf("%d%d", &N, &K);
		Mat a(N, 1);
		for (int i = 0; i < N; i++) {
			scanf("%d", &a.arr[i][0]);
			a.arr[i][0] %= MOD;
		}

		int x, pos;
		Mat b(N, N);
		for (int i = 0; i < N; i++) {
			scanf("%d", &x);
			for (int j = 0; j < x; j++) {
				scanf("%d", &pos);
				b.arr[i][pos] = 1;
			}
		}

		a = pow_mat(a, b, K);

		printf("%d", a.arr[0][0]);
		for (int i = 1; i < N; i++)
			printf(" %d", a.arr[i][0]);
		printf("\n");
	}
	return 0;
}
