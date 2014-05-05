#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

const int N = 100005;
int n, v[N], c[N];
char num[N];

void init () {
	n = 0;
	memset(v, 0, sizeof(v));
	memset(c, 0, sizeof(c));
	scanf("%s", num);

	int x = 0;
	for (int i = strlen(num) - 1; i >= 0; i--) {
		x++;
		if (num[i] != '0') {
			c[n] = x; v[n] = num[i] - '0'; 
			n++; x = 0;
		}
	}
}

int solve () {
	int ans = 1;
	int cnt = c[n-1], val = v[n-1];
	for (int i = n-2; i >= 0; i--) {
		if (cnt > c[i] || (cnt == c[i] && val >= v[i])) ans++;
		else ans = 1;
		cnt += c[i];
	}
	return ans;
}

int main () {
	init();
	printf("%d\n", solve());
	return 0;
}
