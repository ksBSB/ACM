#include <stdio.h>
#include <string.h>

const int N = 1005;

int m;
char num[N];

void swap(char& a, char& b) {
	char c = a;
	a = b;
	b = c;
}

void solve() {
	int len = strlen(num);

	if (m == 0) return;
	int c = num[0] - '0', id = len;
	for (int j = len - 1; j; j--)
		if (num[j] - '0' < c && num[j] != '0') {
			id = j, c = num[j] - '0';
		}

	if (c != num[0] - '0') {
		swap(num[0], num[id]), m--;
	}


	for (int i = 1; i < len; i++) {
		if (m == 0) return;

		c = num[i] - '0';
		for (int j = len - 1; j > i; j--) {
			if (num[j] - '0' < c) {
				id = j, c = num[j] - '0';
			}
		}

		if (c != num[i] - '0') {
			swap(num[i], num[id]), m--;
		}
	}
}

int main() {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s%d", num, &m);
		solve();
		printf("%s\n", num);	
	}
	return 0;
}
