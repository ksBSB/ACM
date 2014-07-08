#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100;

int n, m;
char s[maxn+5][maxn+5];

int main () {

	scanf("%d%d", &n, &m);
	for (int i = 0; i < n; i++)
		scanf("%s", s[i]);

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++)
			if (s[i][j] == '.') {
				printf("%c", (i+j)%2 ? 'W' : 'B');
			} else
				printf("%c", s[i][j]);
		printf("\n");
	}
	return 0;
}
