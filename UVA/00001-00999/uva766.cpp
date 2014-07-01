#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 25;


ll m[N], a[N][N];
ll C[N][N];

ll gcd (ll a, ll b) {
	return b == 0 ? a : gcd(b, a%b);
}

inline ll cal (ll d) {
	if (d < 0)
		return -d;
	return d;
}

inline ll sign (ll d) {
	if (d > 0)
		return 1;
	else if (d < 0)
		return -1;
	else
		return 0;
}

void del (ll& t, ll* p, int n) {
	ll d = gcd(t, p[0]);
	for (int i = 1; i <= n; i++) {
		if (p[i] == 0)
			continue;
		d = gcd(d, cal(p[i]));
	}

	t /= d;
	for (int i = 0; i <= n; i++)
		p[i] = cal(p[i]) / d * sign(p[i]);
}

void add (ll* p, ll* q, ll k, ll& t, ll f, int n) {

	for (int i = 0; i <= n; i++)
		p[i] = p[i] * f - q[i] * k * t;
	t *= f;

	del(t, p, n);
}

void init () {
	C[0][0] = 1;
	for (int i = 1; i < N; i++) {
		C[0][i] = C[i][i] = 1;
		for (int j = 1; j < i; j++)
			C[j][i] = C[j-1][i-1] + C[j][i-1];
	}

	memset(a, 0, sizeof(a));
	m[0] = 1;
	a[0][1] = 1;

	for (int i = 1; i <= 20; i++) {

		int u = i+1;
		for (int j = 1; j <= u; j++)
			a[i][j] += C[j][u];

		m[i] = 1;
		for (int j = 0; j < i; j++) {
			add (a[i], a[j], C[j][u], m[i], m[j], u);

			/*
			for (int x = 0; x <= j + 1; x++) {
				a[i][x] -= (a[j][x] * C[j][u] * tmp / m[j]);
			}
			*/
		}

		m[i] *= C[i][u];
		del(m[i], a[i], u);
	}
}

int main () {
	init();
	int cas, k;
	scanf("%d", &cas);

	while (cas--) {
		scanf("%d", &k);
		printf("%lld", m[k]);
		for (int i = k+1; i >= 0; i--)
			printf(" %lld", a[k][i]);
		printf("\n");
		if (cas)
			printf("\n");
	}
	return 0;
}
