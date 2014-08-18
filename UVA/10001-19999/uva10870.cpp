#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxsize = 100;
typedef long long ll;
typedef long long type;

type MOD;

struct Mat {
	int r, l;
	type arr[maxsize][maxsize];

	Mat (int r = 0, int l = 0) { 
		set(r, l);
		memset(arr, 0, sizeof(arr));
	}

	void set (int r, int l) {
		this->r = r;
		this->l = l;
	}

	Mat operator * (const Mat& u) {
		Mat ret(r, u.l);
		for (int k = 0; k < l; k++) {
			for (int i = 0; i < r; i++)
				for (int j = 0; j < u.l; j++)
					ret.arr[i][j] = (ret.arr[i][j] + arr[i][k] * u.arr[k][j]) % MOD;
		}
		return ret;
	}
};

void put (Mat x) {
	for (int i = 0; i < x.r; i++) {
		for (int j = 0; j < x.l; j++)
			printf("%lld ", x.arr[i][j]);
		printf("\n");
	}
}

Mat pow_mat (Mat ans, Mat x, ll n, ll m) {
	MOD = m;

	while (n) {
		if (n&1)
			ans = x * ans;
		x = x * x;
		n >>= 1;
	}
	return ans;
}


int main () {
	int D;
	ll N, M;
	while (scanf("%d%lld%lld", &D, &N, &M) == 3 && D + N + M) {
		Mat x(D, D);
		for (int i = 1; i < D; i++)
			x.arr[i-1][i] = 1;
		for (int i = 0; i < D; i++) {
			scanf("%lld", &x.arr[D-1][D-1-i]);
			x.arr[D-1][D-1-i] %= M;
		}

		Mat ans(D, 1);
		for (int i = 0; i < D; i++) {
			scanf("%lld", &ans.arr[i][0]);
			ans.arr[i][0] %= M;
		}

		if (N > D) {
			Mat tmp = pow_mat(ans, x, N - D, M);
			printf("%lld\n", tmp.arr[D-1][0]);
		} else
			printf("%lld\n", ans.arr[N-1][0]);
	}
	return 0;
}
