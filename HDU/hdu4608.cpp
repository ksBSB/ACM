#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5 + 5;

int N, num[maxn];
char str[maxn];

void add () {
	int s = 1;
	for (int i = 0; i < N; i++) {
		s += num[i];
		num[i] = s % 10;
		s /= 10;
	}
	while (s) {
		num[N++] = s % 10;
		s /= 10;
	}
}

bool judge () {
	int s = 0;
	for (int i = 0; i < N; i++)
		s = (s + num[i]) % 10;
	return s == 0;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%s", str);
		N = strlen(str);

		for (int i = 0; i < N; i++)
			num[N-i-1] = str[i] - '0';

		do {
			add();
		}while (!judge());

		for (int i = N-1; i >= 0; i--)
			printf("%d", num[i]);
		printf("\n");
	}
	return 0;
}
