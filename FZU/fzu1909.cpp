
#include <stdio.h>
#include <string.h>

bool judge(int *a, int sum) {

	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < 4; j++)
			if (sum == (a[i] + a[j]) * 2) return true;
	}
	return false;
}

int main () {

	int cas, a[4];

	scanf("%d", &cas);

	for (int i = 1; i <= cas; i++) {
		int sum = 0;
		for (int j = 0; j < 4; j++) {
			scanf("%d", &a[j]);
			sum += a[j];
		}
		printf("Case %d: %s\n", i, judge(a, sum) ? "Yes" : "No");	
	}

	return 0;
}
