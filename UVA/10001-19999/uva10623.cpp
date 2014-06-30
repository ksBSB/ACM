#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
typedef  long long ll;
const int N = 100005;

struct state {
	ll n, m, p;
	void set (ll m, ll n, ll p) {
		this->m = m;
		this->n = n;
		this->p = p;
	}
}s[N];

bool cmp (const state& a,const state& b) {
	if (a.m != b.m)
		return a.m < b.m;
	if (a.n != b.n)
		return a.n < b.n;
	return a.p < b.p;
}

int main () {
	int cas = 1;
	ll n;
	while (scanf("%lld", &n) == 1 && n != -1) {
		printf("Case %d:\n", cas++);
		if (n == 1) {
			printf("0 0 0\n");
			continue;
		}
		int c = 0;

		for (ll m = 0; m < 100; m++) {
			for (ll p = 0; p < 100; p++) {
				ll sum = 2 + 2 * m * (m-1) + 3 * p * (p-1) + 6 * m * p;
				sum = n - sum;

				ll a = 4 * m + 6 * p - 1;

				/*
				if (m == 0 && p == 0)
					printf("%lld %lld! \n", sum, a);
					*/

				double tmp = sum + a * a / 4.0;

			

				if (tmp < 0)
					continue;

				tmp = sqrt(tmp);
				double x = (tmp - ((double)a / 2.0));

				if (x < 0 || x >= 20000)
					continue;

				ll n = x;
				/*
					*/
				if (n * n + a * n == sum)
					s[c++].set(m, n, p);

			}
		}

		sort (s, s + c, cmp);
		if (c) {
			for (int i = 0; i < c; i++)
				printf("%lld %lld %lld\n", s[i].m, s[i].n, s[i].p);
		} else
			printf("Impossible.\n");
	}
	return 0;
}
