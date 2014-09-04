#include <cstdio>
#include <cstring>
#include <map>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;
const int maxn = 105;
const int maxm = 10005;

int N, sz, len[maxn];
int s[maxn][maxm], jump[maxm];

char word[maxm];
string name[maxn];
map<string, int> g;

inline bool check (char ch) {
	return ch == ' ';
}

int get_id() {
	string str = "";
	int n = strlen(word);
	while (n && check(word[n-1]))
		n--;

	for (int i = 0; i < n; i++) {
		if (check(word[i]) && (i == 0 || check(word[i-1])))
			continue;
		str += word[i];
	}

	if (str == "")
		return 0;

	if (g.count(str))
		return g[str];

	return g[str] = sz++;
}

void get_jump (int n, int* a) {
	int p = jump[0] = jump[1] = 0;

	for (int i = 2; i <= n; i++) {
		while (p && a[p+1] != a[i])
			p = jump[p];

		if (a[p+1] == a[i])
			p++;
		jump[i] = p;
	}
}

int find (int* a, int n, int* b, int m) {
	
	int p = 0, ret = 0;
	for (int i = 1; i <= n; i++) {
		while (p && b[p+1] != a[i])
			p = jump[p];

		if (b[p+1] == a[i])
			p++;

		if (p >= m)
			return m;
		ret = max(ret, p);
	}
	return ret;
}

void init () {
	sz = 1;
	g.clear();
	memset(s, 0, sizeof(s));

	getchar();
	for (int i = 0; i <= N; i++) {
		if (i != N) {
			gets(word);
			name[i] = word;
		}

		int n = 0;
		while (gets(word) && strcmp(word, "***END***")) {
			int k = get_id();
			if (k == 0)
				continue;
			s[i][++n] = k;
		}

		len[i] = n;
	}

	/*
	for (int i = 0; i <= N; i++) {
		for (int j = 1; j <= len[i]; j++)
			printf("%d ", s[i][j]);
		printf("\n");
	}
	*/
}

void solve () {
	int ans = 0, rec[maxn];
	memset(rec, 0, sizeof(rec));

	for (int k = 0; k <= len[N]; k++) {

		get_jump(len[N] - k, s[N]);
		for (int i = 0; i < N; i++)
			rec[i] = max(rec[i], find(s[i], len[i], s[N], len[N] - k));

		for (int i = 1; i < len[N] - k; i++)
			s[N][i] = s[N][i+1];
	}

	for (int i = 0; i < N; i++)
		ans = max(ans, rec[i]);

	cout << ans;

	if (ans) {
		for (int i = 0; i < N; i++)
			if (rec[i] == ans)
				cout << " " << name[i];
	}
	cout << endl;
}

int main () {
	while (cin >> N) {
		init();
		solve();
	}
	return 0;
}
