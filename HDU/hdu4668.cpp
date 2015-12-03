#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e6 + 5;
const int maxm = 505;

char a[maxm], b[maxm], str[maxn];
int fail[maxm], cnt[maxn];

void get_fail(char* str) {
	int n = strlen(str+1);
	int p = fail[0] = fail[1] = 0;

	for (int i = 2; i <= n; i++) {
		while (p && str[p+1] != str[i])
			p = fail[p];

		if (str[p+1] == str[i])
			p++;
		fail[i] = p;
	}
}

ll match(char* s, char* t) {
	ll ret = 0;
	int p = 0, n = strlen(s+1), k = strlen(t+1);

	get_fail(t);

	for (int i = 1; i <= n; i++) {
		while (p && t[p+1] != s[i])
			p = fail[p];

		if (t[p+1] == s[i]) p++;

		if (p >= k) ret += cnt[i];
	}
	return ret;
}

void draw(char* str, int& p, char* a, int l, int r, int t, int c) {
	for (int ti = 0; ti < t; ti++) {
		for (int i = l; i <= r; i++) {
			cnt[p] = c;
			str[p++] = a[i];
		}
	}
}

int get_number(char* a, int n, int& p) {
	int ret = 0;
	while (p <= n && a[p] >= '0' && a[p] <= '9') {
		ret = ret * 10 + (a[p] - '0');
		p++;
	}
	return ret;
}

void init(char* str, char* odd, int k) {
	int n = strlen(odd+1), p = 1, u = 1;

	while (p <= n) {
		if (odd[p] == '[') {
			int l = p;
			while (p <= n && odd[p] != ']') p++;
			int r = p++;
			int len = r - l - 1;

			int t = get_number(odd, n, p);

			if (len == 0) continue;
			int tmp = k / len + (k % len ? 1 : 0);

			if (2 * tmp > t)
				draw(str, u, a, l+1, r-1, t, 1);
			else {
				draw(str, u, a, l+1, r-1, tmp, 1);
				draw(str, u, a, l+1, r-1, 1, t - 2 * tmp);
				draw(str, u, a, l+1, r-1, tmp, 1);
			}
		} else {
			cnt[u] = 1;
			str[u++] = odd[p++];
		}
	}
	str[u] = '\0';
	/*
	   int nn = strlen(str + 1);
	   for (int i = 1; i <= nn; i++)
	   printf("%c ", str[i]);
	   printf("\n");
	   for (int i = 1; i <= nn; i++)
	   printf("%d ", cnt[i]);
	   printf("\n");
	   */
}

int main () {
	while (scanf("%s%s", a + 1, b + 1) == 2) {
		init(str, a, strlen(b+1));
		printf("%lld\n", match(str, b));
	}
	return 0;
}
