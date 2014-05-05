#include <stdio.h>
#include <string.h>
#define min(a,b) (a)<(b)?(a):(b)
const int S = 10;
const int N = 105;
const int M = 25;
const int T = 8000;

struct teacher {
	int val;
	int cnt;
	int cas[S];
	teacher () {
		val = 0;
		cnt = 0;
		memset(cas, 0, sizeof(cas));
	}
}work[M], app[N];;
int s, n, m, dp[T]; 
int begin, end;

teacher read() {
	teacher now;
	char str[N];
	gets(str);
	int len = strlen(str), sum = 0;
	for (int i = 0; i <= len; i++) {
		if (str[i] >= '0' && str[i] <= '9')
			sum = sum * 10 + str[i] - '0';
		else {
			now.cas[now.cnt++] = sum;
			sum = 0;
		}
	}
	now.val = now.cas[0];
	return now;
}

void init() {
	memset(work, 0, sizeof(work));
	memset(app, 0, sizeof(app));
	for (int i = 0; i < m; i++) 
		work[i] = read();
	for (int i = 0; i < n; i++)
		app[i] = read();
}

int hash(int rec[]) {
	int sum = 0;
	for (int i = 1; i <= s; i++) {
		if (rec[i] > 2) rec[i] = 2;
		sum = sum * 3 + rec[i];
	}
	return sum;
}

void change(int rec[], int cur) {
	memset(rec, 0, sizeof(rec));
	for (int i = s; i > 0; i--) {
		rec[i] = cur % 3;
		cur /= 3;
	}
}

int handle() {
	int rec[S], sum = 0;
	memset(rec, 0, sizeof(rec));
	memset(dp, -1, sizeof(dp));
	for (int i = 0; i < m; i++) {
		sum += work[i].val;
		for (int j = 1; j < work[i].cnt; j++)
			rec[work[i].cas[j]]++;
	}
	begin = hash(rec);
	for (int i = 1; i <= s; i++)
		rec[i] = 2;
	end = hash(rec);
	return sum;
}

int solve() {
	int rec[S];
	int sum = handle();
	dp[begin] = sum;
	for (int i = 0; i < n; i++) {
		for (int j = end; j >= begin; j--) {
			if (dp[j] >= 0) {
				change(rec, j);
				for (int k = 1; k < app[i].cnt; k++)
					rec[app[i].cas[k]]++;
				int t = hash(rec);
				if (dp[t] == -1)
					dp[t] = dp[j] + app[i].val;
				else
					dp[t] = min(dp[t], dp[j] + app[i].val);
			}
		}
	}
	return dp[end];
}

int main() {
	while (scanf("%d%d%d", &s, &m, &n), s || n || m) {
		char str[N];
		gets(str);
		init();
		printf("%d\n", solve());
	}
	return 0;
}
