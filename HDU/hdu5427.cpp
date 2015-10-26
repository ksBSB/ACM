#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
const int maxn = 205;
typedef pair<int,int> pii;

int N;
pii G[maxn];
char name[maxn][maxn];

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%*c", &N);
		for (int i = 0; i < N; i++) {
			gets(name[i]);
			int n = strlen(name[i]);
			int& u = G[i].first;
			u = 0;
			for (int j = 4; j; j--) {
				u = u * 10 + name[i][n-j] - '0';
			}
			G[i].second = i;
			name[i][n-5] = '\0';
		}
		sort(G, G + N);
		for (int i = N-1; i >= 0; i--)
			printf("%s\n", name[G[i].second]);
	}
	return 0;
}
