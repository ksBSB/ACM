#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 105;

char str[maxn];

bool judge () {
	int n = strlen(str) - 1;
	int d = str[n] - '0';
	if ((d&1) == 0 || d == 5) return true;
	int s = 0;
	for (int i = 0; i <= n; i++)
		s += str[i] - '0';
	return s % 3 == 0;
}

int main () {
	while (scanf("%s", str) == 1) {
		printf("%s\n", judge() ? "YES" : "NO");
	}
	return 0;
}
