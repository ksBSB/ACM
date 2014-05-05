#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int N = 1e6+5;

bool flag;
char str[N];
int a[20], b[20];

void init () {
	flag = false;
	memset(a, 0, sizeof(a));
	memset(b, 0, sizeof(b));

	scanf("%s", str);
	int len = strlen(str);
	for (int i = 0; i < len; i++)
		a[str[i]-'0']++;

	scanf("%s", str);
	len = strlen(str);
	for (int i = 0; i < len; i++)
		b[str[i]-'0']++;
}

void putOne () {
	for (int i = 9; i >= 0; i--) {
		for (int j = 1; j < 10; j++) {
			if (i == j) 
				continue;

			int t = ((i + 10) - j)%10;
			if (a[j] && b[t]) {
				a[j]--;
				b[t]--;

				if (i) {
					flag = true;
					printf("%d", i);
				}
				return ;
			}
		}
	}
}

void solve () {
	putOne();

	for (int i = 9; i >= 0; i--) {
		int c = 0;

		for (int j = 0; j < 10; j++) {
			int t = ((i + 10) - j)%10;

			int tmp = min(a[j], b[t]);
			a[j] -= tmp;
			b[t] -= tmp;
			c += tmp;
		}

		if (i && c)
			flag = true;

		if (i == 0 && flag == false) {
			printf("0");
			return;
		}

		for (int j = 0; j < c; j++)
			printf("%d", i);
	}
}

int main () {
	int cas;
	scanf("%d", &cas);
	for (int i = 1; i <= cas; i++) {
		init ();
		printf("Case #%d: ", i);
		solve();
		printf("\n");
	}
	return 0;
}

