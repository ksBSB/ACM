#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;

struct Stack {
	int n, s[maxn];
	void init() { n = 0; }
	int find (int x) { return upper_bound(s, s + n, x) - s; }
	void insert(int p, int x) {
		s[p] = x;
		n = max(n, p + 1);
	}
}S;

int N, A[maxn], dp[maxn];

bool judge () {
	S.init();
	int ans = 0;
	for (int i = 1; i <= N; i++) {
		dp[i] = S.find(A[i]);
		S.insert(dp[i], A[i]);
		ans = max(ans, dp[i] + 1);
	}
	return ans >= N-1;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++) scanf("%d", &A[i]);

		bool flag = judge();
		reverse(A + 1, A + N + 1);
		flag |= judge();
		printf("%s\n", flag ? "YES" : "NO");
	}
	return 0;
}
