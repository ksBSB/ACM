#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int arr[4];

bool judge () {
	int a[4];
	memcpy(a, arr, sizeof(arr));
	sort(a, a + 4);

	for (int i = 1; i < 4; i++)
		if (a[i-1] > a[i])
			return false;

	int s = a[0] + a[3];
	if (s&1 || s != a[1] + a[2])
		return false;
	if (s / 2 != a[3] - a[0])
		return false;
	return true;
}

int main () {
	int n;
	scanf("%d", &n);
	if (n == 0)
		printf("YES\n1\n2\n2\n3\n");
	else {
		for (int i = 0; i < n; i++)
			scanf("%d", &arr[i]);

		if (n < 4) {
			int& i = arr[3];
			for (i = 1; i <= 1e6; i++) {
				if (n == 1) 
					arr[1] = arr[0], arr[2] = arr[3];
				else if (n == 2)
					arr[2] = arr[0] + arr[3] - arr[1];

				if (judge()) {
					printf("YES\n");
					for (int j = n; j < 4; j++)
						printf("%d\n", arr[j]);
					return 0;
				}
			}
			printf("NO\n");
		} else
			printf("%s\n", judge() ? "YES" : "NO");
	}
	return 0;
}
