#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;

int n, arr[maxn], pos[maxn];

bool judge (int l, int r) {
	for (int i = 0; i + l <= r; i++) {
		if (arr[l+i] != pos[r-i])
			return false;
	}
	return true;
}

int main () {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
		pos[i] = arr[i];
	}

	sort(pos, pos + n);
	int l = 0, r = n-1;
	while (l < n && pos[l] == arr[l]) l++;
	while (r >= 0 && pos[r] == arr[r]) r--;
	
	if (judge(l, r)) {
		if (r < l)
			l = r = 0;
		printf("yes\n%d %d\n", l+1, r+1);
	} else
		printf("no\n");
	return 0;
}
