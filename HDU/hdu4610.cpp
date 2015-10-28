#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>

using namespace std;
const int maxn = 1e6;
const int maxm = 1e3 + 5;
const int mod = 1e9 + 7;
const int inf = 0x3f3f3f3f;
typedef long long ll;

int cnt[maxn+5], sum[maxn+5], vis[maxn+5], val[20];

ll pow_mod(ll x, int n, ll mod) {
	ll ret = 1;
	while (n) {
		if (n&1) ret = ret * x % mod;
		x = x * x % mod;
		n >>= 1;
	}
	return ret;
}

bool miller_rabin(int n) {
	if (n <= maxn) return vis[n];
	srand(time(0));
	for (int i = 0; i < 10; i++)
		if (pow_mod(rand() % (n-1) + 1, n-1, n) != 1)
			return false;
	return true;
}

void presolve() {
	vis[1] = 1;

	for (int i = 2; i <= maxn; i++) {
		cnt[i]++, sum[i] += i;
		for (int j = i + i; j <= maxn; j += i) {
			cnt[j]++;
			sum[j] += i;
			vis[j] = 1;
		}
	}

	for (int i = 1; i <= maxn; i++) {
		vis[i] = 1^vis[i];
		cnt[i]++, sum[i]++;
	}

	val[0] = 0;
	for (int i = 1; i < 16; i++)
		val[i] = val[i>>1] + (i&1);
}

bool judge (int s) {
	if (cnt[s]&1) {
		s = (int)sqrt(s);
		return cnt[s]&1;
	}
	return ((cnt[s]>>1)&1) == 0;
}

int N, K, C[20], extra[10];

int getstatus(int x) {
	int s = 0;
	if (vis[x]) s |= 1;
	if (vis[cnt[x]]) s |= 2;
	if (miller_rabin(sum[x])) s |= 4;
	if (judge(x)) s |= 8;
	return s;
}

void init () {
	int a, b;
	scanf("%d%d", &N, &K);
	memset(C, 0, sizeof(C));
	for (int i = 1; i <= N; i++) {
		scanf("%d%d", &a, &b);
		int s = getstatus(a);
		C[s] += b;
		printf("%d%c", val[s], i == N ? '\n' : ' ');
	}

	for (int i = 0; i < 4; i++)
		scanf("%d\n", &extra[i]);
}

int solve () {
	int ret = -inf, c[10];

	for (int i = 0; i < (1<<16); i++) {
		int n = K, s = 0, g = 0;
		memset(c, 0, sizeof(c));

		for (int j = 0; j < 16; j++) {
			if ((i&(1<<j)) == 0) continue;
			if (C[j]) {
				s |= j;
				n--;
				g += val[j];
				c[val[j]] += C[j]-1;
			} else
				n = -1;
		}

		if (n < 0) continue;

		for (int j = 4; j >= 0; j--) {
			int tmp = min(n, c[j]);
			g += tmp * j;
			n -= tmp;
		}

		if (n) continue;

		for (int j = 0; j < 4; j++) {
			if ((s&(1<<j)) == 0)
				g += extra[j];
		}
		ret = max(ret, g);
	}
	return ret;
}

int main () {
	presolve();

	int cas;
	scanf("%d", &cas);
	while (cas--) {
		init();
		printf("%d\n", solve());
	}
	return 0;
}
