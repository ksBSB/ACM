#include <stdio.h>
#include <string.h>
#include <math.h>
const int L = 100;
const int N = 1005;
const int INF = 1 << 30;

int n, row, len[N], dp[N][N], rec[N][N];
char word[N][L], str[N];

void handle(char s[]) {
	int l = strlen(s);
	for (int i = 0; s[i]; ) {  
		sscanf(s + i, "%s", word[n]);  
		len[n] = strlen(word[n]);  
		i += len[n++];
		while (s[i] == ' ')  i++;  
	}
}

void init() {
	n = 0;
	sscanf(str, "%d", &row);
	row++;
	while (gets(str)) {
		if (!str[0]) break;
		handle(str);
	}
}

int solve(int x, int y) {
	if (dp[x][y] > -1) return dp[x][y];
	if (x == n) {
		if (y != 0) return INF;
		else return 0;
	}
	int& ans = dp[x][y];
	int& p = rec[x][y];
	int begin = y + len[x] + 1, end = row - len[x  + 1], t;
	ans = INF;
	if (!y) {
		t = solve(x + 1, 0) + 500;
		if (t < ans) {
			ans = t;
			rec[x][y] = 0;
		}
	}

	if (begin == row) {
		t = solve(x + 1, 0);
		if (t < ans) {
			ans = t;
			rec[x][y] = 0;
		}
	}
	for (int i = begin; i <= end; i++) {
		t = solve(x + 1, i) + (i - begin) * (i - begin);
		if (t < ans) {
			ans = t;
			rec[x][y] = i;
		}
	}
	return ans;
}

void put() {
	int x = 0, y = 0;
	row--;
	while (x < n) {
		for (int i = 0; i < row;) {
			if (i == y) {
				printf("%s", word[x]);
				i += len[x];
				y = rec[x][y];
				x++;
			}
			else if (i > y) break;
			else {
				printf(" ");
				i++;
			}
		}
		printf("\n");
	}
	/*
	   for (int i = 0, j = 0; i < n; i++) {
	   printf("%s", word[i]);
	   if (rec[i][j] > 0) {
	   int x = sqrt(dp[i][j]-dp[i+1][rec[i][j]]);
	   for (int k = 0; k <= x; k++)
	   printf(" ");
	   }
	   else
	   printf("\n");
	   j = rec[i][j];
	   }
	   */
}

int main () {
	while (gets(str)) {
		init();
		if (row == 1) break;
		memset(dp, -1, sizeof(dp));
		solve(0, 0);
		put();
		printf("\n");
	}
	return 0;
}
