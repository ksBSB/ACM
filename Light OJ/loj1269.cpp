#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 50005 * 32;
const int sigma_size = 2;

struct Tire {
    int sz;
    int g[maxn][sigma_size];
	int c[maxn];

    void init();
    void insert(int s);
	int findMax(int s);
	int findMin(int s);
}T;

int N, A[maxn];

int main () {
	int cas, x;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		T.init();
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) {
			scanf("%d", &x);
			A[i] = A[i-1] ^ x;
		}

		for (int i = 0; i <= N; i++)
			T.insert(A[i]);

		int ansMax = 0, ansMin = (1<<31)-1;
		for (int i = 0; i <= N; i++) {
			ansMax = max(ansMax, T.findMax(A[i]));
			ansMin = min(ansMin, T.findMin(A[i]));
		}
		printf("Case %d: %d %d\n", kcas, ansMax, ansMin);
	}
	return 0;
}

void Tire::init() {
    sz = 1;
	c[0] = 0;
    memset(g[0], 0, sizeof(g[0]));
}

int Tire::findMin(int s) {
	int ret = 0, u = 0;
	for (int i = 30; i >= 0; i--) {
		int v = (s>>i) & 1;

		if (g[u][v] == 0 || (g[u][v^1] && c[g[u][v]] < 2)) {
			v = v ^ 1;
			ret |= (1<<i);
		} 

		u = g[u][v];
	}
	return ret;
}

int Tire::findMax(int s) {
	int ret = 0, u = 0;

	for (int i = 30; i >= 0; i--) {
		int v = ((s>>i)&1)^1;

		if (g[u][v])
			ret |= (1<<i);
		else
			v = v ^ 1;
		u = g[u][v];
	}
	return ret;
}

void Tire::insert(int s) {
	int u = 0;

	for (int i = 30; i >= 0; i--) {
		int v = (s>>i) & 1;

		if (g[u][v] == 0) {
			c[sz] = 0;
			memset(g[sz], 0, sizeof(g[sz]));
			g[u][v] = sz++;
		}

		u = g[u][v];
		c[u]++;
	}
}
