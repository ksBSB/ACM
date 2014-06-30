#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 105;

char str[N], tmp[N];

int main () {
	int cas, n;

	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		scanf("%d", &n);
		scanf("%s", str);
		strcpy(tmp, str);
		sort(tmp, tmp + n);

		int ans = 0;
		for (int j = 0; j < n; j++) 
			if (str[j] != tmp[j]) ans++;
		printf("Case %d: %d\n", i, ans);

	}
	return 0;
}
