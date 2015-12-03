#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 5;
typedef long long ll;

struct Suffix_Arr {
	int n, s[maxn];
	int SA[maxn], rank[maxn], height[maxn];
	int tmp_one[maxn], tmp_two[maxn], c[305];

	int d[maxn][20];

	void init(char* str);
	void build(int m);
	void get_height();
	void rmq_init();
	int rmq_query(int x, int y);
}solver;

char str[maxn];

int bitcount(int n) {
	if (n == 0) return 1;
	int ret = 0;
	while (n) {
		n /= 10;
		ret++;
	}
	return ret;
}

int N, L[maxn], R[maxn];
void solve () {
	ll in = 0, ot = 0;
	scanf("%d", &N);
	L[0] = R[0] = solver.n-1;
	for (int i = 1; i <= N; i++) {
		scanf("%d%d", &L[i], &R[i]);
		int l = solver.rank[L[i-1]], r = solver.rank[L[i]];
		int k = min(solver.rmq_query(l, r), min(R[i-1] - L[i-1], R[i] - L[i]));
		int len = R[i] - L[i];

		in += R[i] - L[i];
		ot += len - k + bitcount(k);
	}
	printf("%lld %lld\n", in + N, ot + 2 * N);
}

int main () {
	while (scanf("%s", str) == 1) {
		solver.init(str);
		solver.build(300);
		solver.get_height();
		solver.rmq_init();
		solve();
	}
	return 0;
}

void Suffix_Arr::init(char* str) {
	n = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++)
		s[n++] = str[i] - 'a' + 1;
	s[n++] = 0;
}

void Suffix_Arr::rmq_init() {
	for (int i = 0; i < n; i++) d[i][0] = height[i];

	for (int k = 1; (1<<k) <= n; k++) {
		for (int i = 0; i + (1<<k) - 1 < n; i++)
			d[i][k] = min(d[i][k-1], d[i+(1<<(k-1))][k-1]);
	}
}

int Suffix_Arr::rmq_query(int x, int y) {
	if (x == y) return n - SA[x];

	if (x > y) swap(x, y);

	x++;
	int k = 0;
	while ((1<<(k+1)) <= y - x + 1) k++;
	return min(d[x][k], d[y-(1<<k)+1][k]);
}

void Suffix_Arr::get_height() {
	for (int i = 0; i < n; i++) rank[SA[i]] = i;

	int mv = height[0] = 0;

	for (int i = 0; i < n - 1; i++) {
		if (mv) mv--;

		int j = SA[rank[i]-1];
		while (s[i+mv] == s[j+mv]) mv++;
		height[rank[i]] = mv;
	}
}

void Suffix_Arr::build(int m) {
	int *x = tmp_one, *y = tmp_two;

	for (int i = 0; i < m; i++) c[i] = 0;
	for (int i = 0; i < n; i++) c[x[i] = s[i]]++;
	for (int i = 1; i < m; i++) c[i] += c[i-1];
	for (int i = n-1; i >= 0; i--) SA[--c[x[i]]] = i;

	for (int k = 1; k <= n; k <<= 1) {
		
		int mv = 0;
		for (int i = n-k; i < n; i++) y[mv++] = i;
		for (int i = 0; i < n; i++) if (SA[i] >= k)
			y[mv++] = SA[i] - k;

		for (int i = 0; i < m; i++) c[i] = 0;
		for (int i = 0; i < n; i++) c[x[y[i]]]++;
		for (int i = 1; i < m; i++) c[i] += c[i-1];
		for (int i = n-1; i >= 0; i--) SA[--c[x[y[i]]]] = y[i];

		swap(x, y);
		mv = 1;
		x[SA[0]] = 0;

		for (int i = 1; i < n; i++)
			x[SA[i]] = (y[SA[i-1]] == y[SA[i]] && y[SA[i-1] + k] == y[SA[i] + k] ? mv-1 : mv++);

		if (mv >= n) break;
		m = mv;
	}
}
