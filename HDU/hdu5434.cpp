#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = (1<<7) + 5;
const int mod = 1000000007;

struct Mat {
	int r, c; 
	ll s[maxn][maxn];
	void init(int r = 0, int c = 0) {
		this->r = r;
		this->c = c;
		memset(s, 0, sizeof(s));
	}
}X[10];

int N, M;
Mat ans;

Mat mul(Mat& a, Mat& b) {
	Mat ret;
	ret.init(a.r, b.c);

	for (int k = 0; k < a.c; k++) {
		for (int i = 0; i < a.r; i++) {
			if (a.s[i][k] == 0) continue;
			for (int j = 0; j < b.c; j++)
				ret.s[i][j] = (ret.s[i][j] + a.s[i][k] * b.s[k][j]) % mod;
		}
	}
	return ret;
}

void powMat (Mat& ret, Mat x, int n) {
	while (n) {
		if (n&1) ret = mul(x, ret);
		x = mul(x, x);
		n >>= 1;
	}
}

bool judge (int s, int t, int n) {
	int k = 0;
	for (int i = 0; i < n; i++) {
		int f = ((s>>i)&1)*2 + ((t>>i)&1);
		if ((k&f) == 0 && k != 0 && f != 0) return false;
		k = f;
	}
	return true;
}

void init() {
	for (int k = 1; k <= 7; k++) {
		int n = (1<<k);
		X[k].init(n, n);
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (judge(i, j, k))
					X[k].s[i][j] = 1;
			}
		}
	}
}

int main () {
	init();
	while (scanf("%d%d", &N, &M) == 2) {
		ans.init((1<<M), 1);
		for (int i = 0; i < (1<<M); i++) ans.s[i][0] = 1;

		powMat(ans, X[M], N-1);
		ll ret = 0;
		for (int i = 0; i < (1<<M); i++) ret = (ret + ans.s[i][0]) % mod;
		printf("%d\n", (int)ret);
	}
	return 0;
}
