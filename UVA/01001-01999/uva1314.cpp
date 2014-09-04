#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;

int N;
char s[maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%s", &N, s);
		
		int p = 0, i = 1;
		while (p < N && i < N) {

			int j;
			for (j = 0; j < N; j++) {
				if (s[(p+j)%N] == s[(i+j)%N])
					continue;
				break;
			}

			if (j == N)
				break;

			if (s[(p+j)%N] > s[(i+j)%N])
				p = p + j + 1;
			else
				i = i + j + 1;

			if (p == i)
				i++;
		}
		printf("%d\n", min(p, i));
	}
	return 0;
}
