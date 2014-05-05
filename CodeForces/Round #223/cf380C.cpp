#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;
const int N = 1000005;

struct node {
	int dl, dr, v;
}s[N*3];

int n, r[N], l[N], len;
char str[N];

int build (int x, int y, int f) {
	s[f].dl = x, s[f].dr = y;

	if (x == y) return s[f].v = l[x];

	int mid = (x + y) / 2;
	return s[f].v = min(build(x, mid, 2 * f), build(mid+1, y, 2*f+1));
}

int query(int x, int y, int f) {
	if (x == s[f].dl && y == s[f].dr) return s[f].v;

	int mid = (s[f].dl + s[f].dr) / 2;
	if (mid >= x && mid < y) return min(query(x, mid, 2*f), query(mid+1, y, 2*f+1));
	else if (mid >= x && mid >= y) return query(x, y, 2*f);
	else return query(x, y, 2*f+1);
}

void solve () {
	memset(r, 0, sizeof(r));
	memset(l, 0, sizeof(l));
	len = strlen(str);
	int tmp = 0;
	for (int i = 1; i <= len; i++) {
		r[i] = r[i-1];

		if (str[i-1] == '(') tmp++;
		else if (tmp) {
			r[i]++; tmp--;
		}
		l[i] = tmp;
	}
	build(1, len, 1);
}

int main () {
	gets(str);
	solve ();

	int a, b;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d%d", &a, &b);
		a = min(len, a); b = min(len, b);
		printf("%d\n", (r[b] - r[a-1] - max(l[a-1] - query(a, b, 1), 0)) * 2);
	}
	return 0;
}
