#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 100005;

int C[maxn];

int judge (int n) {
	int v[11];
	memset(v, 0, sizeof(v));
	while (n) {
		int t = n % 10;
		if (v[t])
			return 0;
		v[t] = 1;
		n /= 10;
	}
	return 1;
}

void preserve () {
	C[0] = 0;
	for (int i = 1; i <= 100000; i++)
		C[i] = C[i-1] + judge(i);
}

int main () {
	preserve();
	int cas, a, b;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d%d", &a, &b);
		printf("%d\n", C[b] - C[a-1]);
	}
	return 0;
}
