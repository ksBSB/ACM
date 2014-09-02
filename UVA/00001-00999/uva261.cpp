#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;
const int maxn = 10005;

struct Suffix_Arr {
	char s[maxn];
	int n;
	int SA[maxn], height[maxn], rank[maxn];
	int tmp_one[maxn], tmp_two[maxn], c[maxn];

	bool input ();
	void build_suffix(int m);
	void get_height();
	int check(int k);
}fuck;

int main () {
	while (fuck.input()) {
		fuck.build_suffix(256);
		fuck.get_height();

		int ans = maxn;
		for (int i = 1; i <= fuck.n; i++)
			ans = min(ans, fuck.check(i));

		if (ans == maxn)
			printf("YES\n");
		else
			printf("NO:%d\n", ans + 1);
	}
	return 0;
}

bool Suffix_Arr::input () {
	if (!gets(s))
		return false;
	memset(height, 0, sizeof(height));
	n = strlen(s) + 1;
	return true;
}

int Suffix_Arr::check(int k) {
	int ret = 0;

	memset(c, -1, sizeof(c));

	for (int i = 1; i < n; i++) {

		if (height[i] < k)
			ret++;

		if (SA[i] > n - k - 1)
			continue;

		c[SA[i]] = ret;
	}

	/*
	for (int i = 1; i < n; i++)
		printf("%d", height[i]);
	printf("\n");

	for (int i = 1; i < n; i++)
		printf("%d", SA[i]);
	printf("\n");

	for (int i = 0; i < n; i++)
		printf("%d", c[i]);
	printf("\n");
	*/

	set<int> g;
	ret = 0;
	for (int i = 0; i < n; i++) {
		if (c[i] == -1)
			continue;

		if (g.find(c[i]) == g.end()) {
			ret++;
			g.insert(c[i]);
		}

		if (ret > k + 1) {
	//		printf("%d %d!\n", k, i);
			return i + k - 1;
		}
	}
	return maxn;
}

void Suffix_Arr::get_height() {
	for (int i = 0; i < n; i++)
		rank[SA[i]] = i;

	int mv = 0;
	for (int i = 0; i < n; i++) {
		if (mv)
			mv--;

		if (rank[i] == 0) {
			height[rank[i]] = 0;
			continue;
		}

		int j = SA[rank[i]-1];
		while (s[i+mv] == s[j+mv])
			mv++;
		height[rank[i]] = mv;
	}
}

void Suffix_Arr::build_suffix(int m) {
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
