#include <stdio.h>
#include <string.h>
#include <string>
#include <iostream>

using namespace std;
const int N = 1005;
struct state {
	string ans;
	int val;
	bool operator >(const state& a) {
		if (this->val != a.val) return this->val > a.val;
		return this->ans < a.ans;
	}
} dp[N][N];

char str[N];

int main () {
	while (scanf("%s", str+1) == 1) {
		int n = strlen(str+1);
		for (int i = n; i >= 1; i--) {
			dp[i][i].val = 1;
			dp[i][i].ans = str[i];
			for (int j = i+1; j <= n; j++) {
				if (str[i] == str[j]) {
					dp[i][j].val = dp[i+1][j-1].val + 2;
					dp[i][j].ans = str[i] + dp[i+1][j-1].ans + str[j];
				} else {
					if (dp[i+1][j] > dp[i][j-1]) {
						dp[i][j].val = dp[i+1][j].val;
						dp[i][j].ans = dp[i+1][j].ans;
					} else {
						dp[i][j].val = dp[i][j-1].val;
						dp[i][j].ans = dp[i][j-1].ans;
					}
				}
			}
		}
		cout << dp[1][n].ans << endl;
	}
	return 0;
}
