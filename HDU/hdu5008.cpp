#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

typedef unsigned long long ll;
const int maxn = 1e5+5;

struct Suffix_Arr {
	int n, s[maxn];
	int SA[maxn], rank[maxn], height[maxn];
	int tmp_one[maxn], tmp_two[maxn], c[maxn];

	ll sum, num[maxn];

	void init (char* str);
	int idx(char ch);
	void build(int m);
	void get_height();
	void get_substring();
	void query(ll x, ll& L, ll& R);
}AC;

int n;
ll l, r, x;
char str[maxn];

int main () {
	while (scanf("%s", str) == 1) {
		AC.init(str);
		AC.build(27);
		AC.get_height();
		AC.get_substring();

		scanf("%d", &n);
		l = r = 0;
		while (n--) {
			scanf("%I64d", &x);

			AC.query((x^l^r) + 1, l, r);
			printf("%I64d %I64d\n", l, r);
		}
	}
	return 0;
}

void Suffix_Arr::query(ll x, ll& L, ll& R) {
	if (x >= sum) {
		L = R = 0;
		return;
	}

	int l = 0, r = n;
	for (int i = 0; i < 100; i++) {
		int mid = (l + r) / 2;
		if (num[mid] < x)
			l = mid;
		else
			r = mid;
	}

	int len = height[l] + x - num[l], pos = SA[l];

	for (int i = l + 1; height[i] >= len && i < n; i++)
		pos = min(SA[i], pos);
	for (int i = l - 1; height[i+1] >= len && i >= 0; i--)
		pos = min(SA[i], pos);

	L = pos + 1;
	R = pos + len;
}

void Suffix_Arr::get_substring() {
	num[0] = 0;
	for (int i = 1; i <= n; i++)
		num[i] = num[i-1] + (n - 1 - SA[i-1]) - height[i-1];
	sum = num[n];
}

void Suffix_Arr::init (char* str) {
	n = strlen(str);
	for (int i = 0; i < n; i++)
		s[i] = idx(str[i]);
	s[n++] = 0;
}

int Suffix_Arr::idx(char ch) {
	return ch - 'a' + 1;
}

void Suffix_Arr::get_height() {
	for (int i = 0; i < n; i++)
		rank[SA[i]] = i;

	int mv = 0;
	for (int i = 0; i < n; i++) {
		if (mv) mv--;

		if (rank[i] == 0) {
			height[0] = 0;
			continue;
		}

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
