#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int maxn = 1e5 + 5;

int N, K, arr[maxn], vis[maxn];

int main () {
	scanf("%d%d", &N, &K);

	int u = 1, s = 1, t = K, mv = 1;

	while (t) {
		arr[mv++] = u;
		u = u + s * t;
		s *= -1;
		t--;
	}
	arr[mv++] = u;
	for (int i = K + 2; i <= N; i++)
		arr[i] = i;
		

	for (int i = 1; i <= N; i++)
		printf("%d%c", arr[i], i == N ? '\n' : ' ');
	return 0;
}
