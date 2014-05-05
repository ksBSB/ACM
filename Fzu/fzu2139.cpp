#include <stdio.h>
#include <algorithm>

using namespace std;

int n, num[5], sum;

int solve() {
	sum -= 2 * n;
	if (sum < 0) sum = 0;

	int ans = sum / 3 + (sum % 3 ? 1 : 0);

	if (ans > num[0])	sum -= num[0];
	else return ans;

	ans = sum / 2 + sum % 2;
	if (ans > num[1]) return sum - num[1];
	else return ans;
}

int main() {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		sum = 0;

		scanf("%d", &n);
		for (int i = 0; i < 5; i++) {
			scanf("%d", &num[i]);
			sum += num[i];
		}
		sort(num, num + 5);

		printf("%d\n",  solve());
	}
	return 0;
}
