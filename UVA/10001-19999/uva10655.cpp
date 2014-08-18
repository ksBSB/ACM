#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxsize = 100;
typedef long long ll;
typedef long long type;

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
					ret.arr[i][j] = (ret.arr[i][j] + arr[i][k] * u.arr[k][j]);
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

Mat pow_mat (Mat ans, Mat x, ll n) {

	while (n) {
		if (n&1)
			ans = x * ans;
		x = x * x;
		n >>= 1;
	}
	return ans;
}

int main () {
	ll p, q, n;
	while (scanf("%lld%lld%lld", &p, &q, &n) == 3 && p + q + n) {
		Mat x(2, 2);
		x.arr[0][1] = 1;
		x.arr[1][0] = -q;
		x.arr[1][1] = p;

		Mat ans(2, 1);
		ans.arr[0][0] = 2;
		ans.arr[1][0] = p;

		if (n > 1) {
			ans = pow_mat(ans, x, n-1);
			printf("%lld\n", ans.arr[1][0]);
		} else
			printf("%lld\n", ans.arr[n][0]);
	}
	return 0;
}
