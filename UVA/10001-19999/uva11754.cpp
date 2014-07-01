#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxc = 15;
const int maxk = 105;
const int limit = 10000;

ll total;
int C, S, X[maxc], k[maxc];
int bestc, Y[maxc][maxk];
set<int> vis[maxc];

void init () {
	total = 1;
	bestc = 0;
	for (int i = 0; i < C; i++) {
		scanf("%d%d", &X[i], &k[i]);
		total *= k[i];

		for (int j = 0; j < k[i]; j++)
			scanf("%d", &Y[i][j]);
		sort(Y[i], Y[i] + k[i]);

		if (k[i] * X[bestc] < k[bestc] * X[i])
			bestc = i;
	}
}

void solveEnum (int s) {

	for (int i = 0; i < C; i++) {
		if (i == s)
			continue;

		vis[i].clear();
		for (int j = 0; j < k[i]; j++)
			vis[i].insert(Y[i][j]);
	}

	for (int t = 0; S; t++) {

		for (int i = 0; i < k[s]; i++) {
			ll n = (ll)X[s] * t + Y[s][i];

			if (n == 0)
				continue;

			bool flag = true;
			for (int c = 0; c < C; c++) {
				if (c == s)
					continue;

				if (!vis[c].count(n%X[c])) {
					flag = false;
					break;
				}
			}

			if (flag) {
				printf("%lld\n", n);
				if (--S == 0)
					break;
			}
		}
	}
}

int a[maxc];
vector<int> sol;

void gcd(ll a, ll b, ll& d, ll& x,ll& y) {
	if (!b) {
		d = a;
		x = 1;
		y = 0;
	} else {
		gcd(b, a%b, d, y, x);
		y -= x*(a/b);
	}
}

int china (int n, int* s, int* m) {
	ll M = 1, d, y, x = 0;

	for (int i = 0; i < n; i++)
		M *= m[i];

	for (int i = 0; i < n; i++) {
		ll w = M / m[i];
		gcd(m[i], w, d, d, y);
		x = (x + y * w * a[i]) % M;
	}
	return (x+M)%M;
}

void dfs (int dep) { 
	if (dep == C)
		sol.push_back(china(C, a, X));
	else {
		for (int i = 0; i < k[dep]; i++) {
			a[dep] = Y[dep][i];
			dfs(dep+1);
		}
	}
}

void solveChina () {
	sol.clear();
	dfs(0);
	sort(sol.begin(), sol.end());

	ll M = 1;
	for (int i = 0; i < C; i++)
		M *= X[i];

	for (int i = 0; S; i++) {
		for (int j = 0; j < sol.size(); j++) {
			ll n = M * i + sol[j];
			if (n > 0){
				printf("%lld\n", n);
				if (--S == 0)
					break;
			}
		}
	}
}

int main () {
	while (scanf("%d%d", &C, &S) == 2 && C + S) {
		init();

		if (total > limit)
			solveEnum(bestc);
		else
			solveChina();
		printf("\n");
	}
	return 0;
}
