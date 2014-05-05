#include <stdio.h>
#include <string.h>

const int N = 15;
const int d[N] = {1, 2, 3, 4, 6, 12};

char str[N];

bool judge(int u) {
	for (int i = 0; i < u; i++) {
		bool flag = true;

		for (int j = i; j < 12; j += u) if (str[j] != 'X') {
			flag = false; break;
		}

		if (flag) return true;
	}
	return false;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s", str);
		int ans = 0, v[N];
		memset(v, 0, sizeof(v));

		for (int i = 0; i < 6; i++) if (judge(12/d[i])) {
			v[i] = 1;
			ans++;
		}

		printf("%d", ans);
		for (int i = 0; i < 6; i++) if (v[i]) {
			printf(" %dx%d", d[i], 12/d[i]);
		}
		printf("\n");
	}
	return 0;
}
