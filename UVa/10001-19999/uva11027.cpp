#include <stdio.h>
#include <string.h>
const int N = 50;

long long tmp[N];
long long n, c[N];

void init() {
	tmp[0] = 1;
	for (long long i = 1; i <= 15; i++)
		tmp[i] = tmp[i - 1] * i;
}

long long count(int t) {
	long long sum = 1;
	for (int i = 0; i < 26; i++)
		sum *= tmp[c[i]];
	return tmp[t] / sum;
}

void solve() {
	int cnt = 0, sum = 0, a = 0;
	char ans[N], ch = '\0';
	for (int i = 0; i < 26; i++) {
		if (c[i] % 2) {
			ch = 'a' + i;
			cnt++;
		}
		sum += c[i] /= 2;
	}

	if (cnt > 1 || count(sum) < n) {
		printf("XXX\n");
		return ;
	}

	bool flag = false;
	while (sum != a) {
		for (int i = 0; i < 26; i++) {

			if (c[i]) {
				c[i]--;
				long long k = count(sum - a - 1);
				c[i]++;
				if (n <= k) {
					ans[a++] = 'a' + i;
					c[i]--;
					break;
				} else {
					n -= k;
				}
			}
		}
	}

	for (int i = 0; i < a; i++)
		printf("%c", ans[i]);
	if (ch != '\0') printf("%c", ch);
	for (int i = a - 1; i >= 0; i--)
		printf("%c", ans[i]);
	printf("\n");
}

int main () {
	init();
	int cas, t = 1;
	char str[N];
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s %lld", str, &n);
		int len = strlen(str);
		memset(c, 0, sizeof(c));
		for (int i = 0; i < len; i++)
			c[str[i] - 'a']++;
		printf("Case %d: ", t++);
		solve();	
	}
	return 0;
}
