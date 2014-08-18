#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 5;
const int M[maxn+5] = {1, 10, 100, 1000, 10000};

int MOD;

struct Mat {
	int arr[maxn][maxn];
	Mat () {
		memset(arr, 0, sizeof(arr));
	}

	Mat operator * (const Mat& u) {
		Mat ret;
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					ret.arr[i][j] = (ret.arr[i][j] + arr[i][k] * u.arr[k][j]) % MOD;
		}
		return ret;
	}
};

Mat pow_mat(Mat x, int n) {
	Mat ret;
	for (int i = 0; i < 2; i++)
		ret.arr[i][i] = 1;

	while (n) {
		if (n&1) 
			ret = ret * x;
		x = x * x;
		n >>= 1;
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		int a, b, n, m;
		scanf("%d%d%d%d", &a, &b, &n, &m);
		MOD = M[m];

		Mat x;
		for (int i = 0; i < 2; i++)
			for (int j = 0; j < 2; j++)
				x.arr[i][j] = 1;
		x.arr[0][0] = 0;

		if (n >= 1) {
		Mat ans = pow_mat(x, n-1);
		printf("%d\n", (ans.arr[1][0] * a % MOD + ans.arr[1][1] * b % MOD) % MOD);
		} else
			printf("%d\n", a);
	}
	return 0;
}
