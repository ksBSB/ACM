#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 1005;

struct Suffix_Arr {
	int n, s[maxn];
	int SA[maxn], rank[maxn], height[maxn];
	int tmp_one[maxn], tmp_two[maxn], c[maxn];

	vector<int> vec;

	void init (char* str);
	void build_arr(int m);
	void get_fail();

	void solve();
	void check(int k);
}AC;

char str[maxn];

int main () {
	while (gets(str) && strcmp(str, "")) {
		AC.init(str);
		AC.build_arr(27);
		AC.get_fail();
		AC.solve();
		printf("\n");
	}
	return 0;
}

void Suffix_Arr::check(int k) {
	int c = 0, ret = 0;
	for (int i = 0; i <= n; i++) {
		if (height[i] < k) {
			ret = max(ret, c);
			c = 1;
		} else
			c++;
	}

	if (ret > 1)
		vec.push_back(ret);
}

void Suffix_Arr::solve() {
	/*
	for (int i = 0; i < n; i++)
		printf("%d ", SA[i]);
	printf("\n");

	for (int i = 0; i < n; i++)
		printf("%d ", height[i]);
	printf("\n");
	*/

	for (int i = 1; i <= n; i++)
		check(i);

	for (int i = 0; i < vec.size(); i++)
		printf("%d\n", vec[i]);
}

void Suffix_Arr::init(char* str) {
	n = 0;
	vec.clear();
	memset(height, 0, sizeof(height));

	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (str[i] != ' ')
			s[n++] = str[i] - 'A' + 1;
	}
	s[n++] = 0;

	/*
	for (int i = 0; i < n; i++)
		printf("%c", s[i] ? 'A' + s[i] - 1 : '!');
	printf("\n");
	*/
}

void Suffix_Arr::get_fail() {
	for (int i = 0; i < n; i++)
		rank[SA[i]] = i;

	int mv = 0;
	for (int i = 0; i < n - 1; i++) {
		if (mv) mv--;

		int j = SA[rank[i] - 1];
		while (s[i+mv] == s[j+mv])
			mv++;
		height[rank[i]] = mv;
	}
}

void Suffix_Arr::build_arr (int m) {

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
			x[SA[i]]  = (y[SA[i-1]] == y[SA[i]] && y[SA[i-1] + k] == y[SA[i] + k] ? mv - 1 : mv++);

		if (mv >= n)
			break;

		m = mv;
	}
}
