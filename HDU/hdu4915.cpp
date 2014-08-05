#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e6+5;

char s[maxn];
int n, l[maxn][2], r[maxn][2];

bool check (int x) {
	int ldown = l[x-1][0] + 1;
	int lup = l[x-1][1] + 1;

	if (ldown > r[x+1][1] || lup < r[x+1][0])
		return false;

	int rdown = r[x+1][0] + 1;
	int rup = r[x+1][1] + 1;

	if (rdown > l[x-1][1] || rup < l[x-1][0])
		return false;
	return true;
}

int judge () {
	n = strlen(s+1);

	if (n&1)
		return 0;

	memset(l[0], 0, sizeof(l[0]));
	memset(r[n+1], 0, sizeof(r[n+1]));

	for (int i = 1; i <= n; i++) {

		if (s[i] == '(') {
			l[i][0] = l[i-1][0] + 1;
			l[i][1] = l[i-1][1] + 1;
		} else if (s[i] == ')') {

			if (l[i-1][1] == 0)
				return 0;

			l[i][0] = (l[i-1][0] == 0 ? l[i-1][0] + 2 : l[i-1][0]) - 1;
			l[i][1] = l[i-1][1] - 1;
		} else {
			l[i][0] = (l[i-1][0] == 0 ? l[i-1][0] + 2 : l[i-1][0]) - 1;
			l[i][1] = l[i-1][1] + 1;
		}
	}

	for (int i = n; i; i--) {
		if (s[i] == ')') {
			r[i][0] = r[i+1][0] + 1;
			r[i][1] = r[i+1][1] + 1;
		} else if (s[i] == '(') {

			if (r[i+1][1] == 0)
				return 0;

			r[i][0] = (r[i+1][0] == 0 ? r[i+1][0] + 2 : r[i+1][0]) - 1;
			r[i][1] = r[i+1][1] - 1;
		} else {
			r[i][0] = (r[i+1][0] == 0 ? r[i+1][0] + 2 : r[i+1][0]) - 1;
			r[i][1] = r[i+1][1] + 1;
		}
	}

	for (int i = 1; i <= n; i++)
		if (s[i] == '?' && check(i))
			return 2;
	return 1;
}

int main () {
	while (scanf("%s", s+1) == 1) {
		int flag = judge();
		if (flag == 2)
			printf("Many\n");
		else if (flag == 1)
			printf("Unique\n");
		else
			printf("None\n");
	}
	return 0;
}
