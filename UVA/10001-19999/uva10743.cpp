#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 3;
const int mod = 10000;
int sign[maxn][maxn] = { {0, 1, 0}, {0, 0, 1}, {4, -7, 5} };

struct MAT {
	int s[maxn][maxn];

	MAT () {}

	void set () {
		for (int i = 0; i < maxn; i++)
			for (int j = 0; j < maxn; j++)
				s[i][j] = sign[i][j];
	}

	MAT operator * (const MAT& a) {
		MAT ans;
		for (int i = 0; i < maxn; i++) {
			for (int j = 0; j < maxn; j++) {
				ans.s[i][j] = 0;
				for (int k = 0; k < maxn; k++)
					ans.s[i][j] = (ans.s[i][j] + s[i][k] * a.s[k][j] % mod) % mod;
			}
		}
		return ans;
	}
};

MAT pow_mat (int n) {
	MAT ans, x;
	ans.set();
	x.set();

	while (n) {
		if (n&1)
			ans = ans * x;
		x = x * x;
		n >>= 1;
	}

	return ans;
}

int solve (int n) {
	if (n < 3)
		return n;
	else if (n == 3)
		return 6;
	else if (n == 4)
		return 19;

	MAT ans = pow_mat(n-5);
	return ((ans.s[2][0] * 2 + ans.s[2][1] * 6 + ans.s[2][2] * 19) % mod + mod) % mod;
}

int main () {
	int cas, n;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%d", &n);
		printf("Case %d: ", i);

		int ans = solve(n);
		if (n <= 9)
			printf("%d\n", ans);
		else
			printf("%04d\n", ans);
	}
	return 0;
}
