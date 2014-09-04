#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 200005;

struct state {
	int pos, len;
	state (int pos = 0, int len = 0) {
		this->pos = pos;
		this->len = len;
	}
};

struct Suffix_Arr {
	int n, s[maxn];
	int SA[maxn], rank[maxn], height[maxn];
	int tmp_one[maxn], tmp_two[maxn], c[maxn];

	void init();
	void add(char* str);
	void build_arr(int m);
	void get_height();
	void solve (int p);
}AC;

inline bool sort_len (const state& a, const state& b) {
	if (a.len != b.len)
		return a.len > b.len;
	return a.pos < b.pos;
}

inline bool sort_pos (const state& a, const state& b) {
	if (a.pos != b.pos)
		return a.pos < b.pos;
	return a.len > b.len;
}

int N, tick;
char str[maxn];

void init () {
	AC.init();

	gets(str);
	while (gets(str) && strcmp(str, "END TDP CODEBASE"))
		AC.add(str);

	AC.s[AC.n++] = 260;
	tick = AC.n;

	gets(str);
	while (gets(str) && strcmp(str, "END JCN CODEBASE"))
		AC.add(str);

	AC.s[AC.n++] = 0;

	AC.build_arr(261);
	AC.get_height();
}

int main () {
	int cas = 0;
	while (~scanf("%d%*c", &N) && N) {

		init();
		if (cas)
			printf("\n");

		printf("CASE %d\n", ++cas);
		AC.solve(tick);
	}
	return 0;
}

void Suffix_Arr::solve(int p) {

	int k = 0;
	memset(c, 0, sizeof(c));

	for (int i = 0; i < n; i++) {
		if (SA[i] < p)
			k = height[i+1];
		else {
			k = min(height[i], k);
			c[i] = max(c[i], k);
		}
	}

	k = 0;
	for (int i = n - 1; i >= 0; i--) {
		if (SA[i] < p) {
			k = height[i];
		} else {
			c[i] = max(c[i], k);
			k = min(height[i], k);
		}
	}

	vector<state> vec, ans;
	for (int i = 0; i < n; i++) {
		if (c[i] >= 1)
			vec.push_back(state(SA[i], c[i]));
	}

	sort(vec.begin(), vec.end(), sort_pos);
	int mv = -1;
	for (int i = 0; i < vec.size(); i++) {
		if (vec[i].pos + vec[i].len <= mv)
			continue;
		ans.push_back(vec[i]);
		mv = vec[i].pos + vec[i].len;
	}

	sort(ans.begin(), ans.end(), sort_len);
	for (int i = 0; i < N && i < ans.size(); i++) {
		printf("INFRINGING SEGMENT %d LENGTH %d POSITION %d\n", i+1, ans[i].len, ans[i].pos - p); 
		for (int j = 0; j < ans[i].len; j++)
			printf("%c", s[ans[i].pos + j]);
		printf("\n");
	}
}

void Suffix_Arr::init() {
	n = 0;
	memset(s, 0, sizeof(s));
	memset(height, 0, sizeof(height));
}

void Suffix_Arr::add (char *str) {
	int len = strlen(str);
	for (int i = 0; i < len; i++)
		s[n++] = str[i];
	s[n++] = '\n';
}

void Suffix_Arr::get_height () {
	for (int i = 0; i < n; i++)
		rank[SA[i]] = i;

	int mv = 0;
	for (int i = 0; i < n - 1; i++) {
		if (mv) mv--;

		int j = SA[rank[i]-1];
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
