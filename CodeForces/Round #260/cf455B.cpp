#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
const int maxn = 1e5+5;

struct node {
	int val, arr[30];
	node () {
		val = 0;
		memset(arr, 0, sizeof(arr));
	}
}t[maxn*2];

int top = 1, len, n, k;
char str[maxn];

inline int get_node () {
	return top++;
}

void insert (int x, int d) {

	if (d == len)
		return;

	int mv = str[d] - 'a';
	if (t[x].arr[mv] == 0)
		t[x].arr[mv] = get_node();
	insert(t[x].arr[mv], d+1);
}

int solve (int x) {

	int& ans = t[x].val;
	ans = 0;

	bool flag = true;
	for (int i = 0; i < 26; i++) {
		if (t[x].arr[i]) {
			flag = false;
			ans |= solve(t[x].arr[i]);
		}
	}

	if (flag)
		ans = 1;
	return 3-ans;
}

int main () {
	scanf("%d%d", &n, &k);

	for (int i = 0; i < n; i++) {
		scanf("%s", str);
		len = strlen(str);
		insert(0, 0);
	}

	solve(0);
	int ans = t[0].val;
	if (ans < 2)
		printf("Second\n");
	else if (ans == 2)
		printf("%s\n", k&1 ? "First" : "Second");
	else
		printf("First\n");
	return 0;
}
