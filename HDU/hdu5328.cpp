#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e6 + 5;

int N, A[maxn];

int solve () {
	if (N <= 2)
		return N;

	int ret = 0, c = 0;
	for (int i = 2; i < N; i++) {
		if (A[i] * 2 == A[i-1] + A[i+1])
			c++;
		else
			c = 0;
		ret = max(ret, c + 2);
	}

	c = 0;
	for (int i = 2; i < N; i++) {
		if ((ll)A[i] * A[i] == (ll)A[i-1] * A[i+1])
			c++;
		else
			c = 0;
		ret = max(ret, c + 2);
	}
	return ret;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 1; i <= N; i++)
			scanf("%d", &A[i]);
		printf("%d\n", solve());
	}
	return 0;
}
