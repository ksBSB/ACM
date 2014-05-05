
#include <stdio.h>
#include <string.h>

const int M = 10;
const int N = 205;

int n, m, r;

struct Mul {
	int s[M][M];
	Mul() {	memset(s, 0, sizeof(s));	}
	Mul operator * (const Mul& c) {
		Mul ans;

		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {
				ans.s[i][j] = 0;
				for (int k = 0; k < 3; k++)
					ans.s[i][j] = (ans.s[i][j] + s[i][k] * c.s[k][j] ) % m;
			}
		}
		return ans;
	}

	void put() {
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++)
				printf("%d ", s[i][j]);
			printf("\n");
		}
	}
};

Mul MulPow(Mul a, int t) {
	if (t == 1) return a;

	Mul x = MulPow(a, t / 2);

	x = x * x;

	if (t % 2) x = x * a;

	return x;
}

void init() {
	if (n > 2) {
		Mul a;
		a.s[0][0] = a.s[0][1] = a.s[1][0] = a.s[2][0] = a.s[2][1] = a.s[2][2] = 1;

		Mul ans = MulPow(a, n - 2);

		r = (ans.s[2][0] + ans.s[2][1] + ans.s[2][2] * 2) % m;
	} else if (n == 2) {
		r = 2 % m;
	} else if (n == 1) {
		r = 1;
	}
}

void solve() {
	if (r == 0 || r % 2)
		printf("No\n");
	else {
		int v[N][N];
		memset(v, -1, sizeof(v));
		printf("Yes\n");

		for (int i = 1; i <= r; i++) {
			int tmp;
			if (i % 2) {
				tmp = (r + i + 1) / 2;
				v[tmp][i] = 0;
			} else
				tmp = (r - i) / 2;
			for (int j = tmp + 1; j <= r; j++)
				v[j][i] = 1;
		}

		for (int i = 1; i <= r; i++) {
			for (int j = 1; j < r; j++)
				printf("%d ", v[i][j]);
			printf("%d\n", v[i][r]);
		}
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%d%d", &n, &m);
		printf("Case %d: ", i);

		init();

		solve();	
	}
	return 0;
}
