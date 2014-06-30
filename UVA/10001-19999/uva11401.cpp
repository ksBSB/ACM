#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;
typedef unsigned long long ll;
const int N = 1e6+5;

ll f[N];
int main () {
	int n;
	f[3] = 0;
	for (ll i = 4; i < N; i++)
		f[i] = f[i-1] + ((i-1)*(i-2)/2 - (i-1)/2)/2;

	while (scanf("%d", &n) == 1 && n >= 3) {
		printf("%llu\n", f[n]);
	}
	return 0;
}
