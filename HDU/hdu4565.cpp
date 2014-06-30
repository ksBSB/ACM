#include <stdio.h>
#include <string.h>
#include <math.h>

#define MOD(a,b) (((a%b)+b)%b)
typedef long long ll;
const int N = 2;

int m;
struct mat {
	ll s[N][N];
	mat () {
		memset(s, 0, sizeof(s));
	}

	void set (ll a, ll b, ll c, ll d) {
		s[0][0] = a; s[0][1] = b;
		s[1][0] = c; s[1][1] = d;
	}

	mat operator * (const mat& c) {
		mat ans;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				
				for (int k = 0; k < N; k++)
					ans.s[i][j] = MOD(ans.s[i][j] + s[i][k] * c.s[k][j], m);
			}
		}
		return ans;
	}
}A;

mat powMat (int n) {

	mat ans;
	ans.set (1, 0, 0, 1);

	while (n) {
		if (n&1)
			ans = ans * A;
		n /= 2;
		A = A * A;
	}
	return ans;
}

int main () {
	int a, b, n;
	while (scanf("%d%d%d%d", &a, &b, &n, &m) == 4) {
		double t = pow (a + sqrt(b), 2);
		ll s1 = 2 * a % m;
		ll s2 = (ll)ceil(t) % m;

		if (n <= 1) {
			printf("%lld\n", s1);
		} else {
			A.set (2 * a, b - a * a, 1, 0);
			mat ans = powMat (n-2);

			printf("%lld\n", MOD(s2 * ans.s[0][0] + s1 * ans.s[0][1], m));
		}
	}
	return 0;
}
