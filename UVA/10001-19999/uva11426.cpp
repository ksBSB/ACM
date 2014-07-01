#include <cstdio>
#include <cstring>

const int N = 4000000;
typedef long long ll;

int phi[N+5];
ll s[N+5], f[N+5];

void phi_table(int n) {
	for (int i = 2; i <= n; i++)
		phi[i] = 0;
	phi[1] = 1;

	for (int i = 2; i <= n; i++) {
		if (!phi[i]) {
			for (int j = i; j <= n; j += i) {
				if (!phi[j])
					phi[j] = j;
				phi[j] = phi[j] / i * (i-1);
			}
		}
	}
}

int main () {
	phi_table(N);

	memset(f, 0, sizeof(f));
	for (int i = 1; i <= N; i++) {
		for (int j = i * 2; j <= N; j += i) {
			f[j] += i * phi[j/i];
		}
	}
	s[2] = f[2];
	for (int i = 3; i <= N; i++)
		s[i] = s[i-1] + f[i];
	int n;
	while (scanf("%d", &n) == 1 && n) {
		printf("%lld\n", s[n]);
	}
	return 0;
}
