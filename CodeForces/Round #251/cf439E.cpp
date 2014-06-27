#include <cstdio>
#include <cstring>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

const int N = 1e5+5;
const int MOD = 1e9+7;

vector<int> vec;
int fact[N], ive_fact[N];

int power (int x, int n) {
	int ans = 1;

	while (n) {
		if (n&1)
			ans = (1ll * ans * x) % MOD;

		n /= 2;
		x = (1ll * x * x) % MOD;
	}
	return ans;
}

void init () {
	fact[0] = 1;
	for (int i = 1; i < N; i++)
		fact[i] = (1ll * fact[i-1] * i) % MOD;

	for (int i = 0; i < N; i++)
		ive_fact[i] = power(fact[i], MOD-2);
}

void divFactor(int cur) {  

	vec.clear();
	int tmp = sqrt(cur+0.5);  
	for (int i = 2; i <= tmp; i++) {  
		if (cur % i == 0) {
			vec.push_back(i);
			while (cur % i == 0)
				cur /= i;  
		}
	}  

	if (cur != 1)
		vec.push_back(cur);
} 

int solve (int n,int f) {
	if (n < f)
		return 0;
	int ans = fact[n];
	ans = 1ll * ans * ive_fact[f] % MOD;
	ans = 1ll * ans * ive_fact[n-f] % MOD;
	return ans;
}

int cal (int n) {
	return (n % MOD + MOD) % MOD;
}

int main () {
	init();
	int cas;
	scanf("%d", &cas);

	while (cas--) {
		int n, f;
		scanf("%d%d", &n, &f);
		divFactor(n);

		int ans = 0, t = 1<<vec.size();
		for (int i = 0; i < t; i++) {
			int tmp = 1, sign = 1;
			for (int j = 0; j < vec.size(); j++) {
				if (i&(1<<j)) {
					sign *= -1;
					tmp *= vec[j];
				}
			}

			ans = cal(ans + sign * solve(n/tmp - 1, f - 1));
		}
		printf("%d\n", ans);
	}
	return 0;
}
