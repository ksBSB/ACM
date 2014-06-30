#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 1005;
const int M = 15;
const int dir[30][2] = { {0, 0}, {4, 0}, {8, 0}, {1, 2}, {1, 6}, {2, 0}, {2, 4}, {2, 8}, {3, 2}, {3, 6}, {4, 4}, {8, 4}, {5, 2}, {5, 6}, {6, 0}, {6, 4}, {6, 8}, {7, 2}, {7, 6}, {8, 8}, {9, 2}, {9, 6} };

int tmp, rec[M], cnt[M];
int n, s[N], x, id;
bool flag;
char ans[N];

void init() {
	char num[N];
	scanf("%s", num);
	x = strlen(num), tmp = 0;

	flag = false;
	memset(rec, 0, sizeof(rec));
	memset(ans, 0, sizeof(ans));

	for (int i = 0; i < x; i++) {
		int cur = num[i] - '0';
		tmp += cur;
		rec[cur]++;
	}
}

void put(int a[], int d, char *str) {
	int len = 0;
	for (int i = 9; i >= 0; i--) {
		for (int j = 0; j < a[i]; j++)
			str[len++] = i + '0';
	}
	
	for (int i = 0; i < 2; i++)
		str[len++] = dir[d][i] + '0';
	str[len] = '\0';
}

bool cmp(char *a, char *b) {
	for (int i = 0; a[i]; i++) {
		if (a[i] != b[i]) return a[i] < b[i];
	}
	return false;
}

void judge(int m) {

	char now[N];
	put(cnt, id, now);

	if (m < x || (cmp(ans, now) && m == x)) {
		flag = true;
		x = m;
		strcpy(ans, now);
	}
}

void dfs(int m, int d, int sum) {

	if (d >= m) {
		if ((sum - tmp) % 9 == 0)	judge(m);
		return;
	}

	for (int i = 1; i <= 8; i++) {
		if (!cnt[i]) continue;
		cnt[i]--;
		dfs(m, d + 1, sum + i);
		cnt[i]++;
	}
}

void search(int d) {
	for (int i = 0; i < 2; i++) {
		cnt[dir[d][i]]--;
		if (cnt[dir[d][i]] < 0) return;
	}

	id = d;
	for (int i = 0; i <= tmp && i <= x; i++)
		dfs(i, 0, 0);
}

bool isOK(char *str) {
	int sum = 0, len = strlen(str);
	if (len == 0 && rec[0] == 0) return false;
	for (int i = 0; i < len; i++)
		sum += str[i] - '0';
	return !sum;
}

void solve() {

	for (int i = 0; i < 22; i++) {
		memcpy(cnt, rec, sizeof(rec));
		search(i);
	}

	if (isOK(ans)) printf("0\n");
	else if (flag) puts(ans);
	else printf("impossible\n");
}

int main() {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {

		init();
		printf("Case %d: ", i);

		solve();
	}
	return 0;
}
