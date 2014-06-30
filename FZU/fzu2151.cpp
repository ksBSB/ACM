#include <stdio.h>
#include <string.h>

const int N = 105;
const char sign[2][N] = {"Fat brother", "Maze"};

int main () {
	int cas, l, r;
	char str[N];
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		int ans = 0;
		scanf("%d%d", &r, &l);
		for (int j = 0; j < r; j++) {
			scanf("%s", str);
			for (int k = 0; k < l; k++) if (str[k] == 'O') ans++;
		}	
		printf("Case %d: %s\n", i, sign[ans % 2]);

	}
	return 0;
}
