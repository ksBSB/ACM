#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 55;

int N;
char S[maxn];
bool dp[maxn][10][10];

bool isvowel(char ch) {
	if (ch == 'A' || ch == 'E' || ch == 'I') return true;
	if (ch == 'O' || ch == 'U' || ch == '?') return true;
	return false;
}

bool isconsoa(char ch) {
	if (!isvowel(ch) || ch == '?') return true;
	return false;
}

bool judge () {
	memset(dp, false, sizeof(dp));
	dp[0][0][0] = true;
	for (int i = 1; i <= N; i++) {
		if (isvowel(S[i])) {
			dp[i][0][2] |= dp[i-1][0][1];
			for (int j = 0; j <= 4; j++)
				dp[i][0][1] |= dp[i-1][j][0];
		}
		if (isconsoa(S[i])) {
			for (int j = 4; j > 1; j--)
				dp[i][j][0] |= dp[i-1][j-1][0];

			for (int j = 0; j <= 2; j++)
			   dp[i][1][0] |= dp[i-1][0][j];	
		}
	}
	bool flag = false;
	for (int i = 0; i <= 4; i++)
		for (int j = 0; j <= 2; j++)
			flag |= dp[N][i][j];
	return flag;
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%s", S + 1);
		N = strlen(S + 1);
		bool good = judge();
		bool bad = false;
	
		for (int i = 1; i <= N && !bad; i++) {
			if (i <= N - 2 && isvowel(S[i])) {
				bool flag = true;
				for (int j = 1; j < 3; j++)
					flag &= isvowel(S[i+j]);
				bad |= flag;
			}
			if (i <= N - 4 && isconsoa(S[i])) {
				bool flag = true;
				for (int j = 1; j < 5; j++)
					flag &= isconsoa(S[i+j]);
				bad |= flag;
			}
		}

		printf("Case %d: ", kcas);
		if (bad && good)
			printf("MIXED\n");
		else if (good)
			printf("GOOD\n");
		else
			printf("BAD\n");
	}
	return 0;
}
