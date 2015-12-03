#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 10;
const int mod = 1e9 + 7;

struct Mat {
	int r, c;
	ll s[maxn][maxn];

	Mat(int r = 0, int c = 0): r(r), c(c) { memset(s, 0, sizeof(s)); }
	void init(int r, int c) {
		this->r = r;
		this->c = c;
		memset(s, 0, sizeof(s));
	}
};

Mat ans, x, tmp;

void mul_mat(Mat& a, Mat& b, Mat& c) {
	tmp.init(a.r, b.c);
	for (int k = 0; k < a.c; k++) {
		for (int i = 0; i < a.r; i++) {
			for (int j = 0; j < b.c; j++)
				tmp.s[i][j] = (tmp.s[i][j] + a.s[i][k] * b.s[k][j] % mod) % mod;
		}
	}
	c = tmp;
}

void pow_mod(Mat& ret, Mat& x, ll n) {
	while (n) {
		if (n&1) mul_mat(x, ret, ret);
		mul_mat(x, x, x);
		n >>= 1;
	}
}

ll N;
int A0, Ax, Ay, B0, Bx, By;

int main () {
	while (scanf("%lld", &N) == 1) {
		scanf("%d%d%d", &A0, &Ax, &Ay);
		scanf("%d%d%d", &B0, &Bx, &By);

		ans.init(5, 1);
		ans.s[0][0] = 1, ans.s[1][0] = A0 % mod, ans.s[2][0] = B0 % mod;
		ans.s[3][0] = 1LL * A0 * B0 % mod;

		x.init(5, 5);
		x.s[0][0] = 1;
		x.s[1][0] = Ay % mod, x.s[1][1] = Ax % mod;
		x.s[2][0] = By % mod, x.s[2][2] = Bx % mod;
		x.s[3][0] = 1LL * Ay * By % mod, x.s[3][1] = 1LL * Ax * By % mod;
		x.s[3][2] = 1LL * Bx * Ay % mod, x.s[3][3] = 1LL * Ax * Bx % mod;
		x.s[4][3] = x.s[4][4] = 1;

		pow_mod(ans, x, N);
		printf("%lld\n", ans.s[4][0]);
	}
	return 0;
}

/*
 * 1    0    0    0    0
 * Ay   Ax   0    0    0
 * By   0    Bx   0    0
 * AyBy AxBy BxAy AxBx 0
 * 0    0    0    1    1
 */
