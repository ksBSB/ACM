#include <cstdio>
#include <cstring>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 90000 + 5;

struct Suffix_Arr {
	int n, s[maxn];
	int SA[maxn], rank[maxn], height[maxn];
	int tmp_one[maxn], tmp_two[maxn], c[305];

	void init(char* str);
	void build(int m);
	void get_height();

	int f[maxn];
	void solve();
	void query(char* str, int k);
}SFA;

char str[maxn];

int main () {
	scanf("%s", str);
	SFA.init(str);
	int q, k;
	SFA.solve();
	scanf("%d", &q);
	while (q--) {
		scanf("%d", &k);
		SFA.query(str, k);
	}
	return 0;
}

void Suffix_Arr::init(char* str) {
	n = 0;
	int len = strlen(str);
	for (int i = 0; i < len; i++)
		s[n++] = str[i];
	s[n++] = 0;
}
void Suffix_Arr::query(char* str, int k) {
	int idx = lower_bound(f, f + n, k) - f;
	int bw = k - f[idx-1] + height[idx], s = SA[idx];
	for (int i = 0; i < bw; i++)
		printf("%c", str[s+i]);
	printf("\n");
}

void Suffix_Arr::solve() {
	build(300);
	get_height();
	f[0] = 0;
	for (int i = 1; i < n; i++)
		f[i] = f[i-1] + (n - 1 - SA[i] - height[i]);
}

void Suffix_Arr::get_height() {
	for (int i = 0; i < n; i++)
		rank[SA[i]] = i;
	int mv = height[0] = 0;
	for (int i = 0; i < n - 1; i++) {
		if (mv) mv--;

		int j = SA[rank[i]-1];
		while (s[i+mv] == s[j+mv]) mv++;
		height[rank[i]] = mv;
	}
}

void Suffix_Arr::build(int m) {
	int* x = tmp_one, *y = tmp_two;

	for (int i = 0; i < m; i++) c[i] = 0;
	for (int i = 0; i < n; i++) c[x[i] = s[i]]++;
	for (int i = 1; i < m; i++) c[i] += c[i-1];
	for (int i = n - 1; i >= 0; i--) SA[--c[x[i]]] = i;

	for (int k = 1; k <= n; k <<= 1) {
		int mv = 0;
		for (int i = n - k; i < n; i++) y[mv++] = i;
		for (int i = 0; i < n; i++) if(SA[i] >= k) 
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

		if (mv >= n) break;
		m = mv;
	}
}
