#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int N = 10;
char str[N];
int dp[N][3*N];

int solve () {
	int len = strlen(str);

	if (len == 1)
		return str[0] - 'a' + 1;;
	
	for (int i = 1; i < len; i++)
		if (str[i] <= str[i-1])
			return 0;

	int pre = str[0] - 'a' + 2;
	memset(dp, 0, sizeof(dp));

	for (int i = 0; i + 'a' <= str[0]; i++)
		dp[1][i] = 1;

	for (int i = 1; i < len; i++) {

		for (int j = 0; j <= 26; j++) {
			for (int k = j+1; k <= 26; k++)
				dp[i+1][k] += dp[i][j];
		}

		for (int j = pre; j + 'a' <= str[i]; j++)
			dp[i+1][j]++;
		pre = str[i] - 'a' + 2;
		dp[i+1][0]++;
	}

	int ans = 1;
	for (int i = 1; i <= 26; i++)
		ans += dp[len][i];
	return ans;
}

int main () {
	while (scanf("%s", str) == 1) {
		printf("%d\n", solve());
	}
	return 0;
}
