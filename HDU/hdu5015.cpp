#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;

const ll mod = 10000007;
const int maxn = 15;

struct Mat {
	int r, c;
	ll s[maxn][maxn];

	Mat (int r = 0, int c = 0) {
		this->r = r;
		this->c = c;
		memset(s, 0, sizeof(s));
	}

	void init(int n) {
		r = c = n + 2;
		memset(s, 0, sizeof(s));
		s[0][0] = s[1][0] = 1;
		s[1][1] = 10;
		for (int i = 2; i < r; i++) {
			for (int j = 1; j <= i; j++)
				s[i][j] = 1;
		}
	}

	Mat operator * (const Mat& u) {
		Mat ret(r, u.c);
		for (int i = 0; i < r; i++) {
			for (int j = 0; j < u.c; j++)
				for (int k = 0; k < c; k++)
					ret.s[i][j] = (ret.s[i][j] + s[i][k] * u.s[k][j]) % mod;
		}
		return ret;
	}
};

int N, M;

Mat pow_mat (Mat ret, int n) {
	Mat x;
	x.init(N+2);
	while (n) {
		if (n&1)
			ret = x * ret;
		x = x * x;
		n >>= 1;
	}
	return ret;
}

int main () {
	while (scanf("%d%d", &N, &M) == 2) {
		Mat ans(N + 2, 1);
		ans.s[0][0] = 3;
		ans.s[1][0] = 233;
		for (int i = 1; i <= N; i++)
			scanf("%I64d", &ans.s[i+1][0]);
		ans = pow_mat(ans, M);
		printf("%I64d\n", ans.s[N+1][0]);
	}
	return 0;
}
