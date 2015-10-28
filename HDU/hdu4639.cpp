#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 10086;
const int mod  = 10007;

int N, f[maxn + 5];
char str[maxn + 5];

int solve () {
	int ret = 1, c = 0;
	N = strlen(str);
	for (int i = 0; i < N; i++) {
		if (str[i] == 'h' && str[i+1] == 'e')
			c++, i++;
		else {
			ret = ret * f[c] % mod;
			c = 0;
		}
	}
	return ret * f[c] % mod;
}

int main () {
	f[0] = f[1] = 1, f[2] = 2;
	for (int i = 3; i <= maxn; i++) f[i] = (f[i-1] + f[i-2]) % mod;

	int cas;
	scanf("%d", &cas);
	for (int kcas = 1; kcas <= cas; kcas++) {
		scanf("%s", str);
		printf("Case %d: %d\n", kcas, solve());
	}
	return 0;
}
