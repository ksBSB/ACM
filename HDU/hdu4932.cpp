#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>

using namespace std;
const int maxn = 100;

int n;
double arr[maxn];

bool judge (double w) {
	double tmp = arr[0];

	for (int i = 1; i < n; i++) {
		if (fabs(arr[i] - tmp) < 1e-9 || arr[i] - tmp > w || fabs(arr[i] - tmp - w) < 1e-9)
			tmp = arr[i];
		else if (arr[i] < tmp)
			return false;
		else
			tmp = arr[i] + w;
	}
	return true;
}

int main () {
	int cas;
	scanf("%d", &cas);
	while (cas--) {
		scanf("%d", &n);
		for (int i = 0; i < n; i++)
			scanf("%lf", &arr[i]);
		sort(arr, arr + n);

		double ans = 0;
		for (int i = 1; i < n; i++) {
			if (judge (arr[i] - arr[i-1]))
				ans = max(ans, arr[i] - arr[i-1]);
			else if (judge((arr[i] - arr[i-1]) / 2))
				ans = max(ans, (arr[i] - arr[i-1]) / 2);
		}

		printf("%.3lf\n", (double)ans);
	}
	return 0;
}
