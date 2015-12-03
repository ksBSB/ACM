#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e3 + 5;

int N, S[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &N);
		for (int i = 0; i < N; i++) scanf("%d", &S[i]);
		int ans = 0;
		for (int i = 0; i < N; i++) {
			for (int j = i + 1; j < N; j++)
				for (int k = j + 1; k < N; k++) {
					ans = max(ans, S[i] ^ (S[j] + S[k]));
					ans = max(ans, S[j] ^ (S[i] + S[k]));
					ans = max(ans, S[k] ^ (S[i] + S[j]));
				}
		}
		printf("%d\n", ans);
	}
	return 0;
}
