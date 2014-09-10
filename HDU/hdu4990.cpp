#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

int N, M;

struct Mat {
	ll s[2][2];
	Mat () {
		memset(s, 0, sizeof(s));
	}
	Mat operator * (const Mat& u) {
		Mat ret;
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 2; j++)
					ret.s[i][j] = (ret.s[i][j] + s[i][k] * u.s[k][j]) % M;
		}
		return ret;
	}
};

ll pow_mat(int n) {
	Mat ret, x;
	ret.s[0][0] = ret.s[1][1] = 1;
	x.s[0][0] = 4;
	x.s[0][1] = x.s[1][1] = 1;

	while (n) {
		if (n&1)
			ret = ret * x;
		x = x * x;
		n >>= 1;
	}
	return ret.s[0][1];
}


int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		ll ans = pow_mat((N+1) / 2);
		if ((N&1) == 0)
			ans *= 2;
		printf("%lld\n", ans % M);
	}
	return 0;
}
