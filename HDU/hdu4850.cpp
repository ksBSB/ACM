#include <cstdio>
#include <cstring>
#include <set>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 26*26*26;
const int mod = 26 * 26;
const int maxl = 500005;

int maxlen;
int v[maxn+5][30], c[maxn+5];
char s[maxl];

inline int get_next (int u, int k) {
	return (u % mod) * 26 + k;
}

int find_next (int u) {
	int x = 0, ans = -1;
	for (int i = 1; i < 26; i++) {
		if (v[u][i])
			continue;

		int tmp = get_next(u, i);
		if (ans == -1 || c[tmp] < c[ans]) {
			ans = tmp;
			x = i;
		}
	}
	return x;
}

void init () {
	maxlen = maxn * 26 + 3;

	int mv, u = 0;
	memset(v, 0, sizeof(v));
	for (mv = 0; mv < 3; mv++)
		s[mv] = 'a';

	while (true) {

		int x = find_next(u);
		int next = get_next(u, x);
		if (c[next] == 26)
			break;

		c[next]++;
		s[mv++] = x + 'a';
		v[u][x] = 1;
		u = next;
	}

	/*
	for (int i = 0; i < maxn; i++) {
		bool flag = false;;
		for (int j = 0; j < 26; j++)
			if (v[i][j] == 0)
				flag = true;
		if (flag)
			printf("%d\n", i);
	}
	printf("%d %d\n", mv, maxlen);
	*/
}

int main () {
	int n;
	init();
	while (scanf("%d", &n) == 1) {
		if (n <= maxlen) {
			for (int i = 0; i < n; i++)
				printf("%c", s[i]);
			printf("\n");
		} else
			printf("Impossible\n");
	}
	return 0;
}
