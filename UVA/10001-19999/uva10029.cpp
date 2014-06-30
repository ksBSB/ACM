#include <stdio.h>
#include <string.h>
#define max(a, b) (a) > (b) ? (a) :(b)

const int N = 25005;
const int M = 20;

int n = 0, dp[N], ans = 1;
char word[N][M];

void add(char *a, char *s, char ch, int in) {
	int i;
	for (i = 0; i < in; i++)
		s[i] = a[i];
	s[in] = ch;
	for ( ; a[i]; i++)
		s[i + 1] = a[i];
	s[i + 1] = '\0';
}

void del (char *a, char *s, int in) {
	int i;
	for (i = 0; i < in; i++)
		s[i] = a[i];
	for (i++; a[i]; i++)
		s[i - 1] = a[i];
	s[i - 1] = '\0';
}

void change(char *a, char *s, char ch, int in) {
	int i;
	for (i = 0; a[i]; i++)
		s[i] = a[i];
    s[in] = ch;
	s[i] = '\0';
}

void handle(char *now, char *s, char ch, int t, int flag) {
	if (flag == 0) change(now, s, ch, t);
	else if (flag == 1) del(now, s, t);
	else add(now, s, ch, t);
}

int search(char *s, int r) {
	r--;
	int l = 0, mid;
	while (l <= r) {
		mid = (l + r) / 2;
		int flag = strcmp(word[mid], s);
		if (flag == 0) return mid;
		else if (flag < 0) l = mid + 1;
		else r = mid - 1;
	}
	return -1;
}

int main() {
	char str[M];
	while (scanf("%s", word[n]) == 1) n++;

	for (int i = 0; i < n; i++) {
		dp[i] = 1;
		for (int k = 0; k < 3; k++) {
			for (int j = 0; word[i][j]; j++) {
				for (int t = 0; t < 26; t++) {
					handle(word[i], str, 'a' + t, j, k);
					if (strcmp(word[i], str) < 0) break;
					int f = search(str, i);
					if (f >= 0)	dp[i] = max(dp[i], dp[f] + 1);
				}
			}
		}
		ans = max(ans, dp[i]);
	}
	printf("%d\n", ans);
	return 0;
}
