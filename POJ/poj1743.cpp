#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 2 * 1e4 + 5;

struct Suffix_Arr {
	int n, s[maxn];
	int SA[maxn], rank[maxn], height[maxn];
	int tmp_one[maxn], tmp_two[maxn], c[205];

	void init (int* t, int k);
	void build(int m);
	void getHeight();

	bool judge(int m);
	int solve();
}AC;

int N, A[maxn];

int main () {
	while (scanf("%d", &N) == 1 && N) {
		for (int i = 0; i < N; i++) scanf("%d", &A[i]);
		for (int i = 0; i < N-1; i++) A[i] = A[i+1] - A[i] + 89;
		AC.init(A, N-1);
		printf("%d\n", AC.solve());
	}
	return 0;
}

bool Suffix_Arr::judge(int m) {
	int p = 1;

	while (p < n) {
		while (p < n && height[p] < m) p++;
		if (p >= n) break;
		int l = SA[p-1];
		int r = SA[p-1];

		while (p < n && height[p] >= m) {
			l = min(l, SA[p]);
			r = max(r, SA[p]);
			p++;
		}
		if (r - l >= m) return true;
	}
	return false;
}

int Suffix_Arr::solve() {
	build(200);
	getHeight();

	int l = 0, r = n / 2;
	for (int i = 0; i < 100; i++) {
		int mid = (l + r) >> 1;
		if (judge(mid)) l = mid;
		else r = mid;
	}
	if (l < 4) return 0;
	return l + 1;
}

void Suffix_Arr::init(int* t, int k) {
	n = 0;
	for (int i = 0; i < k; i++)
		s[n++] = t[i];
	s[n++] = 0;
}

void Suffix_Arr::getHeight() {
	for (int i = 0; i < n; i++)
		rank[SA[i]] = i;
	int mv = height[0] = 0;
	for (int i = 0; i < n - 1; i++) {
		if (mv) mv--;

		int j = SA[rank[i]-1];
		while (s[i+mv] == s[j+mv])
			mv++;
		height[rank[i]] = mv;
	}
}

void Suffix_Arr::build (int m) {
	int *x = tmp_one, *y = tmp_two;

	for (int i = 0; i < m; i++) c[i] = 0;
	for (int i = 0; i < n; i++) c[x[i] = s[i]]++;
	for (int i = 1; i < m; i++) c[i] += c[i-1];
	for (int i = n - 1; i >= 0; i--) SA[--c[x[i]]] = i;

	for (int k = 1; k <= n; k <<= 1) {

		int mv = 0;
		for (int i = n - k; i < n; i++) y[mv++] = i;
		for (int i = 0; i < n; i++) if (SA[i] >= k)
			y[mv++] = SA[i] - k;

		for (int i = 0; i < m; i++) c[i] = 0;
		for (int i = 0; i < n; i++) c[x[y[i]]]++;
		for (int i = 1; i < m; i++) c[i] += c[i-1];
		for (int i = n - 1; i >= 0; i--) SA[--c[x[y[i]]]] = y[i];

		swap(x, y);
		mv = 1;
		x[SA[0]] = 0;

		for (int i = 1; i < n; i++)
			x[SA[i]] = (y[SA[i-1]] == y[SA[i]] && y[SA[i-1] + k] == y[SA[i] + k] ? mv - 1 : mv++);

		if (mv >= n)
			break;
		m = mv;
	}
}
