#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 505;

int N, M, D, K;

struct Mat {
	ll arr[maxn];
};
Mat ceil, x;

Mat mul_mat (const Mat& a, const Mat& b) {
	Mat ans;

	memset(ans.arr, 0, sizeof(ans.arr));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++)
			ans.arr[i] = (ans.arr[i] + a.arr[j] * b.arr[(i-j+N)%N]) % M;
	}
	return ans;
}

void pow_mat (int n) {
	Mat ans = x;

	while (n) {
		if (n&1)
			ans = mul_mat(ans, x);
		x = mul_mat(x, x);
		n >>= 1;
	}
	x = ans;
}

int main () {
	while (scanf("%d%d%d%d", &N, &M, &D, &K) == 4) {
		for (int i = 0; i < N; i++)
			scanf("%lld", &ceil.arr[i]);

		memset(x.arr, 0, sizeof(x.arr));
		for (int i = -D; i <= D; i++)
			x.arr[(i+N)%N] = 1;

		pow_mat(K-1);

		/*
		for (int i = 0; i < N; i++)
			printf("%lld ", x.arr[i]);
		printf("\n");
		*/

		for (int i = 0; i < N; i++) {
			if (i)
				printf(" ");

			ll ret = 0;
			for (int j = 0; j < N; j++)
				ret = (ret + ceil.arr[j] * x.arr[(j-i+N)%N]) % M;
			printf("%lld", ret);
		}
		printf("\n");
	}
	return 0;
}
