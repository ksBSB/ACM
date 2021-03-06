#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <iostream>

using namespace std;
typedef long long ll;
const int N = 90;
const int M = 50;
const ll mod = 1e9+7;

struct mat {
	ll a[N][N];
	mat() { memset(a, 0, sizeof(a)); }
};

int n, k;
ll s, c[M][M];

void init () {
	cin >> s >> k;
	n = k * 2 + 3;
	for (int i = 0; i <= k; i++) {
		c[i][0] = c[i][i] = 1;;
		for (int j = 1; j < i; j++)
			c[i][j] = c[i-1][j-1] + c[i-1][j];
	}
}

mat mul(mat p, mat q) {
	mat ans;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			
			for (int t = 0; t < n; t++) {
				ans.a[i][j] += p.a[i][t]*q.a[t][j];
				ans.a[i][j] %= mod;
			}
		}
	}
	return ans;
}

mat Qpow(mat base, ll t) {
	mat x;
	for (int i = 0; i < n; i++) x.a[i][i] = 1;

	while (t) {
		if (t&1) x = mul(x, base);
		base = mul(base, base);
		t /= 2;
	}
	return x;
}

int main () {
	init();
	mat base;
	for (int i = 0; i <= k; i++) {
		for (int j = 0; j <= i; j++) {
			base.a[i][j] = base.a[i+k+1][j] = base.a[i][j+k+1] = c[i][j];
		}
	}
	base.a[2*k+2][k] = base.a[2*k+2][2*k+2] = 1;

	mat ans = Qpow(base, s);
	ll g = 0;
	for (int i = 0; i < 2*k+2; i++) {
		g = (g + ans.a[2*k+2][i]) % mod;
	}
	cout << g << endl;
	return 0;
}
