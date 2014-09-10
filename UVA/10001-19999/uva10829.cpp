#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <algorithm>

using namespace std;

typedef long long ll;
const int maxn = 100005;

struct Suffix_Arr {
	int n, len, s[maxn];
	int SA[maxn], rank[maxn], height[maxn];
	int tmp_one[maxn], tmp_two[maxn], c[30];

	int d[maxn][20];

	void init(char* str);
	void build_arr(int m);
	void get_height();

	void rmq_init();
	int rmq_query(int l, int r);
	ll solve(int m);

	void put();
}AC;

char str[maxn];

int main () {
	int cas, n;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%d%s", &n, str);
		AC.init(str);
		printf("Case %d: %lld\n", i, AC.solve(n));
	}
	return 0;
}

void Suffix_Arr::put () {
	for (int i = 0; i < n; i++)
		printf("%d ", SA[i]);
	printf("\n");

	for (int i = 0; i < n; i++)
		printf("%d ", height[i]);
	printf("\n");
}

ll Suffix_Arr::solve(int m) {
	build_arr(28);
	get_height();

	rmq_init();

	ll ret = 0;
	for (int l = 1; l < len / 2; l++) {
		for (int i = 0; i < len; i += l) {
			int j = i + l + m, sum = 0;

			if (j < len)
				sum += min(rmq_query(rank[i], rank[j]), l);
			if (i)
				sum += min(rmq_query(rank[n-i-1], rank[n-j-1]), l-1);
			ret += max(0, sum - l + 1);
		}
	}
	return ret;
}

int Suffix_Arr::rmq_query(int l, int r) {

	if (l > r) swap(l, r);
	l++;

	int k = 0;
	while ((1<<(k+1)) <= r - l + 1) k++;
	return min(d[l][k], d[r - (1<<k) + 1][k]);
}

void Suffix_Arr::rmq_init() {
	for (int i = 0; i < n; i++) d[i][0] = height[i];

	for (int k = 1; (1<<k) <= n; k++) {
		for (int i = 0; i + (1<<k) - 1 < n; i++)
			d[i][k] = min(d[i][k-1], d[i+(1<<(k-1))][k-1]);
	}
}

void Suffix_Arr::init(char* str) {
	n = 0;
	len = strlen(str);
	for (int i = 0; i < len; i++)
		s[n++] = str[i] - 'a' + 1;
	s[n++] = 27;
	for (int i = len - 1; i >= 0; i--)
		s[n++] = str[i] - 'a' + 1;
	s[n++] = 0;
}

void Suffix_Arr::get_height() {
	for (int i = 0; i < n; i++)
		rank[SA[i]] = i;

	int mv = height[0] = 0;
	for (int i = 0; i < n - 1; i++) {
		if (mv) mv--;

		int j = SA[rank[i] - 1];
		while (s[i+mv] == s[j+mv])
			mv++;
		height[rank[i]] = mv;
	}
}

void Suffix_Arr::build_arr(int m) {
	int *x = tmp_one, *y = tmp_two;

	for (int i = 0; i < m; i++) c[i] = 0;
	for (int i = 0; i < n; i++) c[x[i] = s[i]]++;
	for (int i = 1; i < m; i++) c[i] += c[i-1];
	for (int i = n-1; i >= 0; i--) SA[--c[x[i]]] = i;

	for (int k = 1; k <= n; k <<= 1) {

		int mv = 0;
		for (int i = n - k; i < n; i++) y[mv++] = i;
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
			x[SA[i]] = (y[SA[i-1]] == y[SA[i]] && y[SA[i-1] + k] == y[SA[i] + k] ? mv - 1 : mv++);

		if (mv >= n)
			break;
		m = mv;
	}
}
