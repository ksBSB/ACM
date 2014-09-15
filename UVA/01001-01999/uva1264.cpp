#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef long long ll;
const int maxn = 20;
const ll mod = 9999991;

ll C[maxn+5][maxn+5];

void get_C (int n) {
	for (int i = 0; i <= n; i++) {
		C[i][0] = C[i][i] = 1;
		for (int j = 1; j < i; j++)
			C[i][j] = (C[i-1][j-1] + C[i-1][j]) % mod;
	}
}

struct BST {
	int sz, cid[maxn+5][2];
	int val[maxn+5], sum[maxn+5];

	void init();
	void insert(int& u, int v);
	void pushup(int u);
	ll count(int u);
}AC;

int main () {
	get_C(maxn);
	int cas, n, x;
	scanf("%d", &cas);
	while (cas--) {
		int R = 0;
		AC.init();

		scanf("%d", &n);
		for (int i = 0; i < n; i++) {
			scanf("%d", &x);
			AC.insert(R, x);
		}

		printf("%lld\n", AC.count(R));
	}
	return 0;
}

ll BST::count(int u) {
	if (u == 0)
		return 1;

	ll ret = 1;
	ret = (ret * count(cid[u][0])) % mod;
	ret = (ret * count(cid[u][1])) % mod;
	ret = (ret * C[sum[u]-1][sum[cid[u][0]]]) % mod;
	return ret;
}

void BST::init() {
	sz = 1;
	sum[0] = val[0] = 0;
	memset(cid[1], 0, sizeof(cid[1]));
}

void BST::pushup(int u) {
	sum[u] = sum[cid[u][0]] + sum[cid[u][1]] + 1;
	/*
	sum[u] = 1;
	if (cid[u][0])
		sum[u] += sum[cid[u][0]];
	if (cid[u][1])
		sum[u] += sum[cid[u][1]];
		*/
}

void BST::insert(int& u, int v) {
	if (u == 0) {
		u = sz++;
		memset(cid[u], 0, sizeof(cid[u]));
		val[u] = v;
		sum[u] = 1;
		return;
	}

	if (val[u] < v)
		insert(cid[u][1], v);
	else
		insert(cid[u][0], v);
	pushup(u);
}
