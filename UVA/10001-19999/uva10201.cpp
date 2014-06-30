#include <stdio.h>
#include <string.h>
const int N = 105;
const int M = 205;
const int MAX = 1 << 30;
int min(int a, int b) { return a > b ? b : a; }

struct star {
	int dis;
	int val;
}s[N];
int n, ans, lenth, dp[N][M];
char str[N];

void read() {
	n = 1;
	memset(s, 0, sizeof(s));

	int a, b;
	gets(str);
	sscanf(str, "%d", &lenth);
	while (gets(str) != NULL) {

		if(str[0] == '\0')  
			break;  

		sscanf(str, "%d%d", &a, &b);
		if (a > lenth) continue;
		s[n].dis = a;
		s[n].val = b;
		n++;
	}
}

bool solve() {
	memset(dp, -1, sizeof(dp));
	int top =  100, l;
	s[0].dis = 0;
	for (int i = 0; i <= 100; i++)
		dp[0][i] = 0;
	for (int i = 101; i <= 200; i++)
		dp[0][i] = MAX;

	for (int i = 1; i < n; i++) {
		l = s[i].dis - s[i - 1].dis;
		if (l > top) return false;
		else dp[i][0] = dp[i - 1][l];

		for (int j = 1; j <= 200; j++) {
			dp[i][j] = dp[i][j - 1] + s[i].val;
			if (l + j > top) continue;
			dp[i][j] = min(dp[i][j], dp[i - 1][l + j]); 
		}
		top = 200;
	}

	l = lenth - s[n - 1].dis;
	if (l > top) return false;
	else dp[n][0] = dp[n - 1][l];
	for (int i = 1; i <= 100; i++) {
		if (i + l > top) return false;
		dp[n][i] = dp[n - 1][i + l];
	}
	ans = dp[n][100];
	return true;
}

int main(){
	int cas;
	gets(str);
	sscanf(str, "%d", &cas);
	gets(str);
	while (cas--) {
		read();
		if (solve())
			printf("%d\n", ans);
		else
			printf("Impossible\n");
		if (cas) printf("\n");
	}
	return 0;
}
